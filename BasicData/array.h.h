
#ifndef T
#error "未定义宏 T. e.g.: #define T double"
#endif

#ifndef TEMPLATE_TYPE
#error "未定义宏 TEMPLATE_TYPE. e.g.: #define TEMPLATE_TYPE(a) a ##_double"
#endif

#ifndef TEMPLATE_FUNCTION
#error "未定义宏 TEMPLATE_FUNCTION. e.g.: #define TEMPLATE_FUNCTION(a, name) a ##_double_## b"
#endif

typedef struct TEMPLATE_TYPE(array) {
    T *end;
    T *stor_begin;
    T *stor_end;
} TEMPLATE_TYPE(array);


int TEMPLATE_FUNCTION(array, init)(TEMPLATE_TYPE(array) *a, int size);
int TEMPLATE_FUNCTION(array, init_copy)(TEMPLATE_TYPE(array) *a, int size, T const *data);

int TEMPLATE_FUNCTION(array, capacity)(TEMPLATE_TYPE(array) *a);
int TEMPLATE_FUNCTION(array, size)(TEMPLATE_TYPE(array) *a);
int TEMPLATE_FUNCTION(array, available)(TEMPLATE_TYPE(array) *a);
bool TEMPLATE_FUNCTION(array, empty)(TEMPLATE_TYPE(array) *a);
bool TEMPLATE_FUNCTION(array, full)(TEMPLATE_TYPE(array) *a);

int TEMPLATE_FUNCTION(array, adjust_capacity)(TEMPLATE_TYPE(array) *a, int c);
int TEMPLATE_FUNCTION(array, size)(TEMPLATE_TYPE(array) *a, int size);
void TEMPLATE_FUNCTION(array, destroy)(TEMPLATE_TYPE(array) *a);

#define ARRAY(a) ((a).stor_begin)
T TEMPLATE_FUNCTION(array, e)(TEMPLATE_TYPE(array) const *a, int i);
T* TEMPLATE_FUNCTION(array, e_ptr)(TEMPLATE_TYPE(array) *a, int i);
T const * TEMPLATE_FUNCTION(array, e_cptr)(TEMPLATE_TYPE(array) const *a, int i);
void TEMPLATE_FUNCTION(array, set)(TEMPLATE_TYPE(array) *a, int i, T v);
void TEMPLATE_FUNCTION(array, set_interval)(TEMPLATE_TYPE(array) *a, int i, T v);

T* TEMPLATE_FUNCTION(array, find)(TEMPLATE_TYPE(array) *a, T v);
int TEMPLATE_FUNCTION(array, find_idx)(TEMPLATE_TYPE(array) *a, T v);

int TEMPLATE_FUNCTION(array, insert)(TEMPLATE_TYPE(array) *a, int i, T v);

int TEMPLATE_FUNCTION(array, remove)(TEMPLATE_TYPE(array) *a, int i);
int TEMPLATE_FUNCTION(array, remove_section)(TEMPLATE_TYPE(array) *a, int from, int to);


