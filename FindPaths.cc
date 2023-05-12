#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "graph.h"

using namespace std;

int pathfindDriver(int argc, char **argv) {
    
    // Begin your code here. Feel free to add any helper functions or classes you need,
    // as long as we only have to call this function to run the specified assignment.
    //Opens file to input to Binomial Queue and hash table.

    // arguments belo w
    const string words_filename(argv[1]);
    const string starting_point(argv[2]);
    int initial_vertex = stoi(starting_point);
    // open file 
    ifstream infile; 
    string line;
    infile.open(words_filename);
    // read in number of vertices
    int number_of_vertices = 0;
    infile >> number_of_vertices;
    
    // create a graph with the given number of vertices
    Graph graph1(number_of_vertices);

    // read every line in the input file 
    while (getline(infile, line)) {
      // Add edges to the graph 
      // Initialize variables to zero so they can reset at each line
      int which_int = 1;
      int vertex = 0;
      int adjacent_vertex = 0;
      double weight = 0;
      stringstream ss(line);
      // read three int inputs vertex1 vertex2 weight 
      while (which_int < 4) {
        if (which_int == 1) ss >> vertex; // first input is vertex
        ss >> adjacent_vertex; // second input is adjacent vertex
        ss >> weight; // third input is weight
        if (ss) graph1.insertEdge(vertex, adjacent_vertex, weight); // insert edge to graph
        which_int++; // increment which_int for next integer in line
      }
    }
      graph1.dijkstra(initial_vertex);
      graph1.printShortestPath(initial_vertex);
      return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    pathfindDriver(argc, argv);

    return 0;
}
