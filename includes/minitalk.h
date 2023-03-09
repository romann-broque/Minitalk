/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:40:08 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/09 15:07:46 by rbroque          ###   ########.fr       */
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

void	init_sigact(void (*handler)(int, siginfo_t *, void *));
void	init_data(t_data *data);
void	reset_data(t_data *data);
uint8_t	get_bit(const int nb);

#endif
