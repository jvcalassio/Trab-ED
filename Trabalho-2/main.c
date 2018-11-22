/** 
 * \mainpage Exame Chunin
 * Jogo Exame Chunin
 */
/**
 * @file main.c
 * @brief Arquivo principal
 * Arquivo principal para a execucao do programa\n
 * Contem o menu principal e a chamada de inicio de jogo
 * @author Joao Victor
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "data_structures.h"
#include "functions.h"

int main() {
	srand(time(0));
	int x = 1;
	while(x){
		int n;
		system("clear");
		printf(C_YELLOW "   EXAME CHUNIN \n\n" C_DEFAULT);
		printf(C_BLUE "1)" C_DEFAULT " Iniciar Exame\n");
		printf(C_BLUE "2)" C_DEFAULT " Sair\n");
		setbuf(stdin, NULL);
		scanf("%d",&n);
		if(n==1){
			int c = start();
			if(c == 2)
				x = 0;
		} else if(n==2){
			x = 0;
		}
	}
	return 0;
}