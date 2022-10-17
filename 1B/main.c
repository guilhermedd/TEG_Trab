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
    for (int i = 0; i < vertex_amount; i += 1) {
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

// DFS algorithm

struct node* createNode(int v);

void DFS(struct Graph* graph, int vertex) {
    struct node* adjList = graph->adjLists[vertex];
    struct node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("Visited %d \n", vertex);
    // visited_node[visited] = vertex;
    // visited++;
    while (temp != NULL) {
    int connectedVertex = temp->vertex;

    if (graph->visited[connectedVertex] == 0) {
        DFS(graph, connectedVertex);
    }
    temp = temp->next;
    }
}

// Create a node
struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Create graph
struct Graph* createGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node*));

  graph->visited = malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }
  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int src, int dest) {
  // Add edge from src to dest
  struct node* newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  // Add edge from dest to src
  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

// Print the graph
void printGraph(struct Graph* graph) {
  int v;
  for (v = 0; v < graph->numVertices; v++) {
    struct node* temp = graph->adjLists[v];
    printf("\n Adjacency list of vertex %d\n ", v);
    while (temp) {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void find_adjacent(double **distances) {
    char buffer[100];
    FILE *file = fopen("edges.txt", "w");
    struct Graph* graph = createGraph(size);
    if (file == NULL) {
        printf("Error");
        return;
    }
    fprintf(file, "%d\n", size);
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (distances[i][j] <= 0.3) addEdge(graph, i + 1, j + 1);
        }
    }

    // printGraph(graph);
    DFS(graph, size);

    // qsort(visited_node, 5, sizeof(int), cmpfunc);


    fclose(file);
}

int main(){
    double **distances = NULL;
    struct Flower *flower = NULL;
    int choice = -1;

    while (1) {
        printf("Digite 0 para sair\nDigite 1 para montar a matriz e gerar um arquivo de texto\nDigite 2 para importar o grafo de um arquivo de texto\nDigite 3 para escrever o grafo\nDigite 4 para achar a lista de adjacencias\n");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            destruct(flower);
            if (distances != NULL) free(distances);
            return 0;
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
        case 4:
            find_adjacent(distances);
            break;

        }
    }
}
