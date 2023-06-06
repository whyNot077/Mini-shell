/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_and_option.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:08:19 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/06 15:44:48 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree_node	*find_rightmost_node(t_tree_node *node)
{
	if (node == NULL)
		return (NULL);
	while (node->right)
		node = node->right;
	return (node);
}

int	find_pipe(t_tree_node *current)
{
	t_tree_node	*dummy;

	dummy = current;	
	while (dummy)
	{
		if (dummy->type == PIPE)
		{
			return (TRUE);
		}
		dummy = dummy->left;
	}
	return (FALSE);
}

static void	connect_command_node_to_tree(t_binarytree *tree, \
	t_tree_node *rightmost, t_tree_node *previous, t_tree_node *command_node)
{
	if (find_pipe(rightmost) == TRUE)
	{
		rightmost->right = command_node;
	}
	else if ((rightmost->type == WORD || rightmost->type == BUILTIN))
	{
		free(command_node);
	}
	else if (is_redirection(rightmost->type))
	{
		command_node->left = rightmost;
		if (previous)
			previous->right = command_node;
		else
			tree->root = command_node;
	}
}

void	add_command_to_the_tree(t_binarytree *tree, t_tree_node *command_node)
{
	t_tree_node	*current;
	t_tree_node	*previous;

	if (tree->root == NULL)
	{
		tree->root = command_node;
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
		connect_command_node_to_tree(tree, current, previous, command_node);
	}
}

void	parse_command_and_option(t_binarytree *tree, t_token *tokens,
		int *index)
{
	t_tree_node	*command_node;

	command_node = create_new_node(tokens[*index].value, tokens[*index].type);
	add_command_to_the_tree(tree, command_node);
	while (tokens[*index].type == WORD || tokens[*index].type == BUILTIN)
	{
		fill_command_structure(tree, tokens[*index].value);
		(*index)++;
	}
}
