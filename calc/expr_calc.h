/**
 * @file expr_calc.h
 * @brief Definicoes das estruturas e funcoes
 * \par
 * Contem as assinaturas das estruturas necessarias para a implementação do tipo float_stack
 * \par
 * Contem as assinaturas das funções principais do programa.
 * @author Joao Victor
*/
#ifndef __EXPR_CALC__
#define __EXPR_CALC__

/**
 * Estrutura para um elemento de uma pilha do tipo float_stack
 */
typedef struct elem_float_stack_s{
	//! valor do elemento
	float val;
	//! elemento anterior na pilha (se for o primeiro, será NULL)
	struct elem_float_stack_s* ant;
} elem_float_stack;

/**
 * Estrutura para uma pilha do tipo float_stack
 */
typedef struct float_stack_s{
	//! elemento no topo da pilha
	elem_float_stack* top;
	//! altura da pilha
	float size;
} float_stack;

/* Float Stack */
float_stack* new_float_stack();
int push_float_stack(float value, float_stack* p);
int pop_float_stack(float_stack* p);
void del_float_stack(float_stack* p);

/* Validação e calculo da expressão */
int valid_expr(char* s);
void in_to_pos(char* s, char* answ);
float calc_expr(char* answ);

/* Funcoes para calculadora */
void print_float_stack(float_stack* p);
void op_float_stack(char op, float_stack* p, int repeat);
float special_string_to_float(char* string, int string_len);

/* etc */
void print_float(float f);

#endif