#include "arquivo.h"

class estrutura {
public:
   void modificaRegistro(int posicaoProcurada); // Modifica um registro em uma dada posição
   void adicionaRegistro(int posicaoNovoRegistro); // Adiciona registro à uma dada posição
   void trocaRegistroDePosicao(int pos1, int pos2); // Troca a posicão de dois registros
   void imprimeTodosRegistros(); // Imprime todos os registros
   void imprimeRegistroEntrePosicoes(int inicio, int fim); // Imprime registros entre duas posições
};

void estrutura::imprimeTodosRegistros() { 
   char arq[] = {"subnationalOrder.dat"};

   FILE *file = fopen(arq, "rb");
   Arquivo c;

   cout << "--------------------------Valores-----------------------\n";
   if(file){
      while(!feof(file)){
         if(fread(&c, sizeof(Arquivo), 1, file)){
            printf("Measure: %s\nQuantile: %s\nArea: %s\nSex: %s\nAge: %s\nEethnic: %s\nValue: %s\n",
               c.measure, c.quantile, c.sex, c.age, c.geography, c.ethnic, c.value);
            cout << "-------------------------------------------------------\n";
         }
      }
      fclose(file);
   }
   else
      printf("\nErro ao abrir arquivo!\n");
   cout << "-------------------------------------------------------\n";

}

int main() {
   estrutura baseDeDados;
   baseDeDados.imprimeTodosRegistros();
   return 0;
}
