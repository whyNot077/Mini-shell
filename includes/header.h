/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:47:19 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/11 13:44:21 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <term.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "token.h"
# include "execute.h"
# include "built_in.h"
# include "../libft/libft.h"
# include "binary_tree.h"
# include "main.h"
# include "signal.h"

#endif