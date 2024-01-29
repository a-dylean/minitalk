CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft
PRINTF = libft/ft_printf
LIBFT_LIB = $(LIBFT)/libft.a
INCLUDES = -I$(LIBFT)

SRCS_SERVER = src/server.c
SRCS_CLIENT = src/client.c
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
TARGET_SERVER = server
TARGET_CLIENT = client

all: $(TARGET_SERVER) $(TARGET_CLIENT)

$(TARGET_SERVER): $(OBJS_SERVER)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(PRINTF)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_LIB)

$(TARGET_CLIENT): $(OBJS_CLIENT)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(PRINTF)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_LIB)

clean:
	$(MAKE) -C $(LIBFT) clean
	$(MAKE) -C $(PRINTF) clean
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	$(MAKE) -C $(PRINTF) fclean
	rm -f $(TARGET_SERVER) $(TARGET_CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

re: fclean all

.PHONY: all clean fclean re