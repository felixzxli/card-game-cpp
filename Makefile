CXX=g++
CXXFLAGS=-std=c++14 -MMD -Werror=vla
OBJECTS=main.o pile.o card.o joker.o hydra.o tableModel.o tableView.o subject.o player.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=hydra

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
	