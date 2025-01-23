CFLAGS = g++ -std=c++98 -Wall -Wextra -Werror
SRCS = ConfigReader.cpp ConfigParser.cpp main.cpp ConfigData.cpp IConfigContext.cpp IConfigDirective.cpp
OBJS = $(SRCS:.cpp=.o)
NAME = webserv

all : $(NAME)

$(OBJS) : %.o: %.cpp
	$(CFLAGS) -c $< -o $@ -I.

$(NAME) : $(OBJS)
	$(CFLAGS) $(OBJS) -o $(NAME) -I.

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all