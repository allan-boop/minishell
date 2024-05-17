#include "../../include/minishell.h"

void	ft_redirection(t_mini *shell)
{
	int	i;

	i = shell->tab_index;
	shell->filein = -1;
	shell->fileout = -1;
	while (shell->tab_pars[i] && shell->tab_pars[i][0] != '|')
	{
		if (shell->tab_pars[i][0] == '<' && shell->tab_pars[i + 1])
			shell->filein = open(shell->tab_pars[i + 1], O_RDONLY);
		if (shell->tab_pars[i][0] == '>'
			&& shell->tab_pars[i][1] == '>' && shell->tab_pars[i + 1])
			shell->fileout = open(shell->tab_pars[i + 1], O_WRONLY
					| O_CREAT | O_APPEND, 0777);
		else if (shell->tab_pars[i][0] == '>' && shell->tab_pars[i + 1])
			shell->fileout = open(shell->tab_pars[i + 1], O_WRONLY
					| O_CREAT | O_TRUNC, 0777);
		i++;
	}
}
