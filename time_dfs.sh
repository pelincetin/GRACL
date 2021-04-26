#!/bin/sh

#make clean
#make

for i in {1..10}
    # get the time in miliseconds for normaldfs
    do ts="$((`date '+%s%N'`/1000000))";

    ./scripts/testone.sh dfs;

    tt="$((`date '+%s%N'`/1000000))";
    diff=`expr $tt - $ts`;
    a=`expr $a + $diff`;

    # get the time in miliseconds for conc dfs
    conc_ts="$((`date '+%s%N'`/1000000))";
    ./scripts/testone.sh concdfs; 

    conc_tt="$((`date '+%s%N'`/1000000))"; 
    diff=`expr $conc_tt - $conc_ts`;
    b=`expr $b + $diff`;
done


# echo the difference between normaldfs and concdfs
echo "Ran the tests ten times. Here are the results: ";
echo "Time taken to run normaldfs ten times is: "$a" milliseconds";
echo "Time taken to run concdfs ten times is: "$b" milliseconds";
res1=`expr $a / 10`;
res2=`expr $b / 10`;
echo "On average, normaldfs ran in: "$res1" milliseconds";
echo "On average, concdfs ran in: "$res2" milliseconds";