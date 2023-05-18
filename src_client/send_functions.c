/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrobert <alrobert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:47:27 by alrobert          #+#    #+#             */
/*   Updated: 2023/03/31 14:51:15 by alrobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./client.h"
# include <signal.h>
# include "libft.h"

void	send_pid(int pid_serv, int pid_client)
{
	int	*binary_pid;
	int	bit_number;

	bit_number = 23;
	binary_pid = ft_int_to_binary(pid_client, bit_number);
	send_to_server(pid_serv, binary_pid, bit_number);
	if (binary_pid)
		free(binary_pid);
}

void	send_len(int pid, char *msg)
{
	int	*binary_len;
	int	bit_number;

	bit_number = 32;
	binary_len = ft_int_to_binary(ft_strlen(msg), bit_number);
	send_to_server(pid, binary_len, bit_number);
	if (binary_len)
		free(binary_len);
}

void	send_msg(int pid, char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		send_char(pid, msg[i]);
		i++;
	}
}

void	send_char(int pid, char c)
{
	int	*binary;

	binary = ft_int_to_binary(c, 8);
	send_to_server(pid, binary, 8);
	if (binary)
		free(binary);
}

void	send_to_server(int pid, int *package, int bit_number)
{
	int	i;

	i = 0;
	while (i < bit_number)
	{
		if (package[i] == 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i++;
		usleep(2);
	}
}
