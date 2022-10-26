#include <stdio.h>


// Alunos: Guilherme Diel & Luigi Belló Boscato


/*
     Verdadeiro Positivo (mesma especie e iguais) mesmo grupo             Falso Negativo (especies diferentes porem iguais) deveria estar em algum grupo, porem nao esta
     Falso Positivo  (mesma especia porem diferentes) grupos diferentes   Verdadeiro Negativo (especie diferente porem diferente) nao esta em um grupo que nao deveria estar

     1 2
     1 3
     1 5

     2 3

     4 5
     4 6

     5 6
     

     -----
     1 2
     1 5 -> 1 50
     2 4 -> 2 15
     51 52 -> 51 55 
     
*/

double calcAcuracia() {
     FILE *file = fopen("edges.txt", "r");
     char aux[100];
     int edge1, edge2, prevEdge1 = 0, prevEdge2 = 0, pinto;
     int TP = 0, TN = 0, FP = 0, FN = 0;
     double acuracia;

     fscanf(file, "%i", &edge1);
     do {
          fscanf(file, "%i %i", &edge1, &edge2);
          //  Entre as arestas do primeiro grupo: 
          if (edge1 <= 50) {
               if (edge1 == prevEdge1 && edge2 > 50 && prevEdge2 < 50) {
                    //  Se a A1 anterior e atual forem iguais mas a ultima A2 for > 50 (nao pertence ao grupo) e a penultima A2 for < 50, quantas faltam entre a penultima e 50
                    /* Ex:
                    1 3
                    1 4
                    1 5  
                    1 99 <- falta de (1 5) até (1 50)
                    */
                    FN += 50 - prevEdge2;
               } else if (edge1 != prevEdge1 && edge2 != edge1 + 1) {
                    //  Se mudar de A1(aresta 1) entre a anterior e a atual (Mudar de planta) e a primeira A2 for diferente de A1 + 1 ela não comecou onde deveria (por exemplo comecar a lisa com: 1 3 em vez de 1 2)
                    FN += edge2 - (edge1 + 1);
               }
          }


          if ((edge1 <= 50 && edge2 <= 50) || (edge1 > 50 && edge2 > 50)){  // Se ambos pertencem ao mesmo grupo -> Verdadeiro Positivo += 1
               TP++;

               // Se a  1a aresta anterior e atual forem iguais e a 2a aresta anterior e a atual pertencerem ao mesmo grupo, a diferença entre elas é o FN
               /* Ex:
               53 54
               53 57 <- falta (53 55), (53 56)
               
               */
               if ((prevEdge2 <= 50 && edge2 <= 50) || (prevEdge2 > 50 && edge2 > 50)) {
                    if (edge1 == prevEdge1 && edge2 != prevEdge2 + 1) { 
                         FN += edge2 - (prevEdge2 + 1);
                    }
               }

          } else { // Se pertencem a grupos diferentes -> Falso Positivo += 1
               FP ++;
          }


          prevEdge1 = edge1;
          prevEdge2 = edge2;

     } while (fgets(aux, sizeof(aux), file));
     printf("TP: %i\nFN: %i\nFP: %i", TP, FN, FP);


     acuracia = (TP + TN) / (TP + FP + TN + FN);
     return acuracia;
}

int main() {
     double acuracia = calcAcuracia();
     printf("\nAcuracia:  %f",acuracia);
     return 0;
}