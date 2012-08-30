#!/bin/sh

#usage
usage(){

    echo "usage: replace <filename> '<pattern>' '<replace string>'"
    exit 0
}

if [ $# -lt 3 ]; then 
    usage
    exit 0
fi

sed "s/$2/$3/" $1 >$1.sedtmp
mv $1.sedtmp $1

