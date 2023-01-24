#include <stdlib.h>
#include "math.h"
#include "value.h"


Value value(double value) {
  Value result = { value, 0.0f, NOTHING, NULL, 0, false };
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

int build_topo(Value v, Value* topo, int topo_size) {
  if (!v.visited) {
    v.visited = true;
    for (int i = 0; i < v.num_prev; i++) {
      topo_size = build_topo(v.prev[i], topo, topo_size);
      topo[topo_size++] = v;
    }
  }
  return topo_size;
}

void backward(Value v) {
  //TODO
}

void backprop(Value v, int network_size) {
  Value* topo = calloc(network_size, sizeof(Value));
  build_topo(v, topo, 0);
  for (int i = network_size; i >= 0; i--) {
    backward(topo[i]);
  }
}

void free_value(Value v) {
  for(int i = 0; i < v.num_prev; i++) {
    free_value(v.prev[i]);
  }
  free(v.prev);
}
