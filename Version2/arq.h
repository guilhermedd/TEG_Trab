struct Flower
{
  int num_vertices;
  struct Vertices *list;
};

struct Vertices
{
  int degree;
  struct Edge *first;
};

struct Edge
{
  int next;
  struct Edge *foward;
};

// struct Flower create *(cria)();
struct create*(cria)();
void destruct(struct Flower *flowers);
void print_graph(struct Flower *flowers);
void createTxt(double **matrix);
double **create_table();
void normalize(double **distances, double highest, double lowest);