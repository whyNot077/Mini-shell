/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:30:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/21 14:13:51 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_tree(t_binarytree *tree, t_token *tokens, int *index)
{
	char	*value;
	int		type;
	int		token_count;

	token_count = tokens->token_count;
	while (*index < token_count)
	{
		value = tokens[*index].value;
		type = tokens[*index].type;
		if (type == WORD || type == BUILTIN)
			parse_command_and_option(tree, tokens, index);
		else if (is_redirection(type))
			parse_redirection(tree, tokens, index);
		else if (type == PIPE)
			parse_pipe(tree, tokens, index);
	}
}

t_binarytree	*parse_tokens(t_token *tokens, char **env)
{
	t_binarytree	*tree;
	int				index;

	index = 0;
	if (!tokens)
		return (NULL);
	tree = create_tree();
	while ((size_t)index < tokens->token_count)
	{
		if (tokens[index].type == WORD)
			tokens[index].type = get_node_type(&tokens[index].value, env);
		index++;
	}
	index = 0;
	parse_tree(tree, tokens, &index);
	// printf("tree->root->value: %s\n", tree->root->data);
	// printf("tree->key_node->value: %s\n", tree->key_node->data);
	// printf("tree->key->right->value: %s\n", tree->key_node->right->data);
	return (tree);
}