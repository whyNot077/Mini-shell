/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:23:31 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 12:12:39 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	next_token_is_io_redirect(t_token *tokens, int index)
{
	return ((size_t)index < tokens->token_count &&
			(tokens[index].type == REDIRECT_OUT
					|| tokens[index].type == REDIRECT_IN
					|| tokens[index].type == REDIRECT_APPEND
					|| tokens[index].type == HEREDOC));
}

tree_node	*parse_cmd_prefix(t_token *tokens, int *index)
{
	tree_node	*node;
	tree_node	*temp_node;

	node = NULL;
	while (next_token_is_io_redirect(tokens, *index))
	{
		temp_node = parse_io_redirect(tokens, index);
		if (!temp_node)
		{
			free_tree(node);
			return (NULL);
		}
		if (!node)
		{
			node = temp_node;
		}
		else
		{
			temp_node->left = node;
			node = temp_node;
		}
	}
	return (node);
}

tree_node	*parse_cmd_suffix(t_token *tokens, int *index)
{
	tree_node	*node;
	tree_node	*temp_node;

	node = NULL;
	while (next_token_is_io_redirect(tokens, *index)
		|| tokens[*index].type == WORD)
	{
		if (next_token_is_io_redirect(tokens, *index))
		{
			temp_node = parse_io_redirect(tokens, index);
			if (!temp_node)
			{
				free_tree(node);
				return (NULL);
			}
		}
		else
		{
			temp_node = parse_commands(tokens, index);
		}
		if (!node)
		{
			node = temp_node;
		}
		else
		{
			temp_node->left = node;
			node = temp_node;
		}
	}
	return (node);
}

tree_node	*parse_redirect(t_token *tokens, int *index)
{
	tree_node	*node;

	if (tokens[*index].type == REDIRECT_OUT
		|| tokens[*index].type == REDIRECT_IN
		|| tokens[*index].type == REDIRECT_APPEND)
	{
		node = create_new_node(&tokens[*index]);
		node->type = tokens[*index].type;
		(*index)++;
	}
	else if (tokens[*index].type == HEREDOC)
	{
		node = create_new_node(&tokens[*index]);
		node->type = tokens[*index].type;
		(*index)++;
	}
	else
	{
		printf("Error: syntax error near unexpected token %s\n",
				tokens[*index].value);
		return (NULL);
	}
	if (tokens[*index].value == NULL)
	{
		free(node);
		printf("Error: syntax error near unexpected token %s\n", tokens[*index
				- 1].value);
		return (NULL);
	}
	else if (tokens[*index].type != WORD)
	{
		free(node);
		printf("Error: syntax error near unexpected token %s\n",
				tokens[*index].value);
		return (NULL);
	}
	node->right = create_new_node(&tokens[*index]);
	node->right->type = tokens[*index].type;
	node->right->data = tokens[*index].value;
	(*index)++;
	return (node);
}

tree_node	*parse_pipe_sequence(t_token *tokens, int *index)
{
	tree_node	*node;
	tree_node	*temp_node;

	node = parse_command(tokens, index);
	while ((size_t)*index < tokens->token_count && tokens[*index].type == PIPE)
	{
		temp_node = create_new_node(&tokens[*index]);
		temp_node->type = tokens[*index].type;
		(*index)++;
		temp_node->left = node;
		temp_node->right = parse_command(tokens, index);
		node = temp_node;
	}
	return (node);
}

tree_node	*parse_io_redirect(t_token *tokens, int *index)
{
	tree_node	*node;

	if (tokens[*index].type == REDIRECT_OUT
		|| tokens[*index].type == REDIRECT_IN ||
		tokens[*index].type == REDIRECT_APPEND
			|| tokens[*index].type == HEREDOC)
	{
		node = create_new_node(&tokens[*index]);
		node->type = tokens[*index].type;
		(*index)++;
		if (tokens[*index].value == NULL)
		{
			free(node);
			printf("Error: syntax error near unexpected token %s\n",
					tokens[*index - 1].value);
			return (NULL);
		}
		else if (tokens[*index].type != WORD)
		{
			free(node);
			printf("Error: syntax error near unexpected token %s\n",
					tokens[*index].value);
			return (NULL);
		}
		node->right = parse_commands(tokens, index);
	}
	else
	{
		printf("Error: syntax error near unexpected token %s\n",
				tokens[*index].value);
		return (NULL);
	}
	return (node);
}
