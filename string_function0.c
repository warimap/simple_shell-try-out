#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - This function returns the length of a string.
 * @s: pointer to the characters string.
 *
 * Return: length of the character string.
 */
int _strlen(const char *s)
{
	int len = 0;

	if (!s)
		return (len);
	for
		(len = 0;
			s[len];
			len++);
	return (len);
}

/**
 * _strcpy - Copies string pointed to by src, with the
 *           terminating null byte, to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t ip;

	for (ip = 0; src[ip] != '\0'; ip++)
		dest[ip] = src[ip];
	dest[ip] = '\0';
	return (dest);
}

/**
 * _strcat - A function concantenates two strings.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_length = _strlen(dest);
	size_t ip;

	for (ip = 0; ip < n && src[ip] != '\0'; ip++)
		dest[dest_length + ip] = src[ip];
	dest[dest_length + ip] = '\0';

	return (dest);
}
