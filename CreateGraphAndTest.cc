#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "graph.h"

using namespace std;

int graphTestDriver(int argc, char **argv) {
    
    // Begin your code here. Feel free to add any helper functions or classes you need,
    // as long as we only have to call this function to run the specified assignment.
    // Begin your code here. Feel free to add any helper functions or classes you need,
    // as long as we only have to call this function to run the specified assignment.
    const string words_filename(argv[1]);
    const string query_filename(argv[2]);
    ifstream infile; 
    string line;
    int num_vertices = 0;
    // open file
    infile.open(words_filename);
    // get number of vertices given
    infile >> num_vertices;
    
    // Create a Graph object with the number of vertices given
    // or Graph graph1 = new Graph(num_vertices) except then you would have 
    // to keep dereferencing the pointer every time you want to use a member
    // function of the Graph class (graph1->insertEdge)
    Graph graph1 (num_vertices);
    // Read every line in the input file 
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

     // Read the query file and check if there is an edge between two vertices in graph
    ifstream infile2;
    infile2.open(query_filename);
    int v1 = 0;
    int v2 = 0;
    double w = 0;
    while (!(infile2.eof())) {
      infile2 >> v1;
      infile2 >> v2;
      w = graph1.edgeCheck(v1, v2);
      if (w != -1) {
        cout << v1 << " " << v2 << ": connected " << w << endl;
      } else {
        cout << v1 << " " << v2 << ": not_connected" << endl;
      }
      w = 0;
    }
    return 0;
}




int main(int argc, char **argv) {
    if (argc != 3) {
      cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
      return 0;
    }

    graphTestDriver(argc, argv);

    return 0;
}
