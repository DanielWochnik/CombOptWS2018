#include "randomgraph.hpp"
#include <cassert>
#include <cmath>

namespace DHBW
{
	void create_random_graph(Graph & g, VertexId n, double p_edge, double directed)
	{
		assert(g.num_vertices() == 0);
		
		// Add vertices
		for (VertexId i = 0; i < n; ++i)
		{
			g.add_vertex();
		}
		
		// add random edges
		for (VertexId i = 0; i < n; ++i)
		{
			for (VertexId j = 0; j < i or (directed and j < n); ++j)
			{
				// Random number in [0,1]
				double const r = ((double) rand() / (RAND_MAX));
				if (p_edge >= r)
				{
					g.add_edge(j,i);
				}
			}
		}
	}
	
	void write_random_graph_to_file(VertexId n, std::string const & filename, double directed)
	{
		// Thats a sharp treshhold for connectivity, i.e. the probability that 
		// a random graph with n vertices and p is 
		// 		1, if p > for all p > log(n)/n
		// 		0, if p > for all p < log(n)/n
		// for n -> infinity (that's pretty cool btw!)
		// see also: https://www.math.cmu.edu/~af1p/MAA2005/L2.pdf
		double const p = std::log(n)/n;
		Graph g;
		create_random_graph(g,n,p,directed);
		g.write_to_file(filename);
	}
}
	