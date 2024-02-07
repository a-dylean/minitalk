CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
PRINTF = libft/ft_printf/ft_printf.a
INCLUDES = -I includes -I libft -I libft/ft_printf

SRCS_SERVER = src/server.c
SRCS_CLIENT = src/client.c
SRCS_SERVER_BONUS = src/server_bonus.c
SRCS_CLIENT_BONUS = src/client_bonus.c
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)
TARGET_SERVER = server
TARGET_CLIENT = client
TARGET_SERVER_BONUS = server_bonus
TARGET_CLIENT_BONUS = client_bonus

all: $(TARGET_SERVER) $(TARGET_CLIENT)

$(TARGET_SERVER): $(LIBFT) $(PRINTF) $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET_SERVER) $(OBJS_SERVER) -L libft -lft -L libft/ft_printf -lftprintf

$(TARGET_CLIENT): $(LIBFT) $(PRINTF) $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET_CLIENT) $(OBJS_CLIENT) -L libft -lft -L libft/ft_printf -lftprintf

bonus: $(TARGET_SERVER_BONUS) $(TARGET_CLIENT_BONUS)

$(TARGET_SERVER_BONUS): $(LIBFT) $(PRINTF) $(OBJS_SERVER_BONUS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET_SERVER_BONUS) $(OBJS_SERVER_BONUS) -L libft -lft -L libft/ft_printf -lftprintf

$(TARGET_CLIENT_BONUS): $(LIBFT) $(PRINTF) $(OBJS_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET_CLIENT_BONUS) $(OBJS_CLIENT_BONUS) -L libft -lft -L libft/ft_printf -lftprintf

$(LIBFT):
	make -C libft

$(PRINTF):
	make -C libft/ft_printf

clean:
	make clean -C libft
	make clean -C libft/ft_printf
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)

fclean: clean
	make fclean -C libft
	make fclean -C libft/ft_printf
	rm -f $(TARGET_SERVER) $(TARGET_CLIENT) $(TARGET_SERVER_BONUS) $(TARGET_CLIENT_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus