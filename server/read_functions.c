/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrobert <alrobert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:57:09 by alrobert          #+#    #+#             */
/*   Updated: 2023/03/31 16:38:46 by alrobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char	*g_str;

char	read_char(void)
{
	char	msg;
	int		bits_number;

	bits_number = 8;
	g_str = ft_calloc(bits_number + 1, 1);
	read_signal(bits_number);
	msg = ft_binary_to_int(g_str, 8);
	if (g_str)
		free(g_str);
	return (msg);
}

int	read_len(void)
{
	int	len;
	int	bits_number;

	bits_number = 32;
	g_str = ft_calloc(bits_number + 1, 1);
	read_signal(bits_number);
	len = ft_binary_to_int(g_str, bits_number);
	if (g_str)
		free(g_str);
	return (len);
}

int	read_pid_client(void)
{
	int	pid;
	int	bits_number;

	bits_number = 23;
	g_str = ft_calloc(bits_number + 1, 1);
	read_signal(bits_number);
	pid = ft_binary_to_int(g_str, bits_number);
	free(g_str);
	return (pid);
}

void	read_signal(int bits_number)
{
	int	i;

	i = 0;
	while (i < bits_number)
	{
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
		i = ft_strlen(g_str);
	}
}

void	handler(int sig)
{
	int	i;

	i = 0;
	while (g_str[i])
		i++;
	if (sig == 10)
		g_str[i] = '0';
	if (sig == 12)
		g_str[i] = '1';
}
