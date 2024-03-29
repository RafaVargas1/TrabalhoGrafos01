#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

#include "./Edge/edge.cpp"
#include "./Graph/graph.cpp"
#include "./Node/node.cpp"


/*
 * Lê e instancia o grafo a partir do arquivo escrito 
 * @params: FILE *file: arquivo de onde o grafo sera lido
 *          bool isDirected: se o grafo é direcionado
 *          bool hasWeightedEdges: se o grafo tem peso nas arestas
 *          bool hasWeightedNodes: se o grafo tem peso nos nos
 * @return: Graph*: Grafo final instaciado 
 ****************************************************************/
Graph *graphReadAndInstantiation(FILE *file, bool isDirected, bool hasWeightedEdges, bool hasWeightedNodes) {
    Graph *graph = new Graph(isDirected, hasWeightedEdges, hasWeightedNodes);

    const int lineSize = 50;

    while (!feof(file)) {
        char line[lineSize];
        char *textInLine = fgets(line, lineSize, file);

        int space = 0;

        if (textInLine != nullptr)
            space = string(textInLine).find(" ", 0);

        if (space > 0) {
            string stringHead, stringTail, stringEdgeWeight;
            int intHead, intTail, intEdgeWeight = 0;

            if (hasWeightedEdges) {
                stringHead = string(textInLine).substr(0, space);
                int newSpace = string(textInLine).find(" ", space + 1);
                stringTail = string(textInLine).substr(space, newSpace);
                stringEdgeWeight = string(textInLine).substr(newSpace, string(textInLine).size());

                intHead = stoi(stringHead);
                intTail = stoi(stringTail);
                intEdgeWeight = stoi(stringEdgeWeight);
            } else {
                stringHead = string(textInLine).substr(0, space);
                stringTail = string(textInLine).substr(space, string(textInLine).size());

                intHead = stoi(stringHead);
                intTail = stoi(stringTail);
                intEdgeWeight = 1;
            }

            Node *nodeHead = graph->createNodeIfDoesntExist(intHead, 0);
            Node *nodeTail = graph->createNodeIfDoesntExist(intTail, 0);

            Edge *edge1 = graph->createEdge(nodeHead, nodeTail, intEdgeWeight);
            if (!isDirected)
                Edge *edge2 = graph->createEdge(nodeTail, nodeHead, intEdgeWeight);
        }

        delete textInLine;
    }

    return graph;
}

/*
 * Pega o subgrafo vertice induzido por escrito e faz a instaciação dele 
 * basedo no grafo origingal
 * @params: Graph* originalGraph: grafo base a partir do qual sera gerado o subgrafo
 *          string nodes: String que descreve o vertice induzido
 * @return: Graph*: subgrafo resultante, podendo ser o grafo original 
 * ou um subgrafo vertice induzido digitado pelo usuario
 ****************************************************************/
Graph* graphNodeInduced(string nodes, Graph* originalGraph){
    std::istringstream aux { nodes };

    Graph* graph = new Graph(originalGraph->getDirected(), originalGraph->isEdgeWeighted(), originalGraph->isNodeWeighted());

    string node;
    vector<Node*> vectorNodes;
    while ( std::getline(aux, node, ',')){
        int nodeInt = stoi(node);

        Node* originalNode = originalGraph->getNodeIfExist(nodeInt);
        vectorNodes.push_back(originalNode);

        graph->createNodeIfDoesntExist( nodeInt, originalNode->getId() );
    }

    for (int i=0; i < vectorNodes.size(); i++){
        int cont = 0;
        int* adjacents = originalGraph->getAllAdjacents( vectorNodes[i]->getId() , &cont);

        for (int j=0; j < cont; j++){

            Node* node = graph->getNodeIfExist(adjacents[j]);

            if (node != nullptr){
            
                Edge* edge = vectorNodes[i]->getFirstEdge();
               
               while (edge != nullptr && edge->getTailNode()->getId() != node->getId()) {
                    edge = edge->getNextEdge();
                } 

                if (edge != nullptr){
                    Edge *edge1 = graph->createEdge(vectorNodes[i], node, edge->getWeight());
                    Edge *edge2 = graph->createEdge(node, vectorNodes[i], edge->getWeight());
                }
            }
           
        }
    }

    return graph;
}

