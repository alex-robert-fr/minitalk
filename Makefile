NAME=minitalk
CC=clang
SRC_SERVER=	./server/server.c
SRC_CLIENT= ./client/client.c
LIBFT_PATH=./libft
LIBFT_NAME=libft.a
OBJ_SERVER=$(SRC_SERVER:.c=.o)
OBJ_CLIENT=$(SRC_CLIENT:.c=.o)

all: $(LIBFT_NAME) $(NAME)

$(NAME): server.out client.out

$(LIBFT_NAME):
	make -C $(LIBFT_PATH)

server.out: $(LIBFT_NAME) $(OBJ_SERVER)
	$(CC) $(OBJ_SERVER) $(LIBFT_PATH)/$(LIBFT_NAME) -o $@

client.out: $(LIBFT_NAME) $(OBJ_CLIENT)
	$(CC) $(OBJ_CLIENT) $(LIBFT_PATH)/$(LIBFT_NAME) -o $@

clean:
	make clean -C $(LIBFT_PATH)
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
	rm server.out client.out
	make fclean -C $(LIBFT_PATH)

re: fclean all

#!   TEMPORAIRE DEBUG   !#
debug:	dbg_server dbg_client

dbg_server: $(LIBFT_NAME)
	$(CC) $(SRC_SERVER) $(LIBFT_PATH)/$(LIBFT_NAME) -g -o $@

dbg_client: $(LIBFT_NAME)
	$(CC) $(SRC_CLIENT) $(LIBFT_PATH)/$(LIBFT_NAME) -g -o $@

dclean:
	rm dbg_server dbg_client
	make fclean -C $(LIBFT_PATH)