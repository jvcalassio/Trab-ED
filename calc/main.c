#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expr_calc.h"

void modo_expressao(){
	system("clear");
	printf("Modo Expressao\n");
	printf("Insira a expressao:\n");
	char expres[200];
	scanf(" %[^\n]",expres);
	if(valid_expr(expres)){ // avalia a expressao
		system("clear");
		printf("Expressao valida!\n\n");
		/* transforma para posfixa */
		char answ[200];
		in_to_pos(expres,answ);
		printf("Forma posfixa: %s\n",answ);

		/* realiza o calculo da expressao */
		float final_res = calc_expr(answ);
		printf("Resultado: ");
		print_float(final_res);
		printf("\n");

		printf("----------------------------------------\n");
	} else {
		system("clear");
		printf("Expressao invalida!\n\n");
		printf("----------------------------------------\n");
	}
}

void modo_calc(){
	system("clear");
	printf("Modo Calculadora\n");
	printf("Digite um numero ou operacao. Digite S para sair:\n\n");
	float_stack* nums = new_float_stack();
	char in[200];
	int error = 0;
	while(in[0]!='s' && in[0]!='S'){
		system("clear");
		printf("Modo Calculadora\n");
		printf("Digite um numero ou operacao. Digite S para sair:\n\n");
		error ? printf("Erro: quantidade de operandos insuficiente.\n") : print_float_stack(nums);
		error = 0;
		printf("->");
		scanf(" %s",in);
		if(in[0]=='+' || in[0]=='-' || in[0]=='*' || in[0]=='/' || in[0]=='c'){
			if(in[1]=='!'){
				if(nums->size <= 1)
					error = 1;
				else
					op_float_stack(in[0], nums, 1);
			} else {
				if(nums->size <= 1)
					error = 1;
				else
					op_float_stack(in[0], nums, 0);
			}
		} else {
			if(in[0]=='s' || in[0]=='S')
				break;
			else {
				float qnum = special_string_to_float(in,strlen(in));
				push_float_stack(qnum, nums);
			}
		}
	}
	del_float_stack(nums);
	printf("\n----------------------------------------\n");
	strcpy(in,"");
}

void print_menu(){
	printf("Escolha o modo de operacao:\n");
	printf("1. Resolucao de Expressao\n");
	printf("2. Calculadora\n");
	printf("3. Sair\n");
}

int main(){
	int x = 1;
	system("clear");
	print_menu();
	while(x){
		scanf("%d",&x);
		if(x==1){
			modo_expressao();
			print_menu();
			x = 1;
		}
		else if(x==2){
			modo_calc();
			print_menu();
			x = 1;
		}
		else
			x = 0;
	}
	return 0;
}