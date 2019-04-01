
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
 * s_array_T_init - 初始化s_array
 *
 * @a: s_array对象
 * @size: s_array初始大小
 * @buf: s_array的存储空间
 * @capacity: s_array容量
 */
int TEMPLATE_FUNCTION(s_array, init)(TEMPLATE_TYPE(s_array) *a, int size, T *buf, int capacity)
{
    a->stor_begin = buf;
    a->stor_end = buf + capacity;
    a->end = buf + size;

    return 0;
}

/*
 * s_array_T_size - 获取s_array的容量
 *
 * @a: s_array对象
 */
int TEMPLATE_FUNCTION(s_array, capacity)(TEMPLATE_TYPE(s_array) *a)
{
    return a->stor_end - a->stor_begin;
}

/*
 * s_array_T_size - 获取s_array的大小 
 *
 * @a: s_array对象
 */
int TEMPLATE_FUNCTION(s_array, size)(TEMPLATE_TYPE(s_array) *a)
{
    return a->end - a->stor_begin;
}

/*
 * s_array_T_available - 获取s_array的可用空间大小 
 *
 * @a: s_array对象
 */
int TEMPLATE_FUNCTION(s_array, available)(TEMPLATE_TYPE(s_array) *a)
{
    return a->stor_end - a->end;
}

/*
 * s_array_T_empty - s_array是否空 
 *
 * @a: s_array对象
 */
bool TEMPLATE_FUNCTION(s_array, empty)(TEMPLATE_TYPE(s_array) *a)
{
    return a->end == a->stor_begin;
}

/*
 * s_array_T_full - s_array是否满
 *
 * @a: s_array对象
 */
bool TEMPLATE_FUNCTION(s_array, full)(TEMPLATE_TYPE(s_array) *a)
{
    return a->end == a->stor_end;
}
/*
 * s_array_T_clear - 清空s_array
 */
void TEMPLATE_FUNCTION(s_array, clear)(TEMPLATE_TYPE(s_array) *a)
{
    a->end = a->stor_begin;
}
/*
 * s_array_T_e - 获取第i个元素值 
 *
 * @a: s_array对象
 */
T TEMPLATE_FUNCTION(s_array, e)(TEMPLATE_TYPE(s_array) const *a, int i)
{
    return *(a->stor_begin + i);
}

/*
 * s_array_T_e_ptr - 获取第i个元素地址
 *
 * @a: s_array对象
 */
T* TEMPLATE_FUNCTION(s_array, e_ptr)(TEMPLATE_TYPE(s_array) *a, int i)
{
    return a->stor_begin + i;
}

/*
 * s_array_T_e_cptr - 获取第i个元素地址
 *
 * @a: s_array对象
 */
T const * TEMPLATE_FUNCTION(s_array, e_cptr)(TEMPLATE_TYPE(s_array) const *a, int i)
{
    return a->stor_begin + i;
}
/*
 * s_array_T_set - 设定第i个元素的值
 *
 * @a: s_array对象
 * @i: 目标元素索引
 * @v: 目标值
 */
void TEMPLATE_FUNCTION(s_array, set)(TEMPLATE_TYPE(s_array) *a, int i, T v)
{
    a->stor_begin[i] = v;
}
/*
 * s_array_T_ptr_set - 设定第i个元素的值
 *
 * @a: s_array对象
 * @i: 目标元素索引
 * @v: 目标值指针
 */
void TEMPLATE_FUNCTION(s_array, ptr_set)(TEMPLATE_TYPE(s_array) *a, int i, T const *v)
{
    a->stor_begin[i] = *v;
}
/*
 * s_array_T_find - 搜索数组中第一个值为v的元素，并返回指针
 *
 * @a: s_array对象
 * @v: 目标值
 */
T* TEMPLATE_FUNCTION(s_array, find)(TEMPLATE_TYPE(s_array) *a, T v)
{
    for (T *p = a->stor_begin; p < a->end; p++) {
        if (v == *p)
            return p;
    }

    return NULL;
}

/*
 * s_array_T_ptr_find - 搜索数组中第一个值为v的元素，并返回指针
 *
 * @a: s_array对象
 * @v: 目标值指针
 */
T* TEMPLATE_FUNCTION(s_array, ptr_find)(TEMPLATE_TYPE(s_array) *a, T const *v)
{
    for (T *p = a->stor_begin; p < a->end; p++) {
        if (*v == *p)
            return p;
    }

    return NULL;
}
/*
 * s_array_T_find_idx - 搜索数组中第一个值为v的元素，并返回索引值
 *
 * @a: s_array对象
 * @v: 目标值
 */
int TEMPLATE_FUNCTION(s_array, find_idx)(TEMPLATE_TYPE(s_array) *a, T v)
{
    int size = TEMPLATE_FUNCTION(s_array, size)(a);

    for (int i = 0; i < size; i++)
        if (v == a->stor_begin[i])
            return i;

    return -1;
}
/*
 * s_array_T_ptr_find_idx - 搜索数组中第一个值为v的元素，并返回索引值
 *
 * @a: s_array对象
 * @v: 目标值指针
 */
