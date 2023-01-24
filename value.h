#ifndef value_h
#define value_h

enum OP { ADD, MUL, RELU, NOTHING };

typedef struct _value{
  double data;
  double grad;
  enum OP op;
  struct _value* prev;
  int num_prev;
} Value;

Value value(double value);
Value add(Value v1, Value v2);
Value mul(Value v1, Value v2);
Value relu(Value v);
void backward(Value v);
void free_value(Value v);

#endif
