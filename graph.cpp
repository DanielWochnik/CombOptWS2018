#include "graph.hpp"
#include <cassert>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

namespace DHBW 
{

//////////////////////////////////////
/// class Vertex

EdgeId Vertex::num_edges() const
{
	return _edges.size();
}

EdgeId const & Vertex::edge(EdgeId id) const
{
	assert(id < num_edges());
	return _edges[id];
}

VertexId Vertex::id() const
{	
	return _id;
}

Vertex::Vertex(VertexId id_, Graph & graph_)
:	
	_id(id_),
	_graph(graph_)
{}
	
void Vertex::add_edge(EdgeId id, VertexId to)
{
	assert(_graph.edge(id).vertex1() == this->id() or _graph.edge(id).vertex2() == this->id());
	_edges.push_back(id);
	gamma_plus.push_back(to);
	_graph.vertex(to).gamma_minus.push_back(_id);
}

//////////////////////////////////////
/// class Edge

VertexId const & Edge::vertex1() const
{
	return _ep1;
}

VertexId const & Edge::vertex2() const
{
	return _ep2;
}


VertexId const & Edge::other_vertex(VertexId v) const
{
	assert(is_adjiazent(v));
	if (v == vertex1())
	{
		return vertex2();
	}
	else 
	{
		return vertex1();
	}
}

bool Edge::is_adjiazent(VertexId id) const
{
	return (id == _ep1 or id == _ep2);
}

Edge::Edge(EdgeId id_, VertexId ep1_, VertexId ep2_, Graph const & graph_)
:
	_graph(graph_),
	_id(id_),
	_ep1(ep1_),
	_ep2(ep2_)
{
	assert(_id >= 0);
	assert(_ep1 < _graph.num_vertices() and _ep2 < _graph.num_vertices());
}

EdgeId Edge::id() const
{
	return _id;
}

//////////////////////////////////////
/// class Graph
Vertex const & Graph::vertex(VertexId id) const
{
	assert(id < num_vertices());
	return _vertices[id];
}

Vertex & Graph::vertex(VertexId id)
{
	return const_cast<Vertex&>(static_cast<Graph const*>(this)->vertex(id));
}

Edge const & Graph::edge(EdgeId id) const
{
	assert(id < num_edges());
	return _edges[id];
}

Edge & Graph::edge(EdgeId id)
{
	// return const_cast<Edge&>(static_cast<Graph const*>(this)->edge(id));
	assert(id < num_edges());
	return _edges[id];
}

VertexId Graph::num_vertices() const
{
	return _vertices.size();
}

EdgeId Graph::num_edges() const
{
	return _edges.size();
}

VertexId Graph::add_vertex()
{
	_vertices.emplace_back(num_vertices(),*this);
	return num_vertices()-1;
}

EdgeId Graph::add_edge(VertexId ep1, VertexId ep2)
{
	_edges.emplace_back(num_edges(),ep1,ep2,*this);
	vertex(ep1).add_edge(num_edges()-1, ep2);
	vertex(ep2).add_edge(num_edges()-1, ep1);

	return num_edges()-1;
}

Graph::Graph()
:
	_vertices(),
	_edges()
{}

Graph::Graph(std::string const & filename,GraphInputFormat format)
:
	_vertices(),
	_edges()
{
	switch (format)
	{
		case GraphInputFormat::plain: read_from_file_plain(filename); break;
	}
}

void Graph::read_from_file_plain(std::string const & filename)
{
	assert(_vertices.empty() and _edges.empty());
	std::ifstream infile(filename.c_str());
	assert(infile.good());
	std::string line;
	
	//Read first line, i.e. the number of vertices
	size_t num_vertices;
	{
		std::getline(infile, line);
		std::istringstream iss(line);
		iss >> num_vertices;
		assert(not iss.fail());
	}
	
	// Add vertices
	_vertices.reserve(num_vertices);
	for(size_t i = 0; i < num_vertices; ++i)
	{
		add_vertex();
	}	

	// Read and add edges
	while(std::getline(infile,line))
	{
		size_t a,b;
		std::istringstream iss(line);
		iss >> a >> b; 
		assert(not iss.fail());
		add_edge(VertexId(a),VertexId(b));
	}
}

void Graph::write_to_file(std::string const & filename, GraphInputFormat format)
{
	switch (format)
	{
		case GraphInputFormat::plain: write_to_file_plain(filename); break;
	}
}

void Graph::write_to_file_plain(std::string const & filename)
{
	std::ofstream outfile(filename.c_str());
	
	// Write cities
	outfile << num_vertices();
	
	// Write edges
	for (Edge const & edge : _edges)
	{
		outfile << "\n" << edge.vertex1() << " " << edge.vertex2();
	}
}

EdgeId Digraph::add_edge(VertexId ep1, VertexId ep2)
{	
	_edges.emplace_back(num_edges(), ep1, ep2, *this);
	vertex(ep1).add_edge(num_edges()-1, ep2);
	
	return num_edges()-1;
}


	
} // namespace DHBW
