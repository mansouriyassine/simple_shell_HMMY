#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * memo_do - Memory management function to allocate and free memory.
 * @size: Size of memory to alloc  memory associated with @ptr.
 * @ptr: Pointer to memory to free. If NULL, frees all allocated memory.
 * Return: Pointer to allocated memory if successful, NULL otherwise.
 */
void *memo_do(size_t size, void *ptr)
{
	static table_lst *allocated_memory;
	void *result = NULL;
	int i = 0, length = 0;

	if (size)
	{
		result = malloc(size);
		if (!result)
			exit_do(2, "malloc failed", EXIT_FAILURE);

		for (i = 0; (unsigned int)i < size; i++)
			((char *)result)[i] = 0;

		__node_insrt_tail(&allocated_memory, result);
		return (result);
	}
	else if (ptr)
	{
		length = __lenght_lst(allocated_memory);

		for (i = 0; i < length; i++)
		{
			if (__nodeget_indx(allocated_memory, i)->ptr == ptr)
			{
				__dlt_nodeindx(&allocated_memory, i);
				break;
			}
		}

		free(ptr);
		return (NULL);
	}
	else
	{
		__lst_free_all(allocated_memory);
		return (NULL);
	}

	return (NULL);
}


/**
 * exit_do - Exit the program with a message and a specific exit code.
 * @fd: File descriptor for writing the message.
 * @msg: Message to print before exiting.
 * @code: Exit code to use.
 */
void exit_do(int fd, char *msg, int code)
{
	if (*msg)
	{
		write(fd, msg, _strlen(msg));
	}

	memo_do(0, NULL);
	exit(code);
}
