#include "asm.h"

t_lexer	*add_list(t_lexer **list, char *name, int type, t_asm *env)
{
	t_lexer *new;
	t_lexer **head;

	head = list;
	new = (t_lexer *)ft_memalloc((sizeof(t_lexer)));
	new->name = name;
	new->type = type;
	new->next = NULL;
	if (!(*list))
		*list = new;
	else
	{
		while ((*list)->next)
			list = &(*list)->next;
		(*list)->next = new;
	}
	list = head;
	return (*head);
}


char	*grab_name(char *s)
{
	int		i;
	char	c;
	int		location;
	char	*string;

	location = -1;
	c = '/';
	string = (char *)s;
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == c)
			location = i;
		i++;
	}
	if (location != -1)
		return (string + location + 1);
	if (string[i] == c)
		return (string + i);
	return (NULL);
}
