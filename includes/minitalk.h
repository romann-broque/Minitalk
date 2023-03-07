/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:40:08 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/07 20:56:16 by rbroque          ###   ########.fr       */
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

t_data	g_string_info;

// signal.c

void	send_signal(const int pid, const int sig, const char *sig_name);
void	signal_answer(int sig_nb, siginfo_t *siginfo);

#endif
