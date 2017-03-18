#ifndef PRACTICAL_13_GRAPH_H
#define PRACTICAL_13_GRAPH_H

class Graph {
public:
    //constructor - create a graph from a file with the given name
    Graph(char* fileName);

    //destructor
    ~Graph();

    //Return the number of vertices
    int get_vertices_count() const { return verticies_count; }

    //return the weight between a source & destination
    //Weight of 0.0 means no edge
    double get_edge(int source, int destination) const;

private:
    int verticies_count;
    bool directed;

    //2-D matrix showing edges from vertices_count vertices to vertices_count vertices
    double** edges;
};

#endif //PRACTICAL_13_GRAPH_H
