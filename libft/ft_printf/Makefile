CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror
NAME	=	libftprintf.a
INCLUDE	=	ft_printf.h
SOURCES	=	ft_handle_conversion.c ft_printf.c ft_putchar_value.c \
			ft_puthex_value.c ft_putnbr_value.c ft_putptr_value.c \
			ft_putstr_value.c ft_putunsigned_value.c 
OBJECTS	=	$(SOURCES:.c=.o)
RM	=	rm -f
AR	=	ar -rcs
all:	$(NAME)

$(NAME):	$(OBJECTS)
			$(AR) $(NAME) $(OBJECTS)

.o:.c	$(CC) $(CFLAGS) $(INCLUDE) -c $<

clean:
		$(RM) $(OBJECTS)

fclean:	clean
		$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re