NAME        = vulkan_engine

CXX         = c++

SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include
SHADERS_DIR = shaders
SPV_DIR     = spv

SRCS        = $(wildcard $(SRC_DIR)/*.cpp)
OBJS        = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

SHADERS_SRC = $(wildcard $(SHADERS_DIR)/*)
SPVS        = $(patsubst $(SHADERS_DIR)/%, $(SPV_DIR)/%.spv, $(SHADERS_SRC))

LDFLAGS     = -lvulkan -lglfw

DEBUG_FLAGS   = -std=c++20 -I include
RELEASE_FLAGS = -std=c++20 -I include -DNDEBUG

all: debug

debug: CXXFLAGS = $(DEBUG_FLAGS)
debug: shaders $(NAME)

release: CXXFLAGS = $(RELEASE_FLAGS)
release: shaders $(NAME)

shaders: $(SPVS)

$(SPV_DIR)/%.spv: $(SHADERS_DIR)/%
	@mkdir -p $(SPV_DIR)
	glslc $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(SPV_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all debug release shaders clean fclean re
