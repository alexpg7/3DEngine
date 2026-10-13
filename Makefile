NAME = 3DEngine

CC = c++
CFLAGS = -Wall -Wextra -Werror -O3
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
CPPFLAGS = -MMD -MP -I. -Iinc/

SRC_DIR = src/
OBJ_DIR = obj/

RM = rm -f

SRC = main.cpp \
	3DEngine.cpp \
	ObjectsList.cpp \
	Vector3.cpp

OBJ = $(patsubst %.cpp, $(OBJ_DIR)%.o, $(SRC))
DEP = $(OBJ:.o=.d)

# Colors
BRED = \033[1;31m
BYEL = \033[1;33m
BGREEN = \033[1;32m
RED = \033[0;31m
YEL = \033[0;33m
GREEN = \033[0;32m
NC = \033[0m

all: $(NAME)

# Compile .cpp -> .o inside obj/
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Special case for files in root (like main.cpp)
$(OBJ_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Link object files into an executable
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)
	@echo "😃 ${BGREEN}Compiled executable ${BYEL}$(NAME)${NC}"

-include $(DEP)

clean:
	@$(RM) $(OBJ) $(DEP)
	@rm -rf $(OBJ_DIR)
	@echo "🗑️  ${BRED}Removed objects${NC}"

fclean: clean
	@$(RM) $(NAME) test.out
	@echo "🗑️  ${BRED}Removed binaries${NC}"

test: $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) -o test.out
	@echo "🧪 ${BGREEN}Compiled executable ${BYEL}test.out${NC}"

re: fclean all

.PHONY: all clean fclean re test