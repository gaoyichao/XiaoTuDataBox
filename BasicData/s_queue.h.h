
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

typedef struct TEMPLATE_TYPE(s_queue) {
    T *begin;
    T *end;
    T *stor_begin;
    T *stor_end;
    union queue_flag flags;
} TEMPLATE_TYPE(s_queue);

int TEMPLATE_FUNCTION(s_queue, init)(TEMPLATE_TYPE(s_queue) *q, T *buf, int capacity);

int TEMPLATE_FUNCTION(s_queue, capacity)(TEMPLATE_TYPE(s_queue) *q);
int TEMPLATE_FUNCTION(s_queue, size)(TEMPLATE_TYPE(s_queue) *q);
int TEMPLATE_FUNCTION(s_queue, available)(TEMPLATE_TYPE(s_queue) *q);
int TEMPLATE_FUNCTION(s_queue, empty)(TEMPLATE_TYPE(s_queue) *q);
int TEMPLATE_FUNCTION(s_queue, full)(TEMPLATE_TYPE(s_queue) *q);

void TEMPLATE_FUNCTION(s_queue, clear)(TEMPLATE_TYPE(s_queue) *q);

int TEMPLATE_FUNCTION(s_queue, enqueue)(TEMPLATE_TYPE(s_queue) *q, T data);
int TEMPLATE_FUNCTION(s_queue, dequeue)(TEMPLATE_TYPE(s_queue) *q, T *buf);

