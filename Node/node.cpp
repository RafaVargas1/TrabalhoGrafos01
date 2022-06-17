#include <iostream>

#include "node.h"

Node::Node(int id, int peso, Graph *graph) {
    this->id = id;
    this->peso = peso;
  
    graph->addCounterOfNodes();
    pk = graph->getCounterOfNodes(); // Primary Key = ID Único

    degreeIn = 0;
    degreeOut = 0;
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

void Node::incrementDegreeOut(){
    this->degreeOut++;
}

void Node::incrementDegreeIn(){
    this->degreeIn++;
}

int Node::getGrauIn(){
    return this->degreeIn;
}

int Node::getGrauOut(){
    return this->degreeOut;
}

bool Node::isInArray(Node* array[], int arraySize){
    for (int i=0; i < arraySize; i++){
        if (array[i] = this) {
            return true;
        }
    }

    return false;
}