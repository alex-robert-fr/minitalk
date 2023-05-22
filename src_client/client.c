/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrobert <alrobert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:53:43 by alrobert          #+#    #+#             */
/*   Updated: 2023/05/22 11:48:50 by alrobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./client.h"
#include <signal.h>
#include "libft.h"

static char	*g_str;

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
	int	bits_number;

	bits_number = 32;
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
	g_str = ft_calloc(bits_number + 1, 1);
	read_seen_server(bits_number);
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

void	read_seen_server(int bits_number)
{
	int	i;
	int	time;

	i = 0;
	time = 0;
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
