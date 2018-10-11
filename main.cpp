#include "graph.hpp"
#include "randomgraph.hpp"
#include <iostream>

// Convenience. If you don't understand just ignore ;)
using namespace DHBW;


// What do I do?
// The '&' in  front of g ensures that we do not copy g, 
// it will be exactly the same Graph g as outside of this function
VertexId example_function1(Graph & g)
{
	// This method is written unneccessary compliceted to give a better feeling of the use of this class
	// EdgeId and GraphId are internally just the same as unsigned int's. I prefer using the aliases for 
	// better readability.
	EdgeId a;
	for (VertexId i = 0; i < g.num_vertices(); ++i)
	{
		// Get the i-th vertex
		Vertex & v = g.vertex(i);
		EdgeId b = 0;
		for (EdgeId e = 0;  e < v.num_edges(); ++ e)
		{
			++b;
		}
		if ( b > a)
		{
			a = b;
		}
	}
	return a;
}

// A vector is a kind of an dynamic_array. std::vector<VertexId> is a vector of VertexIds
// Random path starting at s and ending in t
std::vector<VertexId> random_path(Graph & g, VertexId s, VertexId t)
{
	// Create empty vector
	std::vector<VertexId> path;
	// add first vertex, i.e. s, (represented by its id)
	path.push_back(s);
	
	// random walk :D
	VertexId current = s;
	while (current != t)
	{
		// Get vertex from VertexId
		Vertex & v = g.vertex(current);
		// Ask for number of edges
		EdgeId num_edges = v.num_edges();
		// compute random integer in [0,num_edges-1]
		EdgeId rand_id = rand()%num_edges;
		// Take edge (first take id from v, than get edge from g)
		Edge next_edge = g.edge(v.edge(rand_id));
		// Compute next vertex
		current = next_edge.other_vertex(v.id());
		path.push_back(current);
	}
	return path;
}


int main()
{	
	// Read graph from input file 
	Graph g("input/graph1.plain");
	// Print to console, std::endl is (almost) equivalent to "\n"
	std::cout << example_function1(g) << std::endl;
}