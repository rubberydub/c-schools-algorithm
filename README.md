# README #

This is a greedy set cover algorithm. 

I wrote this during my studies for the University of Melbourne Class Design of Algorithms.

It takes as input a weighted graph consisting of 2 types of verticies - schools and houses.
It returns the optimum school verticies to build schools at. Each house must be within distance 100 of a school.

The input is a text file where:

Line 1 is the number of houses.

Line 2 is the number of schools.

All other lines are edges in the graph - 3 entries consisting of the two verticies adjacent with the edge and the edge weight (distance).

This algorithm includes implementations of:

A heap data type.

A graph data type.

A disjoint sets data type.

Dijkstra's algorithm.

A greedy set cover algorithm.

Usage:

Make with makefile.

Then:

    ./assn2 < test

where:

test is a test file: c_t1, c_t2, c_t3, c_t4.

franzneulistcarroll@gmail.com