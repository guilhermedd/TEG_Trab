typedef struct{
  int num_vertices;
  Vertices* list;
}Flower;

typedef struct{
    int degree;
    Edge *first;
}Vertices;

typedef struct{
    int next;
    Edge *foward;
}Edge;

// struct Flower create *(cria)();
void destruct(Flower *flowers);
Flower* distData();
double **compareValues(Flower* flowers);
void printing(double **distances);
void normalization(double **distances, double highest, double lowest);
void createTxt(double **distances);