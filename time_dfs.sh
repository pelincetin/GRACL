#!/bin/sh
make clean
make

# get the time in miliseconds for normaldfs
ts=$((`date '+%s%N'`/1000000));
./scripts/testone.sh dfs;

tt=$((`date '+%s%N'`/1000000));

# get the time in miliseconds for conc dfs
conc_ts=$((`date '+%s%N'`/1000000));
./scripts/testone.sh concdfs; 

conc_tt=$((`date '+%s%N'`/1000000)); 

# echo the difference between normaldfs and concdfs
echo "Time taken to run normaldfs: "$(($tt-$ts))" milliseconds";
echo "Time taken to run concdfs: "$(($conc_tt-$conc_ts))" milliseconds";
