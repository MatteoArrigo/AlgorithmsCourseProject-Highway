# AlgorithmsCourseProject-Highway

## Description
This project is for the course of "Algoritmi e Principi dell'Informatica" (Algorithms and Principles of Computer Science) at "Politecnico di Milano", for the edition of year 2023.
The course takes place in the second year of Bachelor's degree in Computer Science Engineering. We were given a simple problem, and we had to produce a program in C language that, once submitted to an online platform for verification, could pass all the secret test cases present in the platform. The grade depended on amount of time and space used by the program.

The problem consisted in a highway with a certain number of stations, and each station has a certain number of cars, each of them with a certain capacity. There's the possibility to move from one station to anoter: in this case, from the starting station to the end, a car of the station can be used to reach one the next station, limited to the capacity of the car taken.
We had to implement the five methods to handle the highway:
  * Add a station to the highway.
  * Remove a station from the highway.
  * Add a car to a certain station of the highway (if it exists).
  * Remove a car of given capacity from a certain station of the highway (if the station exists and has a car with that capacity).
  * Calculate the path from a starting station to an ending station which is the shortest in relation to the number of station passed.
    In case of multiple paths of same length, a rule of proximity of stations to the beginning of the highway is applied.
The exact problem formulation is in the [pdf file](/"Presentazione PFAPI 2022-2023.pdf")
