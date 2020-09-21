---
---


I. - The electronic or digital reporting system mentioned in the first paragraph of article L. 34-9-2 and in article R. 20-29-2 of the postal and electronic communications code can be integrated or not integrated into the aircraft traveling without anyone on board.
A non-integrated electronic or digital reporting device can be used on several aircraft traveling without a person on board belonging to the same electronic reporting group listed in the appendix, of identical mass range and belonging to the same owner.
II. - The electronic or digital reporting system mentioned in the first paragraph of article L. 34-9-2 and in article R. 20-29-2 of the postal and electronic communications code is programmed during production and has no possibility of modifying its settings by a third party for the fields identified as compulsory in this decree.

Related links
Article 2

I. - The transmission of the data mentioned in article R. 20-29-2 of the postal and electronic communications code has the following characteristics:
1 ° The signaling message consists of a single wifi frame;
2 ° The signaling message is not encrypted;
3 ° The reference of the geodetic system is EPSG 4326. The coordinates are transmitted in “degrees / decimals of degrees”:


- transmitted latitudes are included in the interval [- 90 °; + 90 °]
- transmitted longitudes are included in the interval] - 180 ° (excluded); + 180 ° (included)].


4 ° The transmitted route, true route, takes geographic north as reference;
5 ° The data are transmitted in units respecting the International System:


- speed in meters per second,
- vertical position in meters.


6 ° The transmission coding system is UTF-8;
7 ° The data are transmitted using the TLV (Type Length Value) mechanism and correspond to the types defined in the table of types appended to this order.
8 ° The time base is UTC + 00/00;
9 ° The signaling message is sent from the take-off of the aircraft traveling without anyone on board until it lands and periodically according to one or other of the following two processes :


- either on any Wifi channel in the 2400 to 2483.5 MHz band and in accordance with the transmission standard for beacon frames as defined by the IEEE 802.11 (100 TU) standard, on condition that the signaling system is native to the aircraft traveling without anyone on board and is coordinated with the command and control system of the latter;
- either on Wifi channel number 6, whichever is the first of the following expired temporal or spatial terms:
- 2 transmissions are separated by at most 3 seconds;
- 2 consignments are separated by no more than 30 meters.


10 ° The transmission power of the electronic or digital signaling device mentioned in the first paragraph of article L. 34-9-2 and in article R. 20-29-2 of the postal and communications code electronic complies with the technical conditions of use of the frequency set by the regulatory authority for electronic communications and postal services in accordance with the provisions of Articles L. 33-3 , L. 36-6 and L. 42 of the Postal Code and electronic communications.
11 ° The transmission power of the electronic or digital signaling device mentioned in the first paragraph of article L. 34-9-2 and in article R.corresponds to the maximum power authorized by decision of the regulatory authority for electronic communications and stations for the 2400 to 2483.5 Mhz band.
12 ° The electronic or digital reporting device mentioned in the first paragraph of article L. 34-9-2 and in article R. 20-29-2 of the postal and electronic communications code emits the signal of omnidirectional way.
II. - The data transmission format mentioned in article R. 20-29-4 of the postal and electronic communications code complies with the following specifications:
1 ° The transmission protocol complies with the IEEE 802.11 standard [in version published on the date of publication of this order (IEEE 802.11-2016).]
a) The 802.11 Wifi frame is of type 0 (management packet) and of subtype 8;
b) The frequency band used is the Wifi band 2400 to 2483.5 Mhz. The Wifi channels used are those in force in France; the width of these channels is 20 Mhz. A channel width of 5 or 10 Mhz is allowed in the context of a transmission in accordance with the transmission standard for beacon frames as defined by the IEEE 802.11 (100 TU) standard on the condition that the modulation principle remains that of OFDM and that the division of the channel width (initially 20 Mhz) is only due to the division of the clock respectively by 4 (case of the channel width of 5 Mhz) or 2 (case of the width of 10 Mhz channel);
c) The signaling message takes place in the payload - vendor specific part of the 802.11 WiFi frame described in the appendix. The message corresponds to an 802.11 WiFi frame transiting over a wireless network. The following CID number is used: 6A-5C-35.
2 ° The payload format is defined as follows and respects the order set:
a) The protocol version number coded on 1 byte and corresponding to type 01 of the table of types in the appendix. For the application of the requirements of this decree, its value is set at 1.
b) The unique identifier of the aircraft without anyone on board, established in accordance with one or the other of the two possibilities described below, the use of standard ANSI / CTA / 2063 (physical serial number - PSN) to define the identifier of the aircraft without anybody on board which is deemed to meet the requirements of this order:
i. either a unique identifier coded on 30 bytes and corresponding to type 02 of the table of types in the appendix, made up of the following three fields:


- the constructor trigram is coded on 3 bytes;
- the model of the aircraft (for an aircraft traveling without 
  anyone on board having an integrated electronic or digital reporting 
  system) or the model of the electronic or digital reporting device (for 
  a non-integrated electronic or digital reporting system) coded on 3 bytes;
