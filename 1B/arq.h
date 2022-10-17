struct Flower{
  int vertex_amount;
  struct Vertices *list;
};

struct Vertices{
  int degree;
  struct Edge *first;
};

struct Edge{
  int next;
  struct Edge *foward;
};

struct node {
  int vertex;
  struct node* next;
};

struct Graph {
  int numVertices;
  int* visited;

  // We need int** to store a two dimensional array.
  // Similary, we need struct node** to store an array of Linked lists
  struct node** adjLists;
};

struct Flower *create();
void destruct(struct Flower *flowers);
void print_graph(struct Flower *flowers);
void createTxt(double **distances);
double **create_table();
void normalize(double **distances, double highest, double lowest);
void printGraph(struct Graph* graph);
void addEdge(struct Graph* graph, int src, int dest);
struct Graph* createGraph(int vertices);
struct node* createNode(int v);
void DFS(struct Graph* graph, int vertex);