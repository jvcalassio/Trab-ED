/**
 * @file data_structures.h
 * @brief Definicoes das estruturas e funcoes principais
 * \par
 * Contem as estruturas que formam a arvore e os ninjas,
 * e as assinaturas para as funcoes utilizadas
 * @author Joao Victor
 */

#ifndef __DSTRUCTURES__
#define __DSTRUCTURES__

/**
 * Estrutura para um elemento Ninja da arvore
 */
typedef struct {
	//! nome do ninja
	char *nome;
	//! elemento do ninja
	char *elemento;
	//! atributo ninjutsu do ninja (0 a 100)
	int ninjutsu;
	//! atributo genjutsu do ninja (0 a 100)
	int genjutsu;
	//! atributo taijutsu do ninja (0 a 100)
	int taijutsu;
	//! atributo defesa do ninja (0 a 100)	
	int defesa;
} Ninja;


/**
 * Estrutura para os nos das arvores
 */
typedef struct node {
	//! ponteiro para o ninja contido neste no
	Ninja *ninja;
	//! ponteiro  para o elemento filho à esquerda
	struct node *left;
	//! ponteiro para o elemento filho à direita
	struct node *right;
} t_node;

/**
 * Estrutura para os elementos da lista duplamente encadeada
 */
typedef struct elem_lista{
	//! ninja contido no elemento da lista
	Ninja* ninja;
	//! elemento anterior, na lista. Caso nao tenha, é NULL
	struct elem_lista *ant;
	//! proximo elemento, na lista. Caso nao tenha, é NULL
	struct elem_lista *prox;
} t_elem_lista;

/**
 * Estrutura para a base da lista duplamente encadeada
 */
typedef struct {
	//! primeiro elemento da lista
	t_elem_lista *first;
	//! ultimo elemento da lista
	t_elem_lista *last;
	//! quantidade de elementos na lista
	int qtd;
} t_lista;

t_node* tree_create();
t_node* node_create();
void tree_free(t_node* tree);


Ninja* ninja_create(char* _nome, char* _elemento, int _ninjutsu, int _genjutsu,
	int _taijutsu, int _defesa);
void ninja_free(Ninja* ninja);
// Obs: funcao Ninja* fight(...) esta no arquivo functions.c

void tree_print_preorder(t_node* root);

// Funcoes da lista
t_lista* list_create();
t_elem_lista* aloc_elem(Ninja* _ninja);
void list_insert(t_lista* lista, Ninja* n);
void remove_lista(t_lista* lista);


#endif
