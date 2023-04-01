/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrobert <alrobert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:29:54 by alrobert          #+#    #+#             */
/*   Updated: 2023/03/31 16:40:31 by alrobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include <signal.h>
# include <stdlib.h>
# include "../libft/libft.h"

void	start(char *argv[]);
void	send_len(int pid, char *msg);
void	send_pid(int pid_serv, int pid_client);
void	send_msg(int pid, char *msg);
void	read_seen_server(int bit_number);
void	send_to_server(int pid, int *package, int bit_number);
void	handler(int sig);
void	send_char(int pid, char c);
int		check_pid(char *pid);

#endif
