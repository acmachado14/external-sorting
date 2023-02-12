compile-conversion:
	g++ transforma_binario.cpp -lm -o conversion.out

compile-treatment:
	g++ manipulacao_dados.cpp -lm -o treatment.out

run-conversion:
	./conversion.out

run-treatment:
	./treatment.out




