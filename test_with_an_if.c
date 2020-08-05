
#include "stdlib.h"

typedef __UINT32_T uint32_t;

typedef unsigned char OnigUChar;

#define UChar OnigUChar

#define BITS_PER_BYTE      8
#define SINGLE_BYTE_SIZE   (1 << BITS_PER_BYTE)
#define BITS_IN_ROOM       32   /* 4 * BITS_PER_BYTE */
#define BITSET_REAL_SIZE   (SINGLE_BYTE_SIZE / BITS_IN_ROOM)

typedef uint32_t  Bits;
typedef Bits      BitSet[BITSET_REAL_SIZE];
typedef Bits*     BitSetRef;

typedef int RelAddrType;
typedef int AbsAddrType;
typedef int LengthType;
typedef int RelPositionType;
typedef int RepeatNumType;
typedef int MemNumType;
typedef void* PointerType;
typedef int SaveType;
typedef int UpdateVarType;
typedef int ModeType;

enum CheckPositionType {
  CHECK_POSITION_SEARCH_START = 0,
  CHECK_POSITION_CURRENT_RIGHT_RANGE = 1,
};

enum TextSegmentBoundaryType {
  EXTENDED_GRAPHEME_CLUSTER_BOUNDARY = 0,
  WORD_BOUNDARY = 1,
};

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

typedef struct {
  const void* opaddr;
  union {
    struct {
      UChar s[16];  /* Now used first 7 bytes only. */
    } exact;
    struct {
      UChar* s;
      LengthType n;   /* number of chars */
    } exact_n; /* EXACTN, EXACTN_IC, EXACTMB2N, EXACTMB3N */
    struct {
      UChar* s;
      LengthType n;   /* number of chars */
      LengthType len; /* char byte length */
    } exact_len_n; /* EXACTMBN */
    struct {
      BitSetRef bsp;
    } cclass;
    struct {
      void*  mb;
    } cclass_mb;
    struct {
      void*  mb; /* mb must be same position with cclass_mb for match_at(). */
      BitSetRef bsp;
    } cclass_mix;
    struct {
      UChar c;
    } anychar_star_peek_next;
    struct {
      ModeType mode;
    } word_boundary; /* OP_WORD_BOUNDARY, OP_NO_WORD_BOUNDARY, OP_WORD_BEGIN, OP_WORD_END */
    struct {
      enum TextSegmentBoundaryType type;
      int not;
    } text_segment_boundary;
    struct {
      enum CheckPositionType type;
    } check_position;
    struct {
      union {
        MemNumType  n1; /* num == 1 */
        MemNumType* ns; /* num >  1 */
      };
      int num;
      int nest_level;
    } backref_general; /* BACKREF_MULTI, BACKREF_MULTI_IC, BACKREF_WITH_LEVEL, BACKREF_CHECK, BACKREF_CHECK_WITH_LEVEL, */
    struct {
      MemNumType n1;
    } backref_n; /* BACKREF_N, BACKREF_N_IC */
    struct {
      MemNumType num;
    } memory_start; /* MEMORY_START, MEMORY_START_PUSH */
    struct {
      MemNumType num;
    } memory_end; /* MEMORY_END, MEMORY_END_REC, MEMORY_END_PUSH, MEMORY_END_PUSH_REC */
    struct {
      RelAddrType addr;
    } jump;
    struct {
      RelAddrType addr;
    } push;
    struct {
      RelAddrType addr;
      UChar c;
    } push_or_jump_exact1;
    struct {
      RelAddrType addr;
      UChar c;
    } push_if_peek_next;
    struct {
      MemNumType id;
    } pop_to_mark;
    struct {
      MemNumType  id;
      RelAddrType addr;
    } repeat; /* REPEAT, REPEAT_NG */
    struct {
      MemNumType  id;
    } repeat_inc; /* REPEAT_INC, REPEAT_INC_NG */
    struct {
      MemNumType mem;
    } empty_check_start;
    struct {
      MemNumType mem;
    } empty_check_end; /* EMPTY_CHECK_END, EMPTY_CHECK_END_MEMST, EMPTY_CHECK_END_MEMST_PUSH */
    struct {
      RelAddrType addr;
    } prec_read_not_start;
    struct {
      LengthType len;
    } look_behind;
    struct {
      LengthType  len;
      RelAddrType addr;
    } look_behind_not_start;
    struct {
      RelPositionType n; /* char relative position */
    } move;
    struct {
      LengthType initial;   /* char length */
      LengthType remaining; /* char length */
      RelAddrType addr;
    } step_back_start;
    struct {
      MemNumType id;
      int restore_pos;  /* flag: restore current string position */
    } cut_to_mark;
    struct {
      MemNumType id;
      int save_pos;  /* flag: save current string position */
    } mark;
    struct {
      SaveType   type;
      MemNumType id;
    } save_val;
    struct {
      UpdateVarType type;
      MemNumType id;
      int clear;  /* UPDATE_VAR_RIGHT_RANGE_FROM_S_STACK or UPDATE_VAR_RIGHT_RANGE_FROM_STACK */
    } update_var;
    struct {
      AbsAddrType addr;
    } call;
    struct {
      MemNumType num;
    } callout_contents;
    struct {
      MemNumType num;
      MemNumType id;
    } callout_name;
  };
} Operation;

Operation FinishCode[1];

int main(void) {
  char *buf;
  buf = malloc(5152);
  OnigUChar *x;

  if(buf) {
    (*((long long *)(buf + 8))) = &("GoOoOgLe")[1];
    (*((long long *)(buf + 24))) = &("GoOoOgLe")[5];
    (*((long      *)(buf + 32))) = 3;
    (*((long long *)(buf + 40))) = &FinishCode;
    StackType* stk_base = (StackType*)&buf[32];
    StackIndex* mem_start_stk = (StackIndex*)&buf[0];
    int i = 1;
    int false_condition = 0;
    x = false_condition ? (stk_base + *(mem_start_stk + i))->u.mem.pstr : 42;
    return x;
  }
  return 0;
}
