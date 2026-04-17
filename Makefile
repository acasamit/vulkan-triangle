NAME        = vulkan_engine

CXX         = c++

SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include

SRCS        = $(wildcard $(SRC_DIR)/*.cpp)
OBJS        = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

LDFLAGS     = -lvulkan -lglfw

DEBUG_FLAGS   = -std=c++20 -I include
RELEASE_FLAGS = -std=c++20 -I include -DNDEBUG

all: debug

debug: CXXFLAGS = $(DEBUG_FLAGS)
debug: $(NAME)

release: CXXFLAGS = $(RELEASE_FLAGS)
release: $(NAME)

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

.PHONY: all debug release clean fclean re
