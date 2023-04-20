#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - A function that frees up memory taken by args.
 * @args: Null-terminated double pointer with commands/arguments
 * @front: Double pointer to the beginning of arguments.
 */
void free_args(char **args, char **front)
{
	size_t ip;

	for (ip = 0; args[ip] || args[ip + 1]; ip++)
		free(args[ip]);

	free(front);
}

/**
 * get_pid - A function that gets the current process ID.
 * Description: Opens the stat file, a space-delimited file with
 *              info about current process. The PID is the
 *              first word in the file. It reads the PID into
 *              a buffer and replace the space at the end
 *              with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_t ip = 0;
	char *buffr;
	ssize_t fil;

	fil = open("/proc/self/stat", O_RDONLY);
	if (fil == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffr = malloc(120);
	if (!buffr)
	{
		close(fil);
		return (NULL);
	}
	read(fil, buffr, 120);
	while (buffr[ip] != ' ')
		ip++;
	buffr[ip] = '\0';

	close(fil);
	return (buffr);
}

/**
 * get_env_value - This function gets the value corresponding
 * to an env variable.
 * @beginning: The env variable to search for.
 * @len: The length of the env var to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *beginning, int len)
{
	char **var_address;
	char *replacemnt = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_address = _getenv(var);
	free(var);
	if (var_address)
	{
		temp = *var_address;
		while (*temp != '=')
			temp++;
		temp++;
		replacemnt = malloc(_strlen(temp) + 1);
		if (replacemnt)
			_strcpy(replacemnt, temp);
	}

	return (replacemnt);
}
