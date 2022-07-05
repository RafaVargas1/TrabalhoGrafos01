#include "graph.h"

#include <cmath>
#include <iostream>
#include <list>
#include <queue>

using std::cout;
using std::endl;
using std::fstream;

using std::greater;
using std::list;
using std::make_pair;
using std::pair;
using std::priority_queue;
using std::vector;

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
 * Função que encontra um nó já existente no grafo através de seu id ou retorna null,
 caso o id não corresponda a um nó existente
 *@params: int id: identificador do vértice a ser encontrado no grafo
 *
 *@return: um ponteiro para o objeto nó já previamente existente ou nullptr
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
 * Função escreve todos os nós do grafo no terminal
 *@params:
 *
 *@return:
 ****************************************************************/
void Graph::printNodes() {
    Node* node = firstNode;
    int cont = 0;

    while (node != nullptr) {
        cout << cont << " - Node " << node->getId() << " Pk Id: " << node->getPkId() << endl;
        node = node->getNextNode();
        cont++;
    }

    cout << "Fim";
}

/*
 * Função que encontra um nó já existente no grafo através de seu pkId ou retorna null,
 caso o id não corresponda a um nó existente
 *@params: int id: identificador do vértice a ser encontrado no grafo
 *
 *@return: um ponteiro para o objeto nó já previamente existente ou nullptr
 ****************************************************************/
Node* Graph::searchNodePkId(int id) {
    Node* node = firstNode;

    while (node != nullptr) {
        if (node->getPkId() == id) {
            return node;
        }

        node = node->getNextNode();
    }

    return nullptr;
}

/*
 * Função que encontra mostra a lista de adjacências de um nó
 *@params: int id: identificador do vértice a ser mostrada a lista de adjacência
 *
 *@return:
 ****************************************************************/
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

/*
 * Função que encontra retorna a lista de adjacências de um nó através de um vetor
 que contém os id's dos nós adjacentes
 *@params: int id: identificador do vértice a ser encontrada a lista de adjacência
 *         int *cont: ponteiro para um contador que indicará quantos nós adjacentes o nó dado possui
 *
 *@return: um ponteiro para o vetor de int's (que correspodem aos id's dos nós adjacentes)
 ****************************************************************/
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
 * Função que mostra o agrupamento local dos nós dado um nó de partida
 *@params: int idNode: id do nó que se quer saber o agrupamento local
 *
 *@return:
 ****************************************************************/
void Graph::coeficienteDeAgrupamentoLocal(int idNode) {
    string outputFileName = "CoeficienteDeAgrupamentoLocal.txt";
    int cont = 0, k = 0;
    float quociente = 0;
    int divisor, dividendo;
    int* allNodeAdjacents = getAllAdjacents(idNode, &cont);

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
        quociente = 0;
        cout << "O coeficiente de agrupamento local eh 0" << endl;
    } else if ((dividendo / divisor) == 1) {
        quociente = 1;
        cout << "O coeficiente de agrupamento local eh: 1" << endl;
    } else {
        quociente = (float)dividendo / divisor;

        cout << "O coeficiente de agrupamento local eh: " << dividendo << "/" << divisor << " =~ " << quociente << endl;
    }

    FILE* outfile = fopen(outputFileName.c_str(), "w+");

    string text = string("O coeficiente de agrupamento local eh: =~") + std::to_string(quociente) + "\n";
    fwrite(text.c_str(), 1, text.size(), outfile);
    cout << "O arquivo " << outputFileName << " foi gerado com sucesso.";
}

/*
 * Função que mostra o agrupamento médio dos nós
 *@params:
 *
 *@return:
 ****************************************************************/
