#include "../../include/minishell.h"

void	ft_list_cmd(t_mini *shell)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	shell->tab_cmd = ft_alloc(sizeof(char **));
	while (shell->tab_pars && shell->tab_pars[i++])
	{
		tmp = NULL;
		printf("i : %d\n", i);
		if (shell->tab_pars[i] && shell->tab_pars[i + 1]
			&& shell->tab_pars[i][0] == '|'
			&& shell->tab_pars[i][0] == '<'
			&& shell->tab_pars[i][0] == '>')
			i++;
		while (shell->tab_pars[i]
			&& shell->tab_pars[i][0] != '|'
			&& shell->tab_pars[i][0] != '<'
			&& shell->tab_pars[i][0] != '>')
		{
			if (tmp == NULL)
				tmp = ft_strdup_shell(shell->tab_pars[i]);
			else
			{
				tmp = ft_strjoin(tmp, " ");
				tmp = ft_strjoin_shell(tmp, shell->tab_pars[i]);
			}
			printf("tmp : %s\n", tmp);
			i++;
		}
		if (tmp)
		{
			shell->tab_cmd[j] = ft_strdup_shell(tmp);
			printf("shell_tab : %s\n", shell->tab_cmd[j]);
			j++;
		}
	}
}
