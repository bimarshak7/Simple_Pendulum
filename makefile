# Compiler
CC = g++
# Compiler flags
CFLAGS =  -g -I $(INC)

# Final executable 
TARGET = pendu

# Source files dir
SRC = src
# Header files dir
INC = inc
# Generated binary files dir
BIN = bin
# List of source files
SOURCE = $(wildcard $(SRC)/*.cc)
# List of binary files generated
OBJECT = $(patsubst %,$(BIN)/%,$(notdir $(SOURCE:.cc=.o)))
# List of header files
# List of linked library
DEPS = $(wildcard $(INC)/*.h)
lflags = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

#Build Instructions
$(TARGET): $(OBJECT)
	@echo "Linking Objects"
	$(CC) -o $@ $^ $(lflags)

$(BIN)/%.o : $(SRC)/%.cc $(DEPS)
	[ -d "$(BIN)" ] && echo "" || mkdir $(BIN)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : help run clean

run: $(TARGET)
	./$(TARGET)

clean: 
	@echo "Cleaning files"
	rm -rf $(BIN) $(TARGET) 


help:
	@echo "src: $(SOURCE)"
	@echo "obj: $(OBJECT)"
	@echo "obj: $(INC_F)" 

