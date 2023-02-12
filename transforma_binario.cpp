#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

struct estrutura {
    char *measure;
    char *quantile;
    char *sex;
    char *age;
    char *geography;
    char *ethnic;
    char *value;
};

void transformaEmBinario(estrutura); // Tranforma as informações lidas em binário
void leArquivo(); // Lê um arquivo

int main() {
    leArquivo(); 
    return 0;
}

void transformaEmBinario(estrutura informacoes) {
    ofstream arquivoBinario("subnational.txt", ios::binary|ios::app);
    arquivoBinario.write((char*) &informacoes, sizeof(informacoes));
    arquivoBinario.close();
}

void leArquivo() {
    ifstream arquivo("Subnational-period-life-tables-2017-2019-CSV.csv");
    estrutura dados;
    string tempString;
    string linha;
    int contadorLinha = 0;

    while(getline(arquivo, linha)){
        stringstream ss(linha);

        getline(ss, tempString, ',');
        dados.measure = new char[tempString.size() + 1];
        strcpy(dados.measure,tempString.c_str());

        getline(ss, tempString, ',');
        dados.quantile = new char[tempString.size() + 1];
        strcpy(dados.quantile,tempString.c_str());

        getline(ss, tempString, ',');
        dados.sex = new char[tempString.size() + 1];
        strcpy(dados.sex,tempString.c_str());

        getline(ss, tempString, ',');
        dados.age = new char[tempString.size() + 1];
        strcpy(dados.age,tempString.c_str());

        getline(ss, tempString, ',');
        dados.geography = new char[tempString.size() + 1];
        strcpy(dados.geography,tempString.c_str());

        getline(ss, tempString, ',');
        dados.ethnic = new char[tempString.size() + 1];
        strcpy(dados.ethnic,tempString.c_str());

        getline(ss, tempString, ',');
        dados.value = new char[tempString.size() + 1];
        strcpy(dados.value,tempString.c_str());

        transformaEmBinario(dados);

    }
    contadorLinha++;

}