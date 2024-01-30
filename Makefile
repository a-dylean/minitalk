CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = 	libft/libft.a
PRINTF = 	libft/ft_printf/ft_printf.a
INCLUDES = 	-I includes -I libft -I libft/ft_printf

SRCS_SERVER = src/server.c
SRCS_CLIENT = src/client.c
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
TARGET_SERVER = server
TARGET_CLIENT = client

all: $(TARGET_SERVER) $(TARGET_CLIENT)

$(TARGET_SERVER): $(LIBFT) $(PRINTF) $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET_SERVER) $(OBJS_SERVER) -L libft -lft -L libft/ft_printf -lftprintf

$(TARGET_CLIENT): $(LIBFT) $(PRINTF) $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET_CLIENT) $(OBJS_CLIENT) -L libft -lft -L libft/ft_printf -lftprintf

$(LIBFT):
	make -C libft

$(PRINTF):
	make -C libft/ft_printf

clean:
	make clean -C libft
	make clean -C libft/ft_printf
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	make fclean -C libft
	make fclean -C libft/ft_printf
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re



