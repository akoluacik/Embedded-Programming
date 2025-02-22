/*
 * queue.c
 *
 *  Created on: 16 Nis 2023
 *      Author: anil
 */

#include "queue.h"
#include <stdlib.h>
void	enqueue(struct queueNode **headPtr, struct queueNode **tailPtr, float data)
{
	struct queueNode *newNode = (struct queueNode*)malloc(sizeof(struct queueNode));
	if (newNode)
	{
		newNode->data = data;
		newNode->next = NULL;

		if (!(*headPtr))
			*headPtr = newNode;
		else
			(*tailPtr) -> next = newNode;
		*tailPtr = newNode;
	}
}

double	dequeue(struct queueNode **headPtr, struct queueNode **tailPtr, float data)
{
	float value = (*headPtr) -> data;
	struct queueNode *temp = *headPtr;
	*headPtr = (*headPtr) -> next;
	free(temp);
	return (value);
}

void    array2queue(struct queueNode **headPtr, struct queueNode **tailPtr, float *arr, int size)
{
	for (int var = 0; var < size; ++var)
		enqueue(headPtr, tailPtr, arr[var]);
}
