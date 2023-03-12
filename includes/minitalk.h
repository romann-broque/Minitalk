/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:40:08 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/12 13:07:15 by rbroque          ###   ########.fr       */
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

// TIME

# define USECONDS_TO_WAIT	100
# define USECONDS_TO_CLOSE	500

// MESSAGE

# define MESSAGE_RECEIVED	"Message received"

// STRUCT

typedef struct s_env
{
	size_t		index;
	char		*final_str;
	int			client_pid;
	char		curr_char;
	bool		end_of_transmission;
	bool		is_waiting;
}				t_env;

// FUNCTIONS

// signal_utils.c

void	send_signal_to_server(const int pid, const int signal);
void	send_signal_to_client(const int pid, const int signal, t_env *env);

// server_transmission.c

void	end_of_transmission_routine(t_env *env);
void	loop_handler(t_env *env);
void	listening_loop_launcher(t_env *env);

// server_process.c

void	init_env(t_env *env);
void	add_char(char **str, const char c);
void	clear_char(t_env *env);
void	process_byte(t_env *env);

#endif
