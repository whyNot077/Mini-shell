/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:30 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/07 15:41:14 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;

	(void)envp;
	if (check_argc(argc, argv))
		return (0);
	while (1)
	{
		printf("%sMinishell >%s", BLUE, DEFAULT);
		input = read_input();
		if (input == NULL)
			break ;
	}
	return (0);
}
