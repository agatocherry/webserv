# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 18:32:32 by shdorlin          #+#    #+#              #
#    Updated: 2022/11/25 11:21:02 by agcolas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv 
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
INCLUDES = -I ./includes/
SRCS = srcs/ServerInfo.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ $(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

%.o: %.cpp
	@ $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@ rm -f $(OBJS)

fclean: clean
	@ rm -f $(NAME)

re: fclean all

test: all
	@ valgrind ./webserv config/default.conf

.PHONY: all clean fclean re test
