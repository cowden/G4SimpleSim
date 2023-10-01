"""
"""

import os
import re

import pandas as pd

pd_read_kwrgs = {"skiprows": 7, "header": None}

columns = ["Eabs", "Egap", "Ebeam"]


def readRun(dirname, name, base="nt_B4", columns=columns, pd_read_kwrgs=pd_read_kwrgs):
    # get list of files
    lst = os.listdir(dirname) 
    df = None
    for fi in lst:
        # apply pattern 
        if re.match("{}_{}_t[0-9]+\.csv".format(name, base),
            fi):
            if df is None:
                df = pd.read_csv(os.path.join(dirname, fi),
                    **pd_read_kwrgs)
            else:
                df = pd.concat((df, pd.read_csv(os.path.join(dirname, fi), **pd_read_kwrgs)))
    df.columns = columns
    return df  
        
