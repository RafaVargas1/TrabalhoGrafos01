#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include <iostream>

#include "./Graph/graph.cpp"
#include "./Node/node.cpp"
#include "./Edge/edge.cpp"

using std::cout; using std::endl;
using std::copy; using std::string;

void printFileDetails(FILE *file, std::string name){
    int i = 1;
    cout << "===== " << name << " =====" << endl;
    cout << "PRIMEIRAS 20 LINHAS " << endl;

    while (!feof(file)){
        char line[100];


        char *result = fgets(line, 100, file);

        if (result && i <= 20)
            cout << "Linha " << i << ": " << line << endl;


        delete result;
        i++;
    }

    cout << " === TOTAL DE LINHAS: " << i << " === \n\n" << endl;

    fclose(file);
}


void readFilesInDirectory (const char *directoryPath) {
    DIR *dir;
    FILE *file;
    struct dirent *lsdir;

    dir = opendir(directoryPath);

    while ( ( lsdir = readdir(dir) ) != NULL ) {

        string path = std::string(directoryPath) + "/" + std::string(lsdir->d_name);
        file = fopen(path.c_str(), "rt");

        if (file == NULL){
            perror("Erro ao abrir o arquivo");
        } else {
            printFileDetails(file, lsdir->d_name);
        }

    }
}

void processingNotWeighted(FILE *file) {
    int i=0;

    Graph *graph = new Graph();

    graph->printGraph();  // Nao funciona


    while (!feof(file)){
        char line[9];
        char *result = fgets(line, 100, file);

        if (i > 253600){
            int space = string(result).find(" ", 0);
            
            
            string head = string(result).substr(0, space);
            string tail = string(result).substr(space, string(result).size() );
           
            int intHead = stoi(head);
            int intTail = stoi(tail);

            Node *nodeHead = graph->createNodeIfDoesntExist(intHead, 0);
            Node *nodeTail = graph->createNodeIfDoesntExist(intTail, 0);

            Edge *edge1 = graph->createEdge(nodeHead, nodeTail, 0);
            Edge *edge2 = graph->createEdge(nodeTail, nodeHead, 0);

        }

        i++;
        delete result;
    }

    graph->printGraph(); // Nao funciona
}

void printArgs(int argc, char *argv[]){
    for (int i=0; i<argc; i++){
        cout << i;
        cout << *argv[i] << endl;
    }
}


int main(int argc, char *argv[]){
    FILE *file;

    // printArgs(argc, argv);

    if (argc < 6){
    //  NOME ENTRADA ?, NOME SAIDA, DIRECIONADO ?, ARESTA PONDERADA ?, PESO VERTICES ?,
        cout << "Os argumentos de excecucao sao invalidos. Os argumentos devem seguir o padrao: " << endl;
        cout << "ARQUIVO DE ENTRADA, ARQUIVO DE SAIDA, (0,1) SE É DIRECIONADO, (0,1) SE AS ARESTAS SAO PONDERADAS, (0,1) SE OS VERTICES TEM PESO" << endl;
        return 0;
    }

    string dirPath = "./EntryFiles/Not_Weighted_Graphs";        
    bool isDirected = false, hasWeightedEdge = false, hasWeightedVertex = false;

    if ( *argv[3] == '1') 
        isDirected = true;

    if ( *argv[4] == '1' )
        hasWeightedEdge = true;

    if ( *argv[5] == '1' ) {
        hasWeightedVertex = true;
        dirPath = "./EntryFiles/Weighted_Graphs";
    }   

    string fileName = argv[1];

    string path = string(dirPath) + "/" + string(fileName);
    file = fopen(path.c_str(), "rt");

    if (file == NULL)
        perror("Erro ao abrir o arquivo");
    
    // printFileDetails(file, fileName);

    if (!hasWeightedVertex){ 
        processingNotWeighted(file);
    }

    return 0;
}

