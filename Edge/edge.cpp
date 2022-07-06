#include "edge.h"

#include <iostream>

//Edge::Edge(Node *nodeHead, Node *tailNode, int weight, Graph *graph) {

Edge::Edge(Node *headNode, Node *tailNode, int weight, Graph *graph) {
    this->headNode = headNode;
    this->tailNode = tailNode;
    this->weight = weight;
    this->nextEdge = nullptr;

    graph->addCounterOfEdges();
    this->id = graph->getCounterOfEdges();
}

void Edge::setNextEdge(Edge *nextEdge) {
    this->nextEdge = nextEdge;
}

Edge *Edge::getNextEdge() {
    return nextEdge;
}

int Edge::getId() {
    return id;
}

Node *Edge::getTailNode() {
    return tailNode;
}

Node* Edge::getHeadNode(){
    return headNode;
}

int Edge::getWeight() {
    return this->weight;
}
