#include "random.h"

static unsigned int rndm_seed = 3301;
static unsigned int rndm_mult = 13;
static unsigned int rndm_incr = 27;
static unsigned int rndm_mod = 10267;

int rndm_int() {
  rndm_seed = (rndm_mult * rndm_seed + rndm_incr) % rndm_mod;
  return rndm_seed;
}

double rndm(double max) {
  return ((double)rndm_int() / (double)(rndm_mod)) * max;
}
