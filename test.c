
#include "stdlib.h"

typedef unsigned char OnigUChar;

typedef long long intptr_t;
typedef intptr_t StackIndex;

struct mem_struct {
  OnigUChar *pstr ;
  StackIndex prev_start ;
  StackIndex prev_end ;
};

union u_union {
  struct mem_struct mem;
};

struct _StackType {
  unsigned int type;
  int zid;
  union u_union u;
};

typedef struct _StackType StackType;

int main(void) {
  char *buf;
  buf = malloc(5152);
  if(buf) {
    (*((long long *)(buf + 8))) = &("\000G\000o\000O\000o\000O\000g\000L\000e\000\000")[2];
    (*((long long *)(buf + 24))) = &("\000G\000o\000O\000o\000O\000g\000L\000e\000\000")[10];
    (*((long long *)(buf + 32))) = 3;
    StackType* stk_base = (StackType*)&buf[32];
    StackIndex* mem_start_stk = (StackIndex*)&buf[0];
    int i = 1;
    int x = stk_base + *(mem_start_stk + i);
    return x;
  }
  return 0;
}
