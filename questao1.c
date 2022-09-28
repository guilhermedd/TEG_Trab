#include <stdlib.h>
#include <stdio.h>
#include "arq.h"
#include "flower.c"
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

int main() {
     Flower *flowers;

     return 0;
}

/*
     1 = 2, 5, 6, 8
     2 = 1, 4, 5, 20 
*/ 