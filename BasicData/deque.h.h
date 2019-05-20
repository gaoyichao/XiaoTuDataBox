
#ifndef T
#error "未定义宏 T. e.g.: #define T double"
#endif

#ifndef TEMPLATE_TYPE
#error "未定义宏 TEMPLATE_TYPE. e.g.: #define TEMPLATE_TYPE(a) a ##_double"
#endif

#ifndef TEMPLATE_FUNCTION
#error "未定义宏 TEMPLATE_FUNCTION. e.g.: #define TEMPLATE_FUNCTION(a, name) a ##_double_## b"
#endif

#include <types.h>

typedef struct TEMPLATE_TYPE(deque) {
    T *begin;
    T *end;
    T *stor_begin;
    T *stor_end;
} TEMPLATE_TYPE(deque);

int TEMPLATE_FUNCTION(deque, init)(TEMPLATE_TYPE(deque) *q);
void TEMPLATE_FUNCTION(deque, destroy)(TEMPLATE_TYPE(deque) *q);

int TEMPLATE_FUNCTION(deque, capacity)(TEMPLATE_TYPE(deque) *q);
int TEMPLATE_FUNCTION(deque, size)(TEMPLATE_TYPE(deque) *q);
int TEMPLATE_FUNCTION(deque, available)(TEMPLATE_TYPE(deque) *q);
int TEMPLATE_FUNCTION(deque, empty)(TEMPLATE_TYPE(deque) *q);
int TEMPLATE_FUNCTION(deque, full)(TEMPLATE_TYPE(deque) *q);

void TEMPLATE_FUNCTION(deque, clear)(TEMPLATE_TYPE(deque) *q);
int TEMPLATE_FUNCTION(deque, adjust_capacity)(TEMPLATE_TYPE(deque) *q, int c);
void TEMPLATE_FUNCTION(deque, rearrange)(TEMPLATE_TYPE(deque) *q);

int TEMPLATE_FUNCTION(deque, push_front)(TEMPLATE_TYPE(deque) *q, T data);
int TEMPLATE_FUNCTION(deque, push_back)(TEMPLATE_TYPE(deque) *q, T data);
int TEMPLATE_FUNCTION(deque, pop_front)(TEMPLATE_TYPE(deque) *q, T *buf);
int TEMPLATE_FUNCTION(deque, pop_back)(TEMPLATE_TYPE(deque) *q, T *buf);

int TEMPLATE_FUNCTION(deque, peek_front)(TEMPLATE_TYPE(deque) *q, T *buf);
int TEMPLATE_FUNCTION(deque, peek_back)(TEMPLATE_TYPE(deque) *q, T *buf);

