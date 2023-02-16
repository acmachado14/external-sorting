#include "arquivo.h"
#include <sstream>

/*
    Modos de abertura de arquivos:
    wb -> Escrita
    rb -> leitura
    ab -> anexar
    rb+ -> leitura e escrita
    wb+ -> leitura e escrita (apaga o conteúdo caso o arquivo exista)
    ab+ -> leitura e escrita (adiciona ao final do arquivo)
*/

using namespace std;

int contador = 0;

void transformaEmBinario(Arquivo, char arq[]); // Tranforma as informações lidas em binário

void transformaEmBinario(Arquivo dados, char arq[]) {
    FILE *file = fopen(arq, "ab");

    if(file){
        fwrite(&dados, sizeof(Arquivo), 1, file);
        fclose(file);
    }
    else
        printf("\nErro ao abrir arquivo!\n");

}

vector<string> split(const string &str, char sep)
{
    vector<string> tokens;
 
    string token;
    stringstream ss(str);
    while (getline(ss, token, ',')) {
        token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
 
    return tokens;
}

int main() {
    ifstream arquivo("Subnational-period-life-tables-2017-2019-CSV.csv");
    Arquivo dados;
    string tempString;
    string linha;

    char arquivoEscrita[] = {"subnational.dat"};

    while(getline(arquivo, linha)){
        char sep = ',';
        vector<string> tokens = split(linha, sep);

        strcpy(dados.measure,tokens[0].data());
        strcpy(dados.quantile,tokens[1].data());
        strcpy(dados.sex,tokens[2].data());
        strcpy(dados.age,tokens[3].data());
        strcpy(dados.geography,tokens[4].data());
        strcpy(dados.ethnic,tokens[5].data());
        strcpy(dados.value,tokens[6].data());

        transformaEmBinario(dados, arquivoEscrita);
    }

    return 0;
}