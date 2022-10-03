typedef struct {
  int vertex;
  double x;
  double y;
  double z;
  double w;
} Flower;

Flower* distData();
double **compareValues(Flower* flowers);
void printing(double **distances);
void normalization(double **distances, double highest, double lowest);