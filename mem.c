#include "shell.h"

/**
 * _realloc - moves data in pointer to new area with different space allocated
 *
 * @ptr: pointer to move data from
 * @old_size: size of current pointer
 * @new_size: size of new pointer
 * Return: returns pointer to space allocated
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *newspace;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		newspace = malloc(new_size);
		if (newspace == NULL)
			return (NULL);
		return (newspace);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	newspace = malloc(new_size);
	if (newspace == NULL)
		return (NULL);
	for (i = 0; i < old_size && i < new_size; i++)
		newspace[i] = ((char *)ptr)[i];
	free(ptr);
	return (newspace);
}

/**
 * _memcpy - copies memory location in src to destination
 *
 *@dest: destination memory location
 *@src: source memory location
 *@n: number of bytes
 *Return: returns pointer to destination
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	int i;

	i = 0;
	while (i < (int)n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

/**
 * mloc - malloc function that bails out on failure and attempts to free
 * might miss some stuff (like the buffer) however. if helper is supplied
 * NULL, mloc will just exit on code 98.
 *
 * @b: size to malloc
 * @helper: helper func so we can free it out if needed
 * Return: returns malloc'd space, or nothing on failure (exits)
 */
void *mloc(unsigned int b, helper_t *helper)
{
	void *pointer;

	pointer = malloc(b);
	if (pointer == NULL)
	{
		perror("Memory allocation failure. Bailing out!");
		if (helper == NULL)
			_exit(98);
		exitBuiltin("98", NULL, helper);
	}
	return (pointer);
}
