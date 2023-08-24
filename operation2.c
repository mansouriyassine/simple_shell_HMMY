#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 *__lst_free_all - Frees a linked list of table_lst nodes and their data.
 *@head: A pointer to the head of the linked list.
 */
void __lst_free_all(table_lst *head)
{
	table_lst *current_node = NULL;

	while (head != NULL)
	{
		current_node = head;
		head = head->next;
		free(current_node->ptr);
		free(current_node);
	}
}

/**
 *__nodeget_indx - Returns the node at a specified index in a linked list.
 *@head: A pointer to the head of the linked list.
 *@index: The index of the node to retrieve.
 *
 *Return: A pointer to the node at the specified index, or NULL if not found.
 */
table_lst *__nodeget_indx(table_lst *head, unsigned int index)
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
 *__nodeinsrt_indx - Inserts a new node at a specified index in a linked list.
 *@head: A pointer to a pointer to the head of the linked list.
 *@idx: The index at which to insert the new node.
 *@ptr: A pointer to the data to be stored in the new node.
 *
 *Return: A pointer to the newly inserted node, or NULL on failure.
 */
table_lst *__nodeinsrt_indx(table_lst **head, unsigned int idx, void *ptr)
{
	table_lst *new_node = NULL, *container = *head;
	unsigned int i = 0;

	if (!idx)
	{
		new_node = malloc(sizeof(table_lst));
		if (!new_node)
			return (NULL);

		new_node->ptr = ptr;
		new_node->next = *head;

		*head = new_node;

		return (*head);
	}

	while (container)
	{
		if (i == (idx - 1))
		{
			new_node = malloc(sizeof(table_lst));
			if (!new_node)
				return (NULL);
			new_node->ptr = ptr;
			new_node->next = container->next;
			container->next = new_node;
			return (new_node);
		}

		container = container->next;
		i++;
	}

	return (NULL);
}

/**
 *__dlt_nodeindx - Deletes a node at a specified index in a linked list.
 *@head: A pointer to a pointer to the head of the linked list.
 *@index: The index of the node to delete.
 *
 *Return: 1 on success, -1 on failure.
 */
int __dlt_nodeindx(table_lst **head, unsigned int index)
{
	table_lst *container = NULL, *to_delete = NULL;
	unsigned int i = 0, action = 0;

	if (!*head)
		return (-1);

	for (i = 0, container = *head;
		container && index;
		i++, container = container->next)
	{
		if (i == (index - 1))
		{
			action = 1;
			break;
		}
	}

	if (action)
	{
		to_delete = container->next;
		container->next = to_delete->next;
		free(to_delete);
		return (1);
	}
	else if (!index && (*head)->next)
	{
		to_delete = *head;
		*head = to_delete->next;
		free(to_delete);
		return (1);
	}
	else if (!index && *head)
	{
		free(*head);
		*head = NULL;
		return (1);
	}

	return (-1);
}