- the serial number of the aircraft (for an aircraft traveling without anyone 
  on board having an integrated electronic or digital reporting system) or the 
  serial number of the electronic or digital reporting device (for an electronic 
  or digital reporting system not integrated) encoded on 24 bytes. If the 
  serial number has less than 24 characters, 0s will be added upstream of it;


This unique identifier must not contain any space sign. In addition, the uniqueness of this identifier cannot be obtained by taking into account the case sensitivity to discriminate between two different unique identifiers.
ii. or a unique identifier conforming to standard ANSI / CTA / 2063 (physical serial number - PSN) and corresponding to type 03 of the table of types in the appendix.
c) The position of the aircraft without anyone on board at the time of sending the message coded on 10 bytes, composed of the following fields:
i. latitude coded on 4 bytes corresponding to type 04 of the table of types in the appendix; the information is coded according to the calculation methods indicated in the appendix;
ii. longitude coded on 4 bytes corresponding to type 05 of the table of types in the appendix; the information is coded according to the calculation methods indicated in the appendix;
iii. the vertical position of the aircraft traveling without a person on board, coded on 2 bytes and signed according to the calculation methods indicated in the appendix, is expressed in meters and corresponds to one or the other of the two information below:


- either its altitude above mean sea level, absolute altitude, corresponding to type 06 in the table of types given in the appendix,
- or its height in relation to its take-off point or to the position of the remote pilot corresponding to type 07 of the table of types in the appendix.


d) The position of the take-off point of the aircraft without anybody on board coded on 8 bytes, composed of the following fields:
i. latitude coded on 4 bytes corresponding to type 08 of the table of types in the appendix; the information is coded according to the calculation methods indicated in the appendix;
ii. longitude coded on 4 bytes corresponding to type 09 of the table of types in the appendix; the information is coded according to the calculation methods indicated in the appendix.
e) The horizontal ground speed coded on 1 byte corresponding to type 10 of the table of types given in the appendix; in meters per second;
f) The route coded on 2 bytes corresponding to type 11 of the table of types in the appendix; in degrees from 0 ° to 359 °.

Related links
Article 3

The manufacturer's trigram mentioned in article 3 is assigned by the minister in charge of civil aviation who ensures its uniqueness. It is obtained by each manufacturer by means of CERFA n ° 15963 * 01.

Article 4

Each manufacturer ensures the uniqueness of the electronic identifier of the aircraft or of the electronic or digital reporting device and communicates it to the owner of the aircraft traveling without anyone on board who registers it in accordance with the provisions of the article R. 114-2 of the civil aviation code.

Related links
Fold backChapter 2: Provisions relating to the light signaling device (Article 5)
Article 5

Le dispositif de signalement lumineux mentionné à l'alinéa premier de l'article L. 34-9-2 et à l'article R. 20-29-3 du code des postes et des communications électroniques respecte les spécifications suivantes :
1° L'utilisation des couleurs rouge et blanche est proscrite pour le signalement lumineux des aéronefs circulant sans personne à bord ;
2° Le feu de signalement doit être visible de nuit par un observateur au sol, jusqu'à une hauteur de vol d'au moins 150 mètres et dans un rayon au sol d'au moins 150 mètres par rapport à son aplomb.

Liens relatifs
ReplierChapitre 3 : Dispositions finales (Articles 6 à 8)
Article 6

Les dispositions du présent arrêté sont applicables en Polynésie française, à Wallis-et-Futuna, et dans les Terres australes et antarctiques françaises.

Article 7

1° Le présent arrêté entrera en vigueur 6 mois après sa publication.
2° Pour les aéronefs circulant sans personne à bord enregistrés en application de l'article L. 6111-1 du code des transports avant la date d'entrée en vigueur mentionnée au 1°, les dispositions du présent arrêté n'entrent en vigueur que 12 mois après sa publication.

Liens relatifs
Article 8

Le présent arrêté sera publié au Journal officiel de la République française.

ReplierAnnexe
Article

ANNEXES
ANNEXE I
DÉFINITION DES GROUPES DE SIGNALEMENT ÉLECTRONIQUE


Type d'aéronef
(enregistrement)  
Groupes de signalement électronique

Aérostat captif 
1

Aéromodèle de vol circulaire

Aéromodèle de vol libre

Montgolfière

Planeur, aile volante (aéronef non motorisé)  
2

Dirigeable

Parachute, parapente

Aéronef à ailes battantes

Hélicoptère,  
3

Multirotors

Paramoteur

Convertible / combiné

Autogire

Avion, aile, planeur (aéronef motorisé) 
4
ReplierAnnexe
Article

ANNEXE II
DÉFINITION DES TYPES DE TLV


Les types 0 à 200 sont réservés à l'usage exclusif de l'application du présent arrêté.


TYPE  
DESCRIPTION 
TAILLE DU CHAMP EN OCTETS

00  
Réservé à une utilisation postérieure 

01  
Version du protocole  
1

02  
Identifiant FR sur 30 caractères  
30

03  
Identifiant ANSI CTA 2063 UAS (numéro de série physique - PSN)  
Conforme à la norme visée

