Markovian Queue M/M/2/10 with Threshold
=====================
Compiling
---------------------
You need **main.cpp**, **Makefile**, a recent C++11 Compiler and Standard Library. Then just run **$ make**.

Usage
---------------------
After compiling run **$ ./main** to get usage message.
To simulate the system with threshold (K, λ) = (1,1), where the simulation stops after 10.000 succesful arrivals in the queue, give $ ./main 1 1

Script
---------------------
To simulate the system under configurations of K and λ, run the shell script with **$ ./run.sh**. It runs all simulations for the given ranges of K and λ and produces all results in different files for each input.