/*
 * Recebe um grafo e permite que o usuario pegue um subgrafo vertice 
 * induzido desse grafo
 * @params: originalGraph: grafo base a partir do qual sera gerado o subgrafo
 * @return: Graph*: subgrafo resultante, podendo ser o grafo original 
 * ou um subgrafo vertice induzido digitado pelo usuario
 ****************************************************************/
Graph* processGraphNodeInduced(Graph* originalGraph){
    int option;
    cout << "Defina os nos a serem considerados: " << endl;

    cout << "(0) Todos os nos (Grafo completo)" << endl;
    cout << "(1) Nos especificos" << endl;
    cin >> option;

    string nodes;
    switch (option){
    case 0:
        return originalGraph;
        break;
    case 1:
        cout << "Defina os nos pelo ID separados por virgula" << endl;
        cout << "Exemplo: 1,2,3" << endl;
        cin >> nodes;  
        return graphNodeInduced(nodes, originalGraph);;
        break;
    default:
        cout << "Opcao invalida" << endl;
        return processGraphNodeInduced(originalGraph);
        break;
    }
 
    
}

/*
 * Exibe os detalhes da entrada por escrito de forma descritiva 
 * e permite que o usuario confirme ou nao essa entrada.
 * @params: string fileName: nome do arquivo
 *          string path: caminho ate o arquivo
 *          bool hasWeightedEdge: se o grafo tem peso nas arestas
 *          bool hasWeightedNode: se o grafo tem peso nos nos
 *          bool isDirected: se o grafo é direcionado
 * @return: bool: Se o usuário confirma a entrada
 ****************************************************************/
bool confirmEntry(string fileName, string path, bool hasWeightedEdge, bool hasWeightedNode, bool isDirected) {
    int confirmation;

    cout << "\n\n =========================================== \n\n";
    cout << "---- Confirmacao dos argumentos de entrada ---- \n"
         << endl;
    cout << "-> Caminho do arquivo de Entrada: " << path << endl;
    cout << "-> Nome arquivo de Entrada: " << fileName << endl;

    cout << "-> Grafo DIRECIONADO: ";
    isDirected ? cout << "SIM" << endl : cout << "NAO" << endl;

    cout << "-> Grafo PONDERADOS nas ARESTAS: ";
    hasWeightedEdge == true ? cout << "SIM" << endl : cout << "NAO" << endl;

    cout << "-> Grafo PONDERADOS nos NOS: ";
    hasWeightedNode == true ? cout << "SIM" << endl : cout << "NAO" << endl;

    cout << "\n\n =========================================== \n\n";
    cout << "Voce confirma a entrada de dados ? [1 = SIM | 0 = NAO] " << endl;
    cout << "-> ";
    cin >> confirmation;

    if (confirmation == 1) return true;

    return false;
}

/*
 * Exibe e processa os opções e escolhas
 * @params: char *argv[]: lista de argumentos
 *          bool hasWeightedNode: se o grafo tem peso nos nos
 *          bool hasWeightedEdge: se o grafo tem peso nas arestas
 *          bool isDirected: se o grafo e direcionado
 *          Graph *graph: grafo já instanciado
 * @return:
 ****************************************************************/
