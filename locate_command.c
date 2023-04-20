#include "shell.h"
char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

/**
 * get_location - A function that locates a command in the PATH.
 * @command: The command to be located.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Else - the full pathname of the command.
 */
char *get_location(char *command)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			free_list(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	free_list(head);

	return (NULL);
}

/**
 * fill_path_dir - This function copies path but also replaces
 * leading/sandwiched/trailing colons (:) with current
 * working directory.
 * @path: The colon-separated list of directories.
 * Return: A copy of path with any leading/sandwiched/trailing
 * colons replaced with the current working directory.
 */
char *fill_path_dir(char *path)
{
	int ip, leng = 0;
	char *path_cpy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (ip = 0; path[ip]; ip++)
	{
		if (path[ip] == ':')
		{
			if (path[ip + 1] == ':' || ip == 0 || path[ip + 1] == '\0')
				leng += _strlen(pwd) + 1;
			else
				leng++;
		}
		else
			leng++;
	}
	path_cpy = malloc(sizeof(char) * (leng + 1));
	if (!path_cpy)
		return (NULL);
	path_cpy[0] = '\0';
	for (ip = 0; path[ip]; ip++)
	{
		if (path[ip] == ':')
		{
			if (ip == 0)
			{
				_strcat(path_cpy, pwd);
				_strcat(path_cpy, ":");
			}
			else if (path[ip + 1] == ':' || path[ip + 1] == '\0')
			{
				_strcat(path_cpy, ":");
				_strcat(path_cpy, pwd);
			}
			else
				_strcat(path_cpy, ":");
		}
		else
		{
			_strncat(path_cpy, &path[ip], 1);
		}
	}
	return (path_cpy);
}

/**
 * get_path_dir - Tokenizes a colon-separated list of
 *                directories to a list_s linked list.
 * @path: The colon-separated list of dirs.
 *
 * Return: pointer to the initialized linked list.
 */
list_t *get_path_dir(char *path)
{
	int indexx;
	char **dirs, *path_cpy;
	list_t *head = NULL;

	path_cpy = fill_path_dir(path);
	if (!path_cpy)
		return (NULL);
	dirs = _strtok(path_cpy, ":");
	free(path_cpy);
	if (!dirs)
		return (NULL);

	for (indexx = 0; dirs[indexx]; indexx++)
	{
		if (add_node_end(&head, dirs[indexx]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
