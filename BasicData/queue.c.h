
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
 * queue_T_init - 初始化queue,初始容量为4
 *
 * @q: queue对象
 */
int TEMPLATE_FUNCTION(queue, init)(TEMPLATE_TYPE(queue) *q)
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
 * queue_T_destroy - 销毁queue对象
 *
 * @a: queue对象
 */
void TEMPLATE_FUNCTION(queue, destroy)(TEMPLATE_TYPE(queue) *q)
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
 * queue_T_size - 获取queue的容量
 *
 * @a: queue对象
 */
int TEMPLATE_FUNCTION(queue, capacity)(TEMPLATE_TYPE(queue) *q)
{
    return q->stor_end - q->stor_begin;
}

/*
 * queue_T_size - 获取queue的大小 
 *
 * @a: queue对象
 */
int TEMPLATE_FUNCTION(queue, size)(TEMPLATE_TYPE(queue) *q)
{
    if (0 == q->end)
        return 0;

    if (q->begin < q->end)
        return q->end - q->begin;
    else
        return (q->stor_end - q->begin) + (q->end - q->stor_begin);
}

/*
 * queue_T_available - 获取queue的可用空间大小 
 *
 * @a: queue对象
 */
int TEMPLATE_FUNCTION(queue, available)(TEMPLATE_TYPE(queue) *q)
{
    int cap = TEMPLATE_FUNCTION(queue, capacity)(q);
    int size = TEMPLATE_FUNCTION(queue, size)(q);

    return cap - size;
}

/*
 * queue_T_empty - queue是否空 
 *
 * @a: queue对象
 */
int TEMPLATE_FUNCTION(queue, empty)(TEMPLATE_TYPE(queue) *q)
{
    return q->end == 0;
}

/*
 * queue_T_full - queue是否满
 *
 * @a: queue对象
 */
int TEMPLATE_FUNCTION(queue, full)(TEMPLATE_TYPE(queue) *q)
{
    return q->end == q->begin;
}
/*
 * queue_T_clear - 清空queue
 */
void TEMPLATE_FUNCTION(queue, clear)(TEMPLATE_TYPE(queue) *q)
{
    q->begin = q->stor_begin;
    q->end = 0;
}
/*
 * queue_T_adjust_capacity - 调整队列容量
 */
int TEMPLATE_FUNCTION(queue, adjust_capacity)(TEMPLATE_TYPE(queue) *q, int c)
{
    int size = TEMPLATE_FUNCTION(queue, size)(q);
    if (c < size) {
        TEMPLATE_FUNCTION(queue, rearrange)(q);
        return 1;
    }

    int capacity = TEMPLATE_FUNCTION(queue, capacity)(q);
    if (c == capacity) {
        TEMPLATE_FUNCTION(queue, rearrange)(q);
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
 * queue_T_rearrange - 整理queue
 */
void TEMPLATE_FUNCTION(queue, rearrange)(TEMPLATE_TYPE(queue) *q)
{
    if (q->stor_begin == q->begin)
        return;

    int capacity = TEMPLATE_FUNCTION(queue, capacity)(q);
    int size = TEMPLATE_FUNCTION(queue, size)(q);

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
/*
 * queue_T_enqueue - 数据进队
 *
 * @data: 需要入队的数据
 */
int TEMPLATE_FUNCTION(queue, enqueue)(TEMPLATE_TYPE(queue) *q, T data)
{
    // 队列已满
    if (q->end == q->begin) {
        int c = TEMPLATE_FUNCTION(queue, capacity)(q);
        TEMPLATE_FUNCTION(queue, adjust_capacity)(q, c*2);
    }
    // 队列为空
    if (0 == q->end)
        q->end = q->begin;

    q->end[0] = data;
    q->end++;
    if (q->end == q->stor_end)
        q->end = q->stor_begin;

    return QUEUE_NOERR;
}
/*
 * queue_T_dequeue - 数据出队
 *
 * @buf: 保存数据的缓存
 */
int TEMPLATE_FUNCTION(queue, dequeue)(TEMPLATE_TYPE(queue) *q, T *buf)
{
    // 队列为空
    if (0 == q->end)
        return QUEUE_EMPTY;

    *buf = *(q->begin);

    q->begin++;

    if (q->begin == q->stor_end)
        q->begin = q->stor_begin;

    if (q->begin == q->end) {
        q->begin = q->stor_begin;
        q->end = 0;
    }

    return QUEUE_NOERR;
}

