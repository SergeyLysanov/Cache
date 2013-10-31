#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int value_type;
struct SElement
{
	value_type			Value;
	struct 	SElement* 	pNext;
};
typedef struct SElement SElement;

typedef struct SDeque
{
	SElement* pBottom;
	SElement* pTop;
} SDeque;

//deque functions
SDeque* create_deque();
void push_front(SDeque* pDeque, value_type Value);
void push_back(SDeque* pDeque, value_type Value);

value_type front(const SDeque* pDeque);
value_type back(const SDeque* pDeque);

value_type pop_front(SDeque* pDeque);
value_type pop_back(SDeque* pDeque);

bool isEmpty(const SDeque* pDeque);
void clear(SDeque* pDeque);
void deque_print(const SDeque* pDeque);

#endif
