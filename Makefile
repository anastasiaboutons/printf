NAME	= libftprintf.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f

SRCS	= ft_printf.c conversion.c ft_putnbr_16.c ft_putnbr_unsignedint.c ft_putnbr_unsignedlong_16.c count_l.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

LIBFT = libft/libft.a

$(LIBFT):
	make -C libft

$(NAME): $(OBJS) $(LIBFT)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
