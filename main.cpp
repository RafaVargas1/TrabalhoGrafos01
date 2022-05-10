#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include <iostream>

// #include "./Vertex/vertex.h";
// #include "./Edge/edge.h";

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

    while (!feof(file)){
        char line[9];
        char *result = fgets(line, 100, file);

        if (i > 253600){
            int space = string(result).find(" ", 0);
            
            
            string vertex = string(result).substr(0, space);
            string node = string(result).substr(space, string(result).size() );

            cout << vertex << " " << node << endl;
        }

        i++;
        delete result;
    }
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

    // DIRECIONADO ?, ARESTA PONDERADA ?, PESO VERTICES ?, NOME ARQUIVO ?
    string dirPath = "./EntryFiles/Not_Weighted_Graphs";        
    bool isDirected = false, hasWeightedEdge = false, hasWeightedVertex = false;

    if ( *argv[2] == '1') 
        isDirected = true;

    if ( *argv[3] == '1' )
        hasWeightedEdge = true;

    if ( *argv[4] == '1' ) {
        hasWeightedVertex = true;
        dirPath = "./EntryFiles/Weighted_Graphs";
    }   

    string fileName = argv[5];


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

