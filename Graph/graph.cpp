#include <iostream>

#include "graph.h"

using std::cout; 
using std::endl;

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

    if (node == 0) return 0;

    while (node->getNextNode() != 0) {


        if (node->getId() == id){
            return node;    
        }
        
        node = node->getNextNode();
    } 

}

Node* Graph::createNodeIfDoesntExist(int id, int peso){
    Node* node = this->getNodeIfExist(id);

    if (node == 0){        

        Node* newNode = new Node(id, peso, this);      
        Node* oldFirstNode = firstNode;
        newNode->setNextNode(oldFirstNode);
        setFirstNode(newNode);

        return newNode;
    } 

    return node;
}

Edge* Graph::createEdge(Node *nodeHead, Node *tailNode, int weight){
    Edge *newEdge = new Edge(nodeHead, tailNode, weight, this);

    Edge *nodeFirstEdge = nodeHead->getFirstEdge();

    if (nodeFirstEdge == 0){
        nodeHead->setFirstEdge(newEdge);
    } else {
        newEdge->setNextEdge(nodeFirstEdge);
        nodeHead->setFirstEdge(newEdge);
    }

    return newEdge;

}

void Graph::printGraph() {
    int cont = 0;
    Node* node = firstNode;

    while ( node->getNextNode() != 0) {
        cont++;
        Edge* edge = node->getFirstEdge();

        cout << cont << " - Node " << node->getId() << " -> ";

        while (edge->getNextEdge() != 0 ) {
            // Id da Aresta (Linha do arquivo em que a aresta é criada)
            cout << edge->getId() << " | ";
            edge = edge->getNextEdge();
        } 

        cout << " . " << endl;
        node = node->getNextNode();

    } 
}

void Graph::printNodes() {
    Node* node = firstNode;
    int cont = 0;

    while ( node->getNextNode() != 0) {
        cont++;
        cout << cont << " - Node " << node->getId() << endl;
        node = node->getNextNode();

    }
}
