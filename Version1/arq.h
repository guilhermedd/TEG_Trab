typedef struct {
  int vertex;
  double x;
  double y;
  double z;
  double w;
} Flower;

struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode* head;
};

Flower* distData();
double **compareValues(Flower* flowers);
void printing(double **distances);
void normalization(double **distances, double highest, double lowest);
void createTxt(double **distances);