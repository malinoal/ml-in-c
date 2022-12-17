#ifndef neural_net_h
#define neural_net_h

#include "perceptron.h"

typedef struct _layer {
  int size;
  perceptron* neurons;
  struct _layer* input;
  struct _layer* output;
} Layer;


double forward(double *input, Layer layer);
double backprop(double* gradient, Layer layer);
double adjust(perceptron neuron, double* gradient);

#endif
