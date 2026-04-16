NAME        = vulkan_engine

CXX         = c++
CXXFLAGS    = -std=c++20 -I include
LDFLAGS     = -lvulkan -lglfw

SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include

SRCS        = $(wildcard $(SRC_DIR)/*.cpp)
OBJS        = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
