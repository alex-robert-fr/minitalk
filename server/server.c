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
		printf("\n---------------------\n");
		pid_server = getpid();
		printf("PID SERVER: %i\n", pid_server);
		pid_client = read_pid_client();
		printf("PID CLIENT: %i\n", pid_client);
		len_msg = read_len();
		printf("LEN MSG: %i\n", len_msg);
		if (pid_client > 0)
			msg_seen(pid_client);
		// str = ft_calloc(len, 1);
		// msg = read_message(len);
		// printf("Le message est : %s\n", msg);
		// free(str);
	}
	return(0);
}

int    read_len()
{
	int len;
	int i_bit;
	int bits_number;

	bits_number = 32;
	read_signal(bits_number);
	len = ft_binary_to_int(str, bits_number);
	free(str);
	return (len);
}

int		read_pid_client()
{
	int	pid;
	int	bits_number;

	bits_number = 23;
	read_signal(bits_number);
	pid = ft_binary_to_int(str, bits_number);
	free(str);
	return (pid);
}

void	msg_seen(int pid_client)
{
	int	*binary_msg;
	int	bits_number;

	printf("CLIENT MSG");
	bits_number = 32;
	binary_msg = ft_int_to_binary(1802070889, bits_number);
	send_signal(pid_client, binary_msg, bits_number);
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
		usleep(100000);
	}
}

void	read_signal(int bits_number)
{
	int	i;

	i = 0;
	str = ft_calloc(bits_number + 1, 1);
	while (i < bits_number)
	{
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
		i = ft_strlen(str);
	}
}

// char    *read_message(int len)
// {
//     int     count;
//     char    letter;
//     int     i_string;
//     char    *string;

//     letter = 1;
//     i_string = 0;
//     string = ft_calloc(len, 1);
//     while (letter) // letter != 0b00000000
//     {
//         count = 0;
//         while (count < 8)
//         {
//             signal(SIGUSR1, handler);
//             signal(SIGUSR2, handler);
//             count = ft_strlen(str);
//         }
//         letter = binary_to_int(str, 8);
//         string[i_string] = letter;
//         printf("position str: %i\n", i_string);
//         printf("STR: %s\n", string);
//         i_string++;
//         ft_putchar_fd(letter, 1);
//         ft_bzero(str, 8);
//     }
//     return (string);
// }

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