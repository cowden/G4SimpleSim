#!/bin/bash

# cycle over scripts 
macro_dir=scripts
macros=($macro_dir/*mac)
count=0
total=${#macros[@]}

for macro in "${macros[@]}"; do
    echo "`date` $count $total $macro" | tee -a progress.log
    docker run -v /data/me/calox/dkr/:/work -v /home/me/proj/CaloX/calo-cali-lss/sim/fiber:/sim calox bash /sim/scripts/run-geant.sh /sim/$macro | tee -a log.log
    docker rm $(docker container ls -q -f status=exited)
    count=$((count+1))
done

