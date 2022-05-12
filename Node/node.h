#ifndef NODE_H
#define NODE_H

#include <iostream> 

#include "../Edge/edge.h"
#include "../Graph/graph.h"

class Edge;
class Graph;
class Node {
    public: 
        Node(int id, int peso, Graph *graph);
        ~Node();

        void addNode(Node* node, Edge* edge, Graph* graph);
        int getPkId();
        int getId();

        Node* getNextNode();
        void setNextNode(Node *node);

        Edge* getFirstEdge();
        void setFirstEdge(Edge *firstEdge);

    private:
        int pk; // Primary Key = ID Único 
        int id;
        int degree;
        int peso;
        int grauIn;
        int grauOut;
        Node *nextNode;
        Edge *firstEdge;
};

#endif 