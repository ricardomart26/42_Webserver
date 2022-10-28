NAME = server

CC = c++ -Wall -Wextra -Werror -std=c++98 -pedantic -fsanitize=address -g

SRCDIR = src/
INCDIR = inc


SRCS =	main.cpp $(shell find $(SRCDIR) -name '*.cpp')
INC =	$(shell find $(INCDIR) -name '*.hpp')

# SRCS := $(addprefix $(SRCDIR), $(SRCS))
# INC := $(addprefix $(SRCDIR), $(INC))

# db:
# 	echo $(SRCS)
# 	echo $(INC)

all: $(NAME)

$(NAME): $(SRCS) $(INC)
	$(CC) $(SRCS) -I$(INCDIR)/configuration -I$(INCDIR)/utils -o $(NAME)

exec:
	$(NAME)

debug: $(SRCS) $(INC)
	$(CC) -I$(INCDIR) -DDEBUG=1 $(SRCS) -o log_$(NAME)

clean:
	rm -rf $(NAME)

re: clean all

.PHONY: all clean re
