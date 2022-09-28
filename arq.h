typedef struct {
  int vertex;
  double x;
  double y;
  double z;
  double w;
  double normalizedValue;
  double adjacent[];
} Flower;

Flower* distData();
void compareValues(Flower* flowers);