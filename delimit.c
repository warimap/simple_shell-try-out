#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - Functions locates the delimiter index marking end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The delimiter index marking the end of
 *         the intitial token pointed to be str.
 */
int token_len(char *str, char *delim)
{
	int indexx = 0, length = 0;

	while (*(str + indexx) && *(str + indexx) != *delim)
	{
		length++;
		indexx++;
	}

	return (length);
}

/**
 * count_tokens - A function counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int count_tokens(char *str, char *delim)
{
	int indexx, tokens = 0, length = 0;

	for (indexx = 0; *(str + indexx); indexx++)
		length++;

	for (indexx = 0; indexx < length; indexx++)
	{
		if (*(str + indexx) != *delim)
		{
			tokens++;
			indexx += token_len(str + indexx, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - This function tokenizes a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int indexx = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[indexx] == *delim)
			indexx++;

		letters = token_len(line + indexx, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (indexx -= 1; indexx >= 0; indexx--)
				free(ptr[indexx]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[indexx];
			indexx++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
