## PCB Design Files  

* The Base ADC Board is a modular unit which houses a single ADS1194 ADC placed on a standard 64-pin breakout board. The unit can interface with 4-channel differential electrodes and a microcontroller. In case of use in a Daisy-chain, this must be the base ADC (```DAISY_IN``` grounded) as it provides the sampling clock to all other ADCs in the chain.  
* The Daisy ADC Board is a modular unit similar to the Base ADC Board, and is meant to be connected in a Daisy-chain. Breakout pins on the board facillitate the connection according to Daisy-chain specifications.  
* The Main Board is a single, large PCB which can house 6 ADS1194 ADCs (and hence has a channel count of 24). It also has provisions for a PIC32MX microcontroller, a Wi-Fi chip, an SD card holder, and an accelerometer.
