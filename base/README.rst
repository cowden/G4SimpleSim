G4 Simple Base Simulation
=========================
Simple simulation of sampling calorimeter.
This is a modification of the B4 example
included in the Geant4 distribution.

Setup
-----

Use ``cmake`` and ``make`` to build this executable.
.. ::
    cmake G4SimpleSim/base -B sim
    cd sim
    make


To build with debug symbols,
.. ::
    cmake -DCMAKE_BUILD_TYPE=Debug .
    make clean install