void Graph::coeficienteDeAgrupamentoMedio() {
    string outputFileName = "CoeficienteDeAgrupamentoMedio.txt";
    float quociente;
    int divisor, dividendo;
    int* allNodeAdjacents;
    float coeficienteDeAgrupamento = 0;
    int k = 0;
    int cont = 0;

    for (Node* node = getFirstNode(); node != nullptr; node = node->getNextNode()) {
        k = 0;
        cont = 0;
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
            quociente = (float)dividendo / divisor;

            coeficienteDeAgrupamento += quociente;
        }
    }

    // coeficienteDeAgrupamento = coeficienteDeAgrupamento / getCounterOfNodes();
    cout << "O coeficiente de agrupamento médio eh: " << coeficienteDeAgrupamento << "/" << getCounterOfNodes() << " =~ " << coeficienteDeAgrupamento / getCounterOfNodes() << endl;
    FILE* outfile = fopen(outputFileName.c_str(), "w+");

    string text = string("O coeficiente de agrupamento médio eh =~") + std::to_string(coeficienteDeAgrupamento / getCounterOfNodes());
    fwrite(text.c_str(), 1, text.size(), outfile);
    cout << "O arquivo " << outputFileName << " foi gerado com sucesso.";
}

/*
 * Função que verifica se dois nós possuem arestas entre si
 *@params: Node* node1: ponteiro de objeto do tipo nó
 *         Node* node2: ponteiro de objeto do tipo nó
 *
 *@return: retorna verdadeiro se forem vizinhos e falso caso não forem
 ****************************************************************/
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

/*
 * Função que mostra os nós que podem ser acessados a partir de um nó dado (Fecho Direto)
 *@params: int id: identificador do vértice a ser encontrado o fecho transitivo direto
 *
 *@return:
 ****************************************************************/
void Graph::fechoTransitivoDireto(int id) {
    Node* node = this->getNodeIfExist(id);

    if (node == nullptr) {
        return;
    }

    string outputFileName = "FechoTransitivoDireto.txt";
    int* aux = depthSearch(node);
    bool emptyClasp = 1;
    Node* nodes[getCounterOfNodes()];
    int cont = 1;
    nodes[0] = node;

    cout << "Vertices que podem ser acessados atraves do no " << node->getId() << ": ";

    for (int i = 0; i < getCounterOfNodes() + 1; i++) {
        if (aux[i] == 1 && i != node->getPkId()) {
            if (emptyClasp)
                emptyClasp = 0;

            nodes[cont] = searchNodePkId(i);
            cont++;
            cout << searchNodePkId(i)->getId() << ", ";
        }
    }

    output(outputFileName, nodes, cont, "Vertices que podem ser acessados atraves do no ");
    if (emptyClasp)
        cout << "Fecho vazio" << endl;
}

/*
 * Função que mostra os nós que chegam ao nó dado (Fecho Indireto)
 *@params: int id: identificador do vértice a ser encontrado o fecho transitivo indireto
 *
 *@return:
 ****************************************************************/
void Graph::fechoTransitivoIndireto(int id) {
    Node* node = this->getNodeIfExist(id);
    bool emptyClasp = 1;

    if (node == nullptr) {
        cout << "No de id inexistente" << endl;
        return;
    }

    string outputFileName = "FechoTransitivoIndireto.txt";
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

    output(outputFileName, nodes, cont, "Vertices que chegam ao no ");
    if (emptyClasp)
        cout << "Fecho vazio" << endl;
}

/*
 * Função que faz a busca em profundidade e retorna um vetor contendo os id's dos
 vértices visitados a partir de um nó dado
 *@params: Node* node: ponteiro de objeto do tipo nó
 *
 *@return: um ponteiro para o vetor de int's (que correspodem aos id's dos vértices visitados)
 ****************************************************************/
int* Graph::depthSearch(Node* node) {
    int* cont = 0;
    int* visitedNodes = new int[getCounterOfNodes()];
    for (int i = 0; i <= getCounterOfNodes(); i++) {
        visitedNodes[i] = 0;
    }

    auxDepthSearch(node, visitedNodes, cont);

    return visitedNodes;
}

/*
 * Função que auxiliar da função de busca em profundidade que efetivamente procura
 os nós do grafo em profundidade  a partir de um dado nó
 *@params: Node* node: ponteiro de objeto do tipo nó de onde partirá a busca
 *         int visitedNodes[]: vetor de int's que contém os id's dos vértices visitados
 *         int* cont: ponteiro para um contador que indicará quantos nós foram visitados
 *
 *@return:
 ****************************************************************/
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

