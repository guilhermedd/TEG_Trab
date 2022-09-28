#include <stdlib.h>
#include <stdio.h>
#include "arq.h"
#define size 150

Flower* distData() {
     FILE* file = fopen("IrisDataset.csv", "r");

     if(file == NULL) {
          perror("Error opening the file");
          return NULL;
     } 

     Flower *flowers[size];
     char aux[60] = fgets(aux, 30, file);

     double x, y, z, w;
     int vertex = 1;
     while (!feof(file)) {
          flowers[vertex - 1]->vertex = vertex;
          fscanf(file, "%f, %f, %f, %f,", &flowers[vertex - 1]->x, &flowers[vertex - 1]->y, &flowers[vertex - 1]->z, &flowers[vertex - 1]->w);
          vertex ++;
     }

     fclose(file);

     return flowers;
}

void compareValues(Flower* flowers) {
     double maior, menor, dist;
     for (int i  = 0; i < size - 1; i++) {
          for (int j = i + 1; j < size; j++) {
               dist = sqrt(pow((flowers[i].x - flowers[j].x), 2) + pow((flowers[i].y - flowers[j].y), 2) + pow((flowers[i].z - flowers[j].z), 2) + pow((flowers[i].w - flowers[j].w), 2));
               
               if(i == 0) {
                    maior = dist;
                    menor = dist;
               }
               if (dist > maior) maior = dist;
               if (dist < menor) menor = dist;

          }
     }
}

