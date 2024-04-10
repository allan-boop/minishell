#include "../../include/minishell.h"

static int	ft_count_simple_quotes(char *arg, size_t simple_quote)
{
	size_t		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			simple_quote++;
	}
	return (simple_quote);
}

static int	ft_count_double_quotes(char *arg, size_t double_quote)
{
	size_t		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			double_quote++;
	}
	return (double_quote);
}

char	*ft_del_quotes(char *arg)
{
	size_t		simple_quote;
	size_t		double_quote;

	simple_quote = 0;
	double_quote = 0;
	simple_quote = ft_count_simple_quotes(arg, simple_quote);
	double_quote = ft_count_double_quotes(arg, double_quote);
}
