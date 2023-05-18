# ---------------------------------- PROGRAM --------------------------------- #
NAME		=	minitalk
SERVER_NAME	=	server
CLIENT_NAME	=	client
# -------------------------------- COMPILATION ------------------------------- #
CC			=	clang
CFLAGS		=	-Werror -Wextra -Wall -Ilibft -Ilibft/ft_printf
# ---------------------------------- LIBRARY --------------------------------- #
LIBFT_PATH	=	./libft
LIBFT_NAME	=	libft.a
# ----------------------------------- FILES ---------------------------------- #
SRC_SERVER	=	./src_server/server.c	\
				./src_server/read_functions.c
SRC_CLIENT	=	./src_client/client.c	\
				./src_client/send_functions.c
OBJ_SERVER	=	$(SRC_SERVER:.c=.o)
OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

all: $(LIBFT_NAME) $(NAME)

$(NAME): $(SERVER_NAME) $(CLIENT_NAME)

$(LIBFT_NAME):
	make -C $(LIBFT_PATH)

$(SERVER_NAME): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT_PATH)/$(LIBFT_NAME) -o $@

$(CLIENT_NAME): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT_PATH)/$(LIBFT_NAME) -o $@

clean:
	make clean -C $(LIBFT_PATH)
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all
