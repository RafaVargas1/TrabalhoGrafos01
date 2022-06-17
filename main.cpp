#include <iostream>

#include <dirent.h>
#include <stdlib.h>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

#include "./Edge/edge.cpp"
#include "./Graph/graph.cpp"
#include "./Node/node.cpp"


Graph *graphReadAndInstantiation(FILE *file, bool isDirected, bool hasWeightedEdges) {
    Graph *graph = new Graph();

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
            }
           
            Node *nodeHead = graph->createNodeIfDoesntExist(intHead, 0);
            Node *nodeTail = graph->createNodeIfDoesntExist(intTail, 0);

            Edge *edge1 = graph->createEdge(nodeHead, nodeTail, intEdgeWeight);
            if (!isDirected) 
                Edge *edge2 = graph->createEdge(nodeTail, nodeHead, 0);      
        }

        delete textInLine;
    }

    return graph;
}

bool confirmEntry(string fileName, string path, bool hasWeightedEdge, bool  hasWeightedNode, bool  isDirected){
    int confirmation;
    
    cout << "\n\n =========================================== \n\n";
    cout << "---- Confirmacao dos argumentos de entrada ---- \n" << endl;
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

void processOperationChoice(char *argv[], bool hasWeightedNode, bool hasWeightedEdge, bool isDirected, Graph *graph){
    int option;
    cout << "\nDigite a funcionalidade que deseja para o grafo inserido: " << endl;
    cout << "(1) Print lista de adjacencia" << endl;
    cout << "(2) Print nodes" << endl;
    cout << "(3) Fecho Transitivo Direto" << endl;
    cout << "(4) Fecho Transitivo Indireto" << endl;
    cout << "(5) Coeficiente de Agrupamento Local" << endl;
    cout << "(6) Coeficiente de Agrupamento Medio" << endl;
    cout << "(7) Output do grafo no formato .dot" << endl;
    cout << "(8) Arvore gerada pela ordem da busca em profundidade" << endl;
    cout << "-> ";
    cin >> option;
    cout << "\n";

    int no;
    switch (option) {
        case 1:
            cout << "Lista de adjacencia de qual no?" << endl;
            cin >> no;
            graph->printListAdjacents(no);
            break;
        case 2:
            graph->printNodes();
            break;
        case 3:
            cout << "Fecho Transitivo Direto de qual no?" << endl;
            cin >> no;
            graph->fechoTransitivoDireto(no);
            break;
        case 4:
            cout << "Fecho Transitivo Indireto de qual no?" << endl;
            cin >> no;
            graph->fechoTransitivoIndireto(no);
            break;
        case 5:
            cout << "Coeficiente de Agrupamento Local de qual no?" << endl;
            cin >> no;
            graph->coeficienteDeAgrupamentoLocal(no);
            break;
        case 6:
            graph->coeficienteDeAgrupamentoMedio();
            break;
        case 7:
            graph->outputGraph(argv[2], hasWeightedEdge, isDirected);
            break;
        case 8:
            graph->treeDeepthSearch();
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

    
    if (!confirmEntry(fileName, path, hasWeightedEdge, hasWeightedNode, isDirected) ) return 0;

    Graph *graph = new Graph();

    graph = graphReadAndInstantiation(file, isDirected, hasWeightedEdge);

    processOperationChoice(argv, hasWeightedEdge, hasWeightedNode, isDirected, graph);
    
    return 0;
}

