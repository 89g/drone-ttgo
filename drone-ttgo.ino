/**
 * The first 3 characters require permission from the french
 * government. aQute SARL has requested AQU (in progress). 
 * 
 * aQute SARL also has code 1642 for the ANSI code.
 * 
 * This is a template, the Wifi MAC code is used as serial number
 * and inserted at the end in runtime as hex.
 */
const char* DRONE_MANUFACTURER_ID = "AQUTEG000000000000000000000000";


#define T_BEAM_V10      //same v1.1 version
#define ENABLE_GPS

#include "board_def.h"

#include <cstdint>
#include <string.h>
#include <WiFi.h>
#include <axp20x.h>
#include <WiFiUdp.h>


extern "C" {
#include "esp_wifi.h"
esp_err_t esp_wifi_80211_tx(wifi_interface_t ifx, const void *buffer, int len, bool en_sys_seq);
}

class Frame {
public:
  uint8_t    buffer[256];
  int       in = 0;

  void put08( int8_t value ) {
    buffer[in++]=value;    
  }

  void set08( int p, int8_t value ) {
    buffer[p]=value;    
  }

  void put16( int16_t value ) {
    buffer[in++]=0xFF & (value>>0);    
    buffer[in++]=0xFF & (value>>8);    
  }

  void put32( int32_t value ) {
    buffer[in++]=0xFF & (value >>  0);    
    buffer[in++]=0xFF & (value >>  8);    
    buffer[in++]=0xFF & (value >> 16);    
    buffer[in++]=0xFF & (value >> 24);    
  }

  void put48( int64_t value ) {
    buffer[in++]=0xFF & (value >>  0);    
    buffer[in++]=0xFF & (value >>  8);    
    buffer[in++]=0xFF & (value >> 16);    
    buffer[in++]=0xFF & (value >> 24);    
    buffer[in++]=0xFF & (value >> 32);    
    buffer[in++]=0xFF & (value >> 40);    
  }

  void put64( int64_t value ) {
    buffer[in++]=0xFF & (value >>  0);    
    buffer[in++]=0xFF & (value >>  8);    
    buffer[in++]=0xFF & (value >> 16);    
    buffer[in++]=0xFF & (value >> 24);    
    buffer[in++]=0xFF & (value >> 32);    
    buffer[in++]=0xFF & (value >> 40);    
    buffer[in++]=0xFF & (value >> 48);    
    buffer[in++]=0xFF & (value >> 56);    
  }

  void put08s( void * data, int start, int length ) {
    memcpy(&buffer[in], data+start, length);
    in += length;
  }

  int current() {
    return in;
  }

  void reset( int set) {
    in = set;
  }

  void print() {
    int row = 0;
    int col = 0;
    int rover = 0;
    
    while (rover < in) {
      switch(col) {
        case 0:
            Serial.printf("%04X", rover);

        case 16:
            Serial.printf(" ");

        default:
            Serial.printf(" %02X", 0xFF & buffer[rover]);
            col++;
            break;
            
        case 32:
            Serial.println();
            col=0;
            row++;
            break;
      }
      rover = row*32 + col;
    }
    Serial.println();
  }
};

TinyGPSPlus   gps;
boolean       debug = true;
Frame         frame;
int           marker;
AXP20X_Class  axp;
char          droneId[31];
IPAddress     remoteIP(255,255,255,255);
WiFiUDP       udp;


