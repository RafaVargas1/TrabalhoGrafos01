#ifndef EDGE_H
#define EDGE_H

#include <iostream> 
#include "../Node/node.h"


class Graph;
class Node;
class Edge {
    public: 
        Edge(Node *nodeHead, Node *tailNode, int weight, Graph *graph);
        void createEdge(Node *nodeHead, Node *tailNode, int weight, Graph *graph);
        void setNextEdge(Edge* nextEdge);
        Edge* getNextEdge();
        int getId();

    private:
        int id;
        int weight;        
        Node *tailNode;
        Edge *nextEdge;   
};

 #endif