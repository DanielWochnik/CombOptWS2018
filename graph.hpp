#ifndef DHBW_Graph_HPP
#define DHBW_Graph_HPP
#include<queue>
#include<vector>
#include<iostream>
#include<string>
#include<stddef.h>
// This file containts of three classes, namely
//  1. Vertex
//  2. Edge
//  3. Graph 
// You can read a Graph from file in the following formats
// 
// plain:
// 		<number of vertices (n)>
// 		<endpoint 0> <endpoint 0>
// 		<endpoint 1> <endpoint 1>
//     		...
// 		<endpoint m-1> <endpoint m-1>
//
// The endpoints of the vertices are determined by their id, i.e. the order they are read (starting with 0).

namespace DHBW 
{

// Forward declaration
class Graph;
class Edge;

// Typedefs to improve code quality
using EdgeId = size_t;
using VertexId = size_t;

enum class GraphInputFormat
{
	plain
};

// class Vertex 
// Represents a Vertex of the Graph, containing 
//   - id, 
//   - list of adijazant edges
//   - reference to corresponding Graph
class Vertex 
{
friend class DHBW::Graph;
public:

	// Define Construtor explicit to avoid copying of cities
	explicit Vertex(VertexId id_, Graph const & graph_);

	// Returns the number of Vertex edges i.e. the number of neighbour cities
	EdgeId num_edges() const;
	
	// Return  edge 
	EdgeId const & edge(EdgeId id) const;

	// Getter for id
	VertexId id() const;
private:
	
	// Add new Edge by id
	void add_edge(EdgeId id);

	//////////////
	// Member 
	VertexId const         _id;
	Graph const &          _graph;
	std::vector<EdgeId>    _edges;
};

// Class representing the edge between two cities
class Edge
{
	friend class DHBW::Graph;
public:
	
	// C'tor
	explicit Edge(EdgeId id_, VertexId ep1_, VertexId ep2_, Graph const & Graph_);

	VertexId const & vertex1() const;
	VertexId const & vertex2() const;
	// returns the endpoint which is not Vertex
	VertexId const & other_vertex(VertexId v) const;
	
	// checks whether this edge is adjazant with  vertex1
	bool is_adjiazent(VertexId id) const;
private:
    //////////////
	// Member 
	EdgeId _id;
	VertexId const _ep1;
	VertexId const _ep2;
	Graph const &  _graph;
};

// Class Graph
class Graph 
{
public:
	// C'tor for empty Graph
	Graph();
	
	// Construct Graph by file
	Graph(std::string const & filename, GraphInputFormat format = GraphInputFormat::plain);

	// returns Vertex by id
	Vertex const & vertex(VertexId id) const;
	Vertex & vertex(VertexId id);
	
	// returns Edge by id
	Edge const & edge(EdgeId id) const;
	Edge & edge(EdgeId id);
	
	// returns number of cities
	VertexId num_vertices() const;
	
	// returns number of Vertex edges
	EdgeId num_edges() const;
	
	// add new Vertex
	// returns the id of the new Vertex
	VertexId add_vertex();
	
	// add new edge
	// returns the id of the new edge
	EdgeId add_edge(VertexId ep1, VertexId ep2);
	
	// write graph to file
	void write_to_file(std::string const & filename, GraphInputFormat format = GraphInputFormat::plain);
	
private:
	// Read input file and create cities and edges
	void read_from_file_plain(std::string const & filename);
	
	void write_to_file_plain(std::string const & filename);


	std::vector<Vertex>     _vertices;
	std::vector<Edge> 		_edges;
	
};
	
} //namespace DHBW
#endif //DHBW_Graph_HPP