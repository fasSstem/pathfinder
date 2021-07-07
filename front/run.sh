#!/bin/bash
absolute_path=`readlink -e "$0"`
absolute_path=`dirname "$absolute_path"`
absolute_path=${absolute_path%/llvm-cfg-utils}

for arg in $*
do
    if [[ ${arg:0:1} != "-" ]]; then
        aarg="$aarg `readlink -e "$arg"`"
    else
        aarg="$aarg $arg"
    fi
done

cd $absolute_path

if [[ $1 == "-test" ]]; then
    build/test
else
    python llvm-cfg-utils/code/llvm.py -front-only $aarg
    build/core build/
fi