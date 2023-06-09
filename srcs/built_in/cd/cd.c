/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:05:25 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/08 21:28:23 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	update_pwd(t_arraylist *env, t_arraylist *export, \
						char *old_pwd_value)
{
	char	*pwd_value;
	char	*pwd;
	char	*old_pwd;
	char	*export_old_pwd;
	char	*export_pwd;

	apply_unset("OLDPWD", env, export);
	old_pwd = ft_strjoin("OLDPWD=", old_pwd_value);
	al_add_rear(env, old_pwd);
	export_old_pwd = ft_strdup(old_pwd);
	al_add_rear(export, export_old_pwd);
	apply_unset("PWD", env, export);
	pwd_value = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", pwd_value);
	al_add_rear(env, pwd);
	export_pwd = ft_strdup(pwd);
	al_add_rear(export, export_pwd);
	free(old_pwd_value);
	free(pwd_value);
}

static int	check_home_dir(t_execute *execute)
{
	int		home_value;
	char	*home;
	char	*pwd_value;

	pwd_value = getcwd(NULL, 0);
	if (pwd_value == NULL)
	{
		home = get_target_value("HOME", execute->env);
		chdir(home);
		return (ERROR);
	}
	home_value = get_env_value("HOME", execute->env);
	if (home_value == ERROR)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_exit_code = 1;
		return (ERROR);
	}
	return (SUCCESS);
}

static int	count_args(char **args)
{
	int	args_count;

	args_count = 0;
	while (args[args_count])
		args_count++;
	return (args_count);
}

void	apply_cd(t_execute *execute, char *pwd_value)
{
	update_pwd(execute->env, execute->export, pwd_value);
}

void	cd(char **args, t_execute *execute)
{
	char	*pwd_value;
	int		args_count;

	args_count = count_args(args);
	g_exit_code = 0;
	if (args_count > 2)
		return (g_exit_code = 1,
			ft_putstr_fd("bash: cd: too many arguments\n", 2));
	if (args[1] == NULL && check_home_dir(execute) == ERROR)
		return ;
	if (args[1] == NULL)
	{
		apply_normal_cd(execute);
		return ;
	}
	pwd_value = getcwd(NULL, 0);
	if (pwd_value == NULL)
		return (g_exit_code = 1,
			ft_putstr_fd("bash: cd: No such file or directory\n", 2));
	if (validate_chdir(args, pwd_value) == ERROR)
		return ;
	apply_cd(execute, pwd_value);
}
