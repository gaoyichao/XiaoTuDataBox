
#ifndef T
#error "未定义宏 T. e.g.: #define T double"
#endif

#ifndef TEMPLATE_TYPE
#error "未定义宏 TEMPLATE_TYPE. e.g.: #define TEMPLATE_TYPE(a) a ##_double"
#endif

#ifndef TEMPLATE_FUNCTION
#error "未定义宏 TEMPLATE_FUNCTION. e.g.: #define TEMPLATE_FUNCTION(a, name) a ##_double_## b"
#endif

#include <stdlib.h>
#include <assert.h>

/*
 * array_T_init - 初始化array申请内存，成功运行返回0，否则返回1
 *
 * e.g. array_double_init(&a, 3);
 *
 * @a: array对象
 * @size: array初始大小
 */
int TEMPLATE_FUNCTION(array, init)(TEMPLATE_TYPE(array) *a, int size)
{
    int alloc_size = size > 0 ? size : 1;

    a->stor_begin = (T*)malloc(alloc_size * sizeof(T));
    if (0 == a->stor_begin)
        return 1;

    a->stor_end = a->stor_begin + alloc_size;
    a->end = a->stor_begin + size;

    return 0;
}

/*
 * array_T_init_copy - 拷贝初始化array
 *
 * @a: array对象
 * @size: array初始大小
 * @data: 目标数据
 */
int TEMPLATE_FUNCTION(array, init_copy)(TEMPLATE_TYPE(array) *a, int size, T const *data)
{
    int err = TEMPLATE_FUNCTION(array, init)(a, size);
    if (0 != err)
        return err;

    memcpy(a->stor_begin, data, (size_t)size * sizeof(T));
    return 0;
}

/*
 * array_T_size - 获取array的容量
 *
 * @a: array对象
 */
int TEMPLATE_FUNCTION(array, capacity)(TEMPLATE_TYPE(array) *a)
{
    return a->stor_end - a->stor_begin;
}

/*
 * array_T_size - 获取array的大小 
 *
 * @a: array对象
 */
int TEMPLATE_FUNCTION(array, size)(TEMPLATE_TYPE(array) *a)
{
    return a->end - a->stor_begin;
}

/*
 * array_T_available - 获取array的可用空间大小 
 *
 * @a: array对象
 */
int TEMPLATE_FUNCTION(array, available)(TEMPLATE_TYPE(array) *a)
{
    return a->stor_end - a->end;
}

/*
 * array_T_empty - array是否空 
 *
 * @a: array对象
 */
bool TEMPLATE_FUNCTION(array, empty)(TEMPLATE_TYPE(array) *a)
{
    return a->end == a->stor_begin;
}

/*
 * array_T_full - array是否满
 *
 * @a: array对象
 */
bool TEMPLATE_FUNCTION(array, full)(TEMPLATE_TYPE(array) *a)
{
    return a->end == a->stor_end;
}

/*
 * array_T_adjust_capacity - 调整array容量
 *
 * 调整的容量一定不小于array的大小
 *
 * @a: array对象
 * @c: 容量
 */
int TEMPLATE_FUNCTION(array, adjust_capacity)(TEMPLATE_TYPE(array) *a, int c)
{
    int size = TEMPLATE_FUNCTION(array, size)(a);
    if (c < size)
        return 1;

    int capacity = TEMPLATE_FUNCTION(array, capacity)(a);
    if (c == capacity)
        return 0;

    capacity = c > 0 ? c : 1;
    T *tmp = (T*)realloc(a->stor_begin, capacity * sizeof(T));
    a->stor_begin = tmp;
    a->stor_end = a->stor_begin + capacity;
    a->end = a->stor_begin + size;
    return 0;
}

/*
 * array_T_adjust_capacity - 调整array大小
 *
 * @a: array对象
 * @c: 容量
 */
int TEMPLATE_FUNCTION(array, resize)(TEMPLATE_TYPE(array) *a, int size)
{
    int cap = TEMPLATE_FUNCTION(array, capacity)(a);
    while (cap < size)
        cap = 2 * cap;

    TEMPLATE_FUNCTION(array, adjust_capacity)(a, cap);

    a->end = a->stor_begin + size;
    return 0;
}
/*
 * array_T_clear - 清空array
 */
