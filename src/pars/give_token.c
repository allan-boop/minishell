#include "../../include/minishell.h"

static int	define_token_redirection(t_list_struct *node)
{
	if (node->content[0] == '>')
	{
		if (node->content[1] == '>')
		{
			if (node->content[2] != '\0')
				return (0);
			return (1);
		}
		if (node->content[1] != '\0')
			return (0);
		return (1);
	}
	else if (node->content[0] == '<')
	{
		if (node->content[1] == '<')
		{
			if (node->content[2] != '\0')
				return (0);
			return (1);
		}
		if (node->content[1] != '\0')
			return (0);
		return (1);
	}
	return (0);
}

static int	define_token_operator(t_list_struct *node)
{
	if (node->content[0] == '|')
	{
		if (node->content[1] != '\0')
			return (0);
		return (1);
	}
	return (0);
}

void	give_token(t_list_struct *node)
{
	node->is_operator = false;
	node->is_redir = false;
	if (define_token_operator(node) == 1)
		node->is_operator = true;
	else if (define_token_redirection(node) == 1)
		node->is_redir = true;
}
