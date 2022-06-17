#ifndef NODE_H
#define NODE_H

#include <iostream>

#include "../Edge/edge.h"
#include "../Graph/graph.h"

class Edge;
class Graph;
class Node {
    /*
    Id: não pode repetir -> a partir do contador incrementado
    Pk: a partir da entrada do txt -> sem repetir
    */
   public:
    Node(int id, int peso, Graph* graph);
    ~Node();

    void addNode(Node* node, Edge* edge, Graph* graph);
    int getPkId();
    int getId();

    Node* getNextNode();
    void setNextNode(Node* node);

    Edge* getFirstEdge();
    void setFirstEdge(Edge* firstEdge);

    void incrementDegreeOut();
    void incrementDegreeIn();

    int getGrauIn();
    int getGrauOut();

    bool isInArray(Node* array[], int arraySize);

   private:
    int pk;  // Primary Key = ID Único
    int id;
    int peso;
    int degreeIn;
    int degreeOut;
    Node* nextNode;
    Edge* firstEdge;
};

#endif