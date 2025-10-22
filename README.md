<h1 align="center">5G Broadcast Transmitter for QRD and CRD</h1>
<p align="center">
  <img src="https://img.shields.io/badge/Status-Under_Development-yellow" alt="Under Development">
  <img src="https://img.shields.io/github/v/tag/5G-MAG/rt-mbms-tx-for-qrd-and-crd?label=version" alt="Version">
  <img src="https://img.shields.io/badge/License-AGPL_v3-blue.svg" alt="License">
</p>

## Introduction

The 5G Broadcast Transmitter for QRD and CRD is an extension of and MBMS-enabled eNodeB tailored to operate as a 5G Broadcast transmitter compatible with Qualcomm Reference Design (QRD) and QRC devices.

Additional information can be found at: https://5g-mag.github.io/Getting-Started/pages/lte-based-5g-broadcast/

### About the implementation

This implementation is based on the [srsRAN_4G Project](https://github.com/srsran/srsRAN_4G). The eNodeB has been modified to disable uplink connectivity for the reception of MBMS data.

## Install dependencies

On Ubuntu 22.04 LTS:
````
sudo apt update
sudo apt install ssh g++ git libboost-atomic-dev libboost-thread-dev libboost-system-dev libboost-date-time-dev libboost-regex-dev libboost-filesystem-dev libboost-random-dev libboost-chrono-dev libboost-serialization-dev libwebsocketpp-dev openssl libssl-dev ninja-build libspdlog-dev libmbedtls-dev libboost-all-dev libconfig++-dev libsctp-dev libfftw3-dev vim libcpprest-dev libusb-1.0-0-dev net-tools smcroute python3-pip clang-tidy gpsd gpsd-clients libgps-dev
sudo snap install cmake --classic
sudo pip3 install cpplint
sudo pip3 install psutil
````

## Downloading
````
git clone --recurse-submodules https://github.com/5G-MAG/rt-mbms-tx-for-qrd-and-crd.git
cd rt-mbms-tx-for-qrd-and-crd
git submodule update
mkdir build && cd build
````

## Building
````
cmake -DCMAKE_INSTALL_PREFIX=/usr -GNinja ..
ninja
````

## Installing
````
sudo ninja install
````

## Configuration after installation
Install the configuration:
``
sudo ./srsran_install_configs.sh user
``

After the installtion, you have to adjust the enb, rr, epc config files to your desired frequency, bandwith, tx gain, MNC, MCC ...

or you can use our [templates](https://github.com/5G-MAG/rt-mbms-tx-for-qrd-and-crd/tree/main/Config-Template). Download them and place them in ``/root/.config/srsran/``.

Also make sure to copy the adapted sib.conf.mbsfn file to the build directory:

````
cd rt-mbms-tx-for-qrd-and-crd/Config-Template
cp sib.conf.mbsfn ../build/sib.conf.mbsfn
````

## Running
Starting the transmitter requires the follwing 3 steps:
1. Starting the MBMS-Gateway
2. Starting the EPC
3. Starting the ENB

### Starting the MBMS-Gateway
``
sudo srsmbms
``

The MBMS-GW receives multicast packets on one tunnel interface, packages them to GTP-U-Packets and sends them to ENB over another tunnel interface.
The command above creates the sgi_mb interface (you could see it by entering ``ifconfig`` for example). In order for the incoming data to be routed correctly, a route has to be added:

``
sudo route add -net 239.11.4.0 netmask 255.255.255.0 dev sgi_mb
``

You can use any multicast route. 

### Starting the EPC
``
sudo srsepc
``

### Starting the ENB
````
cd rt-mbms-tx-for-qrd-and-crd/build

sudo srsenb/src/srsenb
````

After this, the transmitter is running and is ready to receive a multicast stream. Now you can, for example, transcode a local .mp4 file to rtp with ffmpeg:

``
ffmpeg -stream_loop -1 -re -i <Input-file> -vcodec copy -an -f rtp_mpegts udp://239.11.4.50:9988
``
