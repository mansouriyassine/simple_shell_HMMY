#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 *lenght_lst - Calculate the length of a linked list.
 *@h: Pointer to the head of the linked list.
 *
 *Return: The length of the linked list.
 */
size_t lenght_lst(sig_list *h)
{
	size_t count = 0;

	while (h)
	{
		count++;
		h = h->next;
	}

	return (count);
}

/**
 *add_node - Add a new node at the beginning of the linked list.
 *@head: Pointer to a pointer to the head of the linked list.
 *@ptr: Pointer value to store in the new node.
 *
 *Return: A pointer to the new node, or NULL if allocation fails.
 */
sig_list *add_node(sig_list **head, char *ptr)
{
	sig_list *new_node = NULL;

	new_node = memo_do(sizeof(sig_list), NULL);
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
 *node_insrt_tail - Insert a new node at the end of the linked list.
 *@head: Pointer to a pointer to the head of the linked list.
 *@ptr: Pointer value to store in the new node.
 *
 *Return: A pointer to the new node, or NULL if allocation fails.
 */
sig_list *node_insrt_tail(sig_list **head, char *ptr)
{
	sig_list *new_node = NULL, *last = NULL;

	new_node = memo_do(sizeof(sig_list), NULL);
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
	{
	}

	last->next = new_node;
	return (new_node);
}

/**
 *lst_free - Frees a linked list of sig_list nodes.
 *@head: Pointer to the head of the linked list.
 */
void lst_free(sig_list *head)
{
	sig_list *hold = NULL;

	while (head != NULL)
	{
		hold = head;
		head = head->next;
		memo_do(0, hold);
	}
}
