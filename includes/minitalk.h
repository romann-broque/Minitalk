/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:40:08 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/09 23:35:36 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>

# define BUFFER_SIZE_SIG	4
# define CHAR_SIZE			8
# define END_CHAR			'\0'

typedef struct s_env
{
	size_t		index;
	int			client_pid;
	char		curr_char;
	char		*final_str;
}				t_env;

#endif
