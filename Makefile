NAME = chess

SRCS = $(wildcard ./SRCS/*.cpp)

FLAGS = -Wall -Werror -Wextra -Wno-unused
LDFLAGS = -lSDL2

OBJS = $(SRCS:./SRCS/%.cpp=./obj/%.o)

CC = c++

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	$(MAKE) clean

./obj/%.o: ./SRCS/%.cpp
	mkdir -p ./obj 
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf ./obj

fclean: clean
	rm -f $(NAME)

re: fclean all
