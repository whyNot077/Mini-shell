/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_apply.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:55:45 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/09 18:43:57 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_commands(char **args, char **full_path, \
								t_execute *exe_tool)
{
	int		paths_idx;
	char	*temp_path;

	if (access(args[0], X_OK) == 0)
	{
		*full_path = ft_strdup(args[0]);
		return (SUCCESS);
	}
	paths_idx = 0;
	while (exe_tool->paths[paths_idx])
	{
		temp_path = ft_strjoin(exe_tool->paths[paths_idx], "/");
		*full_path = ft_strjoin(temp_path, args[0]);
		if (access(*full_path, X_OK) == 0)
		{
			free(temp_path);
			return (SUCCESS);
		}
		free(*full_path);
		free(temp_path);
		paths_idx++;
	}
	return (ERROR);
}

void	execute_command(char *full_path, char **args, t_execute *exe_tool)
{
	pid_t	pid;
	int		status;

	exe_tool->dup_tmp = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
		child_process(full_path, args, exe_tool);
	else
	{
		parent_process(exe_tool);
		waitpid(pid, &status, 0);
		exe_tool->pipe_flag = FALSE;
		free(full_path);
		if (exe_tool->outfile_fd > 0)
		{
			dup2(exe_tool->dup_tmp, STDOUT_FILENO);
			close(exe_tool->outfile_fd);
		}
	}
	restore_redirect_in(exe_tool);
	restore_redirect_out(exe_tool);
}

void	apply_command(char **args, t_execute *exe_tool)
{
	char	*full_path;

	full_path = NULL;
	// exe_tool->paths = get_paths(exe_tool->env->data);
	if (exe_tool->paths == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return ;
	}
	if (validate_commands(args, &full_path, exe_tool) == ERROR)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return ;
	}
	execute_command(full_path, args, exe_tool);
}