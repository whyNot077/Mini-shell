/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:09:54 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/24 18:03:36 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "structure.h"

int				get_node_type(t_token *tokens, int index, char **env);
t_binarytree	*parse_tokens(t_token *tokens, char **env);
void			parse_command_and_option(t_binarytree *tree, t_token *tokens,
					int *index);
int				is_redirection(int type);
void			parse_redirection(t_binarytree *tree, t_token *tokens,
					int *index);
void			parse_pipe(t_binarytree *tree, t_token *tokens, int *index);
void			parse_command(t_binarytree *tree, char *value, int type);
void			parse_and_or(t_binarytree *tree, t_token *tokens, int *index);
t_tree_node		*find_rightmost_node(t_tree_node *node);
void			fill_command_structure(t_binarytree *tree, char *value);
int				find_pipe(t_tree_node *current);
void			replace_env_key_to_value(char **value, char **env);
void			remove_quotes(char *value);

#endif