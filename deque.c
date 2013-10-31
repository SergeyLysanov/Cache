#include "deque.h"

SDeque* create_deque()
{
	SDeque* pTemp = (SDeque*)malloc(sizeof(SDeque));
	pTemp->pBottom = 0;
	pTemp->pBottom = 0;
	return pTemp;
}
void push_back(SDeque* pDeque, value_type Value)
{
	SElement* pTemp = (SElement*)malloc(sizeof(SElement));
	pTemp->Value = Value;
	pTemp->pNext = 0;
	if (!pDeque->pBottom) //если первый
		pDeque->pTop = pTemp;
	else
		pDeque->pBottom->pNext = pTemp;
	pDeque->pBottom = pTemp;
}

void push_front(SDeque* pDeque, value_type Value)
{
	SElement* pTemp = (SElement*)calloc(1, sizeof(SElement));
	pTemp->Value = Value;
	pTemp->pNext = pDeque->pTop;
	if (!pDeque->pBottom) //если первый
		pDeque->pBottom = pTemp;
	pDeque->pTop = pTemp;
}

value_type front(const SDeque* pDeque)
{
	return pDeque->pTop ? pDeque->pTop->Value : NULL;
}

value_type back(const SDeque* pDeque)
{
	return pDeque->pBottom ? pDeque->pBottom->Value : NULL;
}

value_type pop_front(SDeque* pDeque)
{
	if(isEmpty(pDeque))
		return NULL;
	SElement* pTemp = pDeque->pTop;
	pDeque->pTop = pDeque->pTop->pNext;

	if(!pDeque->pTop)
		pDeque->pBottom = 0;

	value_type val = pTemp->Value;
	free(pTemp);

	return val;
}

value_type pop_back(SDeque* pDeque)
{
	if(isEmpty(pDeque))
		return NULL;
	SElement* pPrev = pDeque->pTop;
	while(pPrev->pNext != pDeque->pBottom && (pPrev->pNext))
		pPrev = pPrev->pNext;

	SElement* pTemp = pDeque->pBottom;

	if(!pPrev->pNext)
	{
		pDeque->pTop = 0;
		pDeque->pBottom = 0;
	}
	else
	{
		pPrev->pNext = 0;
		pDeque->pBottom = pPrev;
	}

	value_type val = pTemp->Value;
	free(pTemp);

	return val;
}

bool isEmpty(const SDeque* pDeque)
{
	return !pDeque->pTop;
}

void clear(SDeque* pDeque)
{
	while (pDeque->pTop)
	{
		SElement* pTemp = pDeque->pTop;
		pDeque->pTop = pDeque->pTop->pNext;
		free(pTemp);
	}
}

void deque_print(const SDeque* pDeque)
{
	SElement* pTemp = pDeque->pTop;
	while(pTemp)
	{
		printf("%d ", pTemp->Value);
		pTemp = pTemp->pNext;
	}
	printf("\n");
}
