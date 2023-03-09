#!/usr/bin/env bash
cd ./lib
cp libhtp* /usr/local/lib/
cd ../include
cp -r htp /usr/local/include
cd ../bin
pwd
ldconfig
./suricata --build-info

