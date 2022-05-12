#include <iostream>

#include "node.h"

Node::Node(int id, int peso, Graph *graph) {
    this->id = id;
    this->peso = peso;
  
    graph->addCounterOfNodes();
    pk = graph->getCounterOfNodes(); // Primary Key = ID Único

    degree = 0;
    grauIn = 0;
    grauOut = 0;
    nextNode = NULL;
    firstEdge= NULL;

}

void Node::addNode(Node *node, Edge *edge, Graph *graph) {
    
    nextNode = node;
    firstEdge = edge;

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
void Node::setNextNode(Node *node){
    nextNode = node;
}

int Node::getId(){
    return id;
}

Edge* Node::getFirstEdge(){
    return firstEdge;
}

void Node::setFirstEdge(Edge *firstEdge){
    this->firstEdge = firstEdge;
}

