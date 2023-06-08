#!/bin/bash

Core_number=15
Orange="\e[0;33m"
Green="\e[0;32m"
Reset='\e[m'
Red='\e[0;31m'

# Handle arguments.. 
if [ "$1" ]
then
    if [ "$1" = "clean" ]
    then
        if [ ! -d build -o ! -f build/Makefile ]
        then
            printf "${Red}Nothing to clean !${Reset}\n"
        else
            printf "${Green}Cleaning build folder${Reset}\n"
            cd build
            make clean
            cd ../
        fi
        exit 0
    elif [ "$1" = "fclean" ]
    then
         if [ ! -d build ]
         then
             printf "${Red}No build folder to delete${Reset}\n"
         else
             printf "${Green}Removing the build folder${Reset}\n"
             rm -rf build/
         fi
         exit 0
    else
        printf "${Red}Arguments not exist - compiling...${Reset}\n"
    fi
fi

# compilation

project=$(grep project CMakeLists.txt | cut -d '(' -f2 | cut -d ')' -f1)

printf "${Green}Compiling : ${project}${Reset}\n"

if [ ! -d build ]
then
    printf "${Orange}Creating build folder${Reset}\n"
    mkdir build
fi

cd build

if [ ! -f Makefile ]
then
    printf "${Orange}Create compilation files${Reset}\n"
    emcmake cmake .. -DCMAKE_TOOLCHAIN_FILE=/home/jserin/src/vcpkg/scripts/buildsystems/vcpkg.cmake
fi

make -j $Core_number

if [ ! -f $project ]
then
    printf "${Red}error durring compilation${Reset}\n"
else
    mv $project ../
fi
    
cd ../

exit 0
