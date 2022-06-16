#include "graph.h"

#include <cmath>
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
    Node* node = this->firstNode;

    if (node == nullptr) return nullptr;

    while (node != nullptr) {
        if (node->getId() == id) {
            return node;
        }

        node = node->getNextNode();
    }

    return nullptr;
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
        cout << cont << " - Node " << node->getId() << "Pk:" << node->getPkId() << endl;
        node = node->getNextNode();
    }
}

Node* Graph::searchNodePkId(int id) {
    Node* node = firstNode;
    int cont = 0;

    while (node->getNextNode() != 0) {
        if (node->getPkId() == id) {
            break;
        }
        cont++;
        node = node->getNextNode();
    }

    if (cont >= getCounterOfNodes()) {
        cout << "No nao encontrado";
        return NULL;
    }

    return node;
}

void Graph::printListAdjacents(int id) {
    Node* node = this->getNodeIfExist(id);

    if (node == nullptr) {
        return;
    }

    Edge* edge = node->getFirstEdge();

    cout << " Lista de adjacencia do no " << node->getId() << ": " << endl;
    while (edge != nullptr) {
        cout << "- No: " << edge->getTailNode()->getId() << endl;
        edge = edge->getNextEdge();
    };

    cout << "Fim" << endl;
}

int* Graph::getAllAdjacents(int id, int* cont) {
    Node* node = this->getNodeIfExist(id);
    int* allNodeAdjacents = new int[getCounterOfNodes()];

    if (node == nullptr) {
        return 0;
    }

    Edge* edge = node->getFirstEdge();

    while (edge != nullptr) {
        allNodeAdjacents[*cont] = edge->getTailNode()->getId();
        (*cont)++;
        edge = edge->getNextEdge();
    };

    return allNodeAdjacents;
}

/*
int Graph::coeficienteDeAgrupamentoLocal(int idNode){
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
}
*/

void Graph::coeficienteDeAgrupamentoLocal(int idNode) {
    int cont = 0;
    int resto = 0, quociente = 0, fracionario = 0;
    int divisor, dividendo, aux;
    int* allNodeAdjacents = getAllAdjacents(idNode, &cont);
    int k = 0;

    for (int i = 0; i < cont; i++) {
        for (int j = i + 1; j < cont; j++) {
            Node* node1 = this->getNodeIfExist(allNodeAdjacents[i]);
            Node* node2 = this->getNodeIfExist(allNodeAdjacents[j]);
            if (node1 != node2 && checkRelationship(node1, node2)) {
                k++;
            }
        }
    }

    dividendo = 2 * k;
    divisor = cont * (cont - 1);

    if (dividendo == 0) {
        cout << "O coeficiente de agrupamento local eh 0";
    } else if ((dividendo / divisor) == 1) {
        cout << "O coeficiente de agrupamento local eh: 1";
    } else {
        aux = dividendo;

        while (aux >= divisor) {
            quociente += 1;
            aux = aux - divisor;
        }

        for (int i = 0; aux > 0; i--) {
            fracionario += (10 ^ i) * (aux * 10) / divisor;
            resto = aux - (divisor * ((aux * 10) / divisor));
            aux = resto;
        }
        cout << "O coeficiente de agrupamento local eh: " << dividendo << "/" << divisor << " = " << quociente << ",  " << fracionario;
    }
}

