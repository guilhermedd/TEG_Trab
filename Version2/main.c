#include "arq.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define size 150

// Alunos: Guilherme Diel e Luigi Belló Boscato

struct Flower *create() {
    // Tenta abrir arquivo
    FILE *file = fopen("edges.txt", "r");
    if (file == NULL) return NULL;

    int n_vertex;
    fscanf(file, "%d", &n_vertex);
    struct Flower *flowers = malloc(sizeof(struct Flower));
    flowers->vertex_amount = n_vertex;
    flowers->list = calloc(n_vertex, sizeof(struct Vertices));
    flowers->list->first = NULL;
    int v1, v2;

    while (1) {     // Bloco de codigo que vai encadear a ligacao do primeiro vertice da dupla ordenada (aresta)
        fscanf(file, "%d %d", &v1, &v2);
        if (feof(file)) return flowers;

        struct Edge *new_edge = malloc(sizeof(struct Edge));
        new_edge->next = v2;
        new_edge->foward = NULL;

        if (flowers->list[v1 - 1].first == NULL){
            flowers->list[v1 - 1].first = new_edge;
            flowers->list[v1 - 1].degree = 1;
        } else {
            flowers->list[v1 - 1].degree += 1;
            struct Edge *aux = malloc(sizeof(struct Edge));

            aux = flowers->list[v1 - 1].first;
            while (aux->foward != NULL) {
                aux = aux->foward;
            }
            aux->foward = new_edge;
        }

        if (v1 != v2) {     // Bloco de codigo que vai encadear a ligacao do segundo vertice da dupla ordenada (aresta)
            struct Edge *new_edge2 = malloc(sizeof(struct Edge));
            new_edge2->next = v1;
            new_edge2->foward = NULL;
            if (flowers->list[v2 - 1].first == NULL) {
                flowers->list[v2 - 1].degree += 1;
                flowers->list[v2 - 1].first = new_edge2;
            } else {
                flowers->list[v2 - 1].degree += 1;

                struct Edge *aux = malloc(sizeof(struct Edge));

                aux = flowers->list[v2 - 1].first;
                while (aux->foward != NULL) {
                    aux = aux->foward;
                }
                aux->foward = new_edge2;
            }
        }
    }
    if (file != NULL) fclose(file);
}

void destruct(struct Flower *flowers) {
    if (flowers == NULL) return;
    
    int vertex_amount = flowers->vertex_amount;
    for (int i = 0; i < vertex_amount; i += 1) {
        if (flowers->list[i].first == NULL){
            free(flowers->list[i].first);
        } else {
            struct Edge *aux = flowers->list[i].first;

            while (aux->foward != NULL) {
                flowers->list[i].first = aux->foward;
                free(aux);
                aux = flowers->list[i].first;
            }
            free(flowers->list[i].first);
        }
    }
    free(flowers);
    return;
}

void print_graph(struct Flower *flowers) {
    int vertex_amount = flowers->vertex_amount;
    for (int i = 0; i < vertex_amount; i ++) {
        printf("\nv[%d]", i + 1);
        struct Edge *aux = flowers->list[i].first;

        while (aux != NULL) {
            printf("-%d", aux->next);
            aux = aux->foward;
        }
        printf("\n");
    }
}


// Le a matriz e cria um .txt 
void createTxt(double **distances) {
    char buffer[100];
    FILE *file = fopen("edges.txt", "w");
    if (file == NULL) return;

    fprintf(file, "%d\n", size);
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (distances[i][j] <= 0.3) fprintf(file, "%d %d\n", i + 1, j + 1);
        }
    }
    fclose(file);
}

double **create_table() {
    FILE *file = fopen("IrisDataset.csv", "r");
    if (file == NULL) return NULL;

    double highest = 0.0; // para fazer a normalização
    double lowest = 0.0;
    double dist = 0.0;   // distancia entre nodos
    double **distances = calloc(size, sizeof(double *));
    if (distances == NULL) return NULL;

    char buffer[100];
    fpos_t current_line;
    fgetpos(file, &current_line);
    fgets(buffer, 100, file);    // Ignorando a ultima coluna
    fsetpos(file, &current_line);
    double x, y, z, w, esp, x2, y2, z2, w2, esp2;

    int i = 0, j = 1;
    while (i < size) {
        fgets(buffer, 100, file); // Ignorando a linha
        fgetpos(file, &current_line);
        fscanf(file, "%lf, %lf, %lf, %lf,", &x, &y, &z, &w);
        fgets(buffer, 100, file); // Ignorando a ultima coluna
        distances[i] = calloc(size, sizeof(double));

        while (j < size) {
            fscanf(file, "%lf, %lf, %lf, %lf,", &x2, &y2, &z2, &w2);
            fgets(buffer, 100, file);
            dist = sqrt(pow((x - x2), 2) + pow((y - y2), 2) + pow((z - z2), 2) + pow((w - w2), 2));
            distances[i][j] = dist;
            if (i == 0){
                highest = dist;
                lowest = dist;
            } else if (dist < lowest) {
                lowest = dist;
            } else if (dist > highest) {
                highest = dist;
            }
            j++;
        }
        fsetpos(file, &current_line);
        i++;
        j = i + 1;
    }
    normalize(distances, lowest, highest);
    return distances;
}

void normalize(double **distances, double lowest, double highest){
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            distances[i][j] = (distances[i][j] - lowest) / (highest - lowest);
        }
    }
}

int main(){
    double **distances = NULL;
    struct Flower *flower = NULL;
    int choice = -1;
    while (1) {
        printf("Digite 1 para montar a matriz e gerar um arquivo de texto\nDigite 2 para importar o grafo de um arquivo de texto\nDigite 3 para escrever o grafo\nDigite 0 para sair\n");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            distances = create_table();
            if (distances == NULL) {
                printf("Erro ao importar arquivo\n");
                break;
            }
            createTxt(distances);
            printf("Sucesso ao criar txt\n");
            break;

        case 2:
            flower = create();
            if (flower == NULL) {
                printf("Erro ao importar grafo do arquivo\n");
            } else {
                printf("Grafo importado com sucesso!\n");
            }
            break;

        case 3:
            if (flower == NULL) {
                printf("Grafo ainda nao foi importado!\n");
                break;
            }
            print_graph(flower);
            break;

        case 0:
            destruct(flower);
            if (distances != NULL) free(distances);
            return 0;
        }
    }
}
