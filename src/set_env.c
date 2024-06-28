#include "../include/minishell.h"

void	set_env(char **envp, t_env *env, int argc, char **argv)
{
	env->copy_envp = ft_copy_envp_no_sort(envp);
	if (argc == 3 && ft_strcmp(argv[1], "env") == 0
		&& ft_strcmp(argv[2], "-i") == 0)
	{
		env->pwd = false;
		env->oldpwd = false;
		env->home = false;
		env->shlvl = false;
		env->path = false;
		return ;
	}
	env->pwd = true;
	env->oldpwd = true;
	env->home = true;
	env->shlvl = true;
	env->path = true;
}
