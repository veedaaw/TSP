/*
 * COMP 6651 Programming Assignment #1
 * Author: Vida Abdollahi
 * Student Id: 40039052
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <array>
using namespace std;

vector<int> PERMUTED_VERTICES;

//************************* FACTORIAL *******************************//
unsigned factorial(unsigned n)
{
    if (n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

//************************* PERMUTATION *******************************//

void permutations(vector<int> &toPermute, int index)
{
    if (index == toPermute.size())
        {
            for (int i = 0; i < toPermute.size(); i++)
            {
                PERMUTED_VERTICES.push_back(toPermute[i]);
            }
            
            return;
        }
    
    for ( int j = index; j< toPermute.size(); j++)
    {
        swap(toPermute[j], toPermute[index]);
        permutations(toPermute, index + 1);
        swap(toPermute[j], toPermute[index]);
    }
}

//************************* TSP *******************************//

int TSP(int *matrix , vector<int> vertices)
{
    int current_weight;
    int min_Hamilton_weight = INT_MAX;
    
    // Assuming that the first index of vertices is our start point and is always 0
    int start = 0;
    for (int i = 1; i < vertices.size(); ++i)
    {
        // Works like: 0->1->2
        current_weight += *(matrix + start + (vertices[i] * vertices.size()));
        start = vertices[i];
    }
    
    // And then 2->0
    current_weight += *(matrix + start);
    
    if(current_weight < min_Hamilton_weight)
    {
        min_Hamilton_weight = current_weight;
    }
    
    return min_Hamilton_weight;
}


//*************************** main *******************************//

int main(int argc, char* argv[])
{

  if(argc != 3)
  {
    cout << "Error: Incorrect number of arguments!!!" << endl;
    return -1;
  }

  fstream input(argv[1]);
  ofstream output(argv[2]);

  if(!input)
  {
    cout << "Error: Cannot open input file!!!" << endl;
    return -1;
  }

  if(!output)
  {
    cout << "Error: Cannot open output file (Permission issue?) !!!" << endl;
    return -1;
  }

    // Reading first integer of the input file ( =number of graphs)
    int n;
    input >> n;
    for (int i = 0; i<n; i++)
        
    {
        int vertices, edges;
        input >> vertices >> edges;
        
        // Initializing graph
        int graph [vertices][vertices];
        for (int j = 0; j < edges; j++)
        {
            int v1, v2, weight;
            input >> v1 >> v2 >> weight;
            
            graph[v1][v2] = weight;
            graph[v2][v1] = weight;
            graph[v1][v1] = 0;
            graph[v2][v2] = 0;
        }
      
        vector<int> toPermute_vertices;
        vector<int> toTSP_vertices(vertices);
        
         // We assume that the first node is always zero so we don't pass it to permute function
        for(int t= 1; t< vertices ; t++)
        {
            toPermute_vertices.push_back(t);
        }
        
        permutations(toPermute_vertices, 0);
        
        // To pass the permuted vertices to TSP, we have to build it up again (first node = 0)
        toTSP_vertices[0] = 0;
        int permutedVertices = vertices -1;
        int counter = 0;
        int final_result = INT_MAX;
        
        
        while (counter < (factorial(permutedVertices) * permutedVertices) -permutedVertices-1)
        {
            for (int i=0; i<permutedVertices; i++)
            {
                toTSP_vertices[i+1] = PERMUTED_VERTICES[i+counter];
            }
           
            // Finally calling the TSP function!
            int result = TSP( (int *)graph, toTSP_vertices);
            if(result <= final_result)
            {
                final_result = result;
            }
            counter += permutedVertices;
        }
         output << final_result <<endl;
    
        // I used this part to print the graph
        /*for (int k = 0; k < vertices; ++k)
        {
            for (int m = 0; m < vertices; ++m)
            {
                output << graph[k][m] << "";
            }
                output << endl;
        }*/
        
        // Since we are using the same data scrutures to store our values, we clear them all befor
        // using them again. [OMG!]
        
        toTSP_vertices.clear();
        toPermute_vertices.clear();
        PERMUTED_VERTICES.clear();
    }
    
  input.close();
  output.close();


}

