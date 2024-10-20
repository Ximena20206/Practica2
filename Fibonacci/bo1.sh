#!/bin/bash

echo BFibonacci >> tiemposfibo.txt
gcc fibonacci.c tiempo.c tiempo.h -o fibonacci
./fibonacci 1000 10millones.txt 746 >> tiemposfibo.txt
./fibonacci 2000 10millones.txt 109 >> tiemposfibo.txt
./fibonacci 3000 10millones.txt 1287 >> tiemposfibo.txt
./fibonacci 4000 10millones.txt 12948 >> tiemposfibo.txt
./fibonacci 5000 10millones.txt 1293 >> tiemposfibo.txt
./fibonacci 8000 10millones.txt 12347 >> tiemposfibo.txt
./fibonacci 10000 10millones.txt 234890 >> tiemposfibo.txt
./fibonacci 50000 10millones.txt 12348 >> tiemposfibo.txt
./fibonacci 100000 10millones.txt 12391 >> tiemposfibo.txt
./fibonacci 150000 10millones.txt 213409 >> tiemposfibo.txt
./fibonacci 200000 10millones.txt 1243918 >> tiemposfibo.txt
./fibonacci 300000 10millones.txt 539882 >> tiemposfibo.txt
./fibonacci 400000 10millones.txt 23509223 >> tiemposfibo.txt
./fibonacci 500000 10millones.txt 5795920 >> tiemposfibo.txt
./fibonacci 600000 10millones.txt 129834 >> tiemposfibo.txt
./fibonacci 700000 10millones.txt 1231211 >> tiemposfibo.txt
./fibonacci 800000 10millones.txt 183426991 >> tiemposfibo.txt
./fibonacci 900000 10millones.txt 183458006 >> tiemposfibo.txt
./fibonacci 1000000 10millones.txt 218919239 >> tiemposfibo.txt
./fibonacci 1500000 10millones.txt 259718613 >> tiemposfibo.txt
./fibonacci 2000000 10millones.txt 354324267 >> tiemposfibo.txt
