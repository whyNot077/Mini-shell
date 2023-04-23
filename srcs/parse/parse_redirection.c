/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:24:15 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/23 20:33:58 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_filename(t_tree_node *new_node, char *value, int *index)
{
	new_node->filename = value;
	(*index)++;
}

/*
** if the tree is empty, add the command node to the root
** else, find the rightmost node.
** If the rightmost node is of type WORD, BUILTIN,
**	add the command node to the left of the rightmost node.
** else,
**	store the previous rightmost node as the left child of the new command node,
** and the command node should be the rightmost node.
*/
static void	connect_redirection_node(t_binarytree *tree, t_tree_node *current, \
		t_tree_node *previous, t_tree_node *new_node)
{
	if (current->type == WORD || current->type == BUILTIN)
	{
		new_node->left = current->left;
		current->left = new_node;
	}
	else
	{
		new_node->left = current;
		if (previous)
		{
			previous->right = new_node;
		}
		else
		{
			tree->root = new_node;
		}
	}
}

static void	redirection_to_tree(t_binarytree *tree, t_tree_node *new_node)
{
	t_tree_node	*current;
	t_tree_node	*previous;

	if (tree->root == NULL)
	{
		tree->root = new_node;
		return ;
	}
	else
	{
		current = tree->root;
		previous = NULL;
		while (current->right)
		{
			previous = current;
			current = current->right;
		}
		connect_redirection_node(tree, current, previous, new_node);
	}
}

void	parse_redirection(t_binarytree *tree, t_token *tokens, int *index)
{
	int			type;
	char		*redirection;
	t_tree_node	*new_node;

	type = tokens[*index].type;
	redirection = tokens[*index].value;
	if (is_redirection(type) == 0)
		return ;
	new_node = create_new_node(redirection, type);
	redirection_to_tree(tree, new_node);
	(*index)++;
	if (tokens[*index].type == WORD)
		parse_filename(new_node, tokens[*index].value, index);
	else
		printf("Error: Missing filename after '%s'\n", redirection);
}
