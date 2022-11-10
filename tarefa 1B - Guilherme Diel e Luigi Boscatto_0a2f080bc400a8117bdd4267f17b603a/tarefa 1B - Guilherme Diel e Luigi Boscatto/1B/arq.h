typedef struct Flower{
  int vertex_amount;
  struct Vertices *list;
} Flower;

typedef struct Vertices{
  int degree;
  struct Edge *first;
} Vertices;

typedef struct Edge{
  int next;
  struct Edge *foward;
} Edge;

struct Flower *create();
void destruct(struct Flower *flowers);
void print_graph(struct Flower *flowers);
void createTxt(double **distances);
double **create_table();
void normalize(double **distances, double highest, double lowest);