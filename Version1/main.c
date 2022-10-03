#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arq.h"
#define size 150

// Alunos: Guilherme Diel & Luigi Belló Boscato

Flower* distData() {
     FILE* file = fopen("IrisDataset.csv", "r");

     if(file == NULL) {
          perror("Error opening the file");
          return NULL;
     } 
     
     Flower *flowers;
     flowers = (Flower*) malloc(size*sizeof(Flower));
     char aux[120];

     double x, y, z, w;
     int vertex = 1;
     while (fgets(aux, sizeof(aux), file)) {
          if (vertex == 151) break;
          flowers[vertex - 1].vertex = vertex;
          fscanf(file, "%lf, %lf, %lf, %lf,", &flowers[vertex - 1].x, &flowers[vertex - 1].y, &flowers[vertex - 1].z, &flowers[vertex - 1].w);
          vertex ++;
     }
     fclose(file);
     
     return flowers;
}

double **compareValues(Flower* flowers) {
     double highest = 0.0, lowest = 0.0, dist = 0.0;
     double **distances = calloc((size), sizeof(double *));
      
     for (int i = 0; i < size - 1; i++) {
          distances[i] = calloc(size, sizeof(double));
          for (int j = i + 1; j < size; j++) {
               dist = sqrt(pow((flowers[i].x - flowers[j].x), 2) + pow((flowers[i].y - flowers[j].y), 2) + pow((flowers[i].z - flowers[j].z), 2) + pow((flowers[i].w - flowers[j].w), 2));
               
               if(i == 0) {
                    highest = dist;
                    lowest = dist;
               }
               if (dist > highest) highest = dist;
               if (dist < lowest) lowest = dist;
               if (i == j) printf("%d %d\n", i, j);
               distances[i][j] = dist;
          }
     }
     normalization(distances, highest, lowest);
     return distances;
}

void normalization(double **distances, double highest, double lowest) {
     for (int i = 0; i < size - 1; i++) {
          for (int j = i + 1; j < size; j++) {
               distances[i][j] = (distances[i][j] - lowest) / (highest - lowest);
          }
     }
}

void createTxt(double **distances) {
     FILE *out = fopen ("output.txt", "w");
     fprintf(out, "%d\n", size);
     for (int i = 0; i < size - 1; i++) {
          for (int j = i + 1; j < size; j++) {
               if (distances[i][j] < 0.3){
                    fprintf(out, "%d, %d\n", i + 1, j + 1);
               }
          }
     }

     fclose(out);
}

void printing(double **distances) {
     for (int i = 0; i < size - 1; i++) {
          for (int j = i + 1; j < size; j++) {
               printf("%lf ", distances[i][j]);
          }
          printf("\n");
     }
}

int main() {
     double **distances = NULL;
     Flower *flowers = NULL;
     
     flowers = distData();
     distances = compareValues(flowers);
     createTxt(distances);

     return 0;
}