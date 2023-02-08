#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "server.h"

static char    *str;

// TODO : Ecouter signaux
// TODO : Pack de signaux x8
// TODO : Traitement des signaux
// TODO : SIGUSR1 = 0   
// TODO : SIGUSR2 = 1

int main()
{
	int     pid_server;
	int		pid_client;
	int     len_msg;
	char	*msg;
	
	while (1)
	{
		printf("---------------------\n");
		pid_server = getpid();
		printf("PID SERVER: %i\n", pid_server);
		pid_client = read_pid_client();
		printf("PID CLIENT: %i\n", pid_client);
		len_msg = read_len();
		printf("LEN MSG: %i\n", len_msg);
		msg = read_msg(len_msg);
		printf("\nLe message est : %s\n", msg);
		if (msg)
			free(msg);
		usleep(50000);
		ft_putstr_fd("PID CLIENT: ", 1);
		ft_putnbr_fd(pid_client, 1);
		ft_putstr_fd("\n", 1);
		if (pid_client > 0)
			msg_seen(pid_client);
		// ft_putstr_fd("\n", 1);
		// str = ft_calloc(len, 1);
		// msg = read_message(len);
		// free(str);
	}
	return(0);
}

char	*read_msg(int len)
{
	int		i;
	char	*msg;

	i = 0;
	msg = ft_calloc(len + 1, 1);
	ft_putstr_fd("READ_MSG: ", 1);
	while (i < len)
	{
		msg[i] = read_char();
		ft_putchar_fd(msg[i], 1);
		i++;
	}
	return (msg);	
}

char	read_char()
{
	char msg;
	int bits_number;

	bits_number = 8;
	str = ft_calloc(bits_number + 1, 1);
	read_signal(bits_number);
	msg = ft_binary_to_int(str, 8);
	if (str)
		free(str);
	return (msg);
}

int    read_len()
{
	int len;
	int i_bit;
	int bits_number;

	bits_number = 32;
	str = ft_calloc(bits_number + 1, 1);
	read_signal(bits_number);
	len = ft_binary_to_int(str, bits_number);
	if (str)
		free(str);
	return (len);
}

int		read_pid_client()
{
	int	pid;
	int	bits_number;

	bits_number = 23;
	str = ft_calloc(bits_number + 1, 1);
	read_signal(bits_number);
	pid = ft_binary_to_int(str, bits_number);
	free(str);
	return (pid);
}

void	msg_seen(int pid_client)
{
	int	*binary_msg;
	int	bits_number;

	ft_putstr_fd("CLIENT MSG: ", 1);
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
		usleep(50000);
	}
}

void	read_signal(int bits_number)
{
	int	i;

	i = 0;
	while (i < bits_number)
	{
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
		i = ft_strlen(str);
	}
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
}