04  
Latitude courante aéronef (signée)  
4

05  
Longitude courante aéronef (signée) 
4

06  
Altitude courante aéronef (signée)  
2

07  
Hauteur courante aéronef (signée) 
2

08  
Latitude point de décollage (signée)  
4

09  
Longitude point de décollage (signée) 
4

10  
Vitesse horizontale 
1

11  
Route vraie 
2

12(…)200  
Réservés à une utilisation postérieure  
ReplierAnnexe
Article

ANNEXE III
PRINCIPES DE STRUCTURATION ET DE CALCUL


Bloc « Vendor specific »
Structure du bloc « vendor specific »
La structure du bloc « Vendor Specific » permettant la surcharge des trames est indiquée ci-dessous :


VS  
Taille  
OUI / CID 
VS Type 
Charge utile

1 octet 
1 octet 
3 octets  
1 octet 
N octets

0xDD  
(1) 
0x6A5C35  
0x01  

Où :


- VS : Vendor Specific, il est défini par la norme 802.11 et prend pour valeur 221 (0xDD),
- Taille : taille totale codée sur un octet des informations contenues dans les champs OUI, VS Type et Charge utile,
- OUI / CID : Organizationally Unique Identifier ou Company ID, identifiant unique pour les organisations ou les sociétés codé sur un octet ; dans le cadre de l'application du présent arrêté, la valeur à utiliser est 0x6A5C35
- VS Type : il s'agit ici du numéro de protocole utilisé pour la transmission d'information, dans le cadre de l'application du présent arrêté, cette valeur est fixée à 0x01
- Charge utile : espace permettant de transmettre les informations nécessaires, elle est présentée ci-dessous. Par définition, la longueur de cet espace ne peut pas excéder une taille de 251 octets (taille maximale - 4).


Charge utile
La structure de la charge utile dépend du protocole (VS type) spécifié. Dans le cas du protocole de localisation des UAS, la charge utile se compose de sous parties adoptant le format TLV (type - longueur - valeur). Ainsi, la structure de la charge utile est de la forme suivante :


T1  
L1  
Valeur1 
… 
… 
… 
Tn  
Ln  
Valeurn

1 octet 
1 octet 
X octet(s)        
1 octet 
1 octet 
Y octet(s)

Où :


- les types sont définis par l'arrêté
- les longueurs représentent les tailles en octets de leurs valeurs respectives
- les valeurs sont les données transmises.


Méthodes de calcul :
La signature des nombres
Les nombres positifs sont transmis selon la méthode de calcul classique.
Les informations négatives doivent être transmises selon la méthode du « complément à 2 » (inversion des bits + 1). Le bit de poids fort porte la valeur -2n (exemple : codage sur 8 bits -27).
A titre d'exemple :


Codage sur :  
Valeur (base 10)  
Valeur (base 2) 
Valeur (base 16)

1 octet
(de -128 à 127) 
-128  
1000 0000 
0x80

-127  
1000 0001 
0x81

-1  
1111 1111 
0xFF

1 
0000 0001 
0x01

127 
0111 1111 
0x7F

128 
Ne peut pas être codé sur 1 octet

2 octets
(de -32768 à 32767) 
-128  
1111 1111 1000 0000 
0xFF 80

-127  
1111 1111 1000 0001 
0xFF 81

-1  
1111 1111 1111 1111 
0xFF FF

1 
0000 0000 0000 0001 
0x00 01

128 
0000 0000 1000 000  
0x00 80

32767 
0111 1111 1111 1111 
0x7F FF

Les coordonnées GPS
Les coordonnées GPS admettent une précision fixe à 5 décimales. Ainsi, la donnée à transmettre correspond à la donnée fournie par le système multipliée par 105. Cette information est ensuite encodée sur 4 octets selon la méthode précisée ci-avant.
A titre d'exemple :


Mesure  
Conversion  
Encodage

48,15278  
4815278 
0x00 49 79 AE

179,12345 
17912345  
0x01 11 52 19

-179,12345  
-17912345 
0xFE EE AD E7

-48,15278 
-4815278  
0xFF B6 86 52

Fait le 27 décembre 2019.


La ministre de la transition écologique et solidaire,
Elisabeth Borne


Le ministre de l'intérieur,
Christophe Castaner


La ministre des outre-mer,
Annick Girardin


The Secretary of State to the Minister of Ecological and Inclusive Transition, in charge of transport,
Jean-Baptiste Djebbari


The Secretary of State to the Minister of the Economy and Finance,
Agnès Pannier-Runacher

Extract from the authenticated electronic Official Journal
PDF - 262.1 KB
Return to the top of the page
Order of 27 December 2019 defining the technical characteristics of electronic and light signaling devices for aircraft traveling without personnel ...
← Back to OJ Summary
‹ Previous text
Next text ›
About this version Legal Notice privacy policy Sitemap Open data and API Accessibility: partially compliant
service-public.fr data.gouv.fr Digital Labor Code government.fr france.fr
Your opinion
*/
