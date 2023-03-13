OUTPUT_ROOT := output
OUT_DIR   := $(OUTPUT_ROOT)/objs
BUILD     := $(OUTPUT_ROOT)/build

SRC       := source

SOURCES   := $(shell find $(SRC) -name '*.cpp')
OBJS      := $(SOURCES:$(SRC)%.cpp=$(OUT_DIR)%.o)

CXX_VER   := c++17
CXX_FLAGS := -std=$(CXX_VER) -Wall

.PHONY: all

$(OUT_DIR)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) -c $(CXX_FLAGS) $< -o $@

$(BUILD)/calc.out: $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $^ -o $@

all: $(BUILD)/calc.out

clean:
	rm -f $(BUILD)/*
	rm -f $(OUT_DIR)/*
	rmdir $(BUILD) $(OUT_DIR) $(OUTPUT_ROOT)
