
import pylab as plt
import numpy as np
import pandas as pd
import os
import subprocess

import sys
sys.path.append('../utils')
import readg4csv

columns = ["evID", "time"]
pd_read_kwrgs = readg4csv.pd_read_kwrgs
pd_read_kwrgs["skiprows"] = 6


base_dir = "/data/me/calox/dkr/fiber_build"
ntuple = "nt_pmt"


impact_parameters = {"0.00mm": 0., "0.15mm": 0.15, "0.3mm": 0.3}

alpha_parameters = { #"0": 0.,
                    "pi6": np.pi/6.,
                    "pi4": np.pi/4.,
                    "pi3": np.pi/3.,
                    "pi2": np.pi/2.,
                    "3pi4": 3.*np.pi/4.,
                    "2pi3": 2.*np.pi/3.,
                    "5pi6": 5.*np.pi/6.,
                    #"pi": np.pi
                    }

def loaddf(alpha, b):
    name = "fib_r0_{}_{}".format(alpha, b)
    return readg4csv.readRun(base_dir, name, base=ntuple, columns=columns, pd_read_kwrgs=pd_read_kwrgs)


def plotCDF(x, label=None):
    n = len(x)
    plt.plot(np.sort(x), np.cumsum(np.ones(n))/n, label=label)


def plotPulse(x, label=None, range=(0., 20.), bins=400, norm=None):
    hist, edges = np.histogram(x, range=range, bins=bins);
    de = np.diff(edges)/2
    pt = edges[:-1] + de
    if norm is not None:
        hist = hist/norm
    plt.plot(pt, hist, label=label)


def aggScan(aggregation="count"):

    agg = np.zeros((len(alpha_parameters), len(impact_parameters)))
    alphas = np.zeros(len(alpha_parameters))
    bs = np.zeros(len(impact_parameters))

    for i, (ak, av) in enumerate(alpha_parameters.items()):
        alphas[i] = av
        for j, (bk, bv) in enumerate(impact_parameters.items()):
            bs[j] = bv
            df = loaddf(ak, bk)
            agg[i,j] = df.groupby("evID").agg(aggregation).mean()

    aindx = np.argsort(alphas)
    bindx = np.argsort(bs)
    agg = agg[aindx][:,bindx]
    alphas = alphas[aindx]
    bs = bs[bindx]
    return alphas, bs, agg

def docker(alpha, b, mac=None, filename=None):
    if mac is None:
        mac = "py_run.mac"
    if filename is None:
        filename = "py_data_0_0.csv"

    with open("/home/me/proj/CaloX/calo-cali-lss/sim/fiber/scripts/"+mac, "w") as f:
       f.write(f"/runaction/fileName {filename}\n")
       f.write(f"/det/nClad 1.4\n")
       f.write(f"/run/initialize\n")
       f.write(f"/pg/impact {b} mm\n")
       f.write(f"/pg/alpha {alpha}\n")
       f.write(f"/run/beamOn 100")

    subprocess.run([
        "docker",
        "run",
        "-v",
        "/data/me/calox/dkr/:/work",
        "-v",
        "/home/me/proj/CaloX/calo-cali-lss/sim/fiber:/sim",
        "calox",
        "bash",
        "/sim/scripts/run-geant.sh",
        f"/sim/scripts/{mac}"
        ])


    return readg4csv.readRun(
        base_dir,
        filename[:-4],
        base=ntuple,
        columns=columns,
        pd_read_kwrgs=pd_read_kwrgs
        )


