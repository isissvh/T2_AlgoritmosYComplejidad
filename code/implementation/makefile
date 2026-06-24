CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -Ofast -march=native -std=c++17

ALGO_DIR = algorithms
SRC = general.cpp \
	$(ALGO_DIR)/brute-force.cpp \
	$(ALGO_DIR)/dynamic-programming.cpp \
	$(ALGO_DIR)/greedy1.cpp \
	$(ALGO_DIR)/greedy2.cpp

OBJ = $(SRC:.cpp=.o)
TARGET = animaraton

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp common.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run_all: $(TARGET)
	@find data/inputs -type f -name "*.txt" | sort -V | while read file; do \
		echo "Corriendo $$file..."; \
		./$(TARGET) "$$file"; \
	done

generate:
	@echo "Generando casos de prueba..."
	python3 scripts/testcases_generator.py

plot:
	@echo "Generando gráficos..."
	python3 scripts/plot_generator.py

pipeline: generate run_all plot
	@echo "Pipeline completo finalizado exitosamente."
