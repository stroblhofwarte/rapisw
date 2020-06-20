# rapisw
RapiSW is a small open HW/SW project. This project use a Raspberry pi 3 and a PCB providing two interfaces for stepper based focuser, a RS232 port (without blocking a USB port) and two USB connectors to power two dew schields.
This board runs with 12V and piggyback the raspberry pi baord. A simple and cheap pre-build DC converter is used for the +5V/5amp for Pi and dew caps. The stepper motors are driven by two DRV8834.
The rapsberry pi could be setup with Astroberry.

State: Board is in production. Nothing tested yet.

# Thanks to:
This driver was inspired by the work of Radek Kaczorek (https://github.com/rkaczorek/astroberry-diy). 

# Build:

```
sudo apt-get install cmake libindi-dev libgpiod-dev

git clone https://github.com/stroblhofwarte/rapisw.git

cd rapisw
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
sudo make install

```
Driver shows up in Astroberry as "RapiSW" under Focuser section.


