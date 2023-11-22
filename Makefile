TARGET		= libmatrix.a

BUILD_DIR	= ./build
SRC_DIR		= ./src
TEST_DIR	= ./tests

SRC_FILES	= common.hpp Vector.hpp Matrix.hpp functions.hpp
TEST_FILES	= test_VectorView.cpp test_Vector.cpp test_Matrix.cpp test_functions.cpp

SRCS		= $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJS		= $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS		= $(OBJS:.o=.d)

TESTS		= $(addprefix $(TEST_DIR)/,$(TEST_FILES))

CPPFLAGS	= -I$(SRC_DIR) -std=c++20 -Wall -Wextra -Werror

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	ar rc $(BUILD_DIR)/$(TARGET) $(OBJS)

$(BUILD_DIR)/%.hpp.o: %.hpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

.PHONY: test clean re

test:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lCatch2Main -lCatch2 ${TEST_DIR}/main.cpp $(TESTS) -o ./tests/tester
	./tests/tester
	rm ./tests/tester

clean:
	rm -r $(BUILD_DIR)

re: clean all

-include $(DEPS)
