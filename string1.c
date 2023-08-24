#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * _strcmp - Compare two strings.
 * @s1: First string to compare.
 * @s2: Second string to compare.
 * Return: The difference in ASCII values of the first differing characters, or 0 if they are equal.
 */
int _strcmp(char *s1, char *s2)
{
	char *str1 = s1;
	char *str2 = s2;

	if (!s1 && !s2)
		return (0);

	if (!s1 || !s2)
		return (-1);

	while (*str1 == *str2)
	{
		if (*str1 == '\0')
			break;
		if (*str2 == '\0')
			break;
		str1++;
		str2++;
	}

	if (*str1 < *str2)
		return (*str1 - *str2);
	if (*str1 > *str2)
		return (*str1 - *str2);

	return (0);
}


/**
 * _strlen - Calculate the length of a string.
 * @s: The input string.
 * Return: The length of the string.
 */
int _strlen(char *s)
{
	int length = 0;

	while (s && s[length] != '\0')
		length++;

	return (length);
}

/**
 * _strcpy - Copy a string.
 * @dest: The destination buffer.
 * @src: The source string.
 * Return: A pointer to the destination buffer.
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; i <= _strlen(src); i++)
	{
		dest[i] = src[i];
	}

	return (dest);
}
/**
 * count_strg - Count the number of non-empty substrings in a string.
 * @str: The input string.
 * @delim: The delimiter character.
 * Return: The count of non-empty substrings.
 */
int count_strg(char *str, char *delim)
{
	int i, isNewSubstring = 0, count = 0;

	for (i = 0; str && str[i]; i++)
	{
		if ((str[i] == delim[0]) && isNewSubstring)
		{
			count++;
			isNewSubstring = 0;
		}
		else if (str[i] != delim[0])
			isNewSubstring = 1;
	}
	if (str && str[0])
		count++;

	return (count);
}


/**
 * _strcat - Concatenate two strings.
 * @dest: The destination string.
 * @src: The source string.
 * Return: The concatenated string.
 */
char *_strcat(char *dest, char *src)
{
	char *destEnd;
	char *srcIter;

	if (!src)
		return (dest);
	if (!dest)
		return (src);

	destEnd = dest;
	srcIter = src;

	while (*destEnd != '\0')
		destEnd++;

	while (*srcIter != '\0')
	{
		*destEnd = *srcIter;
		destEnd++;
		srcIter++;
	}
	*destEnd = '\0';

	return (dest);
}
