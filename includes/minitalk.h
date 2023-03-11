/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:40:08 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/10 01:38:24 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>

# define CHAR_SIZE			8
# define END_TRANSMISSION	0x04
# define NB_SIG				2
# define KILL_FAILURE		-1
# define EXPECTED_NB_ARG	3
# define USECONDS_TO_WAIT	100
# define USECONDS_TO_CLOSE	500

typedef struct s_env
{
	size_t		index;
	char		*final_str;
	int			client_pid;
	bool		end_of_transmission;
	char		curr_char;
}				t_env;


void	send_signal(const int pid, const int signal);

void listening_loop_laucher();

#endif
