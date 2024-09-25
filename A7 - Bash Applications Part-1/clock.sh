#!/bin/bash

display_digit() {
    digit=$1
    i=$2
    if [ $i -eq 0 ]; then 
        case $digit in
            0) echo -n "  ---  ";;
            1) echo -n "   .   ";;
            2) echo -n "  ---  ";;
            3) echo -n "  ---  ";;
            4) echo -n " .   . ";;
            5) echo -n "  ---  ";;
            6) echo -n "  ---  ";;
            7) echo -n "  ---  ";;
            8) echo -n "  ---  ";;
            9) echo -n "  ---  ";;
        esac
    elif [ $i -eq 1 ]; then 
        case $digit in
            0) echo -e -n " |   | ";;
            1) echo -e -n "   |   ";;
            2) echo -e -n "     | ";;
            3) echo -e -n "     | ";;
            4) echo -e -n " |   | ";;
            5) echo -e -n " |     ";;
            6) echo -e -n " |     ";;
            7) echo -e -n "     | ";;
            8) echo -e -n " |   | ";;
            9) echo -e -n " |   | ";;
        esac
    elif [ $i -eq 2 ]; then 
        case $digit in
            0) echo -n " |   | ";;
            1) echo -n "   |   ";;
            2) echo -n "  ---  ";;
            3) echo -n "  ---  ";;
            4) echo -n "  ---| ";;
            5) echo -n "  ---  ";;
            6) echo -n "  ---  ";;
            7) echo -n "     | ";;
            8) echo -n "  ---  ";;
            9) echo -n "  ---  ";;
        esac
    elif [ $i -eq 3 ]; then 
        case $digit in
            0) echo -n " |   | ";;
            1) echo -n "   |   ";;
            2) echo -n " |     ";;
            3) echo -n "     | ";;
            4) echo -n "     | ";;
            5) echo -n "     | ";;
            6) echo -n " |   | ";;
            7) echo -n "     | ";;
            8) echo -n " |   | ";;
            9) echo -n "     | ";;
        esac
    elif [ $i -eq 4 ]; then 
        case $digit in
            0) echo -n "  ---  ";;
            1) echo -n "   .   ";;
            2) echo -n "  ---  ";;
            3) echo -n "  ---  ";;
            4) echo -n "     . ";;
            5) echo -n "  ---  ";;
            6) echo -n "  ---  ";;
            7) echo -n "     . ";;
            8) echo -n "  ---  ";;
            9) echo -n "  ---  ";;
        esac
    fi
}

display_colon() {
    i=$1
    if [ $i -eq 0 ]; then 
        echo -n "       "
    elif [ $i -eq 1 ]; then 
        echo -n "   o   "
    elif [ $i -eq 2 ]; then 
        echo -n "       "
    elif [ $i -eq 3 ]; then 
        echo -n "   o   "
    elif [ $i -eq 4 ]; then 
        echo -n "       "
    fi
}

display_notcolon() {
    i=$1
    if [ $i -eq 0 ]; then 
        echo -n "       "
    elif [ $i -eq 1 ]; then 
        echo -n "       "
    elif [ $i -eq 2 ]; then 
        echo -n "       "
    elif [ $i -eq 3 ]; then 
        echo -n "       "
    elif [ $i -eq 4 ]; then 
        echo -n "       "
    fi
}

blink=1

while true; do
    clear

    src_h=$(tput lines)
    scr_w=$(tput cols)

    clock_h=8  
    lines=$(( (src_h - clock_h) / 2 ))
    for ((line=1; line<=lines; line++)); do echo; done;

    clock_w=64 
    num_spaces=$(( (scr_w - clock_w) / 2 ))


    datetime=$(date +"%A %d %B %Y %I %M %S %p %Z")
    read -r day date month year hour minute second ampm timezone <<< $datetime

    printf "%${num_spaces}s%s %s %s\n" " " "$day" "$date" "$month $year"
    printf "%${num_spaces}s%s %s %s\n" " " "+--------------------------------------------------------------+"
    for ((i=0; i<5; i++))do
        printf "%${num_spaces}s" " "
        echo -n "|  " 
        for ((j=0; j<${#hour}; j++)); do display_digit "${hour:$j:1}" "$i"; done; 
        if [ "$blink" -eq 1 ]; then display_colon "$i"; else display_notcolon "$i"; fi

        for ((j=0; j<${#minute}; j++)); do display_digit "${minute:$j:1}" "$i"; done;
        if [ "$blink" -eq 1 ]; then display_colon "$i"; else display_notcolon "$i"; fi

        for ((j=0; j<${#second}; j++)); do display_digit "${second:$j:1}" "$i"; done;
        if [ $i != 4 ]; then  echo "    |"; fi 
        done

    echo "$ampm  |"
    printf "%${num_spaces}s%s %s %s\n" " " "+--------------------------------------------------------------+"

    remaining_lines=$((src_h - lines - clock_h))
    for ((line=1; line<=remaining_lines; line++)); do echo; done

    if [ $((${second#0} % 2)) -eq 0 ]; then blink=0; else blink=1;fi
    read -t 0.5 -r && break
done
