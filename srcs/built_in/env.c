/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:59:09 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/03 18:10:35 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_arraylist *envp)
{
	int	idx;

	idx = 0;
	while (envp->data[idx])
	{
		ft_putstr_fd(envp->data[idx], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		idx++;
	}
}