/*
 * Função escreve o os nós passados em um arquivo
 *@params: string outputFileName: Nome do arquivo que será registrado os nós
 *         Node* nodes[]: conjuntos de nós resposta da operação realizada
 *         int cont: contador de quantos nós há no array nodes
 *         string textStart: texto inicial a ser escrito
 *@return:
 ****************************************************************/
void Graph::output(string outputFileName, Node* nodes[], int cont, string textStart) {
    FILE* outfile = fopen(outputFileName.c_str(), "w+");

    string text = string(textStart) + std::to_string(nodes[0]->getId()) + ": \n";
    fwrite(text.c_str(), 1, text.size(), outfile);

    for (int i = 1; i < cont; i++) {
        text = std::to_string(nodes[i]->getId()) + string(",");
        fwrite(text.c_str(), 1, text.size(), outfile);
    }

    cout << "O arquivo " << outputFileName << " foi gerado com sucesso.";
}

/*
 * Função verifica o custo da aresta entre dois nós passados
 *@params: Node* nodeHead: nó cuja aresta parte
           Node* tailNode: nó cuja aresta chega
 *@return: retorna o valor do custo da aresta (-1 caso não haja aresta)
 ****************************************************************/
int Graph::edgeCost(Node* nodeHead, Node* tailNode) {
    for (Edge* i = nodeHead->getFirstEdge(); i != nullptr; i = i->getNextEdge()) {
        if (i->getTailNode() == tailNode)
            return i->getWeight();
    }

    return -1;
}

/*
int* Graph::getAdjacents(int id, Node* nodesInvolved[], int quantityNodesInvolved) {
    Node* node = getNodeIfExist(id);
    int cont = 0;
    int* allNodeAdjacents = new int[getCounterOfNodes()];

    if (node == nullptr) {
        return 0;
    }

    Edge* edge = node->getFirstEdge();

    for (int j = 0; j < quantityNodesInvolved; j++) {
        while (edge != nullptr) {
            for (int i = 0; i < quantityNodesInvolved; i++) {
                if (nodesInvolved[i] == edge->getTailNode()) {
                    allNodeAdjacents[cont] = edge->getTailNode()->getId();
                    cont++;
                }
                edge = edge->getNextEdge();
            }
        }
        node = node->getNextNode();
        edge = node->getFirstEdge();
    }

    return allNodeAdjacents;
}
*/
/*
void Graph::outputGraphSetOfNodes(string outputFileName, bool isWeightedGraph, bool isDirectedGraph, Node* nodesUtils[], int quantityNodesUtils) {
    FILE* outfile = fopen(outputFileName.c_str(), "w+");

    string title;
    if (!isDirectedGraph) {
        title = "graph { \n";
    } else {
        title = "digraph { \n";
    }

    fwrite(title.c_str(), 1, title.size(), outfile);

    Node* node = nodesUtils[0];
    int cont = 0;
    int* nodesAdjacents = getAllAdjacents(node->getId(), &cont);

    for (int i = 1; i < quantityNodesUtils - 1; i++) {
        cout << node->getId() << " - " << *nodesAdjacents << endl;
        for (int j = 0; j < cont; j++) {
            if (nodesUtils[i]->getId() == *(nodesAdjacents + j)) {
                cout << node->getId() << " -> " << *nodesAdjacents << endl;
                string nodeBase = std::to_string(node->getId());
                string nodeLinked = std::to_string(*nodesAdjacents);

                int cost = edgeCost(node, getNodeIfExist(*nodesAdjacents));
                *nodesAdjacents++;

                string dotNotation = "";

                if (isWeightedGraph) {
                    string weight = std::to_string(cost);
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
            }
        }
    };

    string end = "}";

    fwrite(end.c_str(), 1, end.size(), outfile);

    cout << "O arquivo " << outputFileName << " foi gerado com sucesso.";
}
*/