int TEMPLATE_FUNCTION(s_array, ptr_find_idx)(TEMPLATE_TYPE(s_array) *a, T const *v)
{
    int size = TEMPLATE_FUNCTION(s_array, size)(a);

    for (int i = 0; i < size; i++)
        if (*v == a->stor_begin[i])
            return i;

    return -1;
}
/*
 * s_array_T_insert - 向数组a中的第i个位置上插入元素V 
 *
 * @a: s_array对象
 * @i: 目标索引[0,n]
 * @v: 目标值
 */
int TEMPLATE_FUNCTION(s_array, insert)(TEMPLATE_TYPE(s_array) *a, int i, T v)
{
    int size = TEMPLATE_FUNCTION(s_array, size)(a);
    int cap = TEMPLATE_FUNCTION(s_array, capacity)(a);
    if (((size + 1) > cap) || (i > size))
        return 1;

    for (int idx = size; idx >= i; idx--)
        a->stor_begin[idx] = a->stor_begin[idx-1];

    a->stor_begin[i] = v;
    a->end++;
    return 0;
}

/*
 * s_array_T_ptr_insert - 向数组a中的第i个位置上插入元素V 
 *
 * @a: s_array对象
 * @i: 目标索引[0,n]
 * @v: 目标值指针
 */
int TEMPLATE_FUNCTION(s_array, ptr_insert)(TEMPLATE_TYPE(s_array) *a, int i, T const *v)
{
    int size = TEMPLATE_FUNCTION(s_array, size)(a);
    int cap = TEMPLATE_FUNCTION(s_array, capacity)(a);
    if (((size + 1) > cap) || (i > size))
        return 1;

    for (int idx = size; idx >= i; idx--)
        a->stor_begin[idx] = a->stor_begin[idx-1];

    a->stor_begin[i] = *v;
    a->end++;
    return 0;
}

int TEMPLATE_FUNCTION(s_array, insert_section)(TEMPLATE_TYPE(s_array) *a, int i, T const *data, int len)
{
    int size = TEMPLATE_FUNCTION(s_array, size)(a);
    int cap = TEMPLATE_FUNCTION(s_array, capacity)(a);
    if (((size + len) > cap) || (i > size))
        return 1;

    for (int idx = size; idx >= i; idx--)
        a->stor_begin[idx + len - 1] = a->stor_begin[idx-1];

    for (int idx = 0; idx < len; idx++)
        a->stor_begin[idx + i] = data[idx];
    a->end += len;
    return 0;
}
/*
 * s_array_T_remove_section - 从数组a中删除[from, to)位置上的元素 
 *
 * @a: s_array对象
 * @i: 目标索引[0,n]
 */
int TEMPLATE_FUNCTION(s_array, remove_section)(TEMPLATE_TYPE(s_array) *a, int from, int to)
{
    if (to < from)
        return 1;

    int size = TEMPLATE_FUNCTION(s_array, size)(a);
    if (to >= size)
        return 2;

    int len = size - to;
    for (int idx = 0; idx < len; idx++)
        a->stor_begin[from + idx] = a->stor_begin[to + idx];
    a->end -= (to - from);
    return 0;
}
/*
 * s_array_T_remove - 从数组a中删除第i个位置上的元素 
 *
 * @a: s_array对象
 * @i: 目标索引[0,n]
 */
int TEMPLATE_FUNCTION(s_array, remove)(TEMPLATE_TYPE(s_array) *a, int i)
{
    return TEMPLATE_FUNCTION(s_array, remove_section)(a, i, i+1);
}

/*
 * s_array_T_push - 入栈，表尾作为栈顶 
 *
 * @a: s_array对象
 * @v: 目标值
 */
int TEMPLATE_FUNCTION(s_array, push)(TEMPLATE_TYPE(s_array) *a, T v)
{
    if (TEMPLATE_FUNCTION(s_array, full)(a))
        return 1;

    a->end[0] = v;
    a->end++;
    return 0;
}
/*
 * s_array_T_ptr_push - 入栈，表尾作为栈顶 
 *
 * @a: s_array对象
 * @v: 目标值指针
 */
int TEMPLATE_FUNCTION(s_array, ptr_push)(TEMPLATE_TYPE(s_array) *a, T const *v)
{
    if (TEMPLATE_FUNCTION(s_array, full)(a))
        return 1;

    a->end[0] = *v;
    a->end++;
    return 0;
}
/*
 * s_array_T_ptr_push - 出栈，表尾作为栈顶 
 *
 * @a: s_array对象
 * @v: 目标值指针
 */
int TEMPLATE_FUNCTION(s_array, pop)(TEMPLATE_TYPE(s_array) *a, T *v)
{
    if (TEMPLATE_FUNCTION(s_array, empty)(a))
        return 1;

    a->end--;
    *v = a->end[0];
    return 0;
}




