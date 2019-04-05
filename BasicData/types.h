#ifndef TYPES_H
#define TYPES_H

#ifdef  __cplusplus  
extern "C" {  
#endif 

typedef signed char             int8;
typedef signed short            int16;
typedef signed long             int32;

typedef signed char const       cint8;
typedef signed short const      cint16;
typedef signed long const       cint32;

typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned long           uint32;
typedef unsigned long long      uint64;

typedef unsigned char const     ucint8;
typedef unsigned short const    ucint16;
typedef unsigned long const     ucint32;
typedef unsigned long long const ucint64;

typedef unsigned char   BOOL;

#ifndef True
#define True 1
#endif

#ifndef False
#define False 0
#endif

#ifndef Null
#define Null 0
#endif

#define U8Bit(n)    ((uint8)(1 << n))
#define U16Bit(n)   ((uint16)(1 << n))
#define U32Bit(n)   ((uint32)(1 << n))

union Data32 {
    uint32 word;
    uint16 half_word[2];
    uint8 byte[4];
};

union Data16 {
    uint16 half_word;
    uint8 byte[2];
};

/*
 * queue_flag_bits - 队列属性
 */
struct queue_flag_bits {
    uint32 overwrite : 1;    // 如果队列已满,是否覆盖队首数据
    uint32 rsv : 30;         // 保留
};

union queue_flag {
    struct queue_flag_bits bits;
    uint32 all;
};

#define QUEUE_NOERR 0
#define QUEUE_FULL 1
#define QUEUE_EMPTY 2

/*
* offsetof - 求取一个结构体某个成员的偏移量
*
* @type: 结构体类型
* @member: 成员名称
*/
#define OffsetOf(type, member) ((unsigned long) &((type *)0)->member)
/*
* container_of - 根据成员地址@ptr和结构体类型,求取所在结构体的地址
*
* @ptr: 结构体成员指针
* @type: 结构体类型
* @member: 成员名称
*/
#define ContainerOf(ptr, type, member) ((type *)((uint8 *)(ptr) - OffsetOf(type, member)))


#ifdef  __cplusplus  
}  
#endif 

#endif
