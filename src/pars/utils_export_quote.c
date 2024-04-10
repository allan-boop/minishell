#include "../../include/minishell.h"

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

int	ft_del_quotes(char *arg, t_mini *shell)
{
	if (ft_check_name_quotes(arg) == 1)
		return (1);
	if (shell->tab_pars[shell->tab_index + 1] != NULL)
	{
		syntax_error(INVALID_IDENTIFIER);
		return (1);
	}
	ft_replace_quote_export(arg, true);
	return (0);
}
