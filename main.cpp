#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <cfloat>
#include "Graph.h"

using namespace std;

bool* initVisited(int size) {
    bool* visited = new bool[size];
    for (int i = 0; i < size; i++)
        visited[i] = false;
    return visited;
}

int* initBackTrack(int size) {
    int* backTrack = new int[size];
    for (int i = 0; i < size; i++)
        backTrack[i] = -1;
    return backTrack;
}

int* createBackTrackFromNode(const Graph *graph, int source) {
    int graphSize = graph->get_verticies_count(); //Number of verticiies
    bool* visited = initVisited(graphSize);
    int* backTrack = initBackTrack(graphSize);

    queue<int> queue; //Queue of verticies not visited
    queue.push(source);  //Initialising the queue
    visited[source] = true;

    while (!queue.empty()) {
        int currentNode = queue.front();
        queue.pop();
        for (int destination = 0; destination < graphSize; destination++) {
            double currentPath = graph->get_edge(currentNode, destination);
            if (!visited[destination] && currentPath > 0.f) {
                queue.push(destination);
                visited[destination] = true;
                backTrack[destination] = currentNode;
            }
        }
    }
    delete visited;
    return backTrack;
}

stack<int>* breathFirstSearch(const Graph *graph, int source, int destination) {
    int* backtrack = createBackTrackFromNode(graph, source);

    stack<int>* reversePath = new stack<int>();
    while(backtrack[destination] != -1) {
        reversePath->push(destination);
        destination = backtrack[destination];
    }

    delete backtrack;
    return reversePath;
}


double* initialiseDistances(Graph* graph, int source) {
    double* initialDistances = new double[graph->get_verticies_count()];
    for (int i = 0; i < graph->get_verticies_count(); i++) {
        double distanceFromSource = graph->get_edge(source, i);
        initialDistances[i] = (distanceFromSource > 0.f) ?
                              distanceFromSource : DBL_MAX;
    }
    return initialDistances;
}

set<int>* initSortingSet(int graphSize, int source) {
    set<int>* sortingSet = new set<int>();
      for (int i = 0; i < graphSize; i++)
        if (i != source) sortingSet->insert(i);
    return sortingSet;
}

int* initialiseDijkstraBackTrack(int graphSize, int source) {
    int* backTrack = new int[graphSize];
    for (int i = 0; i < graphSize; i++)
        backTrack[i] = (i == source) ? -1 : source;
    return backTrack;
}

int* dijkstraBackTrack(Graph* graph, int source) {
    int graphSize = graph->get_verticies_count();
    set<int>* nodeSortingSet = initSortingSet(graphSize, source);

    double* nodeDistances = initialiseDistances(graph, source);
    int* backtrack = initialiseDijkstraBackTrack(graphSize, source);

    while (!nodeSortingSet->empty()) {
        double minDistance = DBL_MAX;
        int shortestNode = -1;

        for (set<int>::iterator iterator = nodeSortingSet->begin(); iterator != nodeSortingSet->end(); iterator++) {
            int currentNode = *iterator;
            if (nodeDistances[currentNode] < minDistance) {
                minDistance = nodeDistances[currentNode];
                shortestNode = currentNode;
            }
        }

        nodeSortingSet->erase(shortestNode); //Remove the shortest node from the set

        for (set<int>::iterator iterator = nodeSortingSet->begin(); iterator != nodeSortingSet->end(); iterator++) {
            int edgeEnd = *iterator;
            double currentEdge = graph->get_edge(shortestNode, edgeEnd);
            if (currentEdge != 0.f) {
                double totalDistance = nodeDistances[shortestNode] + currentEdge;
                if (totalDistance < nodeDistances[edgeEnd]) {
                    nodeDistances[edgeEnd] = totalDistance;
                    backtrack[edgeEnd] = shortestNode;
                }
            }
        }
    }

    delete nodeDistances;
    delete nodeSortingSet;

    return backtrack;
}

stack<int>* dijkstrasShortestPath(Graph* graph, int source, int destination) {
    int *backtrack = dijkstraBackTrack(graph, source);
    stack<int>* reversePath = new stack<int>();

    while(backtrack[destination] != -1) {
        reversePath->push(destination);
        destination = backtrack[destination];
    }

    delete backtrack;
    return reversePath;
}

int main() {
    char *path1 = ".../graph2.txt";
    Graph *graph1 = new Graph(path1);
    stack<int> *shortestPathBreathFirst = breathFirstSearch(graph1, 0, 12);

    while (!shortestPathBreathFirst->empty()) {
        cout << shortestPathBreathFirst->top() << "  ";
        shortestPathBreathFirst->pop();
    } cout << endl;


    char *path2 = ".../graph3.txt";
    Graph *graph2 = new Graph(path2);

    stack<int> *shortestPathDijkstra = dijkstrasShortestPath(graph2, 0, 4);
    while (!shortestPathDijkstra->empty()) {
        cout << shortestPathDijkstra->top() << "  ";
        shortestPathDijkstra->pop();
    } cout << endl;



    delete graph1;
    delete graph2;
    delete shortestPathBreathFirst;
    delete shortestPathDijkstra;
    return 0;
}