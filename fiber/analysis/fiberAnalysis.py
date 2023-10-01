
import pylab as plt
import numpy as np
import pandas as pd

import sys
sys.path.append('../utils')
import readg4csv

columns = ["evID", "time"]
pd_read_kwrgs = readg4csv.pd_read_kwrgs
pd_read_kwrgs["skiprows"] = 6


base_dir = "/data/me/calox/dkr/fiber_build"
ntuple = "nt_pmt"

def loaddf(alpha, b):
    name = "fib_r0_{}_{}".format(alpha, b)
    return readg4csv.readRun(base_dir, name, base=ntuple, columns=columns, pd_read_kwrgs=pd_read_kwrgs)


def plotCDF(x, label=None):
    n = len(x)
    plt.plot(np.sort(x), np.cumsum(np.ones(n))/n, label=label)


def plotPulse(x, label=None):
    hist, edges = np.histogram(x, bins="fd");
    de = np.diff(edges)/2
    pt = edges[:-1] + de
    plt.plot(pt, hist, label=label)


