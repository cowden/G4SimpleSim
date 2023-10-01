Simple Fiber Simulation
=======================

A single fiber oriented along the ``z``-axis transversed
by single electrons is simulated.  The electron momentum direction is
paramterized by the angle w.r.t. the fiber axis and the impact parameter
to the fiber axis.  Geant4 simulates the cherenkov production within the
core of the fiber and traces the rays to the glass plate located the far
end at which point the time of arrival is recorded.

Directory Organization
----------------------

* ``include``, ``src`` -  headers and source code for the fiber simulation
* ``scripts`` - scripts to run the simulation scenarios. These assume
you have the docker image built from the ``cowden/CaloXUtils`` repo.
* ``analysis`` - data analysis scripts.

