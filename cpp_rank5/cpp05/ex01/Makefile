NAME			=	bureaucrat01

############## Compilation & Flags ###########
CXX				=	c++
FLAGS			=	-Wall -Wextra -Werror
STD_FLAG		=	-std=c++98

############## Include Dir ###########
INC_DIR			=	inc/
INC_FD			=	Bureaucrat.hpp \
					Form.hpp
INC				=	$(addprefix $(INC_DIR), $(INC_FD))

############## SRC Dirs & Files ##############
SRCS_DIR		=	src/
SRCS_FD			=	Bureaucrat.cpp \
					Form.cpp \
					main.cpp

SRCS			=	$(addprefix $(SRCS_DIR), $(SRCS_FD))


############## OBJS Dirs & Files #############
OBJ_DIR			=	.obj
OBJS			=	$(SRCS:$(SRCS_DIR)%.cpp=$(OBJ_DIR)/%.o)


############## Recipes #######################
all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[33m Compiling $(NAME)...\033[0m"
	$(CXX) $(OBJS) -o $(NAME)
	@echo "\033[32m$(NAME) is ready to use\033[0m"

$(OBJ_DIR)/%.o:$(SRCS_DIR)%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS) $(STD_FLAG) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)
	@echo "\033[34m $(OBJ_DIR) deleted\033[0m"

fclean:	clean
	rm -f $(NAME)
	@echo "\033[34m$(NAME) deleted\033[0m"
	
re: fclean all

############## .PHONY ########################
.PHONY: clean fclean re