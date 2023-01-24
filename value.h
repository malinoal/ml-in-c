#ifndef value_h
#define value_h
#include "neural_net.h"
#include <stdbool.h>

enum OP { ADD, MUL, RELU, NOTHING };

typedef struct _value{
  double data;
  double grad;
  enum OP op;
  struct _value* prev;
  int num_prev;
  bool visited;
} Value;

Value value(double value);
Value add(Value v1, Value v2);
Value mul(Value v1, Value v2);
Value relu(Value v);
void backward(Value v);
void backprop(Value v, int network_size);
void free_value(Value v);

#endif
