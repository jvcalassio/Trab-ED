/**
 * @file expr_calc.c
 * @brief Contem as funcoes principais para o funcionamento do programa
 * \par
 * Contem a implementação da pilha de ponto flutuante, chamada float_stack
 * \par
 * Contem as funções que realizam as conversões string<->float, e as funcoes que fazem as operacoes algebricas.
 * @author Joao Victor
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "expr_calc.h"

/**
 * Cria uma pilha do tipo float_stack
 */
float_stack* new_float_stack(){
	float_stack* p = malloc(sizeof(float_stack));
	p->top = NULL;
	p->size = 0;
	return p;
}

/**
 * Empilha elementos na pilha
 * @param value valor a ser inserido
 * @param p a pilha em que sera inserido o elemento
*/
int push_float_stack(float value, float_stack* p){
	elem_float_stack* elem = malloc(sizeof(elem_float_stack));
	if(elem!=NULL){
		elem->val = value;
		elem->ant = p->top;
		p->top = elem;
		p->size += 1;
		return 1;
	}
	return 0;
}
/**
 * Desempilha o elemento do topo da pilha
 * @param p a pilha em que sera removido o elemento 
 */
int pop_float_stack(float_stack* p){
	if(p->size > 1){
		elem_float_stack* temp = p->top->ant;
		free(p->top);
		p->top = temp;
		p->size -= 1;
		return 1;
	} else if(p->size == 1){
		free(p->top);
		p->top = NULL;
		p->size -= 1;
		return 1;
	}
	return 0;
}

/**
 * Deleta uma pilha
 * @param p a pilha a ser eliminada
 */
void del_float_stack(float_stack* p){
	if(p->size > 0){
		while(p->size != 0){
			pop_float_stack(p);
		}
	}
	free(p);
}

/**
 * Valida uma expressao matematica infixa
 * Avaliacao da quantidade de parenteses
 * @param s string contendo a expressao na forma infixa
 */
int valid_expr(char* s){
	int len = strlen(s);
	int valid = 1;
	float_stack* p = new_float_stack();

	for(int i=0;i<len;i++){
		if(s[i] == '('){
			push_float_stack(1,p);
		} else if(s[i] == ')'){
			if(p->size == 0){
				valid = 0;
				break;
			} else
				pop_float_stack(p);
		}
	}
	if(p->size != 0){
		valid = 0;
	}
	if(valid==1){
		int achou_op = 0;
		int achou_esp = 0;
		int achou_num = 0;
		int achou_letra = 0;
		for(int i=0;i<len;i++){
			if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/')
				achou_op++;
			else if(s[i]==' ')
				achou_esp++;
			else if(s[i]>='0' && s[i]<='9')
				achou_num++;
			else if(s[i]>='A' && s[i]<='Z')
				achou_letra++;
			else if(s[i]>='a' && s[i]<='z')
				achou_letra++;
		}
		if(achou_op==0 || len<5 || achou_esp==0 || (achou_num==0 && achou_letra==0))
			valid = 0;
		else if(achou_letra>0)
			valid = 2;
	}
	del_float_stack(p);
	return valid;
}

/** 
 * Transforma uma expressao da forma infixa para posfixa
 * -# Os operadores sao empilhados em um float_stack, segundo a seguinte ordem:
 * 	- 1 = -
 * 	- 2 = +
 * 	- 3 = *
 * 	- 4 = /
 * 	- 5 = (
 * -# Prioridades 1 = 2 < 3 = 4
 * @param s string contendo a expressao infixa
 * @param answ string em que sera inserida a expressao na forma posfixa
 */
