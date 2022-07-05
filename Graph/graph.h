#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <queue>

#include "../Edge/edge.h"
#include "../Node/node.h"

using std::list;
using std::make_pair;
using std::pair;
using std::priority_queue;
using std::string;

class Node;
class Edge;

class Graph {
   public:
    Graph();
    ~Graph();

    void addCounterOfNodes();
    int getCounterOfNodes();

    void addCounterOfEdges();
    int getCounterOfEdges();

    void setFirstNode(Node *node);
    Node *getFirstNode();

    Node *getNodeIfExist(int id);
    Node *createNodeIfDoesntExist(int id, int peso);

    Edge *createEdge(Node *nodeHead, Node *tailNode, int weight);

    void outputGraph(string outputFileName, bool isWeightedGraph, bool isDirectedGraph);
    void printNodes();
    void output(string outputFileName, Node *nodes[], int cont, string textStart);
    void outputGraphSetOfNodes(string outputFileName, bool isWeightedGraph, bool isDirectedGraph, int dist, priority_queue<pair<int, int>, std::vector<pair<int, int>>, std::greater<pair<int, int>>> nodes);
    int *getAdjacents(int id, Node *nodesInvolved);
    int *getAdjacents(int id, Node *nodesInvolved[], int quantityNodesInvolved);

    void coeficienteDeAgrupamentoLocal(int idNode);
    bool checkRelationship(Node *node1, Node *node2);
    void coeficienteDeAgrupamentoMedio();

    void fechoTransitivoDireto(int id);
    void fechoTransitivoIndireto(int id);

    int *depthSearch(Node *node);
    void auxDepthSearch(Node *node, int visitedNodes[], int *counter);
    Node *searchNodePkId(int id);

    void printListAdjacents(int id);
    int *getAllAdjacents(int id, int *cont);

    void dijkstra(int idNodeOrig, int idNodeDest, bool isWeightedGraph, bool isDirectedGraph);
    int edgeCost(Node *nodeHead, Node *tailNode);

   private:
    Node *firstNode;
    int nodesTotal;
    int edgesTotal;
};

#endif