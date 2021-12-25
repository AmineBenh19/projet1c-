CC = g++
CFLAGS = -Wall
LDFLAGS = 
SRC = main.cpp 


PROG = main
OBJS = $(SRC:.cpp=.o)
.SUFFIXES: .cpp .o 
all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: matrice.hpp matriceDouble.hpp IndexInvalide.hpp MatriceCreuse.hpp
matrice.o: matrice.hpp
matriceDouble.o: matriceDouble.hpp IndexInvalide.hpp
IndexInvalide.o: IndexInvalide.hpp
MatriceCreuse.o: MatriceCreuse.hpp IndexInvalide.hpp


%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o $(PROG)
