/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:02:24 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/31 17:57:29 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	 execute(t_tree_node *root, t_execute *exe_tool)
{
	if (root == NULL)
		return ;
	execute(root->left, exe_tool);
	// if (root->type == AND)
	// 	apply_and(root, exe_tool);
	// else if (root->type == OR)
	// 	apply_or(root, exe_tool);
	if (root->type == PIPE)
		open_pipe(exe_tool);
	// else if (root->type == REDIRECT_APPEND)
	// 	open_redirect_append(root, exe_tool);
	else if (root->type == REDIRECT_IN || root->type == HEREDOC)
		open_redirect_in(root, exe_tool);
	else if (root->type == REDIRECT_OUT)
		open_redirect_out(root, exe_tool);
	else if (root->type == BUILTIN && exe_tool->pipe_flag == FALSE)
		built_in(root->command, exe_tool);
	else if (root->type == BUILTIN && exe_tool->pipe_flag == TRUE)
	{
		if (exe_tool->curr_pipe_flag == FALSE)
		{
			exe_tool->pipe_flag = FALSE;
			exe_tool->exit_flag = TRUE;
		}
		apply_built_in_pipe(root->command, exe_tool);
	}
	else if (root->type == WORD)
		apply_command(root->command, exe_tool);
	execute(root->right, exe_tool);
}
