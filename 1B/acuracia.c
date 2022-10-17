#include <stdio.h>


// Alunos: Guilherme Diel & Luigi Belló Boscato


/*
     Verdadeiro Positivo (mesma especie e iguais) mesmo grupo             Falso Negativo (especies diferentes porem iguais) deveria estar em algum grupo, porem nao esta
     Falso Positivo  (mesma especia porem diferentes) grupos diferentes   Verdadeiro Negativo (especie diferente porem diferente) nao esta em um grupo que nao deveria estar

     1 2
     1 3
     1 4

     1 23
     2 13
     3 12
*/
typedef struct {
    unsigned int first;
    unsigned int second;
} edge;

void connected_components_recursive(const edge *edges, unsigned int n, int *components, unsigned int order, unsigned int vertex, unsigned int component) {
     unsigned int i;

     // Put this vertex in the current component
     components[vertex] = component; 
     for (i = 0; i < n; i++) {
          if (edges[i].first == vertex || edges[i].second == vertex) {
               // Adjacent
               const unsigned int neighbour = edges[i].first == vertex ?
                         edges[i].second : edges[i].first;
               if (components[neighbour] == -1) {
                    // Not yet visited
                    connected_components_recursive(edges, n, components, order, neighbour, component);
               }
          }
     }
}

unsigned int connected_components(const edge *edges, unsigned int n, unsigned int order, int **components) {
     unsigned int i;
     unsigned int component = 0;
     *components = malloc(order * sizeof(int));
     if (components == NULL) {
          return 0;
     }
     for (i = 0; i < order; i++) {
          (*components)[i] = -1;
     }
          
     for (i = 0; i < order; i++) {
          if ((*components)[i] == -1) {
               connected_components_recursive(edges, n, *components, order, i, component);
               component++;
          }
     }
     return component;
}


void calcAcuracia() {
     // FILE *file = fopen("edges.txt", "r");
     // char aux[100];
     // int edge1, edge2;
     // int TP = 0, TN = 0, FP = 0, FN = 0;
     // int group1, group2, group3;

     // while (fgets(aux, sizeof(aux), file)) {
     //      fscanf(file, "%i %i", edge1, edge2);
     //      if (edge1 <= 50){
     //           if (edge2 <= 50){
                    
     //           }
     //      }
     // }


}

int main() {

     return 0;
}