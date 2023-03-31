/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrobert <alrobert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:53:43 by alrobert          #+#    #+#             */
/*   Updated: 2023/03/31 16:42:01 by alrobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./client.h"

int	main(int argc, char *argv[])
{
	if (argc != 3)
		ft_putstr_fd("Il manque un ou plusieurs argument", 1);
	else
		start(argv);
	return (0);
}

void	start(char *argv[])
{
	int	pid;

	if (check_pid(argv[1]))
	{
		ft_putstr_fd("Mauvais PID", 1);
		return ;
	}
	pid = ft_atoi(argv[1]);
	send_pid(pid, getpid());
	send_len(pid, argv[2]);
	send_msg(pid, argv[2]);
	ft_putstr_fd(argv[2], 1);
	ft_putchar_fd('\n', 1);
	read_seen_server();
}

int	check_pid(char *pid)
{
	int	i;
	int	is_error;

	i = 0;
	is_error = 0;
	while (pid[i] && !is_error)
	{
		if (pid[i] < 48 || pid[i] > 57)
			is_error = 1;
		i++;
	}
	return (is_error);
}

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

void	read_seen_server(void)
{
	int	i;
	int	bits_number;
	int	time;

	i = 0;
	time = 0;
	bits_number = 32;
	g_str = ft_calloc(bits_number + 1, 1);
	while (i < bits_number)
	{
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
		while (!i && time < 100000)
		{
			time++;
			i = ft_strlen(g_str);
			usleep(10);
		}
		i = ft_strlen(g_str);
		if (time == 100000)
		{
			ft_putstr_fd("Aucune connexion au serveur...", 1);
			break ;
		}
	}
	if (i == bits_number)
		ft_putstr_fd("vu", 1);
	free(g_str);
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