void setup()
{
  Serial.begin(115200);

  Wire.begin(21, 22);
  if (!axp.begin(Wire, AXP192_SLAVE_ADDRESS)) {
    Serial.println("AXP192 Begin PASS");
    axp.setPowerOutPut(AXP192_LDO2, AXP202_OFF);   // LORA
    axp.setPowerOutPut(AXP192_LDO3, AXP202_ON);   // GPS
    axp.setPowerOutPut(AXP192_DCDC2, AXP202_ON);
    axp.setPowerOutPut(AXP192_EXTEN, AXP202_ON);
    axp.setPowerOutPut(AXP192_DCDC1, AXP202_ON);
  } else {
    Serial.println("AXP192 Begin FAIL");
  }
  
  Serial1.begin(GPS_BANUD_RATE, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

  byte          mac[6];
  strcpy( droneId, DRONE_MANUFACTURER_ID);
  WiFi.macAddress(mac);
  for ( int i=0; i<6; i++) {
      sprintf( droneId+18+i*2, "%2X", mac[i]);
  }
  
  WiFi.softAP(droneId, nullptr, 6);
  Serial.println(droneId);
  
  wifi_config_t conf_current;
  esp_wifi_get_config(WIFI_IF_AP, &conf_current);
  // Change WIFI AP default beacon interval sending to 1s.
  conf_current.ap.beacon_interval = 1000;
  ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &conf_current));
  
  frame.put16( 0x0080 );                  // 0000   80 00   Control Frame (Version/Type/Subtype)
  frame.put16( 0x0000 );                  // 0002   00 00   Duration
  frame.put48( 0xffffffffffffL );         // 0004   ff ff ff ff ff ff Receiver = Broadcast
  frame.put08s( mac, 0, 6 );              // 000A   .... Transmitter
  frame.put08s( mac, 0, 6 );              // 0010   .... BSSID = repeat transmitter
  frame.put16( 0x0000 );                  // 0016   Sequence/Fragment (hardware)

  // Start of beacon frame   
  // Start of 12 bytes fixed
  
  frame.put64( 0L );                // 0x0018   Timestamp
  frame.put16( 3000 );                    // 0x0020   Interval = About 3000 ms
  frame.put16( 0b0000000000000001 );   // 0x0022   Capabilities = AP

  // TLVs

  frame.put08( 0x00 );    // EI 0 = SSID
  frame.put08( strlen(droneId) );
  frame.put08s( droneId, 0, strlen(droneId) );
  
  frame.put08( 0x03 );    // EI 3 = DS 
  frame.put08( 1 );
  frame.put08( 6 );       // channel 6

  // The signaling message takes place in the payload - vendor specific part of the 
  // 802.11 WiFi frame described in the appendix. The message corresponds to an 802.11 WiFi 
  // frame transiting over a wireless network. The following CID number is used: 6A-5C-35.

  frame.put08( 221 );     // Vendor specific
  marker = frame.current();
}

void loop()
{
    loopgps();
    beacon();
}




