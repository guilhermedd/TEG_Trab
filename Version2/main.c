#include "arq.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define size 150
// Alunos: Guilherme Diel e Luigi Belló Boscato
Flower *(cria)()
{
    // Tenta abrir arquivo
    FILE *fp = fopen("grafo.txt", "r");
    if (fp == NULL)
    {
        return NULL;
    }

    int n_vertices;
    fscanf(fp, "%d", &n_vertices);
    Flower *flowers = malloc(sizeof(Flower));
    flowers->num_vertices = n_vertices;
    flowers->list = calloc(n_vertices,sizeof(Vertices));
    flowers->list->first = NULL;
    int v1, v2;

    while (1)
    {
        fscanf(fp, "%d %d", &v1, &v2);
        if(feof(fp))
            return flowers;

        // Bloco de codigo que vai encadear a ligacao do primeiro vertice da dupla ordenada (aresta)

        Edge *new_edge = malloc(sizeof(Edge));
        new_edge->next = v2;
        new_edge->foward = NULL;
        if (flowers->list[v1 - 1].first == NULL)
        {
            flowers->list[v1 - 1].first = new_edge;
            flowers->list[v1 - 1].degree = 1;
        }
        else
        {
            flowers->list[v1 - 1].degree += 1;
            Edge *aux = malloc(sizeof(Edge));

            aux = flowers->list[v1 - 1].first;
            while (aux->foward != NULL)
            {
                aux = aux->foward;
            }
            aux->foward = new_edge;
        }
        if (v1 != v2)
        {

            // Bloco de codigo que vai encadear a ligacao do segundo vertice da dupla ordenada (aresta)

            Edge *new_edge2 = malloc(sizeof(Edge));
            new_edge2->next = v1;
            new_edge2->foward = NULL;
            if (flowers->list[v2 - 1].first == NULL)
            {
                flowers->list[v2 - 1].degree += 1;
                flowers->list[v2 - 1].first = new_edge2;
            }
            else
            {
                flowers->list[v2 - 1].degree += 1;

                Edge *aux = malloc(sizeof(Edge));

                aux = flowers->list[v2 - 1].first;
                while (aux->foward != NULL)
                {
                    aux = aux->foward;
                }
                aux->foward = new_edge2;
            }
        }
    }
    if (fp != NULL)
        fclose(fp);
}

void destroi(Flower *flowers)
{
    if(flowers == NULL)
        return;
    int tamanho = flowers->num_vertices;
    for (int i = 0; i < tamanho; i += 1)
    {
        if (flowers->list[i].first == NULL)
            free(flowers->list[i].first);
        else
        {
            Edge *aux = flowers->list[i].first;

            while (aux->foward != NULL)
            {
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

void printar_grafo(Flower *flowers)
{
    int tamanho = flowers->num_vertices;
    for (int i = 0; i < tamanho; i += 1)
    {
        printf("\nv[%d]", i + 1);
        Edge *aux = flowers->list[i].first;

        while (aux != NULL)
        {
            printf("-%d", aux->next);
            aux = aux->foward;
        }
        printf("\n");
    }
}

void fazerTxt(double **matrix) // le a matriz e cria um txt
{
    char buffer[100];
    FILE *fp = fopen("grafo.txt", "w");
    if (fp == NULL)
    {
        return;
    }
    fprintf(fp, "%d\n", size);
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (matrix[i][j] <= 0.3)
                fprintf(fp, "%d %d\n", i + 1, j + 1);
        }
    }
    fclose(fp);
}

double **cria_tabela()
{
    FILE *fp = fopen("IrisDataset.csv", "r");
    if (fp == NULL)
    {
        return NULL;
    }
    double maior = 0; // para fazer a normalização
    double menor = 0;
    double dist = 0; // distancia entre nodos
    double **matrix = calloc(size,sizeof(double *));
    if (matrix == NULL)
        return NULL;
    char buffer[100];
    fpos_t linha_atual;
    fgetpos(fp, &linha_atual);
    fgets(buffer, 100, fp); // Ignorando a ultima coluna
    fsetpos(fp, &linha_atual);
    double x, y, z, w, esp, x2, y2, z2, w2, esp2;

    int i = 0, j = 1;
    while (i <size)
    {
        fgets(buffer, 100, fp); // Ignorando a linha
        fgetpos(fp, &linha_atual);
        fscanf(fp, "%lf, %lf, %lf, %lf,", &x, &y, &z, &w);
        fgets(buffer, 100, fp); // Ignorando a ultima coluna
        matrix[i] = calloc(size,sizeof(double));

        while (j <size)
        {

            fscanf(fp, "%lf, %lf, %lf, %lf,", &x2, &y2, &z2, &w2);
            fgets(buffer, 100, fp);
            dist = sqrt(pow((x - x2), 2) + pow((y - y2), 2) + pow((z - z2), 2) + pow((w - w2), 2));
            matrix[i][j] = dist;
            if (i == 0)
            {
                maior = dist;
                menor = dist;
            }
            else if (dist < menor)
            {
                menor = dist;
            }
            else if (dist > maior)
            {
                maior = dist;
            }

            j++;
        }
        fsetpos(fp, &linha_atual);
        i++;
        j = i + 1;
    }
    normaliza(matrix, menor, maior);
    return matrix;
}

void normaliza(double **matrix, double menor, double maior)
{

    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            matrix[i][j] = (matrix[i][j] - menor) / (maior - menor);
        }
    }
}
