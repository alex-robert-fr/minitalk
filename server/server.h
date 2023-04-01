/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrobert <alrobert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:33:05 by alrobert          #+#    #+#             */
/*   Updated: 2023/03/31 16:39:35 by alrobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# define T1 "███╗   ███╗██╗███╗   ██╗██╗████████╗ █████╗ ██╗     ██╗  ██╗\n"
# define T2	"████╗ ████║██║████╗  ██║██║╚══██╔══╝██╔══██╗██║     ██║ ██╔╝\n"
# define T3	"██╔████╔██║██║██╔██╗ ██║██║   ██║   ███████║██║     █████╔╝ \n"
# define T4	"██║╚██╔╝██║██║██║╚██╗██║██║   ██║   ██╔══██║██║     ██╔═██╗ \n"
# define T5	"██║ ╚═╝ ██║██║██║ ╚████║██║   ██║   ██║  ██║███████╗██║  ██╗\n"
# define T6	"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝\n"
# define T7	"------------------------------------------------------------\n"
# include <signal.h>
# include <stdlib.h>
# include "../libft/libft.h"

int		read_len(void);
int		read_pid_client(void);
char	*read_msg(int len);
char	read_char(void);
void	handler(int sig);
void	read_signal(int bits_number);
void	send_signal(int pid, int *package, int bits_number);
void	msg_seen(int pid_client);

#endif
