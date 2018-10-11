#ifndef RANDOMGRAPH_HPP
#define RANDOMGRAPH_HPP
#include "graph.hpp"

namespace DHBW
{
	// Takes an Empty Graph G as argument and adds n vertices. Every possible edge is added with prob. p_edge
	void create_random_graph(Graph & g, VertexId n, double p_edge, double directed=false);
	
	// Somehow I must create test graphs :D
	void write_random_graph_to_file(VertexId n, std::string const &filename, double directed=false);
}
#endif 
