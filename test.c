

struct _StackType {
  unsigned int type;
  int zid;
};

typedef struct _StackType StackType;

typedef long intptr_t;
typedef intptr_t StackIndex;

char t[] = "Duuuuuuuuuuuuupaaaaaaaaaaaa";
char buf[5000];

int main(void) {
  buf[4] = &t[2];
  StackType* stk_base = (StackType*)&buf[32];
  StackIndex* mem_start_stk = (StackIndex*)&buf[0];
  int i = 1;
  int x = stk_base + *(mem_start_stk + i);
  return x;
}