void beacon() {
  static TinyGPSLocation      home;
  static long                 deadline      = 0;
  
  if ( !gps.location.isValid())
      return;

  if ( !home.isValid() ) {
      home = gps.location;
      Serial.println("Marked home");
  }

  if (  deadline > millis() )
    return;
  
  Serial.println("ping");
  frame.reset(marker);
    
  frame.put08(0x00);                    // length, replace later
  
  

  //  c) The signaling message takes place in the payload - vendor specific part of the 802.11 WiFi frame described in the 
  //     appendix. The message corresponds to an 802.11 WiFi frame transiting over a wireless network. The following 
  //     CID number is used: 6A-5C-35.

  frame.put08( 0x6A );
  frame.put08( 0x5C );
  frame.put08( 0x35 );
  frame.put08( 1 ); // VS type (not explicityly mentioned in law but in Appendix III

  // 2 ° The payload format is defined as follows and respects the order set:
  //   a) The protocol version number coded on 1 byte and corresponding to type 01 of 
  //      the table of types in the appendix. For the application of the requirements 
  //      of this decree, its value is set at 1.
  
  frame.put08( 0x01 );
  frame.put08( 1 );
  frame.put08( 1 );

  //   b) The unique identifier of the aircraft without anyone on board, established in 
  //      accordance with one or the other of the two possibilities described below, the 
  //      use of standard ANSI / CTA / 2063 (physical serial number - PSN) to define the 
  //      identifier of the aircraft without anybody on board which is deemed to meet 
  //      the requirements of this order:
  //       i. either a unique identifier coded on 30 bytes and corresponding to type 02 
  //          of the table of types in the appendix, made up of the following three fields:
  //          - the constructor trigram is coded on 3 bytes;
  //          - the model of the aircraft (for an aircraft traveling without anyone on board 
  //            having an integrated electronic or digital reporting system) or the model of 
  //            the electronic or digital reporting device (for a non-integrated electronic 
  //            or digital reporting system) coded on 3 bytes;
  //          - the serial number of the aircraft (for an aircraft traveling without anyone on board having 
  //            an integrated electronic or digital reporting system) or the serial number of the 
  //            electronic or digital reporting device (for an electronic or digital reporting system 
  //            not integrated) encoded on 24 bytes. If the serial number has less than 24 characters, 
  //            0s will be added upstream of it;
  //          This unique identifier must not contain any space sign. In addition, the uniqueness of this 
  //          identifier cannot be obtained by taking into account the case sensitivity to 
  //          discriminate between two different unique identifiers.
  
  frame.put08( 0x02 );
  frame.put08( 30 );
  frame.put08s( droneId, 0, 30 );

  //      ii. or a unique identifier conforming to standard ANSI / CTA / 2063 (physical serial number - PSN) and 
  //          corresponding to type 03 of the table of types in the appendix.
  //
  //   c) The position of the aircraft without anyone on board at the time of sending the message 
  //      coded on 10 bytes, composed of the following fields:
  //      i. latitude coded on 4 bytes corresponding to type 04 of the table of types in the appendix; the information is 
  //         coded according to the calculation methods indicated in the appendix;
  
  frame.put08( 0x04 );
  frame.put08( 4 );
  frame.put32( gpsToInt(gps.location.lat()) );
  

  //      ii. longitude coded on 4 bytes corresponding to type 05 of the table of types in the appendix; 
  //          the information is coded according to the calculation methods indicated in the appendix;
  
  frame.put08( 0x05 );
  frame.put08( 4 );
  frame.put32( gpsToInt(gps.location.lng()) );
  

  //      iii. the vertical position of the aircraft traveling without a person on board, coded on 
  //           2 bytes and signed according to the calculation methods indicated in the appendix, 
  //           is expressed in meters and corresponds to one or the other of the two information below:
  //           - either its altitude above mean sea level, absolute altitude, corresponding to type 06 
  //             in the table of types given in the appendix,
  
  frame.put08( 0x06 );
  frame.put08( 2 );
  frame.put16( gps.altitude.meters() );
  
  //           - or its height in relation to its take-off point or to the position of the remote pilot 
  //             corresponding to type 07 of the table of types in the appendix.


  //    d) The position of the take-off point of the aircraft without anybody on board coded on 8 bytes, 
  //       composed of the following fields:
  //       i. latitude coded on 4 bytes corresponding to type 08 of the table of types in the appendix; 
  //          the information is coded according to the calculation methods indicated in the appendix;
  
  frame.put08( 0x08 );  
  frame.put08( 4 );
  frame.put32( gpsToInt(home.lat()) );


  //      ii. longitude coded on 4 bytes corresponding to type 09 of the table of types in the appendix; 
  //          the information is coded according to the calculation methods indicated in the appendix.

  frame.put08( 0x09 );  
  frame.put08( 4 );
  frame.put32( gpsToInt(home.lng()) );

  //    e) The horizontal ground speed coded on 1 byte corresponding to type 10 of the table of types given 
  //       in the appendix; in meters per second;
  
  frame.put08( 0x0A );
  frame.put08( 1 );
  frame.put08( gps.speed.mps() );
  
  //    f) The route coded on 2 bytes corresponding to type 11 of the table of types in the appendix; in 
  //       degrees from 0 ° to 359 °.
  
  frame.put08( 11 );
  frame.put08( 2 );
  frame.put16( gps.course.deg() );

  
  int size = frame.current() - marker;
  frame.set08( marker, size-1);

  frame.print();

  ESP_ERROR_CHECK(esp_wifi_80211_tx(WIFI_IF_AP, frame.buffer, frame.current(), true));


  // - 2 transmissions are separated by at most 3 seconds;
  // - 2 consignments are separated by no more than 30 meters.

  double periodSecs = gps.speed.mps() < 10 ? 3  : 30   / gps.speed.mps();
  deadline = millis() + periodSecs*1e3;

  udp.beginPacket(remoteIP,2000);
  udp.write(frame.buffer+marker, size);
  udp.endPacket();
};


void loopgps() {
  while (Serial1.available()) {
      gps.encode(Serial1.read());
  }
}

int32_t gpsToInt( double v ) {
  return v * 1e5;
}

void printout() {
      if ( gps.location.isUpdated() ) {
        Serial.print("Latitude  : ");
        Serial.println(gps.location.lat(), 5);
        Serial.print("Longitude : ");
        Serial.println(gps.location.lng(), 4);
        Serial.print("Satellites: ");
        Serial.println(gps.satellites.value());
        Serial.print("Altitude  : ");
        Serial.print(gps.altitude.feet() / 3.2808);
        Serial.println("M");
        Serial.print("Time      : ");
        Serial.print(gps.time.hour());
        Serial.print(":");
        Serial.print(gps.time.minute());
        Serial.print(":");
        Serial.println(gps.time.second());
        Serial.println("**********************");
      }
}
