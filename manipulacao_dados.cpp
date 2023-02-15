#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

struct Arquivo {
   char measure[500];
   char quantile[500];
   char sex[500];
   char age[500];
   char geography[500];
   char ethnic[500]; 
   char value[500];
};

class estrutura {
public:
   estrutura(); // Construtor
   void modificaRegistro(int posicaoProcurada); // Modifica um registro em uma dada posição
   void adicionaRegistro(int posicaoNovoRegistro); // Adiciona registro à uma dada posição
   void trocaRegistroDePosicao(int pos1, int pos2); // Troca a posicão de dois registros
   void imprimeTodosRegistros(); // Imprime todos os registros
   void imprimeRegistroEntrePosicoes(int inicio, int fim); // Imprime registros entre duas posições
};

estrutura::estrutura() {

}

void estrutura::modificaRegistro(int posicaoProcurada) { 
   Arquivo informacoes;

   fstream arquivoBinario("subnational.txt", ios::in|ios::out|ios::binary);

   int posicaoRegistro =  arquivoBinario.tellg() / sizeof(Arquivo); // Posicao no arquivo
   bool registroEncontrado = false;

   while(arquivoBinario.read((char*) &informacoes, sizeof(informacoes)) or registroEncontrado == false) { // Percorre todo o arquivo ou até o registro procurado ser encontrado
      if(posicaoRegistro == posicaoProcurada) {
         cin >> informacoes.measure;
         cin >> informacoes.quantile;
         cin >> informacoes.sex;
         cin >> informacoes.age;
         cin >> informacoes.geography;
         cin >> informacoes.ethnic;
         cin >> informacoes.value;

         arquivoBinario.seekg(posicaoRegistro);
         arquivoBinario.write((char*) &informacoes, sizeof(informacoes));
         registroEncontrado = true;
      }
      posicaoRegistro =  arquivoBinario.tellg() / sizeof(Arquivo);
   }
   arquivoBinario.close();
   if(registroEncontrado == false) { 
      cout << "Nenhum registro encontrado nessa posição" << endl;
   }
}

void estrutura::adicionaRegistro(int posicaoNovoRegistro) {
   Arquivo informacoes;
   Arquivo dadosNovoRegistro;
   ifstream arquivoBinario("subnational.txt", ios::binary);
   ofstream arquivoTemp("Temporario.txt", ios::binary|ios::app);

   int posicaoRegistro =  arquivoBinario.tellg() / sizeof(Arquivo); // Posicao no arquivo
   cin >> dadosNovoRegistro.measure;
   cin >> dadosNovoRegistro.quantile;
   cin >> dadosNovoRegistro.sex;
   cin >> dadosNovoRegistro.age;
   cin >> dadosNovoRegistro.geography;
   cin >> dadosNovoRegistro.ethnic;
   cin >> dadosNovoRegistro.value;

   while(arquivoBinario.read((char*) &informacoes, sizeof(informacoes))) {
      if(posicaoRegistro == posicaoNovoRegistro) {
         arquivoTemp.write((char*) &dadosNovoRegistro, sizeof(dadosNovoRegistro));
         arquivoTemp.write((char*) &informacoes, sizeof(informacoes));
      }
      else {
         arquivoTemp.write((char*) &informacoes, sizeof(informacoes));
      }
      posicaoRegistro =  arquivoBinario.tellg() / sizeof(Arquivo);
   }
   arquivoBinario.close();
   arquivoTemp.close();

   remove("subnational.txt");    
   rename("Temporario.txt", "subnational.txt");
   
}

