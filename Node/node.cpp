#include <iostream>


#include "node.h"

Node::Node(int id, int peso, Graph *graph) {
    id = id;
    peso = peso;
  
    graph->addCounterOfNodes();
    pk = graph->getCounterOfNodes(); // Primary Key = ID Único

    degree = 0;
    grauIn = 0;
    grauOut = 0;
    nextNode = NULL;
    nextEdge = NULL;

}

void Node::addNode(Node *node, Edge *edge, Graph *graph) {
    
    nextNode = node;
    nextEdge = edge;

    degree++;

    grauIn++;  
    grauOut++;  
}

int Node::getPkId(){
    return pk;
}

Node* Node::getNextNode(){
    return nextNode;
}

int Node::getId(){
    return id;
}

Edge* Node::getFirstEdge(){
    return nextEdge;
}

void Node::setFirstEdge(Edge *nextEdge){
    nextEdge = nextEdge;
}