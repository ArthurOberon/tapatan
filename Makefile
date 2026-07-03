NAME 				=	tapatan # 3 Men's Morris

CXX 				=	c++
CXXFLAGS			=	-Wall -Wextra -Werror -g3
SRC_DIR 			=	./srcs/
INCLUDES_DIR 		=	./includes/
OBJ_DIR 			=	.obj/
INCLUDES_H			=	-I./$(INCLUDES_DIR)

DEPS 				=	Makefile $(INCLUDES_DIR)Game.hpp $(INCLUDES_DIR)Piece_Mov.hpp $(INCLUDES_DIR)ShellRenderer.hpp $(INCLUDES_DIR)ShellInput.hpp  $(INCLUDES_DIR)SFMLRenderer.hpp $(INCLUDES_DIR)SFMLInput.hpp
SRCS	=  $(addprefix $(SRC_DIR), \
						main.cpp \
						Game.cpp \
						Piece_Mov.cpp \
						ShellRenderer.cpp \
						ShellInput.cpp \
						SFMLRenderer.cpp \
						SFMLInput.cpp \
						)

OBJS 			=	$(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o, $(SRCS))

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(DEPS)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(INCLUDES_H) -c -o $@ $<

$(NAME): $(OBJS) $(DEPS)
	@echo "\e[36;1mMaking $(NAME)...\e[0m"
	@$(CXX) $(CXXFLAGS) $(INCLUDES_H) $(OBJS) -o $(NAME) -lncurses -lsfml-graphics -lsfml-window -lsfml-system
	@echo "\e[32;1mDone !\e[0m"

bonus: all

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\e[31;1mObject files removed.\e[0m"

fclean:	clean
	@rm -f $(NAME)
	@echo "\e[31;1m$(NAME) removed.\e[0m"

re:		fclean all

clear:
	clear

.PHONY = all bonus clean fclean re
