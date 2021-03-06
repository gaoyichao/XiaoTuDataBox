
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
 * deque_T_init - 初始化deque,初始容量为4
 *
 * @q: deque对象
 */
int TEMPLATE_FUNCTION(deque, init)(TEMPLATE_TYPE(deque) *q)
{
    q->stor_begin = (T*)malloc(4 * sizeof(T));
    if (0 == q->stor_begin)
        return 1;

    q->stor_end = q->stor_begin + 4;
    q->begin = q->stor_begin;
    q->end = 0;

    return 0;
}

/*
 * deque_T_destroy - 销毁deque对象
 *
 * @a: deque对象
 */
void TEMPLATE_FUNCTION(deque, destroy)(TEMPLATE_TYPE(deque) *q)
{
    if (0 != q->stor_begin) {
        free(q->stor_begin);
        q->stor_begin = 0;
        q->stor_end = 0;
        q->begin = 0;
        q->end = 0;
    }
}
/*
 * deque_T_size - 获取deque的容量
 *
 * @a: deque对象
 */
int TEMPLATE_FUNCTION(deque, capacity)(TEMPLATE_TYPE(deque) *q)
{
    return q->stor_end - q->stor_begin;
}

/*
 * deque_T_size - 获取deque的大小 
 *
 * @a: deque对象
 */
int TEMPLATE_FUNCTION(deque, size)(TEMPLATE_TYPE(deque) *q)
{
    if (0 == q->end)
        return 0;

    if (q->begin < q->end)
        return q->end - q->begin;
    else
        return (q->stor_end - q->begin) + (q->end - q->stor_begin);
}
/*
 * deque_T_available - 获取deque的可用空间大小 
 *
 * @a: deque对象
 */
int TEMPLATE_FUNCTION(deque, available)(TEMPLATE_TYPE(deque) *q)
{
    int cap = TEMPLATE_FUNCTION(deque, capacity)(q);
    int size = TEMPLATE_FUNCTION(deque, size)(q);

    return cap - size;
}

/*
 * deque_T_empty - deque是否空 
 *
 * @a: deque对象
 */
int TEMPLATE_FUNCTION(deque, empty)(TEMPLATE_TYPE(deque) *q)
{
    return q->end == 0;
}

/*
 * deque_T_full - deque是否满
 *
 * @a: deque对象
 */
int TEMPLATE_FUNCTION(deque, full)(TEMPLATE_TYPE(deque) *q)
{
    return q->end == q->begin;
}

/*
 * deque_T_clear - 清空deque
 */
void TEMPLATE_FUNCTION(deque, clear)(TEMPLATE_TYPE(deque) *q)
{
    q->begin = q->stor_begin;
    q->end = 0;
}
/*
 * deque_T_adjust_capacity - 调整队列容量
 */
int TEMPLATE_FUNCTION(deque, adjust_capacity)(TEMPLATE_TYPE(deque) *q, int c)
{
    int size = TEMPLATE_FUNCTION(deque, size)(q);
    if (c < size) {
        TEMPLATE_FUNCTION(deque, rearrange)(q);
        return 1;
    }

    int capacity = TEMPLATE_FUNCTION(deque, capacity)(q);
    if (c == capacity) {
        TEMPLATE_FUNCTION(deque, rearrange)(q);
        return 0;
    }

    T *tmp = (T*)malloc(c * sizeof(T));
    T *begin = q->stor_begin;
    int i = 0;
    if (q->begin < q->end) {
        for (i = 0; i < size; i++)
            tmp[i] = q->begin[i];
    } else {
        while (q->begin != q->stor_end) {
            tmp[i] = q->begin[0];
            q->begin++;
            i++;
        }
        while (begin != q->end) {
            tmp[i] = begin[0];
            begin++;
            i++;
        }
    }
    free(q->stor_begin);
    q->stor_begin = tmp;
    q->stor_end = q->stor_begin + c;
    q->begin = q->stor_begin;
    q->end = q->stor_begin + size;
    return 0;
}
/*
 * deque_T_rearrange - 整理deque
 */
