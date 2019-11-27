#include "shell.h"

/**
 * initEnvList - turns the environment list into a linked list
 *
 * @environ: 2d array of environment vars
 * @head: head for our envlist (should start out NULL)
 *
 * Return: returns pointer to new head
 */
env_t *initEnvList(char **environ, env_t **head)
{
	env_t *newnode, *tempnode;
	char *saveptr, *tok, *temp;
	char equals = '=';
	char newline = '\n';
	int i;

	i = 0;
	while (environ[i] != NULL)
	{
		newnode = mloc(sizeof(env_t), NULL);
		if (newnode == NULL)
			return (NULL);
		temp = _strdup(environ[i]);
		tok = splitstr(temp, &equals, &saveptr);
		if (tok != NULL)
			newnode->name = _strdup(tok);
		tok = splitstr(NULL, &newline, &saveptr);
		if (tok != NULL)
			newnode->value = _strdup(tok);
		free(temp);
		if (*head == NULL)
		{
			newnode->next = *head;
			*head = newnode;
		}
		else
		{
			newnode->next = NULL;
			tempnode = *head;
			while (tempnode->next != NULL)
				tempnode = tempnode->next;
			tempnode->next = newnode;
		}
		i++;
	}
	return (*head);
}

/**
 * buildEnv - builds a 2d array from our linked list so we can send
 * it to our child processes
 *
 * @head: head to linked list
 * @envsize: environment size variable to store environment size in
 *
 * Return: returns our new 2d array
 */
char **buildEnv(env_t *head, int *envsize)
{
	env_t *temp;
	char **envs;
	char *env, *env2;
	int i;

	temp = head;
	i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	*envsize = i;
	temp = head;
	envs = mloc(sizeof(char *) * (i + 1), NULL);
	i = 0;
	while (temp != NULL)
	{
		env = _strdup(temp->name);
		env2 = str_concat(env, "=");
		free(env);
		env = str_concat(env2, temp->value);
		envs[i] = _strdup(env);
		free(env);
		free(env2);
		temp = temp->next;
		i++;
	}
	envs[i] = NULL;
	return (envs);
}

/**
 * free_list - frees a list_t linked list
 * @head: head of linked list
 */
void free_list(env_t *head)
{
	env_t *temp;

	temp = head;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
	free(head);
}

/**
 * addEnv - adds a node to the bottom of a linked list
 * does not check to see if one already exists (check beforehand plz)
 *
 * @head: head of linked list
 * @name: name of env to add
 * @value: value of env to add
 *
 * Return: returns a pointer to the new node
 */
env_t *addEnv(env_t **head, char *name, char *value)
{
	env_t *newnode, *tempnode;


	if (head == NULL || name == NULL || value == NULL)
		return (NULL);
	newnode = mloc(sizeof(env_t), NULL);
	if (newnode == NULL)
		return (NULL);
	newnode->name = _strdup(name);
	newnode->value = _strdup(value);
	if (*head == NULL)
	{
		newnode->next = *head;
		*head = newnode;
	}
	else
	{
		newnode->next = NULL;
		tempnode = *head;
		while (tempnode->next != NULL)
			tempnode = tempnode->next;
		tempnode->next = newnode;
	}
	return (newnode);
}

/**
 * getEnvPtr - gets a pointer to a matching environment variable
 *
 * @name: name of environment variable to search for
 * @head: the head of the env linked list
 * Return: returns a pointer to the environment variable, or NULL if none found
 */
env_t *getEnvPtr(char *name, env_t *head)
{
	env_t *environ;

	environ = head;
	while (environ != NULL)
	{
		if (allstrcmp(name, environ->name) == 0)
			return (environ);
		environ = environ->next;
	}
	return (NULL);
}
