/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrobert <alrobert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:34:51 by alrobert          #+#    #+#             */
/*   Updated: 2023/03/31 16:39:33 by alrobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char	*g_str;

void	minitalk(void)
{
	ft_putstr_fd(T1, 1);
	ft_putstr_fd(T2, 1);
	ft_putstr_fd(T3, 1);
	ft_putstr_fd(T4, 1);
	ft_putstr_fd(T5, 1);
	ft_putstr_fd(T6, 1);
	ft_putstr_fd(T7, 1);
}

int	main(void)
{
	int		pid_server;
	int		pid_client;
	int		len_msg;
	char	*msg;

	minitalk();
	pid_server = getpid();
	ft_putstr_fd("PID SERVER: ", 1);
	ft_putnbr_fd(pid_server, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(T7, 1);
	while (1)
	{
		pid_client = read_pid_client();
		len_msg = read_len();
		msg = read_msg(len_msg);
		ft_putstr_fd("user_", 1);
		ft_putnbr_fd(pid_client, 1);
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(msg, 1);
		ft_putchar_fd('\n', 1);
		if (msg)
			free(msg);
		usleep(30);
		if (pid_client > 0)
			msg_seen(pid_client);
	}
	return (0);
}

void	msg_seen(int pid_client)
{
	int	*binary_msg;
	int	bits_number;

	bits_number = 32;
	binary_msg = ft_int_to_binary(1802070889, bits_number);
	send_signal(pid_client, binary_msg, bits_number);
	if (binary_msg)
		free(binary_msg);
}

void	send_signal(int pid, int *package, int bits_number)
{
	int	i;

	i = 0;
	while (i < bits_number)
	{
		if (package[i] == 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i++;
		usleep(2);
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




char	*read_msg(int len)
{
	int		i;
	char	*msg;

	i = 0;
	msg = ft_calloc(len + 1, 1);
	while (i < len)
	{
		msg[i] = read_char();
		i++;
	}
	return (msg);
}

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
