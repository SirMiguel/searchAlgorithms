#include "Graph.h"
#include <fstream>
#include <iostream>

using namespace std;



Graph::Graph(char *fileName) {
    std::ifstream fileIn(fileName);
    //ifstream fileIn(fileName);

    if (!fileIn) {
        cout << "Cannot open the file: " << fileName << endl;
        exit(0);
    } else {
        fileIn >> verticies_count;
        char c;
        fileIn >> c;

        if (c == 'd') directed = true;
        else if (c == 'u') directed = false;
        else {
            cout << "Error in reading graph type" << endl
                 << c << " is not a valid type of graph declaration" << endl;
            exit(0);
        }

        //Initialising graph to it's side and setting all edges to a weight of 0
        edges = new double*[verticies_count];
        for (int i = 0; i < verticies_count; i++) {
            if(c=='d') {
                edges[i] = new double[verticies_count];
                for (int j = 0; j < verticies_count; j++)
                    edges[i][j] = 0.f;
            }
            else if(c=='u') {
                edges[i] = new double[i+1];
                for(int j = 0; j < i + 1; j++) edges[i][j]= 0.;
            }
        }


        int source, destination; double weight;
        while (fileIn >> source >> destination >> weight) {
            if (!directed && destination > source) edges[destination][source] = weight;
            else edges[source][destination] = weight;
        }
        fileIn.close();
    }
}

Graph::~Graph() {
    for (int i = 0; i < verticies_count; i++)
        delete [] edges[i];

    delete [] edges;
}

double Graph::get_edge(int source, int destination) const {
    if (!directed && destination > source) return edges[destination][source];
    return edges[source][destination];
}

