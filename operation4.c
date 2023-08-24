#include "shell.h"

/**
 * arrayify_list - Converts a linked  allocated array of strings.
 * @head: Pointer to the head of the linked list.
 * Return: Dynamically allocated array of strings.
 */
char **arrayify_list(sig_list *head)
{
	char **result_array = NULL;
	char *tmp_str = NULL;
	char *node_value = NULL;
	int list_length = 0;
	int i = 0;

	list_length = lenght_lst(head);
	result_array = memo_do(sizeof(char *) * (list_length + 1), NULL);

	for (i = 0; i < list_length; i++)
	{
		node_value = node_get_index(head, i)->ptr;
		tmp_str = memo_do(sizeof(char) * (_strlen(node_value) + 1), NULL);
		tmp_str = _strcat(tmp_str, node_value);
		result_array[i] = tmp_str;
	}

	result_array[i] = NULL;
	return (result_array);
}


/**
 * lstfy - Creates a linked list from an array of strings.
 * @arr: Array of strings.
 * Return: Pointer to the head of the linked list.
 */
sig_list *lstfy(char **arr)
{
	sig_list *rof = NULL;
	char *tmp = NULL;
	int i = 0;

	while (arr[i])
	{
		tmp = memo_do(sizeof(char) * (_strlen(arr[i]) + 1), NULL);
		tmp = _strcat(tmp, arr[i]);
		node_insrt_tail(&rof, tmp);
		i++;
	}
	return (rof);
}


/**
 * dbl_matrix_free - Frees a double matrix (array of strings).
 * @list: Double matrix to be freed.
 */
void dbl_matrix_free(char **list)
{
	int i = 0;

	for (i = 0; list[i]; i++)
		memo_do(0, list[i]);
	memo_do(0, list);
}

