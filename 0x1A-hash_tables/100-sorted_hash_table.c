#include "hash_tables.h"

/**
 * set_spair - mallocs a key/value pair to the sorted hash table.
 * @key: the key, a string that cannot be empty.
 * @value: the value associated with the key, can be an empty string.
 *
 * Return: pointer to the new node, or NULL on failure.
 */
shash_node_t *set_spair(const char *key, const char *value)
{
    shash_node_t *node = malloc(sizeof(shash_node_t));

    if (node == NULL)
        return (NULL);

    node->key = strdup(key);
    if (node->key == NULL)
    {
        free(node);
        return (NULL);
    }

    node->value = strdup(value);
    if (node->value == NULL)
    {
        free(node->key);
        free(node);
        return (NULL);
    }

    return (node);
}

/**
 * shash_table_set - adds or updates an element to the sorted hash table.
 * @ht: pointer to the sorted hash table.
 * @key: the key, a string that cannot be empty.
 * @value: the value associated with the key, can be an empty string.
 *
 * Return: 1 on success, 0 on error.
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
    unsigned long int index;
    shash_node_t *node, *curr_old_node;

    if (key == NULL || ht == NULL)
        return (0);

    index = key_index((unsigned char *)key, ht->size);
    node = ht->array[index];

    if (node == NULL)
        node = set_spair_only(ht, key, value, index);
    else
    {
        while (node != NULL)
        {
            if (strcmp(node->key, key) == 0)
                return (update_value(node, value));
            node = node->next;
        }
        node = set_spair_front(ht, key, value, index);
    }

    if (node == NULL)
        return (0);

    if (ht->shead == NULL)
        return (slist_set_first(ht, node));

    curr_old_node = ht->shead;

    while (curr_old_node != NULL)
    {
        if (strcasecmp(curr_old_node->key, node->key) >= 0)
            return (slist_set(ht, curr_old_node, node));

        curr_old_node = curr_old_node->snext;
    }

    return (slist_set_end(ht, node));
}




/**
 * shash_table_get - retrieves a value associated with a key.
 * @ht: a pointer to the sorted hash table array.
 * @key: the key, a string that cannot be empty.
 *
 * Return: the value associated with the key, or NULL if key can't be found.
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int index;
	shash_node_t *node;

	if (ht == NULL)
		return (NULL);
	if (key == NULL)
		return (NULL);
	index = key_index((unsigned char *)key, ht->size);
	if (ht->array[index] == NULL)
		return (NULL);
	if (strcmp(ht->array[index]->key, key) == 0)
		return (ht->array[index]->value);
	node = ht->array[index];
	while (node != NULL)
	{
		if (strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

/**
 * shash_table_print - prints key/value pairs in sorted hash table order.
 * @ht: the sorted hash table.
 */
void shash_table_print(const shash_table_t *ht)
{
	unsigned long int count = 0;
	shash_node_t *node = ht->shead;

	if (ht == NULL)
		return;
	printf("{");
	while (node != NULL)
	{
		if (count > 0)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		node = node->snext;
		count++;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - prints sorted key/value pairs in reverse.
 * @ht: the sorted hash table.
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	unsigned long int count = 0;
	shash_node_t *node = ht->stail;

	if (ht == NULL)
		return;
	printf("{");
	while (node != NULL)
	{
		if (count > 0)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		node = node->sprev;
		count++;
	}
	printf("}\n");
}

/**
 * shash_table_delete - deletes a sorted hash table
 * @ht: the sorted hash table.
 */
void shash_table_delete(shash_table_t *ht)
{
	unsigned long int i = 0;
	shash_node_t *node;

	while (i < ht->size)
	{
		while (ht->array[i] != NULL)
		{
			node = ht->array[i]->next;
			free(ht->array[i]->key);
			free(ht->array[i]->value);
			free(ht->array[i]);
			ht->array[i] = node;
		}
		i++;
	}
	free(ht->array);
	free(ht);
}
