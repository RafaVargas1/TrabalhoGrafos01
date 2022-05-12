#include <iostream>

#include "edge.h"

Edge::Edge(Node *nodeHead, Node *tailNode, int weight, Graph *graph) {
    tailNode = tailNode;
    weight = weight;
    nextEdge = NULL;

    graph->addCounterOfEdges();
    id = graph->getCounterOfEdges();
}



void Edge::setNextEdge(Edge* nextEdge){
    this->nextEdge = nextEdge;
}

Edge* Edge::getNextEdge() {
    return nextEdge;
}

int Edge::getId(){
    return id;
}