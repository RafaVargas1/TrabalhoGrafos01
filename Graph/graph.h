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
    Graph(bool isDirected, bool hasWeightedEdge, bool hasWeightedNodes);
    ~Graph();

    void addCounterOfNodes();
    int getCounterOfNodes();

    void addCounterOfEdges();
    int getCounterOfEdges();

    void setFirstNode(Node *node);
    Node *getFirstNode();

    bool isEdgeWeighted();
    bool isNodeWeighted();
    bool getDirected();

    int *getAllAdjacents(int id, int *cont);
    Node *getNodeIfExist(int id);
    Node *getNodePkId(int id);

    Node *createNodeIfDoesntExist(int id, int peso);
    Edge *createEdge(Node *nodeHead, Node *tailNode, int weight);

    void outputGraph(string outputFileName);
    void outputNodes(string outputFileName, Node *nodes[], int cont, string textStart);
    void outputGraphSetOfNodes(string outputFileName, std::queue<int> nodes);
    void outputEdgeInducedSubgraph(string outputFileName, vector<Edge *> &searchTree, vector<Edge *> &returnEdges);
    void printListAdjacents(int id);
    void printNodes();

    void coeficienteDeAgrupamentoLocal(int idNode);
    bool checkRelationship(Node *node1, Node *node2);
    void coeficienteDeAgrupamentoMedio();

    void fechoTransitivoDireto(int id);
    void fechoTransitivoIndireto(int id);

    void floyd(int idNodeOrig, int idNodeDest);
    void dijkstra(int idNodeOrig, int idNodeDest);
    int edgeCost(Node *nodeHead, Node *tailNode);

    int *depthSearch(Node *node);
    void auxDepthSearch(Node *node, int visitedNodes[], int *counter);
    void treeDeepthSearch(Node *node, string outputFileName);
    void auxTreeDeepthSearch(Node *node, vector<Node *> &visitedNodes, vector<Edge *> &mainTreeEdge, vector<Edge *> &returnTreeEdge);

    void kruskal(string outputFileName);
    vector<Edge*> edgesMergeSort(vector<Edge*>& edgesToBeMerged);

    bool isNodeInGraph(Node* searchedNode);
    Edge* insertEdge(Edge* edge);
    Node* insertNode(Node* node);

    void prim(string outputFileName);
    void auxPrim (vector<Edge*> listOfAdjacents, Node* nodeBase, Graph* primGraph, vector<Node*> visitedNodes);

   private:
    Node *firstNode;
    int nodesTotal;
    int edgesTotal;
    bool hasWeightedEdges;
    bool directed;
    bool hasWeightedNodes;
    vector<Edge*> vectorOfEdges;
};

#endif