/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:02:22 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/09 22:11:50 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "structure.h"

t_token	*create_token(const char *value);
int		is_operator(char c);
int		is_space(char c);
void	type_of_token(t_token *tokens, int token_index);
t_token	*create_tokens_by_lexical_analysis(const char *input);
t_token	*special_tokens(t_token *tokens, int token_index);
int		is_special_token(char *token);
int		is_quote_char(char c);
int		is_backslash(char c);
char	*get_line(char quote_char);
int		find_quote_to_the_end(char *buffer, int *buffer_index,
			const char *input, int *i);
void	buffer_to_token_value(char *buffer, int *buffer_index, t_token *tokens,
			int *token_index);
void	read_input_until_finding_the_quote(char quote_char, \
		char *buffer, int *buffer_index, t_process_input_data *data);
int		num_of_special_tokens(t_token *tokens, int token_index);
void	free_tokens(t_token **tokens_ptr);
void	handle_operator(const char *input, int i, t_token *tokens,
		int *token_index);
void	process_input(const char *input, t_token *tokens, int *token_index);

#endif