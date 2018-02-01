# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddosso-d <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 16:54:55 by ddosso-d          #+#    #+#              #
#    Updated: 2018/01/08 16:54:56 by ddosso-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft_malloc_$HOSTTYPE.so
FLAGS	=	-Wall -Wextra -Werror
FILES	=	malloc free realloc show_alloc_mem
SRCS	=	$(addsuffix .c, $(FILES))
OBJS	=	$(addsuffix .o, $(FILES))
INCS	=	malloc.h

all: $(NAME)

$(NAME): $(OBJS) $(INCS)
	@gcc $(FLAGS) -c $(SRCS) 
	@ar rc $@ $^
	@ranlib $@

%.o: %.c
	gcc $(FLAGS) -c $<

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
