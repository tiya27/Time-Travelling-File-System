#for Linus/Mac OS 

#!/bin/bash
# Compile the Time-Travelling File System project

g++ -std=c++17 -Wall -O2 main.cpp -o ttfs

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
else
    echo "Compilation successful. Run ./ttfs to start."
fi
