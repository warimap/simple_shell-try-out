#include "shell.h"

alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

/**
 * add_alias_end - Adds a node to end of a alias_t linked list.
 * @head: pointer to the head of the list_t list.
 * @name: name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Else - a pointer to the new node.
 */
alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *newer_node = malloc(sizeof(alias_t));
	alias_t *lastly;

	if (!newer_node)
		return (NULL);

	newer_node->next = NULL;
	newer_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!newer_node->name)
	{
		free(newer_node);
		return (NULL);
	}
	newer_node->value = value;
	_strcpy(newer_node->name, name);

	if (*head)
	{
		lastly = *head;
		while (lastly->next != NULL)
			lastly = lastly->next;
		lastly->next = newer_node;
	}
	else
		*head = newer_node;

	return (newer_node);
}

/**
 * add_node_end - Adds a node to the end of a list_t linked list
 * @head: Pointer to the head of the list_t list.
 * @dir: Directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Else - a pointer to the new node.
 */
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *newer_node = malloc(sizeof(list_t));
	list_t *lastly;

	if (!newer_node)
		return (NULL);

	newer_node->dir = dir;
	newer_node->next = NULL;

	if (*head)
	{
		lastly = *head;
		while (lastly->next != NULL)
			lastly = lastly->next;
		lastly->next = newer_node;
	}
	else
		*head = newer_node;

	return (newer_node);
}

/**
 * free_alias_list - Frees a alias_t linked list.
 * @head: THe head of the alias_t list.
 */
void free_alias_list(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

/**
 * free_list - Frees a list_t linked list.
 * @head: The head of the list_t list.
 */
void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