void in_to_pos(char* s, char* answ){
	int pos_answ = 0;
	float_stack* p = new_float_stack();
	int len = strlen(s);
	for(int i=0;i<len;i++){
		if(s[i]=='+' || s[i]=='-'){
			while(p->size > 0 && p->top->val!=5){
				char op;
				if(p->top->val == 1) op = '-';
				else if(p->top->val == 2) op = '+';
				else if(p->top->val == 3) op = '*';
				else if(p->top->val == 4) op = '/';
				answ[pos_answ] = op;
				pos_answ++;
				pop_float_stack(p);
			}
			int k;
			if(s[i]=='-') k = 1;
			else k = 2;

			push_float_stack(k,p);

		} else if(s[i]=='*' || s[i]=='/'){
			while(p->size > 0 && (p->top->val == '3' || p->top->val == '4')){
				char op;
				if(p->top->val == 3) op = '*';
				else if(p->top->val == 4) op = '/';
				answ[pos_answ] = op;
				pos_answ++;
				pop_float_stack(p);
			}
			int k;
			if(s[i]=='*') k = 3;
			else k = 4;

			push_float_stack(k,p);

		} else if(s[i]=='('){
			push_float_stack(5,p);

		} else if(s[i]==')'){
			while(p->top->val != 5){
				char op;
				if(p->top->val == 1) op = '-';
				else if(p->top->val == 2) op = '+';
				else if(p->top->val == 3) op = '*';
				else if(p->top->val == 4) op = '/';
				answ[pos_answ] = op;
				pos_answ++;

				pop_float_stack(p);
			}
			pop_float_stack(p); // desempilha o (
			
		} else {
			if(s[i]==' '){
				if(answ[pos_answ-1]!=' ' && s[i+1]!='+' && s[i+1]!='-' && s[i+1]!='*' && s[i+1]!='/'){
					answ[pos_answ] = s[i];
					pos_answ++;
				}
			} else {
				answ[pos_answ] = s[i];
				pos_answ++;
			}
		}
	}
	while(p->size > 0){
		char op;
		if(p->top->val == 1) op = '-';
		else if(p->top->val == 2) op = '+';
		else if(p->top->val == 3) op = '*';
		else if(p->top->val == 4) op = '/';
		answ[pos_answ] = op;
		pos_answ++;
		pop_float_stack(p);
	}
	del_float_stack(p);
	answ[pos_answ] = '\0';
}

/**
 * Transforma uma string com inteiros e virgula para ponto flutuante (float)
 * Feita especificamente para a funcao calc_expr (por conta dos espacos)
 * @param string string a ser convertida
 * @param string_len tamanho da string a ser convertida
 */
float string_to_float(char* string, int string_len){
	float total = 0;
	int casas_ant_virgula = 0;
	int casas_pos_virgula = 0;
	int achou_virgula = 0;
	for(int i=0;i<string_len;i++){
		if(string[i]==',' || string[i]=='.'){
			casas_ant_virgula = i;
			achou_virgula = 1;
		}
	}
	if(achou_virgula == 1){ // numero decimal
		casas_pos_virgula = string_len - casas_ant_virgula - 1;
		int l = casas_ant_virgula-1;
		for(int i=0;i<casas_ant_virgula;i++){
			int k = string[i]-'0';
			total += k * pow(10,l);
			l--;
		}
		l = 1;
		for(int i=casas_ant_virgula+1;i<string_len-1;i++){
			int k = string[i]-'0';
			total += k / pow(10,l);
			l++;
		}
	}
	else { // numero inteiro
		int l = 0;
		for(int i=string_len-2;i>=0;i--){
			int k = string[i]-'0';
			total += k * pow(10,l);
			l++;
		}
	}
	return total;
}

/** 
 * Calcula o resultado de uma expressao na forma posfixa
 * @param answ string da expressao a ser calculada
 */
float calc_expr(char* answ){
	float_stack* p = new_float_stack();
	int len = strlen(answ);
	char to_stack[200];
	float fto_stack = 0;
	int count_to_stack = 0;
	for(int i=0;i<len;i++){
		if(answ[i]!='+' && answ[i]!='-' && answ[i]!='*' && answ[i]!='/' && answ[i]!=' '){
			to_stack[count_to_stack] = answ[i];
			count_to_stack++;
		} else {
			if(answ[i-1]!='+' && answ[i-1]!='-' && answ[i-1]!='*' && answ[i-1]!='/' && answ[i-1]!=' '){
				to_stack[count_to_stack] = '\0';
				count_to_stack++;
				fto_stack = string_to_float(to_stack,count_to_stack);
				count_to_stack = 0;

				push_float_stack(fto_stack, p);
			}
			if(answ[i]=='+'){
				float newval = p->top->val;
				pop_float_stack(p);

				newval += p->top->val;
				pop_float_stack(p);

				push_float_stack(newval, p);
			} else if(answ[i]=='-'){
				float newval = 0;
				float segundo_termo = p->top->val;
				pop_float_stack(p);

				newval = p->top->val - segundo_termo;
				pop_float_stack(p);

				push_float_stack(newval,p);
			} else if(answ[i]=='*'){
				float newval = p->top->val;
				pop_float_stack(p);

				newval *= p->top->val;
				pop_float_stack(p);

				push_float_stack(newval,p);
			} else if(answ[i]=='/'){
				float newval = 0;
				float denomin = p->top->val;
				pop_float_stack(p);

				newval = p->top->val / denomin;
				pop_float_stack(p);

				push_float_stack(newval,p);
			}
		}
	}
	float fansw = p->top->val;
	del_float_stack(p);
	return fansw;
}

/**
 * Transforma uma string com inteiros e virgula para ponto flutuante (float)
 * Funciona com numeros negativos
 * @param string string a ser convertida
 * @param string_len tamanho da string a ser convertida
 */
