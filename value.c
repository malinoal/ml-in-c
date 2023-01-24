#include <stdlib.h>
#include "math.h"
#include "value.h"


Value value(double value) {
  Value result = { value, 0.0f, NOTHING, NULL, 0 };
  return result;
}

Value add(Value v1, Value v2) {
  Value result = value(v1.data + v2.data);
  result.op = ADD;
  Value prev[] = {v1, v2};
  result.prev = prev;
  result.num_prev = 2;
  return result;
}

Value mul(Value v1, Value v2) {
  Value result = value(v1.data * v2.data);
  result.op = MUL;
  Value prev[] = {v1, v2};
  result.prev = prev;
  result.num_prev = 2;
  return result;
}

Value relu(Value v) {
  Value result = value(max(0, v.data));
  result.op = RELU;
  Value prev[] = {v};
  result.prev = prev;
  result.num_prev = 1;
  return result;
}

void backward(Value v) {
  //TODO
}

void free_value(Value v) {
  for(int i = 0; i < v.num_prev; i++) {
    free_value(v.prev[i]);
  }
  free(v.prev);
}
