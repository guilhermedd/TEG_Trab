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
     
*/

double calcAcuracia() {
     FILE *file = fopen("edges.txt", "r");
     // FILE *out = fopen("output.txt", "w");
     char aux[100];
     int edge1, edge2, prevEdge1 = -1, prevEdge2 = -1;
     int TP = 0, TN = 0, FP = 0, FN = 0;
     double acuracia;

     fscanf(file, "%i", &edge1);
     do {
          fscanf(file, "%i %i", &edge1, &edge2);

          if ((edge1 <= 50 && edge2 <= 50) || (edge1 > 50 && edge2 > 50)){  // Se ambos pertencem ao mesmo grupo -> Verdadeiro Positivo += 1
               TP++;
               // fprintf(out, " TP = %i  - %i \n", edge1, edge2);

               if (edge1 == prevEdge1 && edge2 != prevEdge2 + 1) { // Se pular alguma flor que nao deveria ser pulada, a quantidade de flores puladas são as flores que deveriam estar ali
                    FN += edge2 - prevEdge2;
                    // fprintf(out, " FN = %i  ->   %i \n", edge2, prevEdge2);
               }
               
          } else { // Se pertencem a grupos diferentes -> Falso Positivo += 1
               // fprintf(out, " FP = | %i  - %i |\n", edge1, edge2);  
               FP ++;
          }


          prevEdge1 = edge1;
          prevEdge2 = edge2;

     } while (fgets(aux, sizeof(aux), file));
     // printf("\nR: %i", FP);

     acuracia = (TP + TN) / (TP + FP + TN + FN);
     return acuracia;
}

int main() {
     double acuracia = calcAcuracia();
     printf("\nAcuracia:  %lf",acuracia);
     return 0;
}