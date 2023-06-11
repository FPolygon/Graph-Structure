/*The provided header file implements a graph data structure using an adjacency list representation. The graph class is a templated class that allows for the storage and manipulation of vertices and edges. Vertices are stored in a vector, while the adjacency list is implemented as an unordered map, associating each vertex with a vector of pairs representing its neighboring vertices and the corresponding edge weights. The class provides functions to add vertices and edges, retrieve edge weights, and obtain information about the graph such as the number of vertices and edges. It also supports operations like finding neighbors of a vertex and obtaining a list of all vertices in the graph. The dump function allows for the printing of the graph's internal state for debugging purposes. Overall, this graph implementation provides a flexible and efficient way to represent and work with graphs in C++*/

#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <utility>
#include <unordered_map>

using namespace std;

template<typename VertexT, typename WeightT>
class graph {
 private:
  unordered_map<VertexT, vector<pair<VertexT, WeightT> > > adjList;
  vector<VertexT>  Vertices;

  //
  // _LookupVertex
  //
  // Finds the vertex in the Vertices vector and returns it's
  // index position if found, otherwise returns -1.
  //
  int _LookupVertex(VertexT v) const {
    for (int i = 0; i < this->NumVertices(); ++i) {
      if (this->Vertices[i] == v)  // already in the graph:
        return i;
    }

    // if get here, not found:
    return -1;
  }

 public:
  //
  // constructor:
  //
  // Constructs an empty graph where n is the max # of vertices
  // you expect the graph to contain.
  //
  // NOTE: the graph is implemented using an adjacency matrix.
  // If n exceeds the dimensions of this matrix, an exception
  // will be thrown to let you know that this implementation
  // will not suffice.
  //
  graph() {}

  graph(int numVertices) {
  }

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const {
    return static_cast<int>(this->Vertices.size());
  }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const {
    int count = 0;
    for (auto keyVertex : this->adjList) {   // Loop through each vertex
      count += keyVertex.second.size();
    }
    return count;
  }

  //
  // addVertex
  //
  // Adds the vertex v to the graph if there's room, and if so
  // returns true.  If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(VertexT v) {
    // is the vertex already in the graph?  If so, we do not
    // insert again otherwise Vertices may fill with duplicates:
    //
    for (auto i : this->Vertices) {
      if (i == v) {
        return false;
      }
    }

    //
    // if we get here, vertex does not exist so insert.  Where
    // we insert becomes the rows and col position for this
    // vertex in the adjacency matrix.
    //
    this->Vertices.push_back(v);
    return true;
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist or for some reason the
  // graph is full, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(VertexT from, VertexT to, WeightT weight) {
    //
    // we need to search the Vertices and find the position
    // of each vertex; this will denote the row and col to
    // access in the adjacency matrix:
    //

    // If either vertices are not found return false
    if (_LookupVertex(from) < 0 || _LookupVertex(to) < 0) {
      return false;
    }
    for (auto& edgeVector : adjList[from]) {
      if (edgeVector.first == to) {
        edgeVector.second = weight;
        return true;
      }
    }
    pair<VertexT, WeightT> newEdge(to, weight);
    adjList[from].push_back(newEdge);
    return true;
  }

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(VertexT from, VertexT to, WeightT& weight) const {
    // If either verticies are not found return false
    if (_LookupVertex(from) < 0 || _LookupVertex(to) < 0) {
      return false;
    }

    //
    // the vertices exist, but does the edge exist?
    //
    vector<pair<VertexT, WeightT> > targetVertex = adjList.at(from);
    for (auto& edge : targetVertex) {
      if (edge.first == to) {
        weight = edge.second;
        return true;
      }
    }
    return false;
  }


  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const {
    set<VertexT>  S;

    //
    // we need to search the Vertices and find the position
    // of v, that will be the row we need in the adjacency
    // matrix:
    //

    if (_LookupVertex(v) < 0) {
      return S;
    }
    vector<pair<VertexT, WeightT> > targetVector = this->adjList.at(v);
    for (auto key : targetVector) {
      S.insert(key.first);
    }
    return S;
  }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const {
    return this->Vertices;  // returns a copy:
  }

  //
  // dump
  //
  // Dumps the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void dump(ostream& output) const {
    for (auto vertice : this->adjList) {
      cout << vertice.first << ": ";
      for (auto vector : vertice.second) {
        cout << "(" << vertice.first << "," << vector.first << "," << vector.second << ") ";
      }
      cout << endl;
    }
  }
};
