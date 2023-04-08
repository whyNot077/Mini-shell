/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:30 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/08 13:59:55 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_token	*tokens;

	(void)envp;
	if (check_argc(argc, argv))
		return (0);
	while (1)
	{
		input = read_input();
		tokens = create_tokens_by_lexical_analysis(input);
		free(input);
		free_tokens(&tokens);
	}
	// system("leaks --list minishell > tmp.txt");
	return (0);
}