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

void visit1(Graph & g, VertexId v_id, std::set<VertexId> & reached, size_t & n, std::map<size_t, VertexId> & psi_inv)
{
	reached.insert(v_id);
	Vertex v = g.vertex(v_id);
	for(auto w_id: v.gamma_plus)
	{
		if(reached.find(w_id) == reached.end())
		{
			visit1(g, w_id, reached, n, psi_inv);
		}
	}
	n++;
	psi_inv[n] = v_id;
}

void visit2(Graph & g, VertexId v_id, std::set<VertexId> & reached, size_t & k, std::map<size_t, std::vector<VertexId>> & comp_inv)
{
	reached.insert(v_id);
	Vertex v = g.vertex(v_id);
	for(auto w_id: v.gamma_minus)
	{
		if(reached.find(w_id) == reached.end())
		{
			visit2(g, w_id, reached, k, comp_inv);
		}
	}

	comp_inv[k].push_back(v_id);
}

std::map<size_t, std::vector<VertexId>> tarjan(Graph & g)
{
	std::set<VertexId> reached;
	size_t n = 0;
	std::map<size_t, VertexId> psi_inv;

	for(VertexId v_id = 0; v_id < g.num_vertices(); v_id++)
	{
		if(reached.find(v_id) == reached.end())
		{
			visit1(g, v_id, reached, n, psi_inv);
		}
	}
	

	reached.clear();
	size_t k = 0;
	std::map<size_t, std::vector<VertexId>> comp_inv;

	for(size_t n_id = g.num_vertices(); n_id >= 1; n_id--)
	{
		VertexId v_id = psi_inv[n_id];
		if(reached.find(v_id) == reached.end())
		{
			k++;
			visit2(g, v_id, reached, k, comp_inv);
		}
	}

	return comp_inv;
};

void write_zhk_graph(Graph & g, size_t graph_no)
{	
	std::map<size_t, std::vector<VertexId>> connected_comps = determine_connected_comps(g);

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
	}	
}

void write_zhk_digraph(Digraph & g, size_t graph_no)
{
	std::map<size_t, std::vector<VertexId>> connected_comps = tarjan(g);

	std::ofstream fp;
	std::string outfile = "zhk/digraph" + std::to_string(graph_no) + ".plain";
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
	}	
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
	write_zhk_graph(g, graph_no);

	std::cout << "Digraph: " << graph_no << std::endl;
	infile = "input/digraph" + std::to_string(graph_no) + ".plain";
	Digraph dig;
	dig.read_from_file_plain(infile);
	write_zhk_digraph(dig, graph_no);

	return 0;
	
}
