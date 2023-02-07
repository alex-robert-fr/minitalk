/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrobert <alrobert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:53:43 by alrobert          #+#    #+#             */
/*   Updated: 2023/02/07 18:34:00 by alrobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "./client.h"

static char *str;

int	main(int argc, char *argv[])
{
	if (argc != 3)
		printf("Il manque un ou plusieurs argument");
	else
		start(argv);
	return(0);
}

void	start(char *argv[])
{
	int	i_char;
	int	i_bit;
	int	pid;
	
	pid = ft_atoi(argv[1]);
	ft_putstr_fd("\nSEND PID:", 1);
	send_pid(pid, getpid());
	ft_putstr_fd("SEND LEN:", 1);
	send_len(pid, argv[2]);
	// pause();
	// read_seen_server();
	
	// i_char = 0;

	// while (argv[2][i_char])
	// {
	// 	i_bit = 7;
	// 	while (i_bit >= 0)
	// 	{
	// 		if (argv[2][i_char] >> i_bit & 1)
	// 		{
	//     		kill(pid, SIGUSR2);
	// 			ft_putstr_fd("1", 1);
	// 		}
	// 		else
	// 		{
	//     		kill(pid, SIGUSR1);
	// 			ft_putstr_fd("0", 1);
	// 		}
	// 		i_bit--;
	// 		usleep(100000);
	// 	}
	// 	i_char++;
	// }
	// i_bit = 0;
	// while (i_bit < 7)
	// {
	// 	kill(pid, SIGUSR1);
	// 	usleep(100000);
	// 	i_bit++;
	// }
	printf("\nPID: %s\n", argv[1]);
	printf("Message: %s", argv[2]);
}

void	send_len(int pid, char *msg)
{
	int	*binary_len;
	int	bit_number;

	bit_number = 32;
	binary_len = ft_int_to_binary(ft_strlen(msg), bit_number);
	send_to_server(pid, binary_len, bit_number);
}

void	send_pid(int pid_serv, int pid_client)
{
	int *binary_pid;
	int bit_number;

	bit_number = 23;
	binary_pid = ft_int_to_binary(pid_client, bit_number);	
	send_to_server(pid_serv, binary_pid, bit_number);
}

void	send_to_server(int pid, int *package, int bit_number)
{
	int	i;

	i = 0;
	printf("\nPID SERVER!!! %i !!!\n", pid);
	while (i < bit_number)
	{
		if (package[i] == 1)
		{
			kill(pid, SIGUSR2);
			ft_putstr_fd("1", 1);
		}
		else
		{
			kill(pid, SIGUSR1);
			ft_putstr_fd("0", 1);
		}
		i++;
		ft_putchar_fd('a', 1);
		ft_putchar_fd('{', 1);
		ft_putnbr_fd(i, 1);
		ft_putchar_fd('}', 1);
		usleep(100000);
	}
	ft_putstr_fd("\nPID SERVER !!!\n", 1);
}

void	read_seen_server()
{
	int i;
	int	bits_number;
	
	i = 0;
	bits_number = 32;
	str = ft_calloc(bits_number + 1, 1);	
	while (i < bits_number)
	{
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
		i = ft_strlen(str);
	}
	if (i == bits_number)
		ft_putstr_fd("\nOK\n", 1);
	free(str);
}

void    handler(int sig)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (sig == 10)
		str[i] = '0';
	if (sig == 12)
		str[i] = '1';
	ft_putchar_fd(str[i], 1);
	ft_putchar_fd('\n', 1);
}