#!/bin/bash

echo BFibonacci >> tiemposfibo1.txt
gcc fibonacci.c tiempo.c tiempo.h -o fibonacci
./fibonacci 1000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 2000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 3000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 4000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 5000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 8000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 10000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 50000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 100000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 150000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 200000 10millones.txt 17957576 >> tiemposfibo1.txt
./fibonacci 300000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 400000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 500000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 600000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 700000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 800000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 900000 10millones.txt 17957576 >> tiemposfibo1.txt
./fibonacci 1000000 10millones.txt 17957576  >> tiemposfibo1.txt
./fibonacci 1500000 10millones.txt 17957576 >> tiemposfibo1.txt
./fibonacci 2000000 10millones.txt 17957576  >> tiemposfibo1.txt
