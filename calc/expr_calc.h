#ifndef __EXPR_CALC__
#define __EXPR_CALC__

typedef struct elem_float_stack_s{
	float val;
	struct elem_float_stack_s* ant;
} elem_float_stack;

typedef struct{
	elem_float_stack* top;
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