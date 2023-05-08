# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itchinda <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 12:41:26 by itchinda          #+#    #+#              #
#    Updated: 2023/05/08 12:41:28 by itchinda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

SRC=	  main.c\
			utils.c\
			utils2.c\
			routine.c\
			init.c\
			actions.c\
			destroy_free.c\
			

CC= cc -g3

OBJ_DIR= obj

CFLAGS= -Wall -Werror -Wextra

OBJ=	$(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

RM=	rm -rf

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

clean:		
		$(RM) $(OBJ)
		$(RM) $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:	all clean fclean re
