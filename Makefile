# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 18:32:32 by shdorlin          #+#    #+#              #
#    Updated: 2022/12/12 19:09:21 by kejebane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv 
CC = c++
CFLAGS = -std=c++98 #-Wall -Wextra -Werror -std=c++98
INCLUDES = -I ./includes/

SRCS = srcs/Server.cpp \
       srcs/ServerInfo.cpp \
       srcs/File.cpp \
       srcs/ConfigInfo.cpp \
       srcs/main.cpp

CLIE = client.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ $(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

client:
	@ $(CC) $(CFLAGS) $(INCLUDES) $(CLIE) -o client

%.o: %.cpp
	@ $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@ rm -f $(OBJS)

fclean: clean
	@ rm -f $(NAME)

re: fclean all

pouette: $(OBJS)
	@ $(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)


test: all
	@ valgrind ./webserv config/default.conf

.PHONY: all clean fclean re bonus
