#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * _free - Frees memory allocated for a list of strings.
 * @list: A pointer to the list of strings.
 * @count: The number of elements in the list.
 */
void _free(char **list, int count)
{
	while (count >= 0)
	{
		memo_do(0, list[count]);
		count--;
	}
	memo_do(0, list);
}


char **_strtok(char *str, char *delim)
{
	int i = 0, j = 0, d = 0, l = 0, c = 0, f = 0;
	char **list = NULL;

	while (!(c = count_strg(str, delim)))
		return (NULL);
	list = memo_do((c + 1) * sizeof(char *), NULL);
	if (!list)
		return (NULL);
	for (i = 0, l = 0, c = 0; str[i] || l;)
	{
		for (d = 0, f = 0; delim[d]; d++)
		{
			if (((str[i] == delim[d]) || (!str[i])))
			{
				f += 1;
				if (l)
				{
					list[c] = memo_do(sizeof(char) * (l + 1), NULL);
					if (!list[c])
					{
						_free(list, c);
						return (NULL);
					}
					for (j = 0; l; l--, j++)
						list[c][j] = str[i - l];
					list[c][j] = '\0';
					c++;
				}
			}
		}
		if (!f)
			l++;
		if (str[i])
			i++;
	}
	list[c] = NULL;
	return (list);
}

