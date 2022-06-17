#include <dirent.h>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

/*
 * AS FUNÇÕES CONTIDAS NESSE ARQUIVO SAO EXCLUSIVAMENTE USADAS
 * PARA DEBUGS E TESTES AUTOMATIZADOS DURANTE O DESENVOLVIMENTO. 
 * 
************************************************************/


/*
 * Função que escreve as 20 primeiras linhas do grafo
 *@params: FILE *file: arquivo onde se encontra o grafo
 *         std::string name: nome
 *@return:
 ****************************************************************/
void printArgs(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        cout << i;
        cout << *argv[i] << endl;
    }
}
/*
 * AS FUNÇÕES CONTIDAS NESSE ARQUIVO SAO EXCLUSIVAMENTE USADAS
 * PARA DEBUGS E TESTES AUTOMATIZADOS DURANTE O DESENVOLVIMENTO. 
 * 
************************************************************/


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


/*
 * Função que le os arquivos de um determinado diretório
 *@params: char *directoryPath: Caminho ate o diretório partindo de /
 * 
 *@return:
 ****************************************************************/
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
