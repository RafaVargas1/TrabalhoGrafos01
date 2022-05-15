#include <iostream>

#include "graph.h"

using std::cout; 
using std::endl;
using std::fstream;
using std::string;

Graph::Graph() {
    firstNode = nullptr;
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

    if (node == nullptr) return nullptr;

    while (node->getNextNode() != nullptr) {


        if (node->getId() == id){
            return node;    
        }
        
        node = node->getNextNode();
    } 

}

Node* Graph::createNodeIfDoesntExist(int id, int peso){
    Node* node = this->getNodeIfExist(id);

    if (node == nullptr){        

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

    if (nodeFirstEdge == nullptr){
        nodeHead->setFirstEdge(newEdge);
    } else {
        newEdge->setNextEdge(nodeFirstEdge);
        nodeHead->setFirstEdge(newEdge);
    }

    return newEdge;

}

void Graph::outputGraph(string outputFileName) {
    Node* node = this->firstNode;

    FILE *outfile = fopen(outputFileName.c_str(), "w+");
    string title = "graph NovoGrapho { \n";
    fwrite(title.c_str(), 1, title.size(), outfile);

    while (node != nullptr) {    
        Edge* edge = node->getFirstEdge();
  
        while (edge != nullptr) {        
            // Id da Aresta (Linha do arquivo em que a aresta é criada)
        
            string nodeBase = std::to_string(node->getId());
            string nodeLinked = std::to_string((edge->getTailNode())->getId());
            string dotNotation = string(nodeBase) + "--" + string(nodeLinked) + ";\n";
            
            fwrite(dotNotation.c_str(), 1, dotNotation.size(), outfile);
            
            edge = edge->getNextEdge();   
        }        
      
        node = node->getNextNode();
    };

    string end = "}";

    fwrite(end.c_str(), 1, end.size(), outfile);

    cout << "O arquivo " << outputFileName << " foi gerado com sucesso.";

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
