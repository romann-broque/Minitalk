/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 03:02:40 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/12 03:06:41 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	init_env(t_env *env)
{
	clear_char(env);
	env->client_pid = 0;
	env->final_str = NULL;
	env->end_of_transmission = false;
}

void	add_char(char **str, const char c)
{
	const char	new_str[2] = {c, '\0'};

	*str = ft_strnjoin(*str, new_str, sizeof(char));
}

void	clear_char(t_env *env)
{
	env->index = 0;
	env->curr_char = '\0';
}

void	process_byte(t_env *env)
{
	if (env->curr_char == END_TRANSMISSION)
		env->end_of_transmission = true;
	else
		add_char(&(env->final_str), env->curr_char);
	clear_char(env);
}
