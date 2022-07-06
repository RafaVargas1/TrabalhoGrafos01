#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <queue>
#include <vector>

#include "../Edge/edge.h"
#include "../Node/node.h"

using std::list;
using std::make_pair;
using std::pair;
using std::priority_queue;
using std::string;
using std::vector;

class Node;
class Edge;

class Graph {
   public:
    Graph(bool directed, bool weighted);
    ~Graph();

    void addCounterOfNodes();
    int getCounterOfNodes();

    void addCounterOfEdges();
    int getCounterOfEdges();

    void setFirstNode(Node *node);
    Node *getFirstNode();

    bool getWeighted();
    bool getDirected();

    Node *getNodeIfExist(int id);
    Node *createNodeIfDoesntExist(int id, int peso);

    Edge *createEdge(Node *nodeHead, Node *tailNode, int weight);

    void outputGraph(string outputFileName);
    void printNodes();
    void output(string outputFileName, Node *nodes[], int cont, string textStart);
    void outputGraphSetOfNodes(string outputFileName, std::queue<pair<int, int>> nodes);
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

    void dijkstra(int idNodeOrig, int idNodeDest);
    int edgeCost(Node *nodeHead, Node *tailNode);

    void floyd(int idNodeOrig, int idNodeDest);

    void treeDeepthSearch(Node *node);
    void auxTreeDeepthSearch(Node *node, vector<Node *> &visitedNodes, vector<Edge *> &mainTreeEdge, vector<Edge *> &returnTreeEdge);

    void outputEdgeInducedSubgraph(string outputFileName, vector<Edge *> &subgraph);

   private:
    Node *firstNode;
    int nodesTotal;
    int edgesTotal;
    bool weighted;
    bool directed;
};

#endif