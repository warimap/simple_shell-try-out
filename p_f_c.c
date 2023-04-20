#include "shell.h"

int cant_open(char *file_path);
int proc_file_commands(char *file_path, int *exe_ret);

/**
 * cant_open - A function which if the file doesn't exist or lack
 * proper permissions, print a cant open error.
 * @file_path: The path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *err, *histo_str;
	int length;

	histo_str = _itoa(hist);
	if (!histo_str)
		return (127);

	length = _strlen(name) + _strlen(histo_str) + _strlen(file_path) + 16;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(histo_str);
		return (127);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, histo_str);
	_strcat(err, ": Can't open ");
	_strcat(err, file_path);
	_strcat(err, "\n");

	free(histo_str);
	write(STDERR_FILENO, err, length);
	free(err);
	return (127);
}

/**
 * proc_file_commands - Ths function takes a file and attempts
 * to run the commands stored within.
 * @file_path: The path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Else the return value of the last command ran.
 */
int proc_file_commands(char *file_path, int *exe_ret)
{
	ssize_t files, b_rread, ip;
	unsigned int line_size = 0;
	unsigned int older_size = 120;
	char *line, **args, **front;
	char buff[120];
	int retn;

	hist = 0;
	files = open(file_path, O_RDONLY);
	if (files == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * older_size);
	if (!line)
		return (-1);
	do {
		b_rread = read(files, buff, 119);
		if (b_rread == 0 && line_size == 0)
			return (*exe_ret);
		buff[b_rread] = '\0';
		line_size += b_rread;
		line = _realloc(line, older_size, line_size);
		_strcat(line, buff);
		older_size = line_size;
	} while (b_rread);
	for (ip = 0; line[ip] == '\n'; ip++)
		line[ip] = ' ';
	for (; ip < line_size; ip++)
	{
		if (line[ip] == '\n')
		{
			line[ip] = ';';
			for (ip += 1; ip < line_size && line[ip] == '\n'; ip++)
				line[ip] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (ip = 0; args[ip]; ip++)
	{
		if (_strncmp(args[ip], ";", 1) == 0)
		{
			free(args[ip]);
			args[ip] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}

	ret = call_args(args, front, exe_ret);

	free(front);
	return (retn);
}
