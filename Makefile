memtest: memtest.o ackerman.o my_allocator.o
	g++ -std=c++11 -o memtest memtest.c ackerman.c ackerman.h my_allocator.c my_allocator.h
clean:
	rm *.o
