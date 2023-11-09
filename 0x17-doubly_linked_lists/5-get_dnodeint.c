#include "lists.h"

dlistint_t *get_dnodeint_at_index(dlistint_t *head, unsigned int index)
{
dlistint_t *tmp;
unsigned int i;

tmp = head;
i = 0;
if (head == NULL)
return (NULL);
while (tmp != NULL)
{
if (i == index)
return (tmp);
tmp = tmp->next;
i++;
}
return (NULL);
}
