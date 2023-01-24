#include <stdlib.h>

#include "math.h"
#include "neural_net.h"
#include "perceptron.h"

double forward(double *input, Layer layer) {
  double* outputs = calloc(layer.size, sizeof(double));
  for (int i = 0; i < layer.size; i++) {
    outputs[i] = max(0, evaluate_perceptron(layer.neurons[i], input));
  }

  double result;
  if (layer.output != NULL) {
    result = forward(outputs, *layer.output);
  } else {
    result = outputs[0];
  }

  free(outputs);

  return result;
}

//double backprop(double* gradient, Layer layer) {
//}

double adjust(perceptron neuron, double* gradient) {
}
