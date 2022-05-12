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
        Node* createNodeIfDoesntExist(int id, int peso, Graph *graph);

        Edge* getFirstEdge();
        void setFirstEdge(Edge *nextEdge);

    private:
        int pk; // Primary Key = ID Único 
        int id;
        int degree;
        int peso;
        int grauIn;
        int grauOut;
        Node *nextNode;
        Edge *nextEdge;


};

#endif 