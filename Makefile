compile-conversion:
	g++ convert.cpp -lm -o conversion.out

compile-ordering:
	g++ order.cpp -lm -o order.out

run-conversion:
	./conversion.out

run-ordering:
	./order.out subnational.dat subnationalOrder.dat 100000


