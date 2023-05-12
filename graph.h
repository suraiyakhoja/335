#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <list>
#include <climits>

// This file is for your graph implementation.
// Add everything you need in between the "ifndef and "endif" statements.
// Do not put anything outside those statements
class Graph
{
public:
	/**
	 * Graph constructor
	 * Initializes the graph by creating a vector of vertices and stores 
	 * information about the vertices/graph. 
	*/
	Graph(int &num_vertices) {
		number_of_vertices_ = num_vertices; 
		vertices_.resize(number_of_vertices_);
		indegrees_per_vertex_.resize(number_of_vertices_);
		// Initialize each element of vertices_ by creating a new Vector
		for (auto &i : vertices_) { 
			i = new Vertex;
		}
		// Each vertex gets an index. 
		for (int i = 1; i < number_of_vertices_; i++) {
			vertices_[i]->vertex_index_ = i + 1;
		}
	}

	/**
	 * Add edges to the graph. Do this by updating the Adjacent member of 
	 * each Vertex struct to include pointers to the vertices that it is 
	 * adjacent to. 
	*/
	void insertEdge(int &v1, int &v2, double &w) {
		// Create an instance of Adjacent struct
    	Vertex::Adjacent edge;
		// Set adjacent_vertex_index_ (Adjacent struct that represents 
		// the edge from v1 to v2 is created above. Below assigns v2 as the
		//endpoint of the edge.)
		edge.adjacent_vertex_index_ = v2;
		// Set weight
		edge.weight_ = w;
		// Add vertex to the adjacent_vertices list of vertices_
		// vertices_[v2-1] is a pointer to a Vertex object
		// adjacent_vertices_ is a member of the Vertex object
		vertices_[v1-1]->adjacent_vertices_.push_back(edge);
		// Update indegrees of v2 (b/c v1 points to v2)
		indegrees_per_vertex_[v2-1]++;
	}

	double edgeCheck(int v1, int v2) {
    	// get a pointer to the vertex in the graph corresponding to v1
		Vertex* match = vertices_[v1 - 1];
		// create reference to adjacency list that allows for accessing and iterating
		// through adjacency list w/o copy
		// below we access the adjacency list of the vertex match points to
		const auto& matchs_adjacents = match->adjacent_vertices_; 
		for (auto i = matchs_adjacents.begin(); i != matchs_adjacents.end(); i++) {
		if (i->adjacent_vertex_index_ == v2) {
			return i->weight_;
		} 
		}
		return -1;
  	}
	
	void dijkstra(const int& start_index) {
		BinaryHeap<Vertex*> bh;

		for(Vertex* v: vertices_)
		{
			v->known_ = false;
			v->distance_ = INT_MAX;
		}

		Vertex* s = vertices_[start_index - 1];
		s->distance_ = 0;

		bh.insert(s);
		while(!bh.isEmpty())
		{
			Vertex* current_vertex = bh.findMin();
			bh.deleteMin();
			current_vertex->known_ = true;

			for(auto adjacent : current_vertex->adjacent_vertices_)
			{
				Vertex* adj_vertex = vertices_[(adjacent.adjacent_vertex_index_)-1];
				if(adj_vertex->known_ == false)
				{
					int cvw = adjacent.weight_;
					if(current_vertex->distance_ + adjacent.weight_ < adj_vertex->distance_)
					{
						adj_vertex->distance_ = current_vertex->distance_ + adjacent.weight_;
						adj_vertex->path_ = current_vertex;
						bh.insert(adj_vertex);
					}
				}

			}
			
		
		}
		
	}


	void printShortestPath(const int& s)
	{
		vector<int> shortest_path;
		for (int i = 0; i < vertices_.size(); i++) {
			cout << i + 1 << ": ";
			Vertex* hold = vertices_[i];
			double cost = hold->distance_;
			while (hold != nullptr) {
				if (hold->vertex_index_ == 0) {
					hold->vertex_index_ = i + 1;
				}
				shortest_path.push_back(hold->vertex_index_);
				hold = hold->path_;
			}
			reverse(shortest_path.begin(), shortest_path.end());
			for (int i = 0; i < shortest_path.size(); i++) {
				cout << shortest_path[i] << " ";
			}
			shortest_path.clear();
			cout << "cost: " << std::fixed << std::setprecision(1) << cost << endl;

		}

		
		
	}


	

  	


	
	
private:
	struct Vertex {
			struct Adjacent {
				int adjacent_vertex_index_;
				double weight_;
				Adjacent() : adjacent_vertex_index_{}, weight_{} {};
				Adjacent(int avi, double w) : adjacent_vertex_index_{avi}, weight_{w} {};
			}; // end Adjacent
			list<Adjacent> adjacent_vertices_;
			int vertex_index_;
			int distance_;
			bool known_;
			Vertex* path_;
			Vertex() : adjacent_vertices_{}, vertex_index_{}, distance_{}, known_{}, path_{} {};
			Vertex(list<Adjacent> av, int vi, int d, bool k, Vertex* p) : adjacent_vertices_{av}, vertex_index_{vi}, distance_{d}, known_{k}, path_{p} {};
		}; // end Vertex
	
	

	struct compareNodes {
		bool operator() (const Vertex* v1,  const Vertex* v2) {
			return (v1->distance_ > v2->distance_);
		}

	}; // end ShortestDistance

	vector<int> indegrees_per_vertex_; // vector of indegrees (one index = one vertex)
	vector<Vertex*> vertices_; // vector of vertices
	int number_of_vertices_; // number of vertices, obviously. 	

}; // end Graph 
#endif
