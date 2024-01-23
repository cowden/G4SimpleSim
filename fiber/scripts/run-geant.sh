#!/bin/bash

source /opt/geant4/install/share/Geant4-11.0.2/geant4make/geant4make.sh

cd /work/fiber_build

./simFiber -t 4 -m $1
