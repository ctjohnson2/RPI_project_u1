########### Z2GaugeLattice #######################

u1.h : u1.cpp u1.hpp
	g++ -c -O u1.hpp

run_u1.o : run_u1.cpp u1.hpp
	g++ -c -g -O run_u1.cpp

run_u1 : u1.o run_u1.o
	g++ -O -o run_u1 u1.o run_u1.o

# Book2.h : Book2.cpp Book2.hpp
# 	g++ -c -O Book2.cpp

# UseBookClass2.o : UseBookClass2.cpp Book2.hpp
# 	g++ -c -O UseBookClass2.cpp

# UseBookClass2 : Book2.o UseBookClass2.o
# 	g++ -O -o UseBookClass2 Book2.o UseBookClass2.o