void estrutura::trocaRegistroDePosicao(int pos1, int pos2) {
   Arquivo informacoes;
   Arquivo RegistroPos1;
   Arquivo RegistroPos2;

   ifstream arquivoBinario("subnational.txt", ios::binary);

   int posicao = arquivoBinario.tellg() / sizeof(Arquivo); // Posicao no arquivo

   while(arquivoBinario.read((char*) &informacoes, sizeof(informacoes))) {
      if(posicao == pos1) {
         RegistroPos1 = informacoes;
      }
      else if(posicao == pos2) {
         RegistroPos2 = informacoes; 
      } 
      posicao = arquivoBinario.tellg() / sizeof(Arquivo);
   }
   arquivoBinario.close();

   ifstream arquivoB("subnational.txt", ios::binary);
   ofstream arquivoTemp("Temp.txt", ios::binary|ios::app);

   int posicaoRegistro =  arquivoB.tellg() / sizeof(Arquivo); // Posicao no arquivo

   while(arquivoB.read((char*) &informacoes, sizeof(informacoes))) {
      if(posicaoRegistro == pos1) {
         arquivoTemp.write((char*) &RegistroPos2, sizeof(RegistroPos2));
      }
      else if(posicaoRegistro == pos2) {
         arquivoTemp.write((char*) &RegistroPos1, sizeof(RegistroPos1));
      }
      else {
         arquivoTemp.write((char*) &informacoes, sizeof(informacoes));
      }
      posicaoRegistro = arquivoB.tellg() / sizeof(Arquivo);
   }
   
   arquivoB.close();
   arquivoTemp.close();

   remove("subnational.txt");    
   rename("Temp.txt", "subnational.txt");
}

void estrutura::imprimeTodosRegistros() { 
   char arq[] = {"subnational.dat"};

   FILE *file = fopen(arq, "rb");
   Arquivo c;

   if(file){
      while(!feof(file)){
         if(fread(&c, sizeof(Arquivo), 1, file))
               printf("\nMeasure: %s\nQuantile: %s\nSex: %s\nAge: %s\nGeography: %s\nEthnic: %s\nValue: %s\n",
               c.measure, c.quantile, c.sex, c.age, c.geography, c.ethnic, c.value);
      }
      fclose(file);
   }
   else
      printf("\nErro ao abrir arquivo!\n");

}

void estrutura::imprimeRegistroEntrePosicoes(int inicio, int fim) { 
   Arquivo informacoes;
   ifstream arquivoBinario("subnational.txt", ios::binary);
   int pos = arquivoBinario.tellg() / sizeof(Arquivo);
   
   while(arquivoBinario.read((char*) &informacoes, sizeof(informacoes))) { // Percorre todo o arquivo mas apenas imprime os registros que se encontram entre duas posições específicas
      if(pos >= inicio and pos <= fim) {
         cout << informacoes.measure << " ";
         cout << informacoes.quantile << " "; 
         cout << informacoes.sex << " " ;
         cout << informacoes.age << " "; 
         cout << informacoes.geography << " ";
         cout << informacoes.ethnic << " "; 
         cout << informacoes.value << " "; 
      }
      pos = arquivoBinario.tellg() / sizeof(Arquivo);
   };
   arquivoBinario.close();
}

void Menu() {
   cout << "1) Adicionar registro" << endl;
   cout << "2) Alterar registro" << endl;
   cout << "3) Trocar registro de posicao" << endl;
   cout << "4) Visualizar todos os registros" << endl;
   cout << "5) Visualizar registros entre posicoes" << endl;
   cout << "6) Finalizar execucao do programa" << endl;
}

int main() {
   estrutura baseDeDados;
   int comando;

   cout << "Digite o numero correspondente a acao desejada: " << endl; 
   Menu();
   cin >> comando;

   while(comando != -1) {
         if(comando == 1) {
            int posicao;
            cout << "Posição em que o novo registro sera inserido: ";
            cin >> posicao;
            baseDeDados.adicionaRegistro(posicao);
         }

         else if(comando == 2) {
            int pos;
            cout << "Posicao do registro a ser alterado: ";
            cin >> pos;
            
            baseDeDados.modificaRegistro(pos);
         }

         else if(comando == 3) {
            int posicao1, posicao2;
            cout << "Trocar registro da posicao ";
            cin >> posicao1;
            cout << "com o registro da posicao ";
            cin >> posicao2;

            baseDeDados.trocaRegistroDePosicao(posicao1, posicao2);
         }

         else if(comando == 4) {
            baseDeDados.imprimeTodosRegistros();
         }

         else if(comando == 5) {
            int posicaoInicial, posicaoFinal;
            cout << "Imprimir da posicao ";
            cin >> posicaoInicial;
            cout << "ate a posicao ";
            cin >> posicaoFinal;

            baseDeDados.imprimeRegistroEntrePosicoes(posicaoInicial, posicaoFinal);
         }

         else if(comando == 6) {
            cout << "Fim do programa..." << endl;
            comando = -1;
         }
         
         else {
            cout << "Comando invalido!" << endl;
         }

      cout << "Digite o numero correspondente a acao desejada: " << endl; 
      Menu();
      cin >> comando;
   }
   return 0;
}
