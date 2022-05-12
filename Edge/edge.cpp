#include <iostream>

#include "edge.h"

Edge::Edge(Node *nodeHead, Node *tailNode, int weight, Graph *graph) {
    graph->addCounterOfEdges();
    id = graph->getCounterOfEdges();   
    
    tailNode = tailNode;
    weight = weight;
    nextEdge = NULL;
}


void Edge::setNextEdge(Edge* nextEdge){
    nextEdge = nextEdge;
}

Edge* Edge::getNextEdge() {
    return nextEdge;
}

int Edge::getId(){
    return id;
}

// void Edge::createEdgeIfDoesntExist(Node *nodeHead, Node *nodeTail, int weight, Graph *graph){
    // Assumindo que nao é problema criar varias aresta entre os mesmos nos
    // Caso seja problema, tem que fazer um doesEdgeExist passando nodeHead e nodeTail     
// }

// bool Edge::doesEdgeExist(Node *nodeHead, Node *nodeTail){
// }