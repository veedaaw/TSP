# TSP
Travelling Salesman Problem 


Solving the “Traveling Salesman Problem”: given a complete, undirected
weighted graph of N>2 vertices you have to find the minimum Hamiltonian cycle. A Hamiltonian cycle is a cycle
that visits all vertices exactly once (with the exception of the first and last vertex). You can assume that the
weights are positive, but you cannot assume that the weights obey the triangle inequality.

Specifications

The input is specified in a file whose name is the first argument of the program. The first line contains an integer
M specifying how many datasets are in the file. The reminder of the file encodes the datasets. Each dataset
consists of a definition of a graph as follows: It starts with two space separated positive integers V and E on the
first line that indicates the number of vertices and edges respectively. The following lines specify the weights on
the edges of the graph as following: each edge is specified on one line as 3 numbers: u v w. u is the index of the
first vertex, v is the index of the second vertex and w is a positive integer weight of the edge (u,v). Note that all
edges of the graph appear in this list exactly once. (i.e. if we have an entry for (u,v) we will not have one for (v,
u)).

Here is an example:

2

3 3

0 1 1

0 2 1

1 2 1

4 6

0 1 2

0 2 1

0 3 2

1 2 2

1 3 1

2 3 2

The output is a file whose name is the second argument of the program. Each line encodes the results of each
test case. The algorithm should output the length of the minimal Hamiltonian cycle.

For example, the output corresponding to the input above is as follows:

3

6
