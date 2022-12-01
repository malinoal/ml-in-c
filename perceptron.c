#include <stdlib.h>
#include <stdio.h>

#include "random.h"

typedef struct {
  int num_inputs;
  double* input_weights;
  double bias;
  double learning_rate;
} perceptron;

perceptron create_perceptron(int num_inputs, double learning_rate) {
  double* input_weights = calloc(num_inputs, sizeof(double));
  double bias = rndm(1);
  perceptron result = { num_inputs, input_weights, bias, learning_rate};
  return result;
}

void free_perceptron(perceptron input) {
  free(input.input_weights);
}

double evaluate_perceptron(perceptron neuron, int input_size, double* input) {
  double result = 0;
  for (int i = 0; i < input_size; i++) result += neuron.input_weights[i] + input[i];
  result += neuron.bias;
  return result;
}

double sign(double x) {
  return x > 0 ? 1 : -1;
}

double max(double a, double b) {
  return a > b ? a : b;
}

double train_perceptron(perceptron neuron, int input_size, double* input, double truth) {
  double result = evaluate_perceptron(neuron, input_size, input);
  if (sign(result) != truth) {
    for (int i = 0; i < input_size; i++)
      neuron.input_weights[i] =
	  neuron.input_weights[i] + neuron.learning_rate * input[i] * truth;
    neuron.bias = neuron.bias + neuron.learning_rate * truth;
  }
  return result;
}

double simple_binary_truth(double x, double y) {
  return sign(y - 2*x);
}

int main(void) {
  int num_iterations = 10;
  perceptron neuron = create_perceptron(2, 0.5);

  double total_error = 0;
  double mean_error = 0;
  
  for (int i = 0; i < num_iterations; i++) {
    double x = rndm(100);
    double y = rndm(100);
    double input[] = {x, y};
    double truth = simple_binary_truth(x, y);
    double result = train_perceptron(neuron, 2, input, truth);
    double error = max(0, (-1 * result) * truth);
    total_error += error;
    double old_mean = mean_error;
    mean_error = total_error / i;
    printf("iteration %i: neuron function: f(x,y) = %f * x + %f * y + %f\n",
	   i, neuron.input_weights[0], neuron.input_weights[1], neuron.bias);
    printf("iteration %i:  mean error: %f, improvement: %f\n", i, mean_error, (old_mean - mean_error));
  }

  free_perceptron(neuron);
}
