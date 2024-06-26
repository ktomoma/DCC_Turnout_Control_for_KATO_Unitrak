# DCC_Turnout_Control_for_KATO_Unitrak
## Introduction
This page introduces several methods of controlling KATO Unitrack turnouts via DCC.
My prototype models introruced here are consist of
* JMRI
* DCC Accessory Decoder
* Turnout Controller made with Arduino
* Relays
* 12V DC power source to drive turnouts

## Turnout Control by KATO Unitrak Power Pack
First, let's take a look at the signal waveform that KATO Unitrak Power Pack [^1] is controling Unitrack Turnouts.
The Unitrak Power Pack has a connector on the side to connect Turnout switches as seen in the below picture.

<img src="https://github.com/ktomoma/DCC_Turnout_Control_for_KATO_Unitrak/assets/131932595/ceae95d0-d266-4a1e-84e9-1a6f170ed1ce" width="480">

Signal waveform of the turnout solinoid drive.

The signal is a half of sign wave taken from AC current by a diode. The length is around 50 ms to 80 ms which is the duration when a mechanical momentum switch closes the circuit. 

Thrown to Close

<img src="https://github.com/ktomoma/DCC_Turnout_Control_for_KATO_Unitrak/assets/131932595/563ba333-87cf-4418-a241-f7bf4a76cd5f" width="320">

Close to Thrown

<img src="https://github.com/ktomoma/DCC_Turnout_Control_for_KATO_Unitrak/assets/131932595/c4e7edc8-fbc7-4707-a752-79139fe73953" width="320">

Because the load controled by the driver siangl is a solenoid in the turnout, it is not necessary the signal to be a sin wave or the duration is exactly same as what KATO Power Pack provies.
DCC Turnout Controller in my prototypes generate the signals with similar voltage for simialr period with several differnt method.

Also KATO introduced the compatibility of their UNITRAK product with DCC here.
* https://katousa.com/using-unitrack-with-dcc/

## Methods to control a turnout
There are several possible approach to generate 12V signal to operate the solenoid in the Kato Unitrack turnout.
The proposed circuit is describef in Turnout Controller HW section.

Type 1. Using a charing and discharging current for a capacitor

Type 2. Motor Driver IC TA7219P

Type 3. Combination of TA7219P and relays for multiple turnouts

## Hardware
### DCC Accesary Decoder
DCC Accesary Decoder consits of an analog cirtuit portion to downconvert 12V~18V DC of DCC siangl to 5V DC so that Arduino can handle the siangl, and decoder made by Ardhino.
The analog circuit portion is made with octocuppler IC 6N137, and the recommended circuit is described in DCCInspector-EX section of DCC-EX project page [^2] and Fun with Arduino 29 DCC Accessory Decoder [^3].
The decoder portion is included in Arduino sketch in in the Turnout Controller. Please see Turnout Contoller next.

### Turnout Controller HW
#### Type 1.

Type 1 uses a momentary DC current that is generated when charging a capacitor and discharging it.

Digital Out in Arduino with HIGH/LOW control the relay module to switch the circuit to the capacitor. The DC current is generated when the pinout is changed from HIGH to LOW, from LOW to HIGH.

<img src="https://github.com/ktomoma/DCC_Turnout_Control_for_KATO_Unitrak/assets/131932595/c26ea17c-5443-4fb6-9071-999ae2f11de1" width="480">

#### Type 2.

Type 2 uses Motor Driver IC TA8219P. TA8219 has 2 inputs/outputs and the voltage of the output is equal to the voltage at the reference input at pin 4. 12V DC is induced to Pin 4 of TA8219P, and output at Pin 2 and 10 become the putput 12V pulse signal which are in sync to pin 5 and 6.

Sketch Turnout_Control_Type2_for_Kato_Unitrack.ino sends 100 ms pulse of 12D VC to one one the output. 

<img src="https://github.com/ktomoma/DCC_Turnout_Control_for_KATO_Unitrak/assets/131932595/d525b9fb-4677-46b2-b1a8-707e32c69474" width="480">

#### Type 3.

Type 2 uses two pinout in an Arduino for one turnout. Type 3 is a design to manage multiple turnouts with less number of pinout in the Arduino. The polarity is made with two output from TA8219P Motor Driver. Then, the selection for the turnout to be controled is managed by a relay. The idea is to close just one relay and pick one turnout, and generate 12V pulse signal from TA82129P.
The required outpin in the Arduino becomes number of turnout + 2.

<img src="https://github.com/ktomoma/DCC_Turnout_Control_for_KATO_Unitrak/assets/131932595/5ec596be-5b4e-4158-a9b0-6e40f694b818" width="480">


## Reference
[^1]: Kato Power Pack: 
https://www.katousa.com/onlineshop/index.php?main_page=product_info&cPath=164&products_id=2132&zenid=81443cc49b92c96d755dbbbbe64d14cc)https://www.katousa.com/onlineshop/index.php?main_page=product_info&cPath=164&products_id=2132&zenid=81443cc49b92c96d755dbbbbe64d14cc

[^2]: DCC-EX Inspector
https://github.com/DCC-EX/DCCInspector-EX

[^3]: Fun with Arduino 29 DCC Accessory Decoder
https://rudysarduinoprojects.wordpress.com/2019/05/06/fun-with-arduino-29-dcc-accessory-decoder/
