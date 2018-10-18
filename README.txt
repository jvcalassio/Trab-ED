Instruções de compilação:
	Compilar com o compilador gcc os arquivos expr_calc.c e main.c, na seguinte ordem e com os seguintes comandos:

	expr_calc.c
		gcc -c expr_calc.c
	main.c
		gcc -o main main.c expr_calc.o -lm

	Versão do compilador utilizada:
	gcc (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609

	Bibliotecas utilizadas:
		stdio.h
		stdlib.h
		string.h
		math.h
		expr_calc.h

	Produzido e testado no Linux Mint 18.3 Cinnamon 64-bit