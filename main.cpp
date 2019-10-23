#include "graph.hpp"
#include "randomgraph.hpp"
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <fstream>

// Convenience. If you don't understand just ignore ;)
using namespace DHBW;


// What do I do?
// The '&' in  front of g ensures that we do not copy g, 
// it will be exactly the same Graph g as outside of this function
VertexId determine_vertice_with_max_edges(Graph & g)
{
	// This method is written unneccessary compliceted to give a better feeling of the use of this class
	// EdgeId and GraphId are internally just the same as unsigned int's. I prefer using the aliases for 
	// better readability.
	
	unsigned int max;
	for (VertexId i = 0; i < g.num_vertices(); ++i)
	{
		// Get the i-th vertex
		Vertex & v = g.vertex(i);
		unsigned int count = 0;
		for (EdgeId e = 0;  e < v.num_edges(); ++ e)
		{
			++count;
		}
		if ( count > max)
		{
			max = count;
		}
	}
	return max;
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

std::set<VertexId> graph_scan(Graph & g, VertexId s) 
{
	std::set<VertexId> reachable_vertices{s}; 
	std::queue<VertexId> Q;
	Q.push(s);
	std::set<EdgeId> contained_edges;

	while(!Q.empty()) {
		VertexId v_id = Q.front();
		Q.pop();

		Vertex & v = g.vertex(v_id);

		for(EdgeId e_id=0; e_id < v.num_edges(); e_id++) {
			Edge e = g.edge(v.edge(e_id));
			VertexId w_id = e.other_vertex(v_id);

			if(reachable_vertices.find(w_id) == reachable_vertices.end())
			{
				reachable_vertices.insert(w_id);
				contained_edges.insert(e.id());
				Q.push(w_id);
			}
		}

	}
	
	return reachable_vertices;
}

std::map<size_t, std::vector<VertexId>> determine_connected_comps(Graph & g)
{
	std::map<size_t, std::vector<VertexId>> connected_comps;
	size_t comp_count = 0;

	std::set<VertexId> total_vertices;
	for(VertexId v=0; v < g.num_vertices(); v++)
	{
		total_vertices.insert(v);
	}	
	while(!total_vertices.empty())
	{
		std::set<VertexId>::iterator first = total_vertices.begin();
		VertexId s = *first;
		total_vertices.erase(first);
	
		std::set<VertexId> reachable_vertices = graph_scan(g, s);
		for(auto v: reachable_vertices) {
			total_vertices.erase(v);
			connected_comps[comp_count].push_back(v);
		}
		comp_count++;
	}
	
	return connected_comps;
}


int main(int argc, char *argv[])
{	
	size_t graph_no = 2;
	
	if(argc > 1) {
		try {
			graph_no = static_cast<size_t>(std::stoi(argv[1])); 
		} catch (std::exception const &e) {
			std::cout << "Failed to cast" << std::endl;
		}
	}
	std::cout << "Graph: " << graph_no << std::endl;

	std::string infile = "input/graph" + std::to_string(graph_no) + ".plain";
	Graph g(infile);
	
	//std::cout << "Max edges: " << determine_vertice_with_max_edges(g) << std::endl;
	std::map<size_t, std::vector<VertexId>> connected_comps = determine_connected_comps(g);
	//std::cout << connected_comps.size() << std::endl;

	std::ofstream fp;
	std::string outfile = "zhk/graph" + std::to_string(graph_no) + ".plain";
	fp.open(outfile);
	if(fp) {
		fp << connected_comps.size() << std::endl;
		
		for(auto elem: connected_comps)
		{
			for(auto v : elem.second)
			{
				fp << v << " ";
			}
			fp << std::endl;
		}
	} else
	{
		return 1;
	}

	return 0;
	
}
