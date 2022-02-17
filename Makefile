NAME_M_STD	= map_std
NAME_M_FT	= map_ft
NAME_V_STD	= vector_std
NAME_V_FT	= vector_ft
NAME_S_STD	= stack_std
NAME_S_FT	= stack_ft
NAME = ${NAME_M_STD} ${NAME_M_FT} ${NAME_V_STD} ${NAME_V_FT} ${NAME_S_STD} ${NAME_S_FT}

SRCS	= main_map.cpp \
	  main_vector.cpp \
	  main_stack.cpp

OBJS_M	= main_map.o
OBJS_V	= main_vector.o
OBJS_S	= main_stack.o
OBJS	= ${OBJS_M} ${OBJS_V} ${OBJS_S}

DEPS	= map.hpp \
	  map_iterator.hpp \
	  vector.hpp \
	  vector_iterator.hpp \
	  stack.hpp \
	  common_utils.hpp \
	  iterator_utils.hpp

CPPFLAGS = -Wall -Werror -Wextra -std=c++98

STD = -D STD

all: map vector stack

%.o: %.cpp ${DEPS}
	clang++ -c -o $@ $< ${CPPFLAGS} 

map: ${OBJS_M}
	clang++ ${CPPFLAGS} ${OBJS_M} -o ${NAME_M_FT}

vector: ${OBJS_V}
	clang++ ${CPPFLAGS} ${OBJS_V} -o ${NAME_V_FT}

stack: ${OBJS_S}
	clang++ ${CPPFLAGS} ${OBJS_S} -o ${NAME_S_FT}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

std: ${SRCS}
	clang++ ${CPPFLAGS} main_map.cpp -o ${NAME_M_STD} ${STD}
	clang++ ${CPPFLAGS} main_vector.cpp -o ${NAME_V_STD} ${STD}
	clang++ ${CPPFLAGS} main_stack.cpp -o ${NAME_S_STD} ${STD}
