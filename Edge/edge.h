#ifndef EDGE_H
#define EDGE_H

#include <iostream>

#include "../Graph/graph.h"
#include "../Node/node.h"

class Graph;
class Node;
class Edge {
   public:
    Edge(Node *nodeHead, Node *tailNode, int weight, Graph *graph);
    ~Edge();

    void setNextEdge(Edge *nextEdge);
    Edge *getNextEdge();

    int getId();
    Node *getTailNode();

    int getWeight();
    int edgeCost(Node *nodeHead, Node *tailNode);

   private:
    int id;
    int weight;
    Node *tailNode;
    Edge *nextEdge;
};

#endif