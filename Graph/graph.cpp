#include <iostream>

#include "graph.h"

using std::cout; using std::endl;

Graph::Graph() {
    firstNode = NULL;
    nodesTotal = 0;
    edgesTotal = 0;
}

void Graph::addCounterOfNodes() {
    nodesTotal++;
}

int Graph::getCounterOfNodes() {
    return nodesTotal;
}

void Graph::addCounterOfEdges() {
    edgesTotal++;
}

int Graph::getCounterOfEdges() {
    return edgesTotal;
}

void Graph::setFirstNode(Node *node){
    firstNode = node;
}

Node* Graph::getFirstNode(){
    return firstNode;
}




Node* Graph::getNodeIfExist(int id) {
    Node* node = firstNode;

    while (node->getNextNode() != NULL) {
        if (node->getId() == id){
            return node;    
        }
        
        node = node->getNextNode();
    }

    return NULL;
}

Node* Graph::createNodeIfDoesntExist(int id, int peso){
    Node* node = this->getNodeIfExist(id);

    if (node == NULL){
        Node* node = new Node(id, peso, this);
    }

    return node;
}

Edge* Graph::createEdge(Node *nodeHead, Node *tailNode, int weight){
    Edge *newEdge = new Edge(nodeHead, tailNode, weight, this);
    
    Edge *nodeFirstEdge = nodeHead->getFirstEdge();

    if (nodeFirstEdge == NULL){
        nodeHead->setFirstEdge(newEdge);
    } else {
        newEdge->setNextEdge(nodeFirstEdge);
        nodeHead->setFirstEdge(newEdge);
    }

    return newEdge;

}

void Graph::printGraph() {
    Node* node = firstNode;
    cout << "oi" << endl;

    while ( node->getNextNode() != NULL){
        Edge* edge = node->getFirstEdge();
        cout << "Node " << node->getId() << " -> ";
        while (edge->getNextEdge() != NULL ){
            cout << edge->getId() << " |";
            edge = edge->getNextEdge();
        }

        cout << " . " << endl;

        node = node->getNextNode();
    }
}