void TEMPLATE_FUNCTION(deque, rearrange)(TEMPLATE_TYPE(deque) *q)
{
    if (q->stor_begin == q->begin)
        return;

    int capacity = TEMPLATE_FUNCTION(deque, capacity)(q);
    int size = TEMPLATE_FUNCTION(deque, size)(q);

    T *tmp = (T*)malloc(capacity * sizeof(T));
    T *begin = q->stor_begin;
    int i = 0;
    if (q->begin < q->end) {
        for (i = 0; i < size; i++)
            tmp[i] = q->begin[i];
    } else {
        while (q->begin != q->stor_end) {
            tmp[i] = q->begin[0];
            q->begin++;
            i++;
        }
        while (begin != q->end) {
            tmp[i] = begin[0];
            begin++;
            i++;
        }
    }
    free(q->stor_begin);
    q->stor_begin = tmp;
    q->stor_end = q->stor_begin + capacity;
    q->begin = q->stor_begin;
    q->end = q->stor_begin + size;
}

int TEMPLATE_FUNCTION(deque, push_front)(TEMPLATE_TYPE(deque) *q, T data)
{
    // 队列已满
    if (q->end == q->begin) {
        int c = TEMPLATE_FUNCTION(deque, capacity)(q);
        TEMPLATE_FUNCTION(deque, adjust_capacity)(q, c*2);
    }
    // 队列为空
    if (0 == q->end)
        q->end = q->begin;

    q->begin--;
    if (q->begin < q->stor_begin)
        q->begin = q->stor_end - 1;
    q->begin[0] = data;

    return DEQUE_NOERR;
}


int TEMPLATE_FUNCTION(deque, push_back)(TEMPLATE_TYPE(deque) *q, T data)
{
    // 队列已满
    if (q->end == q->begin) {
        int c = TEMPLATE_FUNCTION(deque, capacity)(q);
        TEMPLATE_FUNCTION(deque, adjust_capacity)(q, c*2);
    }
    // 队列为空
    if (0 == q->end)
        q->end = q->begin;

    q->end[0] = data;
    q->end++;
    if (q->end == q->stor_end)
        q->end = q->stor_begin;

    return DEQUE_NOERR;
}

int TEMPLATE_FUNCTION(deque, pop_front)(TEMPLATE_TYPE(deque) *q, T *buf)
{
    // 队列为空
    if (0 == q->end)
        return DEQUE_EMPTY;

    *buf = *(q->begin);

    q->begin++;

    if (q->begin == q->stor_end)
        q->begin = q->stor_begin;

    if (q->begin == q->end) {
        q->begin = q->stor_begin;
        q->end = 0;
    }

    return DEQUE_NOERR;
}

int TEMPLATE_FUNCTION(deque, pop_back)(TEMPLATE_TYPE(deque) *q, T *buf)
{
    // 队列为空
    if (0 == q->end)
        return DEQUE_EMPTY;

    q->end--;
    if (q->end < q->stor_begin)
        q->end = q->stor_end - 1;

    *buf = *(q->end);

    if (q->begin == q->end) {
        q->begin = q->stor_begin;
        q->end = 0;
    }

    return DEQUE_NOERR;
}


int TEMPLATE_FUNCTION(deque, peek_front)(TEMPLATE_TYPE(deque) *q, T *buf)
{
    // 队列为空
    if (0 == q->end)
        return QUEUE_EMPTY;

    *buf = *(q->begin);

    return DEQUE_NOERR;
}

int TEMPLATE_FUNCTION(deque, peek_back)(TEMPLATE_TYPE(deque) *q, T *buf)
{
    // 队列为空
    if (0 == q->end)
        return DEQUE_EMPTY;

    T *tmp = q->end - 1;
    if (tmp < q->stor_begin)
        tmp = q->stor_end - 1;

    *buf = *tmp;
    return DEQUE_NOERR;
}

