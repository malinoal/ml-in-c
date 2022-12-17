#ifndef perceptron_h
#define perceptron_h

typedef struct {
  int num_inputs;
  double* input_weights;
  double bias;
  double learning_rate;
} perceptron;

perceptron create_perceptron(int num_inputs, double learning_rate);
void free_perceptron(perceptron input);
double evaluate_perceptron(perceptron neuron, double* input);
double train_perceptron(perceptron* neuron, double* input, double truth);
void test_perceptron();

#endif
