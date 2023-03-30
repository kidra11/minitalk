# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsion <nsion@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 15:48:31 by nsion             #+#    #+#              #
#    Updated: 2023/03/30 18:11:21 by nsion            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_C = ft_printf/ft_printf.c  ft_printf/ft_find.c client.c

SRCS_S = ft_printf/ft_printf.c  ft_printf/ft_find.c server.c

INCLUDES = ft_printf/

NAME_S = server

NAME_C = client

GCC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

OBJS_C = $(SRCS_C:.c=.o)

OBJS_S = $(SRCS_S:.c=.o)

all	: $(NAME_S) $(NAME_C)

.c.o	:
	$(GCC) -I. -I $(INCLUDES) -o $@ -c $? $(CFLAGS)

$(NAME_S)	: $(OBJS_S)
	$(GCC) $(OBJS_S) -o $(NAME_S)

$(NAME_C)	: $(OBJS_C)
	$(GCC) $(OBJS_C) -o $(NAME_C)

clean	:
	$(RM) $(OBJS_C) $(OBJS_S)

fclean	:	clean
	$(RM) $(NAME_S) $(NAME_C)

re	: fclean all

.PHONY	: all clean fclean re