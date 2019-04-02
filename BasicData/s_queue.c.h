
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
 * s_queue_T_init - 初始化s_queue,默认队列满时不覆盖队首数据
 *
 * @a: s_queue对象
 * @buf: s_queue的存储空间
 * @capacity: s_queue容量
 */
int TEMPLATE_FUNCTION(s_queue, init)(TEMPLATE_TYPE(s_queue) *q, T *buf, int capacity)
{
    q->stor_begin = buf;
    q->stor_end = q->stor_begin + capacity;

    q->begin = q->stor_begin;
    q->end = 0;

    q->flags.bits.overwrite = 0;
    return 0;
}

/*
 * s_queue_T_size - 获取s_queue的容量
 *
 * @a: s_queue对象
 */
int TEMPLATE_FUNCTION(s_queue, capacity)(TEMPLATE_TYPE(s_queue) *q)
{
    return q->stor_end - q->stor_begin;
}

/*
 * s_queue_T_size - 获取s_queue的大小 
 *
 * @a: s_queue对象
 */
int TEMPLATE_FUNCTION(s_queue, size)(TEMPLATE_TYPE(s_queue) *q)
{
    if (0 == q->end)
        return 0;

    if (q->begin < q->end)
        return q->end - q->begin;
    else
        return (q->stor_end - q->begin) + (q->end - q->stor_begin);
}

/*
 * s_queue_T_available - 获取s_queue的可用空间大小 
 *
 * @a: s_queue对象
 */
int TEMPLATE_FUNCTION(s_queue, available)(TEMPLATE_TYPE(s_queue) *q)
{
    int cap = TEMPLATE_FUNCTION(s_queue, capacity)(q);
    int size = TEMPLATE_FUNCTION(s_queue, size)(q);

    return cap - size;
}

/*
 * s_queue_T_empty - s_queue是否空 
 *
 * @a: s_queue对象
 */
int TEMPLATE_FUNCTION(s_queue, empty)(TEMPLATE_TYPE(s_queue) *q)
{
    return q->end == 0;
}

/*
 * s_queue_T_full - s_queue是否满
 *
 * @a: s_queue对象
 */
int TEMPLATE_FUNCTION(s_queue, full)(TEMPLATE_TYPE(s_queue) *q)
{
    return q->end == q->begin;
}
/*
 * s_queue_T_clear - 清空s_queue
 */
void TEMPLATE_FUNCTION(s_queue, clear)(TEMPLATE_TYPE(s_queue) *q)
{
    q->begin = q->stor_begin;
    q->end = 0;
}

/*
 * s_queue_T_enqueue - 数据进队
 *
 * @data: 需要入队的数据
 */
int TEMPLATE_FUNCTION(s_queue, enqueue)(TEMPLATE_TYPE(s_queue) *q, T data)
{
    // 队列已满
    if (q->end == q->begin) {
        if (0 == q->flags.bits.overwrite)
            return QUEUE_FULL;
        q->begin++;
        if (q->begin == q->stor_end)
            q->begin = q->stor_begin;
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
 * s_queue_T_dequeue - 数据出队
 *
 * @buf: 保存数据的缓存
 */
int TEMPLATE_FUNCTION(s_queue, dequeue)(TEMPLATE_TYPE(s_queue) *q, T *buf)
{
    // 队列为空
    if (0 == q->end)
        return QUEUE_EMPTY;

    *buf = *(q->begin);

    q->begin++;

    if (q->begin == q->stor_end)
        q->begin = q->stor_begin;
    if (q->begin == q->end)
        q->end = 0;

    return QUEUE_NOERR;
}

