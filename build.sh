[ ! -d "./build" ] && mkdir build

rm build/*

g++ ./src/* -o ./build/build.out
