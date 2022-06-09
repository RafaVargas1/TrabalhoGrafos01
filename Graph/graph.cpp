#include "graph.h"

#include <iostream>

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

void Graph::setFirstNode(Node* node) {
    firstNode = node;
}

Node* Graph::getFirstNode() {
    return firstNode;
}

/*
 * Função que encontra um nó já existente no grafo através de seu id
 *@params: int id: identificador do vértice a ser encontrado no grafo
 *
 *@return: um ponteiro para o objeto nó já previamente existente
 ****************************************************************/
Node* Graph::getNodeIfExist(int id) {
    Node* node = firstNode;

    if (node == nullptr) return nullptr;

    while (node->getNextNode() != nullptr) {
        if (node->getId() == id) {
            return node;
        }

        node = node->getNextNode();
    }
}

/*
 * Função que cria o nó caso ele ainda não exista no grafo
 *@params: int id: identificador do vértice a ser criado
 *         int weight: peso do vértice
 *@return: um ponteiro para o objeto nó criado ou já previamente existente
 ****************************************************************/
Node* Graph::createNodeIfDoesntExist(int id, int weight) {
    Node* node = this->getNodeIfExist(id);

    if (node == nullptr) {
        Node* newNode = new Node(id, weight, this);
        Node* oldFirstNode = firstNode;
        newNode->setNextNode(oldFirstNode);
        setFirstNode(newNode);

        return newNode;
    }

    return node;
}

/*
 * Função que cria uma aresta no grafo
 *@params: Node *nodeHead: objeto nó de onde a aresta parte (vértice cabeça)
 *         Node *nodeTail: objeto nó onde a aresta chega (vértice cauda)
 *         int weight: peso da aresta
 *@return: um ponteiro para o objeto aresta criado
 ****************************************************************/
Edge* Graph::createEdge(Node* nodeHead, Node* nodeTail, int weight) {
    Edge* newEdge = new Edge(nodeHead, nodeTail, weight, this);

    Edge* nodeFirstEdge = nodeHead->getFirstEdge();

    nodeHead->incrementDegreeOut();
    nodeTail->incrementDegreeIn();

    if (nodeFirstEdge == nullptr) {
        nodeHead->setFirstEdge(newEdge);
    } else {
        newEdge->setNextEdge(nodeFirstEdge);
        nodeHead->setFirstEdge(newEdge);
    }

    return newEdge;
}

/*
 * Função escreve o grafo no arquivo passado
 *@params: string outputFileName: Nome do arquivo que será registrado o grafo
 *         bool isWeightedGraph: Informa se trata-se de um grafo ponderado
 *@return:
 ****************************************************************/
void Graph::outputGraph(string outputFileName, bool isWeightedGraph, bool isDirectedGraph) {
    Node* node = this->firstNode;

    FILE* outfile = fopen(outputFileName.c_str(), "w+");

    string title;
    if (!isDirectedGraph) {
        title = "graph { \n";
    } else {
        title = "digraph { \n";
    }

    fwrite(title.c_str(), 1, title.size(), outfile);

    while (node != nullptr) {
        Edge* edge = node->getFirstEdge();

        // cout << "No " << node->getId() << " In: " << node->getGrauIn() << " - Out: "<< node->getGrauOut() << endl;

        while (edge != nullptr) {
            // Id da Aresta (Linha do arquivo em que a aresta é criada)
            string nodeBase = std::to_string(node->getId());
            string nodeLinked = std::to_string((edge->getTailNode())->getId());

            string dotNotation = "";

            if (isWeightedGraph) {
                string weight = std::to_string(edge->getWeight());
                if (!isDirectedGraph) {
                    dotNotation = string(nodeBase) + "--" + string(nodeLinked) + " [weight=\"" + string(weight) + "\"] [label=\"" + string(weight) + "\"];\n";
                } else {
                    dotNotation = string(nodeBase) + "->" + string(nodeLinked) + " [weight=\"" + string(weight) + "\"] [label=\"" + string(weight) + "\"];\n";
                }
            } else {
                if (!isDirectedGraph) {
                    dotNotation = string(nodeBase) + "--" + string(nodeLinked) + ";\n";
                } else {
                    dotNotation = string(nodeBase) + "->" + string(nodeLinked) + ";\n";
                }
            }

            fwrite(dotNotation.c_str(), 1, dotNotation.size(), outfile);

            edge = edge->getNextEdge();
        }

        node = node->getNextNode();
    };

    string end = "}";

    fwrite(end.c_str(), 1, end.size(), outfile);

    cout << "O arquivo " << outputFileName << " foi gerado com sucesso.";
}

/*
 * Função escreve os nós do grafo no terminal
 *@params:
 *
 *@return:
 ****************************************************************/
void Graph::printNodes() {
    Node* node = firstNode;
    int cont = 0;

    while (node->getNextNode() != 0) {
        cont++;
        cout << cont << " - Node " << node->getId() << endl;
        node = node->getNextNode();
    }
}

/*int Graph::coeficienteDeAgrupamentoLocal(int idNode){
    Node* node1 = this->firstNode;

    while ( node1->getId() != idNode ){
        node1 = node1->getNextNode();

        if (node1 == nullptr){
            cout << "Erro" << endl;
            return 0;
        }
    }

    Edge* edge1to2 = node1->getFirstEdge();

    while (edge1to2 != nullptr){
        Node* node2 = edge1to2->getTailNode();

        while (node2 != nullptr) {
            Edge *edge2to3 = node2->getFirstEdge();

            while (edge2to3 != nullptr){

                Node* node3 = edge2to3->getTailNode();
                Edge *edge3to1 = node3->getFirstEdge();

                cout << node3->getFirstEdge() << endl;
                cout << node3->getId() << endl;

                while ( edge3to1 != nullptr ){

                    cout << edge3to1 << endl;

                    if (edge3to1->getTailNode() == node1) {
                        cout << "Soma Coeficiente" << endl;
                    }

                }

                edge3to1 = edge3to1->getNextEdge();
            }

            edge2to3 = edge2to3->getNextEdge();
        }

        edge1to2 = edge1to2->getNextEdge();
    }
}*/