void Graph::outputGraphSetOfNodes(string outputFileName, bool isWeightedGraph, bool isDirectedGraph, int dist, std::queue<pair<int, int>> nodes) {
    FILE* outfile = fopen(outputFileName.c_str(), "w+");
    int currentDist = 0;

    string title;
    if (!isDirectedGraph) {
        title = "graph { \n";
    } else {
        title = "digraph { \n";
    }

    fwrite(title.c_str(), 1, title.size(), outfile);

    pair<int, int> p = nodes.front();
    nodes.pop();
    currentDist += p.first;

    while (!nodes.empty() && p.first != dist) {
        pair<int, int> q = nodes.front();
        nodes.pop();

        string nodeBase = std::to_string(p.second);
        string nodeLinked = std::to_string(q.second);

        int costEdge = edgeCost(getNodeIfExist(p.second), getNodeIfExist(q.second));
        if (costEdge == -1)
            continue;

        string dotNotation = "";

        if (isWeightedGraph) {
            string weight = std::to_string(costEdge);
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

        p = q;

        if (currentDist == dist)
            break;

        currentDist += q.first;
    }

    string end = "}";

    fwrite(end.c_str(), 1, end.size(), outfile);

    cout << "O arquivo " << outputFileName << " foi gerado com sucesso.";
}

/*
 * Função verifica o caminho de menor custo entre dois nós passados
 *@params: int idNodeOrig: id do nó origem
           int idNodeDest: id do nó destino
 *@return: retorna o valor do custo da aresta (-1 caso não haja aresta)
 ****************************************************************/
void Graph::dijkstra(int idNodeOrig, int idNodeDest, bool isWeightedGraph, bool isDirectedGraph) {
    bool visitedNodes[getCounterOfNodes()];
    int dist[getCounterOfNodes()];

    // primeiro elemento do par é a distancia e o segundo o vértice
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    std::queue<pair<int, int>> nodes;

    for (int i = 0; i < getCounterOfNodes() + 1; i++) {
        dist[i] = -1;
        visitedNodes[i] = false;
    }

    Node* nodeOrig = getNodeIfExist(idNodeOrig);
    if (nodeOrig == nullptr) {
        cout << "Vertice invalido" << endl;
        return;
    }

    dist[nodeOrig->getPkId()] = 0;

    pq.push(make_pair(dist[nodeOrig->getPkId()], nodeOrig->getId()));
    nodes.push(make_pair(dist[nodeOrig->getPkId()], nodeOrig->getId()));

    while (!pq.empty()) {
        pair<int, int> p = pq.top();
        int idNodeTop = p.second;
        Node* nodeTop = getNodeIfExist(idNodeTop);
        pq.pop();

        if (visitedNodes[nodeTop->getPkId()] == false) {
            visitedNodes[nodeTop->getPkId()] = true;

            int cont = 0;
            int* adjacents = getAllAdjacents(nodeTop->getId(), &cont);

            for (int j = 0; j < cont; j++) {
                Node* nodeAdjacent = getNodeIfExist(*(adjacents + j));

                int costEdge = edgeCost(nodeTop, nodeAdjacent);
                if (costEdge == -1)  // não existem aresta entre eles
                    continue;

                if (dist[nodeAdjacent->getPkId()] == -1 || dist[nodeAdjacent->getPkId()] > (dist[nodeTop->getPkId()] + costEdge)) {
                    dist[nodeAdjacent->getPkId()] = dist[nodeTop->getPkId()] + costEdge;

                    cout << nodeTop->getId() << " -> " << nodeAdjacent->getId() << " = " << dist[nodeAdjacent->getPkId()] << endl;

                    pq.push(make_pair(dist[nodeAdjacent->getPkId()], nodeAdjacent->getId()));
                    nodes.push(make_pair(dist[nodeAdjacent->getPkId()], nodeAdjacent->getId()));
                }
            }
        }
    }

    if (dist[getNodeIfExist(idNodeDest)->getPkId()] == -1) {
        cout << "Nao eh possivel chegar do no " << idNodeOrig << " ao no " << idNodeDest << endl;
        return;
    }

    cout << "A distancia eh de: " << dist[getNodeIfExist(idNodeDest)->getPkId()] << endl;

    outputGraphSetOfNodes("AlgoritmoDijkstra.dot", isWeightedGraph, isDirectedGraph, dist[getNodeIfExist(idNodeDest)->getPkId()], nodes);
}

/*
Acho que pode apagar essa função, mas deixei aqui pois foi a função que a gente
começou a desenvolver na call

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
