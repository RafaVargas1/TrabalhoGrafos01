#ifndef EDGE_H
#define EDGE_H

#include <iostream> 

#include "../Node/node.h"
#include "../Graph/graph.h"

class Graph;
class Node;
class Edge {
    public: 
        Edge(Node *nodeHead, Node *tailNode, int weight, Graph *graph); 
        ~Edge();   

        void setNextEdge(Edge* nextEdge);
        Edge* getNextEdge();
       
        int getId();
        Node* getTailNode();

        int getWeight();
        
    private:
        int id;
        int weight;        
        Node *tailNode;
        Edge *nextEdge;   
};

 #endif