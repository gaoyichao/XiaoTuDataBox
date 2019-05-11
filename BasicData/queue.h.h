
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


typedef struct TEMPLATE_TYPE(queue) {
    T *begin;
    T *end;
    T *stor_begin;
    T *stor_end;
    union queue_flag flags;
} TEMPLATE_TYPE(queue);

int TEMPLATE_FUNCTION(queue, init)(TEMPLATE_TYPE(queue) *q);
void TEMPLATE_FUNCTION(queue, destroy)(TEMPLATE_TYPE(queue) *q);

int TEMPLATE_FUNCTION(queue, capacity)(TEMPLATE_TYPE(queue) *q);
int TEMPLATE_FUNCTION(queue, size)(TEMPLATE_TYPE(queue) *q);
int TEMPLATE_FUNCTION(queue, available)(TEMPLATE_TYPE(queue) *q);
int TEMPLATE_FUNCTION(queue, empty)(TEMPLATE_TYPE(queue) *q);
int TEMPLATE_FUNCTION(queue, full)(TEMPLATE_TYPE(queue) *q);

void TEMPLATE_FUNCTION(queue, clear)(TEMPLATE_TYPE(queue) *q);
int TEMPLATE_FUNCTION(queue, adjust_capacity)(TEMPLATE_TYPE(queue) *q, int c);
void TEMPLATE_FUNCTION(queue, rearrange)(TEMPLATE_TYPE(queue) *q);

int TEMPLATE_FUNCTION(queue, enqueue)(TEMPLATE_TYPE(queue) *q, T data);
int TEMPLATE_FUNCTION(queue, dequeue)(TEMPLATE_TYPE(queue) *q, T *buf);

int TEMPLATE_FUNCTION(queue, peek)(TEMPLATE_TYPE(queue) *q, T *buf);

