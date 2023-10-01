#!/usr/bin/env python

import numpy as np

impact_parameters = {"0.00mm": 0., "0.15mm": 0.15, "0.3mm": 0.3}
alpha_parameters = {"0": 0.,
                    "pi6": np.pi/6.,
                    "pi4": np.pi/4.,
                    "pi3": np.pi/3.,
                    "pi2": np.pi/2.,
                    "3pi4": 3.*np.pi/4.,
                    "2pi3": 2.*np.pi/3.,
                    "5pi6": 5.*np.pi/6.,
                    "pi": np.pi}

nEvents = 10000
beam_cmd = f"/run/beamOn {nEvents}"

for ik, iv in impact_parameters.items():
    impact_cmd = f"/pg/impact {iv} mm"
    for ak, av in alpha_parameters.items():
        alpha_cmd = f"/pg/alpha {av}"
        filename = f"fib_r0_{ak}_{ik}.csv"
        run_cmd = "/runaction/fileName " + filename

        with open(f"scripts/run_{ak}_{ik}.mac", "w") as f:
            f.write(run_cmd)
            f.write("\n")
            f.write("/run/initialize")
            f.write("\n")
            f.write(impact_cmd)
            f.write("\n")
            f.write(alpha_cmd)
            f.write("\n")
            f.write(beam_cmd)
            
 
