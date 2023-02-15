compile-conversion:
	g++ transforma_binario.cpp -lm -o conversion.out

compile-treatment:
	g++ manipulacao_dados.cpp -lm -o treatment.out

compile-ordering:
	g++ order.cpp -lm -o order.out

run-conversion:
	./conversion.out

run-treatment:
	./treatment.out

run-ordering:
	./order.out subnational.dat subnationalOrder.dat 1000000



