/**
 * \mainpage Avaliacao de Expressoes Aritmeticas e Calculadora
 *
 * \section intro_sec Introducao
 * \par Este programa é dividido em duas partes:
 * -# Avaliacao de expressoes aritmeticas
 * \n O programa le do teclado uma expressao aritmetica e se for valida, a converte da forma infixa para a forma posfixa:
 * \n Forma infixa:
 * \n (A + B) * C = D
 * \n Forma posfixa:
 * \n A B + C* = D
 * \n Apos a conversao, o programa calcula o resultado da expressao.
 * -# Calculadora
 * \n O programa inicia uma pilha vazia, e le inputs do teclado.
 * \n Se o input for um numero, este numero e empilhado;
 * \n Se o input for uma operacao, esta operacao e realizada na pilha.
 * \n As operacoes comuns sao soma (+), subtracao (-), multiplicacao (*) e divisao (*);
 * \n As operacoes especiais sao a repeticao (x!) e a copia (c).
 * \n A repeticao, repete uma operacao x em toda a pilha
 * \n A copia define dois numeros x e y, sendo x o elemento do topo da pilha e y o elemento abaixo deste. Entao, os dois elementos sao removidos da pilha, e o elemento y é inserido x vezes na pilha.
 * \n
 * \section archs Arquivos
 * \par Arquivos utilizados:
 * 	- main.c
 * \par
 *	- expr_calc.c
 * \par
 *	- expr_calc.h
 */
/**
 * @file main.c
 * @brief Arquivo principal para a execucao do programa
 * \par
 * Responsavel por exibir os menus, ler os dados do teclado, e chamar as funções para a execução do programa.
 * @author Joao Victor
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expr_calc.h"

/** 
 * \par Modo avaliador de expressões
 * Espera o input de uma expressao matematica na forma infixa pelo usuario.
 * \par
 * Transforma a expressao para a forma posfixa, e imprime o resultado.
 */
void modo_expressao(){
	system("clear");
	printf("Modo Expressao\n");
	printf("Insira a expressao:\n");
	char expres[200];
	scanf(" %[^\n]",expres);
	int valida = valid_expr(expres);
	if(valida>=1){ // Avaliacao da expressao
		system("clear");
		printf("Expressao valida!\n\n");
		// Transformacao para posfixa
		char answ[200];
		in_to_pos(expres,answ);
		printf("Forma posfixa: %s\n",answ);

		// Calculo da expressao se nao tiver letras
		if(valida==1){
			float final_res = calc_expr(answ);
			printf("Resultado: ");
			print_float(final_res);
			printf("\n");
		}

		printf("----------------------------------------\n");
	} else {
		// Caso a expressao seja invalida
		system("clear");
		printf("Expressao invalida!\n\n");
		printf("----------------------------------------\n");
	}
}

/** 
 * \par Modo calculadora 
 * Espera o input do usuario para um numero ou expressao
 * \par
 * Ao receber um numero, este é empilhado
 * \par
 * Ao receber uma operacao, esta é executada
 */
void modo_calc(){
	system("clear");
	printf("Modo Calculadora\n");
	printf("Digite um numero ou operacao. Digite S para sair:\n\n");

	float_stack* nums = new_float_stack();
	char in[20] = {'0','\0'};
	int error = 0;
	while(in[0]!='s' && in[0]!='S'){
		system("clear");
		printf("Modo Calculadora\n");
		printf("Digite um numero ou operacao. Digite S para sair:\n\n");
		error ? printf("Erro: quantidade de operandos insuficiente.\n") : print_float_stack(nums);
		error = 0;
		printf("->");
		scanf(" %s",in);
		if((in[0]=='+' || in[0]=='-' || in[0]=='*' || in[0]=='/' || in[0]=='c') && (in[1]=='\0' || in[1]=='!')){ // Realiza operacoes
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
			else { // Empilha os numeros
				float qnum = special_string_to_float(in,strlen(in));
				push_float_stack(qnum, nums);
			}
		}
	}
	del_float_stack(nums);
	printf("\n----------------------------------------\n");
	strcpy(in,"");
}

/**
 * \par Imprime o menu principal
 */
void print_menu(){
	printf("Escolha o modo de operacao:\n");
	printf("1. Resolucao de Expressao\n");
	printf("2. Calculadora\n");
	printf("3. Sair\n");
}

/**
 * \par Loop principal
 */
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