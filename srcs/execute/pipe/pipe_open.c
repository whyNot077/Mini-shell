/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:59:54 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/07 15:12:43 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	create_pipe(int *fd)
{
	if (pipe(fd) < 0)
	{
		ft_putstr_fd("ERROR: Failed to create a pipe\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	open_pipe(t_execute *exe_tool)
{
	create_pipe(exe_tool->pipe_fd);
	exe_tool->curr_pipe_flag = TRUE;
	exe_tool->pipe_flag = TRUE;
}