void processOperationChoice(char *argv[], bool hasWeightedNode, bool hasWeightedEdge, bool isDirected, Graph *graph) {
    int option;
    cout << "\nDigite a funcionalidade que deseja para o grafo inserido: " << endl;

    cout << "(1) Fecho Transitivo Direto" << endl;
    cout << "(2) Fecho Transitivo Indireto" << endl;
    cout << "(3) Coeficiente de Agrupamento Local" << endl;
    cout << "(4) Coeficiente de Agrupamento Medio" << endl;
    cout << "(5) Caminho minimo pelo Algoritmo de Dijkstra" << endl;
    cout << "(6) Caminho minimo pelo Algoritmo de Floyd" << endl;
    cout << "(7) Algoritmo de Prim" << endl;
    cout << "(8) Algoritmo de Kruskal" << endl;
    cout << "(9) Arvore gerada pela ordem da busca em profundidade" << endl;
    cout << "(10) Output do grafo no formato .dot" << endl;
    cout << "(11) Print lista de adjacencia" << endl;
    cout << "(12) Print nodes" << endl;
    cout << "-> ";
    cin >> option;
    cout << "\n";

    int no, noDest;
    Graph* newGraph;

    switch (option) {
        case 1:
            cout << "Fecho Transitivo Direto de qual no?" << endl;
            cin >> no;
            graph->fechoTransitivoDireto(no);
            break;
        case 2:
            cout << "Fecho Transitivo Indireto de qual no?" << endl;
            cin >> no;
            graph->fechoTransitivoIndireto(no);
            break;
        case 3:
            cout << "Coeficiente de Agrupamento Local de qual no?" << endl;
            cin >> no;
            graph->coeficienteDeAgrupamentoLocal(no);
            break;
        case 4:
            graph->coeficienteDeAgrupamentoMedio();
            break;
        case 5:
            cout << "Dijkstra de qual no de origem?" << endl;
            cin >> no;
            cout << "Dijkstra de qual no de destino?" << endl;
            cin >> noDest;
            graph->dijkstra(no, noDest);
            break;
        case 6:
            cout << "Floyd de qual no de origem?" << endl;
            cin >> no;
            cout << "Floyd de qual no de destino?" << endl;
            cin >> noDest;
            graph->floyd(no, noDest);
            break;
        case 7:
            newGraph = processGraphNodeInduced(graph);
            newGraph->prim(argv[2]);
            break;
        case 8:
            newGraph = processGraphNodeInduced(graph);
            newGraph->kruskal(argv[2]);
            break;
        case 9:
            cout << "A partir de qual no?" << endl;
            cin >> no;
            graph->treeDeepthSearch(graph->getNodeIfExist(no), argv[2]);
            break;
        case 10:
            graph->outputGraph(argv[2]);
            break;
        case 11:
            cout << "Lista de adjacencia de qual no?" << endl;
            cin >> no;
            graph->printListAdjacents(no);
            break;
        case 12:
            graph->printNodes();
            break;
        default:
            processOperationChoice(argv, hasWeightedEdge, hasWeightedNode, isDirected, graph);
            break;
    }

    option = 0;
    cout << "\n\nDeseja realizar nova operacao ? [1 = SIM | 0 = NAO]" << endl;
    cout << "-> ";
    cin >> option;

    if (option == 1) processOperationChoice(argv, hasWeightedEdge, hasWeightedNode, isDirected, graph);
}


/*
 * Funcao principal, faz as leituras dos argumentos passados na linha de comentado
 * @params: argc: numero de arumentos
 *          argv: argumentos 
 * @return:
 ****************************************************************/
int main(int argc, char *argv[]) {
    FILE *file;

    // printArgs(argc, argv);

    string dirPath = "./EntryFiles/Not_Weighted_Graphs";
    bool isDirected = false, hasWeightedEdge = false, hasWeightedNode = false;

    if (argc < 6) {
        //  NOME ENTRADA ?, NOME SAIDA, DIRECIONADO ?, PESO EDGE ?, PESO NODE ?
        cout << "Os argumentos de excecucao sao invalidos. Os argumentos devem seguir o padrao: " << endl;
        cout << "ARQUIVO DE ENTRADA | ARQUIVO DE SAIDA | (0,1) SE É DIRECIONADO | (0,1) SE AS ARESTAS SAO PONDERADAS | (0,1) SE OS VERTICES SAO PONDERADOS" << endl;
        return 0;
    }

    if (*argv[3] == '1')
        isDirected = true;

    if (*argv[4] == '1') {
        hasWeightedEdge = true;
        dirPath = "./EntryFiles/Weighted_Graphs";
    }

    if (*argv[5] == '1')
        hasWeightedNode = true;

    string fileName = argv[1];

    string path = string(dirPath) + "/" + string(fileName);
    file = fopen(path.c_str(), "rt");

    if (file == NULL)
        perror("Erro ao abrir o arquivo");

    if (!confirmEntry(fileName, path, hasWeightedEdge, hasWeightedNode, isDirected)) return 0;

    Graph *graph = graphReadAndInstantiation(file, isDirected, hasWeightedEdge, hasWeightedNode);

    processOperationChoice(argv, hasWeightedEdge, hasWeightedNode, isDirected, graph);

    return 0;
}
