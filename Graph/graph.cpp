#include "graph.h"

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::fstream;
using std::string;
using std::vector;

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

    cout << "O arquivo " << outputFileName << " foi gerado com sucesso. Para visualizar encerre a execucao";
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

    while (node->getNextNode() != 0) {
        cont++;
        cout << cont << " - Node " << node->getId() << "Pk:" << node->getPkId() << endl;
        node = node->getNextNode();
    }
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
    int cont = 0, k = 0;
    float quociente;
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
        cout << "O coeficiente de agrupamento local eh 0";
    } else if ((dividendo / divisor) == 1) {
        cout << "O coeficiente de agrupamento local eh: 1";
    } else {
        quociente = (float)dividendo / divisor;

        cout << "O coeficiente de agrupamento local eh: " << dividendo << "/" << divisor << " =~ " << quociente;
    }
}

/*
 * Função que mostra o agrupamento médio dos nós
 *@params:
 *
 *@return:
 ****************************************************************/
void Graph::coeficienteDeAgrupamentoMedio() {
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

    cout << "O coeficiente de agrupamento médio eh: " << coeficienteDeAgrupamento << "/" << getCounterOfNodes() << " =~ " << coeficienteDeAgrupamento / getCounterOfNodes() << endl;
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

/*
 * Função que faz a busca em profundidade e retorna um vetor contendo os id's dos
 vértices visitados a partir de um nó dado
 *@params: Node* node: ponteiro de objeto do tipo nó
 *
 *@return: um ponteiro para o vetor de int's (que correspodem aos id's dos vértices visitados)
 ****************************************************************/
int* Graph::depthSearch(Node* node) {
    int* cont = 0;
    int* visitedNodes = new int[this->getCounterOfNodes()];
    for (int i = 0; i <= this->getCounterOfNodes(); i++) {
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
 * Faz o output em .dot a partir de um vector de vertices
 *@params: string outputFileName: Nome do arquivo de saida
 *         vector<Edge*>&subgraph: Subgrafo vertice induzido. No vetor estara somente as referencias as arestas
 * 
 *@return:
 ****************************************************************/


void Graph::outputEdgeInducedSubgraph(string outputFileName, vector<Edge*>&subgraph){
    FILE* outfile = fopen(outputFileName.c_str(), "w+");

    string title = "graph { \n";
    fwrite(title.c_str(), 1, title.size(), outfile);

    string dotNotation = "";

    for (int i=0; i< subgraph.size(); i++){
        string nodeBase = std::to_string(subgraph[i]->getHeadNode()->getId());
        string nodeLinked = std::to_string(subgraph[i]->getTailNode()->getId() );
        dotNotation = string(nodeBase) + "--" + string(nodeLinked) + ";\n";
        fwrite(dotNotation.c_str(), 1, dotNotation.size(), outfile);
    }

    string end = "}";
    fwrite(end.c_str(), 1, end.size(), outfile);
    cout << "O arquivo " << outputFileName << " foi gerado com sucesso. Para visualizar encerre a execucao" << endl;
  
}

void Graph::treeDeepthSearch(Node* node) {
    Graph *searchTree = new Graph();
    Graph *returnTree = new Graph();


    /* 
        -> visitedNodes - Auxiliar para marcar os nos visitados no caminhamento 
        -> Os subgrafos serao representados como Subgrafo Vertice Induzido 
            mainTreeEdge - Arvore em ordem de caminhamento 
            returnTreeEdge - Arestas de Retorno
    */

    vector<Node*> visitedNodes;
    vector<Edge*> mainTreeEdge; 
    vector<Edge*> returnTreeEdge;

    auxTreeDeepthSearch(node, visitedNodes, mainTreeEdge, returnTreeEdge);
  
    this->outputEdgeInducedSubgraph("arvore.dot", mainTreeEdge);
    this->outputEdgeInducedSubgraph("arestasRetorno.dot", returnTreeEdge);
}



/*
 * Funcao que verifica se uma aresta esta dentro de um vetor de arestas
 *@params: vector<Edge*>&edgeVector: Referencia a um vetor de arestas
 *         Edge edge: Aresta a ser testada
 *
 *@return: True se edge esta em edgeVector false se nao
 ****************************************************************/
bool isEdgeInVector(vector<Edge*>&edgeVector, Edge* edge){
    for (int i=0; i< edgeVector.size(); i++){
        if (edgeVector[i] == edge){
            return true;
        }
    }

    return false;
}

/*
 * Funcao que verifica se um no esta dentro de um vetor de nos
 *@params: vector<Edge*>&nodeVector: Referencia a um vetor de nos
 *         Edge node: No a ser testada
 *
 *@return: True se no esta em nodeVector false se nao
 ****************************************************************/
bool isNodeVisited(vector<Node*>&nodeVector, Node* node){
       for (int i=0; i< nodeVector.size(); i++){
        if (nodeVector[i] == node){
            return true;
        }
    }

    return false;
}

void Graph::auxTreeDeepthSearch(Node* node, vector<Node*>&visitedNodes, vector<Edge*>&mainTreeEdge, vector<Edge*>&returnTreeEdge){
    if (!isNodeVisited(visitedNodes, node)){
        visitedNodes.emplace_back(node);
    }

    Edge* edge = node->getFirstEdge();

    while (edge != nullptr){
        Node* auxNode = node;
        Node* node = edge->getTailNode();


        if (!isNodeVisited(visitedNodes, edge->getTailNode())) {
            if (!isEdgeInVector(mainTreeEdge, edge)){
                mainTreeEdge.emplace_back(edge);   

                /*
                    Processo que forca as multiarestas a entrarem na arvore.
                    Isso acontece pois essas multiarestas sao criadas no grafo nao direcional para a representacao correta em memoria, mas essas ligacoes nao existem no grafo real. 
                */
                Node* returnNode = edge->getTailNode();
                Edge* returnEdge = returnNode->getFirstEdge();  
                while (returnEdge == nullptr || returnEdge->getTailNode() != edge->getHeadNode()){
                    returnEdge = returnEdge->getNextEdge();
                }

                if (returnEdge != nullptr)
                    mainTreeEdge.emplace_back(returnEdge);
                // Fim do processo que coloca multiarestas na arvore
                           
                auxTreeDeepthSearch(edge->getTailNode(), visitedNodes, mainTreeEdge, returnTreeEdge);
            }

            edge = edge->getNextEdge();  

        } else if ( isNodeVisited(visitedNodes, edge->getTailNode()) ) {
       
            if (!isEdgeInVector(mainTreeEdge, edge)){
                returnTreeEdge.emplace_back(edge);
            }
     
            edge = edge->getNextEdge();
        }
    }
}