float special_string_to_float(char* string, int string_len){
	float total = 0;
	int casas_ant_virgula = 0;
	int casas_pos_virgula = 0;
	int achou_virgula = 0;
	int negativo = 0;
	if(string[0]=='-'){
		negativo = 1;
		string[0] = '0';
	}
	for(int i=0;i<string_len;i++){
		if(string[i]==',' || string[i]=='.'){
			casas_ant_virgula = i;
			achou_virgula = 1;
		}
	}
	if(achou_virgula == 1){ // numero decimal
		casas_pos_virgula = string_len - casas_ant_virgula - 1;
		int l = casas_ant_virgula-1;
		for(int i=0;i<casas_ant_virgula;i++){
			int k = string[i]-'0';
			total += k * pow(10,l);
			l--;
		}
		l = 1;
		for(int i=casas_ant_virgula+1;i<string_len;i++){
			int k = string[i]-'0';
			total += k / pow(10,l);
			l++;
		}
	}
	else { // numero inteiro
		int l = 0;
		for(int i=string_len-1;i>=0;i--){
			int k = string[i]-'0';
			total += k * pow(10,l);
			l++;
		}
	}
	if(negativo) 
		return -total;
	else
		return total;
}

/**
 * Imprime um numero conforme suas casas decimais:
 * -# Caso o numero tenha todas as casas decimais como 0, imprime um inteiro
 * -# Caso o numero tenha uma ou mais casas decimais diferentes de 0, imprime um ponto flutuante com 2 casas decimais de precisao
 * @param f numero em ponto flutuante
 */ 
void print_float(float f){
	int k = (int) f;
	if(f-k == 0){
		printf("%d",k);
	} else {
		float dec = (f-k) * 100;
		printf("%d,%.0f",k,dec);
	}
}

/**
 * Imprime uma pilha
 * @param p pilha a ser impressa
 */
void print_float_stack(float_stack* p){
	if(p->size != 0){
		float_stack* temp = new_float_stack();
		int i = p->size;
		while(p->size != 0){
			push_float_stack(p->top->val,temp);
			//printf("%d. %f\n",i,p->top->val);
			printf("%d. ",i);
			print_float(p->top->val);
			printf("\n");
			i--;
			pop_float_stack(p);
		}
		while(temp->size != 0){
			push_float_stack(temp->top->val,p);
			pop_float_stack(temp);
		}
		del_float_stack(temp);
	} else {
		printf("Pilha Vazia!\n");
	}
}

/**
 * Realiza operacoes em uma pilha
 * @param op operacao a ser realizada
 * @param p em qual pilha deve ser realizada a operacao
 * @param repeat deve-se repetir a operacao ate o final (1 = sim, 0 = nao)
 */
void op_float_stack(char op, float_stack* p, int repeat){
	if(op=='+'){
		if(repeat==1){
			while(p->size != 1){
				float res = p->top->val;
				pop_float_stack(p);
				res += p->top->val;
				pop_float_stack(p);

				push_float_stack(res, p);
			}
		} else {
			float res = p->top->val;
			pop_float_stack(p);
			res += p->top->val;
			pop_float_stack(p);

			push_float_stack(res, p);
		}
	} else if(op=='-'){
		if(repeat==1){
			while(p->size != 1){
				float res = p->top->val;
				pop_float_stack(p);
				res -= p->top->val;
				pop_float_stack(p);

				push_float_stack(res, p);
			}
		} else {
			float res = p->top->val;
			pop_float_stack(p);
			res -= p->top->val;
			pop_float_stack(p);

			push_float_stack(res, p);
		}
	} else if(op=='*'){
		if(repeat==1){
			while(p->size != 1){
				float res = p->top->val;
				pop_float_stack(p);
				res *= p->top->val;
				pop_float_stack(p);

				push_float_stack(res, p);
			}
		} else {
			float res = p->top->val;
			pop_float_stack(p);
			res *= p->top->val;
			pop_float_stack(p);

			push_float_stack(res, p);
		}
	} else if(op=='/'){
		if(repeat==1){
			while(p->size != 1){
				float res = p->top->val;
				pop_float_stack(p);
				res /= p->top->val;
				pop_float_stack(p);

				push_float_stack(res, p);
			}
		} else {
			float res = p->top->val;
			pop_float_stack(p);
			res /= p->top->val;
			pop_float_stack(p);

			push_float_stack(res, p);
		}
	} else if(op=='c'){
		int k = p->top->val;
		pop_float_stack(p);
		float n = p->top->val;
		pop_float_stack(p);
		while(k!=0){
			push_float_stack(n, p);
			k--;
		}
	}
}