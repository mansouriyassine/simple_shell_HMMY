#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 *__lenght_lst - Calculate the length of a linked list.
 *@h: A pointer to the head of the linked list.
 *
 *Return: The length of the linked list.
 */
size_t __lenght_lst(table_lst *h)
{
	int i = 0;

	while (h != NULL)
	{
		i++;
		h = h->next;
	}

	return (i);
}

/**
 *__node_insrt - Insert a new node at the beginning of a linked list.
 *@head: A pointer to a pointer to the head of the linked list.
 *@ptr: A pointer to the data to be stored in the new node.
 *
 *Return: A pointer to the newly created node, or NULL on failure.
 */
table_lst *__node_insrt(table_lst **head, void *ptr)
{
	table_lst *new_node = NULL;

	new_node = malloc(sizeof(table_lst));
	if (!new_node)
	{
		return (NULL);
	}

	new_node->ptr = ptr;
	new_node->next = *head;

	*head = new_node;
	return (new_node);
}

/**
 *__node_insrt_tail - Insert a new node at the end of a linked list.
 *@head: A pointer to a pointer to the head of the linked list.
 *@ptr: A pointer to the data to be stored in the new node.
 *
 *Return: A pointer to the newly created node, or NULL on failure.
 */
table_lst *__node_insrt_tail(table_lst **head, void *ptr)
{
	table_lst *new_node = NULL, *last = NULL;

	new_node = malloc(sizeof(table_lst));
	if (!new_node)
	{
		return (NULL);
	}

	new_node->ptr = ptr;
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}

	for (last = *head; last->next != NULL; last = last->next)
	;

	last->next = new_node;
	return (new_node);
}

/**
 *__lst_free - Frees a linked list of table_lst nodes.
 *@head: A pointer to the head of the linked list.
 */
void __lst_free(table_lst *head)
{
	table_lst *contrainer = NULL;

	while (head != NULL)
	{
		contrainer = head;
		head = head->next;
		free(contrainer);
	}
}
