# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/19 16:05:34 by rsanchez          #+#    #+#              #
#    Updated: 2022/01/28 12:44:31 by rsanchez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

NAMEB = philo_bonus

CC = clang

CFLAGS = -Wall -Wextra -Werror #--analyze

FLAGSHARD = -Weverything

HEADER = includes

HEADERB = includes_bonus

DIR_S = sources

DIR_O = temporary

DIR_SB = sources_bonus

DIR_OB = temporary_bonus

SOURCES = main.c parse_args.c threads.c philo.c status.c buffer.c sleep.c \
	  $(TOOL)/meals.c $(TOOL)/death.c

TOOL = utils

SOURCESB = main.c parse_args.c proc_main.c proc_children.c \
	   philo_routine.c status_display.c \
	   $(TOOL)/buffer.c $(TOOL)/sleep.c $(TOOL)/thread.c \
	   $(TOOL)/semaphore.c $(TOOL)/utoa.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

SRCSB = $(addprefix $(DIR_SB)/,$(SOURCESB))

OBJSB = $(addprefix $(DIR_OB)/,$(SOURCESB:.c=.o))

all: $(NAME)

bonus: $(NAMEB)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $(NAME) $(OBJS)

$(NAMEB): $(OBJSB)
	$(CC) $(CFLAGS) -pthread -o $(NAMEB) $(OBJSB)

$(DIR_O)/%.o: $(DIR_S)/%.c
	@mkdir -p $(DIR_O)
	@mkdir -p $(DIR_O)/$(TOOL)
	$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

$(DIR_OB)/%.o: $(DIR_SB)/%.c
	@mkdir -p $(DIR_OB)
	@mkdir -p $(DIR_OB)/$(TOOL)
	$(CC) $(CFLAGS) -I $(HEADERB) -o $@ -c $<

norme:
	@echo
	norminette $(HEADER)/
	@echo
	norminette $(DIR_S)/
	@echo
	norminette $(HEADERB)/
	@echo
	norminette $(DIR_SB)/

clean:
	rm -rf $(DIR_O)
	rm -rf $(DIR_OB)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAMEB)

re: fclean all

.PHONY:		all clean fclean re bonus norme
