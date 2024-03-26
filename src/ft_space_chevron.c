#include "../include/minishell.h"

void	ft_len_space_redirect(int *i, char *line, size_t *len)
{
	char	chev;
	char	inv_chev;

	if (line[*i] == 62 || line[*i] == 60)
	{
		chev = line[*i];
		if (chev == 62)
			inv_chev = 60;
		else
			inv_chev = 62;
		if (line[*i - 1] != ' ')
			(*len)++;
		if (line[*i + 1] == chev)
			(*i)++;
		if (line[*i] == inv_chev || line[*i + 1] == chev
			|| line[*i + 1] == inv_chev)
		{
			printf("Error bad chevron.\n");
			exit(1);
		}
		if (line[*i + 1] != ' ')
			(*len)++;
	}
}

void	ft_space_redirect(int *i, int *j, char *line, char *tmp)
{
	char	chev;

	chev = line[*i];
	if (line[*i - 1] != ' ')
	{
		tmp[*j] = ' ';
		(*j)++;
	}
	tmp[*j] = chev;
	(*j)++;
	(*i)++;
	if (line[*i] == chev)
	{
		tmp[*j] = chev;
		(*i)++;
		(*j)++;
	}
	if (line[*i] != ' ')
	{
		tmp[*j] = ' ';
		(*j)++;
	}
}
