#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using std::copy;
using std::cout;
using std::endl;
using std::string;

#include "./Edge/edge.cpp"
#include "./Graph/graph.cpp"
#include "./Node/node.cpp"

/*
 * Função que escreve as 20 primeiras linhas do grafo
 *@params: FILE *file: arquivo onde se encontra o grafo
 *         std::string name: nome
 *@return:
 ****************************************************************/
void printFileDetails(FILE *file, std::string name) {
    int i = 1;
    cout << "===== " << name << " =====" << endl;
    cout << "PRIMEIRAS 20 LINHAS " << endl;

    while (!feof(file)) {
        char line[100];

        char *result = fgets(line, 100, file);

        if (result && i <= 20)
            cout << "Linha " << i << ": " << line << endl;

        delete result;
        i++;
    }

    cout << " === TOTAL DE LINHAS: " << i << " === \n\n"
         << endl;

    fclose(file);
}

void readFilesInDirectory(const char *directoryPath) {
    DIR *dir;
    FILE *file;
    struct dirent *lsdir;

    dir = opendir(directoryPath);

    while ((lsdir = readdir(dir)) != NULL) {
        string path = std::string(directoryPath) + "/" + std::string(lsdir->d_name);
        file = fopen(path.c_str(), "rt");

        if (file == NULL) {
            perror("Erro ao abrir o arquivo");
        } else {
            printFileDetails(file, lsdir->d_name);
        }
    }
}

// Grafo ponderado
Graph *processingWeighted(FILE *file, bool isDirected) {
    Graph *graph = new Graph();

    const int lineSize = 50;

    while (!feof(file)) {
        char line[lineSize];
        char *textInLine = fgets(line, lineSize, file);

        int space = 0;

        if (textInLine != nullptr)
            space = string(textInLine).find(" ", 0);

        if (space > 0) {
            string head = string(textInLine).substr(0, space);
            int newSpace = string(textInLine).find(" ", space + 1);
            string tail = string(textInLine).substr(space, newSpace);
            string weight = string(textInLine).substr(newSpace, string(textInLine).size());

            int intHead = stoi(head);
            int intTail = stoi(tail);
            int intWeigth = stoi(weight);

            // cout << intHead << " - " << intTail << " - " << intWeigth << endl;

            // cout << intHead << " + " << intTail << endl;
            Node *nodeHead = graph->createNodeIfDoesntExist(intHead, 0);
            Node *nodeTail = graph->createNodeIfDoesntExist(intTail, 0);

            // Criação nos dois sentidos
            Edge *edge1 = graph->createEdge(nodeHead, nodeTail, intWeigth);
            // cout << edge1->getWeight() << endl;
            if (!isDirected) {
                Edge *edge2 = graph->createEdge(nodeTail, nodeHead, intWeigth);
            }
        }

        delete textInLine;
    }

    return graph;
    // graph->coeficienteDeAgrupamentoLocal(2);
    // graph->printNodes();
}

// Grafo não ponderado nas arestas
Graph *processingNotWeighted(FILE *file, bool isDirected) {
    Graph *graph = new Graph();

    const int lineSize = 50;

    while (!feof(file)) {
        char line[lineSize];
        char *textInLine = fgets(line, lineSize, file);

        int space = 0;

        if (textInLine != nullptr)
            space = string(textInLine).find(" ", 0);

        if (space > 0) {
            string head = string(textInLine).substr(0, space);
            string tail = string(textInLine).substr(space, string(textInLine).size());

            int intHead = stoi(head);
            int intTail = stoi(tail);

            // cout << intHead << " + " << intTail << endl;
            Node *nodeHead = graph->createNodeIfDoesntExist(intHead, 0);
            Node *nodeTail = graph->createNodeIfDoesntExist(intTail, 0);

            // Criação nos dois sentidos
            Edge *edge1 = graph->createEdge(nodeHead, nodeTail, 0);
            if (!isDirected) {
                Edge *edge2 = graph->createEdge(nodeTail, nodeHead, 0);
            }
        }

        delete textInLine;
    }

    return graph;
}

void printArgs(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        cout << i;
        cout << *argv[i] << endl;
    }
}

int main(int argc, char *argv[]) {
    FILE *file;

    // printArgs(argc, argv);

    if (argc < 6) {
        //  NOME ENTRADA ?, NOME SAIDA, DIRECIONADO ?, PESO EDGE ?, PESO NODE ?
        cout << "Os argumentos de excecucao sao invalidos. Os argumentos devem seguir o padrao: " << endl;
        cout << "ARQUIVO DE ENTRADA, ARQUIVO DE SAIDA, (0,1) SE É DIRECIONADO, (0,1) SE AS ARESTAS SAO PONDERADAS, (0,1) SE OS VERTICES TEM PESO" << endl;
        return 0;
    }

    string dirPath = "./EntryFiles/Not_Weighted_Graphs";
    bool isDirected = false, hasWeightedEdge = false, hasWeightedNode = false;

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

    // printFileDetails(file, fileName);

    Graph *graph = new Graph();

    if (!hasWeightedEdge) {
        if (!isDirected) {
            graph = processingNotWeighted(file, false);
            graph->outputGraph(argv[2], false, false);
        } else {
            graph = processingNotWeighted(file, true);
            graph->outputGraph(argv[2], false, true);
        }
    } else {
        if (!isDirected) {
            graph = processingWeighted(file, false);
            graph->outputGraph(argv[2], true, false);
        } else {
            graph = processingWeighted(file, true);
            graph->outputGraph(argv[2], true, true);
        }
    }

    int option;
    std::cout << "Digite a funcionalidade que deseja para o grafo inserido: " << endl;
    std::cout << "(1) Fecho Transitivo Direto" << endl;
    std::cout << "(2) Print nodes" << endl;
    std::cout << "(3) Print lista de adjacencia" << endl;
    std::cin >> option;

    int no;
    switch (option) {
        case 1:
            std::cout << "Fecho Transitivo Direto de qual no?" << endl;
            std::cin >> no;
            graph->fechoTransitivoDireto(no);
            break;
        case 2:
            graph->printNodes();
            break;
        case 3:
            std::cout << "Lista de adjacencia de qual no?" << endl;
            std::cin >> no;
            graph->getAllAdjacents(no);
            break;
    }

    return 0;
}
