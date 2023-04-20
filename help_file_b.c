#include "shell.h"

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - A function that partitions a line read from
 * the standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||",
 * and "&&". Replaces "#" with '\0'.
 */
void handle_line(char **line, ssize_t read)
{
	char *older_line, *newer_line;
	char prev, curr, nxt;
	size_t ip, ja;
	ssize_t new_length;

	new_length = get_new_len(*line);
	if (new_length == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	ja = 0;
	older_line = *line;
	for (ip = 0; older_line[ip]; ip++)
	{
		curr = older_line[ip];
		nxt = older_line[ip + 1];
		if (i != 0)
		{
			prev = older_line[ip - 1];
			if (curr == ';')
			{
				if (nxt == ';' && prev != ' ' && prev != ';')
				{
					newer_line[ja++] = ' ';
					newer_line[ja++] = ';';
					continue;
				}
				else if (prev == ';' && nxt != ' ')
				{
					newer_line[ja++] = ';';
					newer_line[j++] = ' ';
					continue;
				}
				if (prev != ' ')
					newer_line[j++] = ' ';
				newer_line[ja++] = ';';
				if (nxt != ' ')
					newer_line[j++] = ' ';
				continue;
			}
			else if (curr == '&')
			{
				if (nxt == '&' && prev != ' ')
					newer_line[ja++] = ' ';
				else if (prev == '&' && nxt != ' ')
				{
					newer_line[j++] = '&';
					newer_line[j++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (nxt == '|' && prev != ' ')
					newer_line[ja++]  = ' ';
				else if (prev == '|' && nxt != ' ')
				{
					newer_line[ja++] = '|';
					newer_line[ja++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (ip != 0 && older_line[ip - 1] != ' ')
				newer_line[ja++] = ' ';
			newer_line[ja++] = ';';
			if (nxt != ' ' && nxt != ';')
				newer_line[ja++] = ' ';
			continue;
		}
		newer_line[ja++] = older_line[ip];
	}
	newer_line[ja] = '\0';

	free(*line);
	*line = newer_line;
}

/**
 * get_new_len - This function gets the new length of a line
 * partitioned by ";", "||", "&&&", or "#".
 * @line: The line to be checked.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
	size_t ip;
	ssize_t new_length = 0;
	char curr, nxt;

	for (ip = 0; line[ip]; ip++)
	{
		curr = line[ip];
		nxt = line[ip + 1];
		if (curr == '#')
		{
			if (ip == 0 || line[ip - 1] == ' ')
			{
				line[ip] = '\0';
				break;
			}
		}
		else if (ip != 0)
		{
			if (curr == ';')
			{
				if (nxt == ';' && line[ip - 1] != ' ' && line[ip - 1] != ';')
				{
					new_length += 2;
					continue;
				}
				else if (line[ip - 1] == ';' && nxt != ' ')
				{
					new_length += 2;
					continue;
				}
				if (line[ip - 1] != ' ')
					new_length++;
				if (nxt != ' ')
					new_length++;
			}
			else
				logical_ops(&line[ip], &new_length);
		}
		else if (curr == ';')
		{
			if (ip != 0 && line[ip - 1] != ' ')
				new_length++;
			if (nxt != ' ' && nxt != ';')
				new_length++;
		}
		new_length++;
	}
	return (new_length);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char prev, curr, nxt;

	prev = *(line - 1);
	curr = *line;
	nxt = *(line + 1);

	if (curr == '&')
	{
		if (nxt == '&' && prev != ' ')
			(*new_length)++;
		else if (prev == '&' && nxt != ' ')
			(*new_length)++;
	}
	else if (curr == '|')
	{
		if (nxt == '|' && prev != ' ')
			(*new_length)++;
		else if (prev == '|' && nxt != ' ')
			(*new_length)++;
	}
}
