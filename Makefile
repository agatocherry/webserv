# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 18:32:32 by shdorlin          #+#    #+#              #
#    Updated: 2022/12/05 14:53:15 by kejebane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv 
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
INCLUDES = -I ./includes/
SRCS = srcs/Server.cpp \
       srcs/ServerInfo.cpp \
       srcs/File.cpp 
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

pouette: $(OBJS)
	@ $(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

.PHONY: all clean fclean re bonus
