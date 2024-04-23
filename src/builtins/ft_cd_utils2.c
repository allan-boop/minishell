#include "../../include/minishell.h"

void	f_find_dpointb(int *i, int *start, char **str, char **new)
{
	int	j;

	j = (*i) - 2;
	while ((*str)[j] != '/')
		j--;
	while (*start < j)
	{
		(*new)[0] = (*str)[*start];
		(*start)++;
		(*new)++;
	}
	if ((*str)[*i + 2])
		*i += 3;
	else
		*i += 2;
	*start = *i;
	if ((*str)[*i])
	{
		(*new)[0] = '/';
		(*new)++;
	}
}
