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
First, let's take a look at the signal waveform that KATO Unitrak Power Pack is controling Unitrack Turnouts.
The Unitrak Power Pack has a connector on the side to connect Turnout switches as seen in the below picture.

<img src="https://github.com/ktomoma/DCC_Turnout_Control_for_KATO_Unitrak/assets/131932595/ceae95d0-d266-4a1e-84e9-1a6f170ed1ce" width="480">

* https://www.katousa.com/onlineshop/index.php?main_page=product_info&cPath=164&products_id=2132&zenid=81443cc49b92c96d755dbbbbe64d14cc)https://www.katousa.com/onlineshop/index.php?main_page=product_info&cPath=164&products_id=2132&zenid=81443cc49b92c96d755dbbbbe64d14cc


Signal waveform of the turnout solinoid drive.

The signal is a half of sign wave taken from AC current by a diode. The length is around 50 ms to 80 ms which is the duration when a mechanical momentum switch closes the circuit. 

Thrown to Close

<img src="https://github.com/ktomoma/DCC_Turnout_Control_for_KATO_Unitrak/assets/131932595/acc10296-d4a9-430c-89dd-d6b8d84e86cd" width="320">

Close to Thrown

<img src="https://github.com/ktomoma/DCC_Turnout_Control_for_KATO_Unitrak/assets/131932595/5508c496-36ad-4099-b653-a0bd93618ae0" width="320">

Because the load controled by the driver siangl is a solenoid in the turnout, it is not necessary the signal to be a sin wave or the duration is exactly same as what KATO Power Pack provies.
DCC Turnout Controller in my prototypes generate the signals with similar voltage for simialr period with several differnt method.

Also KATO introduced the compatibility of their UNITRAK product with DCC here.
* https://katousa.com/using-unitrack-with-dcc/

## Hardware
### DCC Accesary Decoder
### Turnout Controller

## Reference
[1] Kato Power Pack: 
https://www.katousa.com/onlineshop/index.php?main_page=product_info&cPath=164&products_id=2132&zenid=81443cc49b92c96d755dbbbbe64d14cc)https://www.katousa.com/onlineshop/index.php?main_page=product_info&cPath=164&products_id=2132&zenid=81443cc49b92c96d755dbbbbe64d14cc

