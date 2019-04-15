objects=cmpnt1.o client1.o create.o

all : libcmpnt1 client1

libcmpnt1 : cmpnt1.o
		g++ -shared  -o libcmpnt1.so cmpnt1.o

cmpnt1.o : guids.cpp iface.h  IUnknown.h  type.h
		g++ -g -c -fPIC cmpnt1.cpp -o cmpnt1.o

client1 : client1.o create.o
		g++ -g -rdynamic -o client1 client1.o create.o -ldl

client1.o :
		g++ -g -c client1.cpp

create.o : 
		g++ -g -c create.cpp

.PYTHON : clean
clean :
		rm -f ${objects}
