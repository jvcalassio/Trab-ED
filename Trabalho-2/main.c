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
		printf("Exame Chunin\n");
		printf("1) Iniciar Exame\n");
		printf("2) Sair\n");
		scanf("%d",&n);
		if(n==1){
			start();
		} else if(n==2){
			x = 0;
		}
	}
	return 0;
}