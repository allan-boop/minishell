#include "../include/minishell.h"

static int	define_token_operator(t_tree *node)
{
	if (node->content[0] == '|' || node->content[0] == '&')
	{
		if (node->content[1] == '|' || node->content[1] == '&')
		{
			if (node->content[2] != '\0')
				return (0);
		}
		return (1);
	}
	else if (node->content[0] == '<' || node->content[0] == '>')
	{
		if (node->content[1] == '<' || node->content[1] == '>')
		{
			if (node->content[2] != '\0')
				return (0);
		}
		return (1);
	}
	return (0);
}

static int	define_token_cmd(t_tree *node, char **envp)
{
	ft_replace_space(&node->content);
	if (find_path(node->content, envp) != 0)
		return (2);
	ft_put_space_between(&node->content);
	return (0);
}

static int	define_token_var(t_tree *node)
{
	(void)node;
	return (0);
}

static int	define_token_str(t_tree *node)
{
	(void)node;
	return (0);
}

void	give_token(t_tree *node, char **envp)
{
	node->is_operator = false;
	node->is_cmd = false;
	node->is_var = false;
	node->is_str = false;
	if (define_token_operator(node) == 1)
		node->is_operator = true;
	else if (define_token_cmd(node, envp) == 2)
		node->is_cmd = true;
	else if (define_token_var(node) == 3)
		node->is_var = true;
	else if (define_token_str(node) == 4)
		node->is_str = true;
	printf("node->is_operator = %d\n", node->is_operator);
	printf("node->is_cmd = %d\n", node->is_cmd);
	printf("node->is_var = %d\n", node->is_var);
	printf("node->is_str = %d\n", node->is_str);
}
