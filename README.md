# drone-ttgo

This project is a beacon for drones in France. The French government [mandates](https://www.legifrance.gouv.fr/jorf/id/JORFTEXT000039685188?r=bcL84O7NcL)
that each drone broadcasts its position and home position via an 802.11 beacon 
frame using a custom extension. This clearly makes most existing drones illegal.

There are several beacons for sale that broadcast the required information. However,
I discovered an [open source project](https://www.helicomicro.com/2020/05/26/une-solution-open-source-pour-le-signalement-electronique-a-distance-a-moins-de-40-e/) that used a [Liligo TTGO T-Beam board][1] that
contains an ESP32 with Wifi and a GPS chip.(it also contains a LORA chip.) This project was
written by [Pierre Kancir](https://www.malt.fr/profile/pierrekancir).

The code was, however, not  structured in the way I like it and it was not easy to see what was
going on. It also took some time to get started because it used platform.io and
Arduino. I threfore rewrote the project and threw away a lot of unnecesary code.
It now also only uses Arduino, there are no other dependencies.

## Arduino

You should place the drone-ttgo folder in your Arduino folder. On the mac this is
~/Documents/Arduino. Then clock on the drone-ttgo.ino file. This should open
your Arduino IDE. You can import the library folders via the IDE (Sketch/Include Library, 
although it says ZIP, you can also choose folders.) Do this for all folders in the libraries
folder. A shortcut is to copy these folders directly to ~/Arduino/libraries.

## Board

To install the Liligo T-Beam board in Arduino see [here](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md)

## Code

All the code is now in a single file. Since this is legal stuff, I've translated the law and
put the articles next to the code implementing it.

One of the problems was the lack of information about the 802.11 standard since it is
very expensive. I've tried to document my finding as good as possiible.

## Testing

### Macos

My primary testing took place with the MacOS sniffer. If you click on the Wifi icon in the top bar
while pressing the option key you get an extra large menu with lots of wifi info. You can then
`Open Wireless Diagnostics`. In the top menu, you can then open 'Sniffer'. This tool
can be used to _sniff_ channel 6. The output is stored in /var/tmp after you stopped. These
files can be viewed in [Wireshark](https://www.wireshark.org/). Theoretically it should be possible
to directly sniff in Wireshark but I've not been able to get there.

## Extra

Since listening is not trivial due to security problems on MacOS, the code also broadcasts a copy
of the payload over UDP to port 2000. This might disappear at one point.

## License

The code is licensed GPL. Whatever.

## Contributions

If you want to contribute ... send a [PR](https://github.com/pkriens/drone-ttgo/pulls).

[1]: https://www.amazon.fr/DollaTek-T-Beam-Bluetooth-Support-Batterie/dp/B07RT9FKPL/ref=sr_1_2?__mk_fr_FR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dchild=1&keywords=lilygo+ttgo+t-beam&qid=1600706134&sr=8-2
