
#ifndef T
#error "未定义宏 T. e.g.: #define T double"
#endif

#ifndef TEMPLATE_TYPE
#error "未定义宏 TEMPLATE_TYPE. e.g.: #define TEMPLATE_TYPE(a) a ##_double"
#endif

#ifndef TEMPLATE_FUNCTION
#error "未定义宏 TEMPLATE_FUNCTION. e.g.: #define TEMPLATE_FUNCTION(a, name) a ##_double_## b"
#endif

typedef struct TEMPLATE_TYPE(s_array) {
    T *end;
    T *stor_begin;
    T *stor_end;
} TEMPLATE_TYPE(s_array);

int TEMPLATE_FUNCTION(s_array, init)(TEMPLATE_TYPE(s_array) *a, int size, T *buf, int capacity);

int TEMPLATE_FUNCTION(s_array, capacity)(TEMPLATE_TYPE(s_array) *a);
int TEMPLATE_FUNCTION(s_array, size)(TEMPLATE_TYPE(s_array) *a);
int TEMPLATE_FUNCTION(s_array, available)(TEMPLATE_TYPE(s_array) *a);
int TEMPLATE_FUNCTION(s_array, empty)(TEMPLATE_TYPE(s_array) *a);
int TEMPLATE_FUNCTION(s_array, full)(TEMPLATE_TYPE(s_array) *a);

void TEMPLATE_FUNCTION(s_array, clear)(TEMPLATE_TYPE(s_array) *a);

#define ARRAY(a) ((a).stor_begin)
T TEMPLATE_FUNCTION(s_array, e)(TEMPLATE_TYPE(s_array) const *a, int i);
T* TEMPLATE_FUNCTION(s_array, e_ptr)(TEMPLATE_TYPE(s_array) *a, int i);
T const * TEMPLATE_FUNCTION(s_array, e_cptr)(TEMPLATE_TYPE(s_array) const *a, int i);
void TEMPLATE_FUNCTION(s_array, set)(TEMPLATE_TYPE(s_array) *a, int i, T v);
void TEMPLATE_FUNCTION(s_array, ptr_set)(TEMPLATE_TYPE(s_array) *a, int i, T const *v);

T* TEMPLATE_FUNCTION(s_array, find)(TEMPLATE_TYPE(s_array) *a, T v);
T* TEMPLATE_FUNCTION(s_array, ptr_find)(TEMPLATE_TYPE(s_array) *a, T const *v);
int TEMPLATE_FUNCTION(s_array, find_idx)(TEMPLATE_TYPE(s_array) *a, T v);
int TEMPLATE_FUNCTION(s_array, ptr_find_idx)(TEMPLATE_TYPE(s_array) *a, T const *v);

int TEMPLATE_FUNCTION(s_array, insert)(TEMPLATE_TYPE(s_array) *a, int i, T v);
int TEMPLATE_FUNCTION(s_array, ptr_insert)(TEMPLATE_TYPE(s_array) *a, int i, T const *v);
int TEMPLATE_FUNCTION(s_array, insert_section)(TEMPLATE_TYPE(s_array) *a, int i, T const *data, int len);

int TEMPLATE_FUNCTION(s_array, remove)(TEMPLATE_TYPE(s_array) *a, int i);
int TEMPLATE_FUNCTION(s_array, remove_section)(TEMPLATE_TYPE(s_array) *a, int from, int to);

int TEMPLATE_FUNCTION(s_array, push)(TEMPLATE_TYPE(s_array) *a, T v);
int TEMPLATE_FUNCTION(s_array, ptr_push)(TEMPLATE_TYPE(s_array) *a, T const *v);
int TEMPLATE_FUNCTION(s_array, pop)(TEMPLATE_TYPE(s_array) *a, T *v);


