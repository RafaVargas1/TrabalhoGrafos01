#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

#include "../Edge/edge.h"
#include "../Node/node.h"

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

    int coeficienteDeAgrupamentoLocal(int nodeId);

    void fechoTransitivoDireto(int id);
    int *depthSearch(Node *node);
    void auxDepthSearch(Node *node, int visitedNodes[], int *counter);
    Node *searchNodePkId(int id);
    void getAllAdjacents(int id);

   private:
    Node *firstNode;
    int nodesTotal;
    int edgesTotal;
};

#endif