# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfearow <sfearow@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 18:33:06 by sfearow           #+#    #+#              #
#    Updated: 2021/11/08 18:33:07 by sfearow          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS	=	philo.c time.c checker_life.c\
			utils.c utils2.c exit.c init.c\

OBJS	=	$(SRCS:.c=.o)

%.o:		%.c philo.h
			$(CC) $(CFLAGS) -c -o $@ $< 

NAME	=	philo

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -pthread

RM		=	rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
			$(RM) $(OBJS) $(B_OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus