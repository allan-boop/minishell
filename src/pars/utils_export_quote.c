#include "../../include/minishell.h"

static int	nblen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa_shell(int n)
{
	char	*result;
	int		len;

	len = 0;
	if (n == -2147483648)
		return (ft_strdup_shell("-2147483648"));
	len = nblen(n);
	result = (char *)ft_alloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n == 0)
		result[0] = '0';
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	while (n)
	{
		result[--len] = (n % 10) + '0';
		n = n / 10;
	}
	return (result);
}

static int	ft_check_name_quotes(char *arg)
{
	int		i;
	char	*just_name_var;
	char	quote;

	if (!arg)
		return (1);
	i = 0;
	quote = 0;
	just_name_var = ft_find_name_var(arg);
	while (just_name_var[i])
	{
		if (quote == 0 && (just_name_var[i] == '\''
				|| just_name_var[i] == '\"'))
			quote = just_name_var[i];
		else if (quote == '\'' && just_name_var[i] == '\"')
			return (syntax_error(QUOTE_FAIL), 1);
		else if (quote == '\"' && just_name_var[i] == '\'')
			return (syntax_error(QUOTE_FAIL), 1);
		i++;
	}
	return (0);
}

int	ft_del_quotes(char **arg)
{
	if (ft_check_name_quotes(*arg) == 1)
		return (1);
	if (ft_replace_quote_export(arg) == 1)
		return (1);
	return (0);
}
