/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_apply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:59:54 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/04 21:18:28 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	create_pipe(int *fd)
{
	if (pipe(fd) < 0)
	{
		ft_putstr_fd("ERROR: Failed to create a pipe\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (fd[0] < 0 || fd[1] < 0)
	{
		ft_putstr_fd("ERROR: Failed to create a pipe\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	apply_pipe(t_execute *exe_tool)
{
	create_pipe(exe_tool->pipe_fd);
	exe_tool->pipe_flag = TRUE;
	exe_tool->pid = fork();
}
