# AlgorithmsCourseProject-Highway

## Description
This project is for the course of "Algoritmi e Principi dell'Informatica" (Algorithms and Principles of Computer Science) at "Politecnico di Milano", for the edition of year 2023.
The course takes place in the second year of Bachelor's degree in Computer Science Engineering. We were given a simple problem, and we had to produce a program in C language that, once submitted to an online platform for verification, could pass all the secret test cases present in the platform. The grade depended on amount of time and space used by the program. For 30 cum laude, time used had to be under 1 second, and I reached an avarege time (with the secret test cases) of 0.31 seconds.

The problem consisted in a highway with a certain number of stations, and each station has a certain number of cars, each of them with a certain capacity. There's the possibility to move from one station to anoter: in this case, from the starting station to the end, a car of the station can be used to reach one the next station, limited to the capacity of the car taken.
The highway is empty at the beginning, and we had to implement the five methods to handle the highway:
  * Add a station to the highway.
  * Remove a station from the highway.
  * Add a car to a certain station of the highway (if it exists).
  * Remove a car of given capacity from a certain station of the highway (if the station exists and has a car with that capacity).
  * Calculate the path from a starting station to an ending station which is the shortest in relation to the number of stations passed.
    In case of multiple paths of same length, a rule of proximity of stations to the beginning of the highway is applied.

The exact problem formulation is in the [pdf file](/presentazione-progetto-api2023.pdf) (italian version)

## Tecnology used
 * Language C, compiled with gcc
 * Use of Makefile to compile
 * gdb ad debugger
 * Address SANitizer (ASAN), used with option -fsanitize=address, to locate memory issues
 * Valgrind, used with "valgrind" command, to locate memory issues and other possible problems
 * Callgrind, used with "valgrind --tool=callgrind" command, examined with "kcachegrind", to measure time performance
 * Massif, used with "valgrind --tool=massif" command, examined with "massif-visualizer", to measure memory performance

## How to use
The main program is in [highway.c](/highway.c).
Once compiled with gcc, the program can be launched and the interaction is via command line.
For the exact descrption of the five possible commands, refer to the [pdf file](/presentazione-progetto-api2023.pdf).

The course offered also a certain number of open test to check the correctness of the solution. The 100 open tests are in the file [archivio_test_aperti.rar](archivio_test_aperti.rar). The other code file [highway_opentests.c](highway_opentests.c) can be used with these files.
The open tests must be stored in a folder named "archivio_test_aperti", and the folder must be in the same folder as the .c file. If the code is compiled and executed, it executes the program on all 100 open tests and checks if there is some difference with the expected output.
