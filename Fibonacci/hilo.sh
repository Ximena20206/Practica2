#!/bin/bash

echo BFibonacci >> tiemposfiboh.txt
gcc fibonaccihilos.c tiempo.c tiempo.h -o fibonacci
./fibonacci 1000 10millones.txt 746 >> tiemposfiboh.txt
./fibonacci 2000 10millones.txt 109 >> tiemposfiboh.txt
./fibonacci 3000 10millones.txt 1287 >> tiemposfiboh.txt
./fibonacci 4000 10millones.txt 12948 >> tiemposfiboh.txt
./fibonacci 5000 10millones.txt 1293 >> tiemposfiboh.txt
./fibonacci 8000 10millones.txt 12347 >> tiemposfiboh.txt
./fibonacci 10000 10millones.txt 234890 >> tiemposfiboh.txt
./fibonacci 50000 10millones.txt 12348 >> tiemposfiboh.txt
./fibonacci 100000 10millones.txt 12391 >> tiemposfiboh.txt
./fibonacci 150000 10millones.txt 213409 >> tiemposfiboh.txt
./fibonacci 200000 10millones.txt 1243918 >> tiemposfiboh.txt
./fibonacci 300000 10millones.txt 539882 >> tiemposfiboh.txt
./fibonacci 400000 10millones.txt 23509223 >> tiemposfiboh.txt
./fibonacci 500000 10millones.txt 5795920 >> tiemposfiboh.txt
./fibonacci 600000 10millones.txt 129834 >> tiemposfiboh.txt
./fibonacci 700000 10millones.txt 1231211 >> tiemposfiboh.txt
./fibonacci 800000 10millones.txt 183426991 >> tiemposfiboh.txt
./fibonacci 900000 10millones.txt 183458006 >> tiemposfiboh.txt
./fibonacci 1000000 10millones.txt 218919239 >> tiemposfiboh.txt
./fibonacci 1500000 10millones.txt 259718613 >> tiemposfiboh.txt
./fibonacci 2000000 10millones.txt 354324267 >> tiemposfiboh.txt
