#include "shell.h"
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);
/**
 * get_args - A function that gets a command from standard input
 * @line: A buffer to store the command.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Else - a pointer to the stored command.
 */
char *get_args(char *line, int *exe_ret)
{
	size_t nm = 0;
	ssize_t rread;
	char *prompt = "$ ";

	if (line)
		free(line);

	rread = _getline(&line, &nm, STDIN_FILENO);
	if (rread == -1)
		return (NULL);
	if (rread == 1)
	{
		history++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[rread - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, rread);

	return (line);
}

/**
 * call_args - Partitions operators from commands and calls them.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int call_args(char **args, char **front, int *exe_ret)
{
	int retn, indexx;

	if (!args[0])
		return (*exe_ret);
	for (indexx = 0; args[indexx]; indexx++)
	{
		if (_strncmp(args[indexx], "||", 2) == 0)
		{
			free(args[indexx]);
			args[indexx] = NULL;
			args = replace_aliases(args);
			retn = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++indexx];
				indexx = 0;
			}
			else
			{
				for (indexx++; args[indexx]; indexx++)
					free(args[indexx]);
				return (retn);
			}
		}
		else if (_strncmp(args[indexx], "&&", 2) == 0)
		{
			free(args[indexx]);
			args[indexx] = NULL;
			args = replace_aliases(args);
			retn = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++indexx];
				indexx = 0;
			}
			else
			{
				for (indexx++; args[indexx]; indexx++)
					free(args[indexx]);
				return (retn);
			}
		}
	}
	args = replace_aliases(args);
	retn = run_args(args, front, exe_ret);
	return (retn);
}

/**
 * run_args - A function that calls the execution of a command.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The retn of parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_args(char **args, char **front, int *exe_ret)
{
	int retn, ip;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		retn = builtin(args + 1, front);
		if (retn != EXIT)
			*exe_ret = retn;
	}
	else
	{
		*exe_ret = execute(args, front);
		retn = *exe_ret;
	}

	history++;

	for (ip = 0; args[ip]; ip++)
		free(args[ip]);

	return (retn);
}

/**
 * handle_args - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_args(int *exe_ret)
{
	int retn = 0, indexx;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (retn);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (indexx = 0; args[indexx]; indexx++)
	{
		if (_strncmp(args[indexx], ";", 1) == 0)
		{
			free(args[indexx]);
			args[indexx] = NULL;
			retn = call_args(args, front, exe_ret);
			args = &args[++indexx];
			indexx = 0;
		}
	}
	if (args)
		retn = call_args(args, front, exe_ret);

	free(front);
	return (retn);
}

/**
 * check_args - The function checks if there are any
 * leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid
 * position - 2. Otherwise - 0.
 */
int check_args(char **args)
{
	size_t ip;
	char *currnt, *next;

	for (ip = 0; args[ip]; ip++)
	{
		currnt = args[ip];
		if (currnt[0] == ';' || currnt[0] == '&' || currnt[0] == '|')
		{
			if (ip == 0 || currnt[1] == ';')
				return (create_error(&args[ip], 2));
			next = args[ip + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (create_error(&args[ip + 1], 2));
		}
	}
	return (0);
}
