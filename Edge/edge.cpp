#include "edge.h"

#include <iostream>

Edge::Edge(Node *nodeHead, Node *tailNode, int weight, Graph *graph) {
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

int Edge::getWeight() {
    return this->weight;
}
