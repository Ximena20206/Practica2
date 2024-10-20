#!/bin/bash

echo BFibonacci >> tiemposfibo2h.txt
gcc fibonaccihilos.c tiempo.c tiempo.h -o fibonacci
./fibonacci 1000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 2000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 3000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 4000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 5000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 8000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 10000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 50000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 100000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 150000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 200000 10millones.txt 0 >> tiemposfibo2h.txt
./fibonacci 300000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 400000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 500000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 600000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 700000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 800000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 900000 10millones.txt 0 >> tiemposfibo2h.txt
./fibonacci 1000000 10millones.txt 0  >> tiemposfibo2h.txt
./fibonacci 1500000 10millones.txt 0 >> tiemposfibo2h.txt
./fibonacci 2000000 10millones.txt 0  >> tiemposfibo2h.txt
