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
1. Using a charing and discharging current for a capacitor
2. Motor Driver IC TA7219P
3. Using relays
4. Combination of a capacitor and relays for multiple turnouts
5. Combination of TA7219P and relays for multiple turnouts

## Hardware
### DCC Accesary Decoder
DCC Accesary Decoder consits of an analog cirtuit portion to downconvert 12V~18V DC of DCC siangl to 5V DC so that Arduino can handle the siangl, and decoder made by Ardhino.
The analog circuit portion is made with octocuppler IC 6N137, and the recommended circuit is described in DCCInspector-EX section of DCC-EX project page [^2] and Fun with Arduino 29 DCC Accessory Decoder [^3].
The decoder portion is included in Arduino sketch in in the Turnout Controller. Please see Turnout Contoller next.

### Turnout Controller

## Reference
[^1]: Kato Power Pack: 
https://www.katousa.com/onlineshop/index.php?main_page=product_info&cPath=164&products_id=2132&zenid=81443cc49b92c96d755dbbbbe64d14cc)https://www.katousa.com/onlineshop/index.php?main_page=product_info&cPath=164&products_id=2132&zenid=81443cc49b92c96d755dbbbbe64d14cc

[^2]: DCC-EX Inspector
https://github.com/DCC-EX/DCCInspector-EX

[^3]: Fun with Arduino 29 DCC Accessory Decoder
https://rudysarduinoprojects.wordpress.com/2019/05/06/fun-with-arduino-29-dcc-accessory-decoder/