void Graph::coeficienteDeAgrupamentoMedio() {
    int resto, quociente, fracionario, divisor, dividendo, aux;
    int* allNodeAdjacents;
    float coeficienteDeAgrupamento = 0;
    int k = 0;
    int cont = 0;

    for (Node* node = getFirstNode(); node != nullptr; node = node->getNextNode()) {
        k = 0;
        cont = 0;
        resto = 0;
        quociente = 0;
        fracionario = 0;
        allNodeAdjacents = getAllAdjacents(node->getId(), &cont);

        for (int i = 0; i < cont; i++) {
            for (int j = i + 1; j < cont; j++) {
                Node* node1 = this->getNodeIfExist(allNodeAdjacents[i]);
                Node* node2 = this->getNodeIfExist(allNodeAdjacents[j]);
                if (node1 != node2 && checkRelationship(node1, node2)) {
                    k++;
                }
            }
        }

        dividendo = 2 * k;
        divisor = cont * (cont - 1);

        if (dividendo == 0) {
            coeficienteDeAgrupamento += 0;
        } else if ((dividendo / divisor) == 1) {
            coeficienteDeAgrupamento += 1;
        } else {
            aux = dividendo;

            while (aux >= divisor) {
                quociente += 1;
                aux = aux - divisor;
            }

            int i = 0;
            for (i = 0; aux >= 0; i--) {
                fracionario += (10 ^ i) * (aux * 10) / divisor;
                resto = aux - (divisor * ((aux * 10) / divisor));
                aux = resto;
            }

            coeficienteDeAgrupamento += quociente + pow(10, i - 1) * fracionario;
        }
    }

    cout << "O coeficiente eh: " << coeficienteDeAgrupamento << "/" << getCounterOfNodes() << " = " << coeficienteDeAgrupamento / getCounterOfNodes() << endl;
}

bool Graph::checkRelationship(Node* node1, Node* node2) {
    Edge* edge = node1->getFirstEdge();
    while (edge != nullptr) {
        if (edge->getTailNode() == node2) {
            return true;
        }
        edge = edge->getNextEdge();
    };

    edge = node2->getFirstEdge();
    while (edge != nullptr) {
        if (edge->getTailNode() == node1) {
            return true;
        }
        edge = edge->getNextEdge();
    };

    return false;
}

void Graph::fechoTransitivoDireto(int id) {
    Node* node = this->getNodeIfExist(id);

    if (node == nullptr) {
        return;
    }

    int* aux = depthSearch(node);
    bool emptyClasp = 1;

    cout << "Vertices que podem ser acessados atraves do no " << node->getId() << ": ";
    for (int i = 0; i < getCounterOfNodes() + 1; i++) {
        if (aux[i] == 1 && i != node->getPkId()) {
            emptyClasp = 0;
            cout << searchNodePkId(i)->getId() << ", ";
        }
    }

    if (emptyClasp) {
        cout << "Fecho vazio" << endl;
    }
}

void Graph::fechoTransitivoIndireto(int id) {
    Node* node = this->getNodeIfExist(id);
    bool emptyClasp = 1;

    if (node == nullptr) {
        cout << "No de id inexistente" << endl;
        return;
    }

    Node* nodes[getCounterOfNodes()];
    int cont = 0;

    for (Node* i = firstNode; i != nullptr; i = i->getNextNode()) {
        if (i != node) {
            int* aux = depthSearch(i);

            for (int j = 0; j < getCounterOfNodes() + 1; j++) {
                if (aux[j] == 1 && j == node->getPkId()) {
                    nodes[cont] = i;
                    cont++;
                    break;
                }
            }
        }
    }

    cout << "Vertices que chegam ao no " << node->getId() << ": ";
    for (int i = 0; i < cont; i++) {
        emptyClasp = 0;
        cout << nodes[i]->getId() << ", ";
    }

    if (emptyClasp) {
        cout << "Fecho vazio" << endl;
    }
}

int* Graph::depthSearch(Node* node) {
    int* cont = 0;
    int* visitedNodes = new int[getCounterOfNodes()];
    for (int i = 0; i <= getCounterOfNodes(); i++) {
        visitedNodes[i] = 0;
    }

    auxDepthSearch(node, visitedNodes, cont);

    return visitedNodes;
}

void Graph::auxDepthSearch(Node* node, int visitedNodes[], int* cont) {
    cont++;
    visitedNodes[node->getPkId()] = 1;
    Edge* edge = node->getFirstEdge();

    while (edge != nullptr) {
        if (visitedNodes[edge->getTailNode()->getPkId()] == 0) {
            auxDepthSearch(edge->getTailNode(), visitedNodes, cont);
        }

        edge = edge->getNextEdge();
    };
}