void TEMPLATE_FUNCTION(array, clear)(TEMPLATE_TYPE(array) *a)
{
    a->end = a->stor_begin;
}
/*
 * array_T_destroy - 销毁array对象
 *
 * @a: array对象
 */
void TEMPLATE_FUNCTION(array, destroy)(TEMPLATE_TYPE(array) *a)
{
    if (0 != a->stor_begin) {
        free(a->stor_begin);
        a->stor_begin = 0;
        a->stor_end = 0;
        a->end = 0;
    }
}

/*
 * array_T_e - 获取第i个元素值 
 *
 * @a: array对象
 */
T TEMPLATE_FUNCTION(array, e)(TEMPLATE_TYPE(array) const *a, int i)
{
    return *(a->stor_begin + i);
}

/*
 * array_T_e_ptr - 获取第i个元素地址
 *
 * @a: array对象
 */
T* TEMPLATE_FUNCTION(array, e_ptr)(TEMPLATE_TYPE(array) *a, int i)
{
    return a->stor_begin + i;
}

/*
 * array_T_e_cptr - 获取第i个元素地址
 *
 * @a: array对象
 */
T const * TEMPLATE_FUNCTION(array, e_cptr)(TEMPLATE_TYPE(array) const *a, int i)
{
    return a->stor_begin + i;
}
/*
 * array_T_set - 设定第i个元素的值
 *
 * @a: array对象
 * @i: 目标元素索引
 * @v: 目标值
 */
void TEMPLATE_FUNCTION(array, set)(TEMPLATE_TYPE(array) *a, int i, T v)
{
    a->stor_begin[i] = v;
}
/*
 * array_T_ptr_set - 设定第i个元素的值
 *
 * @a: array对象
 * @i: 目标元素索引
 * @v: 目标值指针
 */
void TEMPLATE_FUNCTION(array, ptr_set)(TEMPLATE_TYPE(array) *a, int i, T const *v)
{
    a->stor_begin[i] = *v;
}
/*
 * array_T_find - 搜索数组中第一个值为v的元素，并返回指针
 *
 * @a: array对象
 * @v: 目标值
 */
T* TEMPLATE_FUNCTION(array, find)(TEMPLATE_TYPE(array) *a, T v)
{
    for (T *p = a->stor_begin; p < a->end; p++) {
        if (v == *p)
            return p;
    }

    return NULL;
}

/*
 * array_T_ptr_find - 搜索数组中第一个值为v的元素，并返回指针
 *
 * @a: array对象
 * @v: 目标值指针
 */
T* TEMPLATE_FUNCTION(array, ptr_find)(TEMPLATE_TYPE(array) *a, T const *v)
{
    for (T *p = a->stor_begin; p < a->end; p++) {
        if (*v == *p)
            return p;
    }

    return NULL;
}
/*
 * array_T_find_idx - 搜索数组中第一个值为v的元素，并返回索引值
 *
 * @a: array对象
 * @v: 目标值
 */
int TEMPLATE_FUNCTION(array, find_idx)(TEMPLATE_TYPE(array) *a, T v)
{
    int size = TEMPLATE_FUNCTION(array, size)(a);

    for (int i = 0; i < size; i++)
        if (v == a->stor_begin[i])
            return i;

    return -1;
}
/*
 * array_T_ptr_find_idx - 搜索数组中第一个值为v的元素，并返回索引值
 *
 * @a: array对象
 * @v: 目标值指针
 */
int TEMPLATE_FUNCTION(array, ptr_find_idx)(TEMPLATE_TYPE(array) *a, T const *v)
{
    int size = TEMPLATE_FUNCTION(array, size)(a);

    for (int i = 0; i < size; i++)
        if (*v == a->stor_begin[i])
            return i;

    return -1;
}
/*
 * array_T_insert - 向数组a中的第i个位置上插入元素V 
 *
 * @a: array对象
 * @i: 目标索引[0,n]
 * @v: 目标值
 */
