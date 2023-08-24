#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 *lst_free_all - Frees a linked list of sig_list nodes along with their ptrs.
 *@head: Pointer to the head of the linked list.
 */
void lst_free_all(sig_list *head)
{
	sig_list *hold = NULL;

	while (head != NULL)
	{
		hold = head;
		head = head->next;
		memo_do(0, hold->ptr);
		memo_do(0, hold);
	}
}

/**
 *node_get_index - Returns the node at a specified index in a linked list.
 *@head: Pointer to the head of the linked list.
 *@index: Index of the desired node.
 *Return: Pointer to the node at the given index, or NULL if not found.
 */
sig_list *node_get_index(sig_list *head, unsigned int index)
{
	unsigned int i = 0;

	for (i = 0; head; i++, head = head->next)
	{
		if (i == index)
		{
			return (head);
		}
	}

	return (NULL);
}

/**
 *node_insert_index - Inserts a new node  in the linked list.
 *@head: Pointer to the head of the linked list.
 *@idx: Index at which the new node should be inserted.
 *@ptr: Data to be stored in the new node.
 *Return: Pointer to the newly inserted node, or NULL on failure.
 */
sig_list *node_insert_index(sig_list **head, unsigned int idx, char *ptr)
{
	sig_list *new_node = NULL, *current = *head;
	unsigned int i = 0;

	if (!idx)
	{
		new_node = memo_do(sizeof(sig_list), NULL);
		if (!new_node)
			return (NULL);

		new_node->ptr = ptr;
		new_node->next = *head;

		*head = new_node;

		return (*head);
	}

	while (current)
	{
		if (i == (idx - 1))
		{
			new_node = memo_do(sizeof(sig_list), NULL);
			if (!new_node)
				return (NULL);
			new_node->ptr = ptr;
			new_node->next = current->next;
			current->next = new_node;
			return (new_node);
		}

		current = current->next;
		i++;
	}

	return (NULL);
}

/**
 *delete_node_index - Deletes a node at the specified index in the linked list.
 *@head: Pointer to the head of the linked list.
 *@index: Index of the node to be deleted.
 *Return: 1 if successful, -1 on failure.
 */
int delete_node_index(sig_list **head, unsigned int index)
{
	sig_list *current = NULL, *to_delete = NULL;
	unsigned int i = 0, action = 0;

	if (!*head)
		return (-1);

	for (i = 0, current = *head; current && index; i++, current = current->next)
	{
		if (i == (index - 1))
		{
			action = 1;
			break;
		}
	}

	if (action)
	{
		to_delete = current->next;
		current->next = to_delete->next;
		memo_do(0, to_delete);
		return (1);
	}
	else if (!index && (*head)->next)
	{
		to_delete = *head;
		*head = to_delete->next;
		memo_do(0, to_delete);
		return (1);
	}
	else if (!index && *head)
	{
		*head = NULL;
		memo_do(0, *head);
		return (1);
	}

	return (-1);
}
