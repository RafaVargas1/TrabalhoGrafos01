#include <iostream>

#include "node.h"

Node::Node(int id, int peso, Graph *graph) {
    this->id = id;
    this->peso = peso;
  
    graph->addCounterOfNodes();
    pk = graph->getCounterOfNodes(); // Primary Key = ID Único

    grauIn = 0;
    grauOut = 0;
    nextNode = nullptr;
    firstEdge= nullptr;

}

int Node::getPkId(){
    return pk;
}

Node* Node::getNextNode(){
    return nextNode;

}
void Node::setNextNode(Node *node){
    this->nextNode = node;
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

