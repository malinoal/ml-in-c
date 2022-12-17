#include <stdlib.h>
#include <stdio.h>

#include "random.h"
#include "perceptron.h"
#include "math.h"


perceptron create_perceptron(int num_inputs, double learning_rate) {
  double* input_weights = calloc(num_inputs, sizeof(double)); 
  for (int i = 0; i < num_inputs; i++) input_weights[i] = rndm(1); //TODO: initialize from normal distribution
  double bias = rndm(1);
  perceptron result = { num_inputs, input_weights, bias, learning_rate};
  return result;
}

void free_perceptron(perceptron input) {
  free(input.input_weights);
}

double evaluate_perceptron(perceptron neuron, double* input) {
  double result = 0;
  for (int i = 0; i < neuron.num_inputs; i++) result += neuron.input_weights[i] * input[i];
  result += neuron.bias;
  return result;
}


double train_perceptron(perceptron* neuron, double* input, double truth) {
  double result = evaluate_perceptron(*neuron, input);
  if (sign(result) != truth) {
    for (int i = 0; i < neuron->num_inputs; i++)
      neuron->input_weights[i] =
	  neuron->input_weights[i] + neuron->learning_rate * input[i] * truth;
    neuron->bias = neuron->bias + neuron->learning_rate * truth;
  }
  return result;
}

double simple_binary_truth(double x, double y) {
  return sign(y - 2*x);
}

void test_perceptron() {
  int num_iterations = 100000;
  perceptron neuron = create_perceptron(2, 0.1);

  double total_error = 0;
  double mean_error = 0;
  int correct = 0;
  int false = 0;

  for (int i = 0; i < num_iterations; i++) {
    double x = rndm(100);
    double y = rndm(100);
    double input[] = {x, y};
    double truth = simple_binary_truth(x, y);
    double result = train_perceptron(&neuron, input, truth);
    double error = max(0, (-1 * result) * truth);
    if (error > 0) false++; else correct++;
    total_error += error;
    double old_mean = mean_error;
    mean_error = total_error / i;
    printf("iteration %i: neuron function: %f * x + %f * y + %f\n",
	   i, neuron.input_weights[0], neuron.input_weights[1], neuron.bias);
    printf("iteration %i: correct: %f, current error: %f  mean error: %f, improvement: %f\n",
	   i, ((double)((double)correct/(correct+false))), error,  mean_error, (old_mean - mean_error));
    if (error > 0) printf("ERROR: x: %f, y: %f, wrongly classified as %f but should be %f\n", x, y, result, truth);
  }

  free_perceptron(neuron);
}
