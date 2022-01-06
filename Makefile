# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/19 16:05:34 by rsanchez          #+#    #+#              #
#    Updated: 2021/12/13 18:53:36 by romain           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = clang

CFLAGS = -Wall -Wextra -Werror #--analyze

FLAGSHARD = -Weverything

HEADER = includes

DIR_S = sources

DIR_O = temporary

SOURCES = main.c parse_args.c threads.c philo.c status.c buffer.c sleep.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $(NAME) $(OBJS) $(LIBFT)

$(NAMEB): $(OBJSB)
	$(CC) $(CFLAGS) -o $(NAMEB) $(OBJSB) $(LIBFT)

$(DIR_O)/%.o: $(DIR_S)/%.c
	@mkdir -p $(DIR_O)
	$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

norme:
	@echo
	norminette $(HEADER)/
	@echo
	norminette $(DIR_S)/

clean:
	rm -rf $(DIR_O)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:		all clean fclean re bonus norme