int TEMPLATE_FUNCTION(array, insert)(TEMPLATE_TYPE(array) *a, int i, T v)
{
    int size = TEMPLATE_FUNCTION(array, size)(a);
    if (i > size)
        return 1;

    TEMPLATE_FUNCTION(array, resize)(a, size + 1);
    if (i < size)
        memmove(a->stor_begin+i+1, a->stor_begin+i, sizeof(T)*(size - i));

    a->stor_begin[i] = v;
    return 0;
}

/*
 * array_T_ptr_insert - 向数组a中的第i个位置上插入元素V 
 *
 * @a: array对象
 * @i: 目标索引[0,n]
 * @v: 目标值指针
 */
int TEMPLATE_FUNCTION(array, ptr_insert)(TEMPLATE_TYPE(array) *a, int i, T const *v)
{
    int size = TEMPLATE_FUNCTION(array, size)(a);
    if (i > size)
        return 1;

    TEMPLATE_FUNCTION(array, resize)(a, size + 1);
    if (i < size)
        memmove(a->stor_begin+i+1, a->stor_begin+i, sizeof(T)*(size - i));

    a->stor_begin[i] = *v;
    return 0;
}
/*
 * array_T_ptr_insert_section - 向数组a中的第i个位置上插入len个元素
 *
 * @a: array对象
 * @i: 目标索引[0,n]
 * @data: 元素缓存 
 * @len: 元素数量
 */
int TEMPLATE_FUNCTION(array, insert_section)(TEMPLATE_TYPE(array) *a, int i, T const *data, int len)
{
    int size = TEMPLATE_FUNCTION(array, size)(a);
    if (i > size)
        return 1;

    TEMPLATE_FUNCTION(array, resize)(a, size + len);

    if (i < size)
        memmove(a->stor_begin+i+len, a->stor_begin+i, sizeof(T)*(size - i));


    memcpy(a->stor_begin+i, data, (size_t)len * sizeof(T));
    return 0;
}
/*
 * array_T_remove_section - 从数组a中删除[from, to)位置上的元素 
 *
 * @a: array对象
 * @i: 目标索引[0,n]
 */
int TEMPLATE_FUNCTION(array, remove_section)(TEMPLATE_TYPE(array) *a, int from, int to)
{
    if (to < from)
        return 1;

    int size = TEMPLATE_FUNCTION(array, size)(a);
    if (to > size)
        return 2;

    memmove(a->stor_begin+from, a->stor_begin+to, sizeof(T)*(size - to));
    a->end -= (to - from);
    return 0;
}
/*
 * array_T_remove - 从数组a中删除第i个位置上的元素 
 *
 * @a: array对象
 * @i: 目标索引[0,n]
 */
int TEMPLATE_FUNCTION(array, remove)(TEMPLATE_TYPE(array) *a, int i)
{
    return TEMPLATE_FUNCTION(array, remove_section)(a, i, i+1);
}
/*
 * array_T_push - 入栈，表尾作为栈顶 
 *
 * @a: array对象
 * @v: 目标值
 */
int TEMPLATE_FUNCTION(array, push)(TEMPLATE_TYPE(array) *a, T v)
{
    int size = TEMPLATE_FUNCTION(array, size)(a);
    TEMPLATE_FUNCTION(array, resize)(a, size + 1);

    a->stor_begin[size] = v;
    return 0;
}
/*
 * array_T_ptr_push - 入栈，表尾作为栈顶 
 *
 * @a: array对象
 * @v: 目标值指针
 */
int TEMPLATE_FUNCTION(array, ptr_push)(TEMPLATE_TYPE(array) *a, T const *v)
{
    int size = TEMPLATE_FUNCTION(array, size)(a);
    TEMPLATE_FUNCTION(array, resize)(a, size + 1);

    a->stor_begin[size] = *v;
    return 0;
}
/*
 * array_T_ptr_push - 出栈，表尾作为栈顶 
 *
 * @a: array对象
 * @v: 目标值指针
 */
int TEMPLATE_FUNCTION(array, pop)(TEMPLATE_TYPE(array) *a, T *v)
{
    if (TEMPLATE_FUNCTION(array, empty)(a))
        return 1;

    a->end--;
    *v = a->end[0];
    return 0;
}



