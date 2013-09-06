#!/bin/bash

# Compile the bianchi_model_11M.cpp 
#g++ -o bianchi_model_11M bianchi_model_11M.cpp 

c=1
rm -rf "result.txt"
while [ $c -le 50 ]
do
    
    ./bianchi_model_11M $c >> result.txt
    

    let "c=c+1"
done
