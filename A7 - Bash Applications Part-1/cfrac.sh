#!/bin/bash

gcd() {
    if [ $2 -eq 0 ]; then echo $1;
    else echo $(gcd $2 $(($1 % $2)));
    fi
}

evalcfrac() {
    echo -n "Enter the array of coefficients: "
    read -a A

    n=${#A[@]}
    p=(${A[n-1]} 1)
    q=(1 0)

    local p=1 
    local q=${A[n-1]} 
    local r=0 
    local s=1

    for ((i=n-2; i>=0; i--)); do
        local x=$((p + A[i] * q))
        local y=$q
        p=$q
        q=$x
        r=$s
        s=$y
    done

    float_val=$(bc -l <<< "scale=10; $q / $p")
    echo "The continued fraction evaluates to $q / $p = $float_val"
}

gencfrac() {
    echo -n "Enter fraction (a / b): "
    read fraction
    a=$(echo $fraction | cut -d'/' -f1)
    b=$(echo $fraction | cut -d'/' -f2)

    echo -n "The continued fraction expansion of $a / $b is: "
    while [ $b -ne 0 ]; do
        q=$((a / b))
        echo -n "$q "
        temp=$((a - q * b))
        a=$b
        b=$temp
    done
    echo
}

evalcfrac
gencfrac