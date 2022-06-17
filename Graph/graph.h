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

    void treeDeepthSearch();
    void auxTreeDeepthSearch(Node* node,  Graph *searchTree);


   private:
    Node *firstNode;
    int nodesTotal;
    int edgesTotal;
};

#endif