/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:40:08 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/09 10:50:13 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>

typedef struct s_data
{
	size_t		index_bit;
	char		curr_byte;
	char		*final_str;
}				t_data;

// signal.c

void	waiting_for_signal(void);
void	send_signal(const int pid, const int sig, const char *sig_name);
void	send_ping_to_client(int sig_nb, siginfo_t *siginfo);

// utils.c

void	init_data(t_data *data);
void	reset_data(t_data *data);
uint8_t	get_bit(const int nb);
void	add_char(t_data *str_info);

#endif
