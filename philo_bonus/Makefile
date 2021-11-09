# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfearow <sfearow@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 18:33:06 by sfearow           #+#    #+#              #
#    Updated: 2021/11/09 19:12:48 by sfearow          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS	=	philo_bonus.c time.c\
			utils.c utils2.c init.c

OBJS	=	$(SRCS:.c=.o)

%.o:		%.c philo_bonus.h
			$(CC) $(CFLAGS) -c -o $@ $< 

NAME	=	philo_bonus

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