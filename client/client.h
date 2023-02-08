void	start(char *argv[]);
void	send_len(int pid, char *msg);
void	send_pid(int pid_serv, int pid_client);
void	send_msg(int pid, char *msg);
void	read_seen_server(void);
void	send_to_server(int pid, int *package, int bit_number);
void    handler(int sig);
void	send_char(int pid, char c);