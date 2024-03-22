#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <Dijkstra.h>

using namespace std;

int main() {
    // Parse the DIMACS format graph file
    ifstream graphFile("florida.dimacs");
    // Skip header lines
    string line;
    while (getline(graphFile, line) && line.substr(0, 2) != "p");

    // Extract number of nodes and edges
    int numNodes, numEdges;
    string problemType;
    graphFile >> problemType >> numNodes >> numEdges;

    // Assuming Dijkstra's algorithm implementation is provided in Dijkstra.h
    Dijkstra dijkstra(numNodes, numEdges);

    // Parse edge descriptors
    int u, v, w;
    while (graphFile >> line >> u >> v >> w) {
        dijkstra.addEdge(u - 1, v - 1, w); // Adjust node labels for custom binary format
    }

    // Generate 200 random source-destination pairs
    srand(time(nullptr));
    const int numPairs = 200;
    vector<pair<int, int>> randomPairs;
    for (int i = 0; i < numPairs; ++i) {
        randomPairs.emplace_back(rand() % numNodes, rand() % numNodes);
    }

    // Measure runtime for 200 random Dijkstra's executions
    clock_t start = clock();
    for (const auto& pair : randomPairs) {
        dijkstra.run(pair.first, pair.second);
    }
    clock_t end = clock();
    double totalRuntime = double(end - start) / CLOCKS_PER_SEC;

    // Output total runtime in seconds
    cout << "Total runtime in seconds for 200 random Dijkstra: " << totalRuntime << endl;

    return 0;
}
