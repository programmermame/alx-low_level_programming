#include "lists.h"



size_t dlistint_len(const dlistint_t *h)
{
size_t i = 0;
const dlistint_t *tmp = h;

while (tmp != NULL)
{
tmp = tmp->next;
i++;
}
return (i);

}
