// char	*ft_strjoin(char const *s1, char const *s2);
// size_t	ft_strlen(const char *c);
// int		ft_atoi(const char *nptr);
// void	ft_putchar_fd(char c, int fd);
// void	ft_putstr_fd(char *s, int fd);
// void	ft_bzero(void *s, size_t n);
// void	*ft_calloc(size_t nmemb, size_t size);
int	    read_len();
int		read_pid_client();
char	*read_msg(int len);
char	read_char(void);
void    handler(int sig);
void	read_signal(int bits_number);
void	send_signal(int pid, int *package, int bits_number);
void	msg_seen(int pid_client);
// char	*read_message(int len);
