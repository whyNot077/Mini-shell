/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:08:27 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/29 15:17:58 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_dollar_question_mark(char *value)
{
	if (ft_strcmp(value, "$?") != 0)
		return ;
	free(value);
	value = ft_itoa(g_exit_code);
}

static int	is_builtin(char *value)
{
	if (ft_strcmp(value, "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(value, "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(value, "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(value, "export") == 0)
		return (TRUE);
	else if (ft_strcmp(value, "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(value, "env") == 0)
		return (TRUE);
	else if (ft_strcmp(value, "exit") == 0)
		return (TRUE);
	else
		return (FALSE);
}

int	is_redirection(int type)
{
	return (type == REDIRECT_OUT || type == HEREDOC \
		|| type == REDIRECT_IN || type == REDIRECT_APPEND);
}

int	get_node_type(t_token *tokens, int index, char **env)
{
	char	*value;

	if (tokens == NULL || index < 0)
		return (ERROR);
	value = tokens[index].value;
	if (value == NULL)
		return (ERROR);
	if (is_builtin(value))
		return (BUILTIN);
	else
	{
		parse_dollar_question_mark(value);
		replace_env_key_to_value(&value, env);
		remove_quotes(value);
		tokens[index].value = value;
		return (WORD);
	}
}
