/**
 * @file data_structures.h
 * @brief Definicoes das estruturas e funcoes relacionadas a estas
 * \par
 * Contem as estruturas que formam a arvore e os ninjas, e as assinaturas para as funcoes utilizadas
 * @author Joao Victor
 */

#ifndef __DSTRUCTURES__
#define __DSTRUCTURES__

/**
 * Estrutura para um elemento Ninja da arvore
 */
typedef struct {
	/*! Nome do ninja*/
	char *nome;
	/*! Elemento do ninja*/
	char *elemento;
	/*! Atributo ninjutsu do ninja (0 a 100)*/
	int ninjutsu;
	/*! Atributo genjutsu do ninja (0 a 100)*/
	int genjutsu;
	/*! Atributo taijutsu do ninja (0 a 100)*/
	int taijutsu;
	/*! Atributo defesa do ninja (0 a 100)*/
	int defesa;
} Ninja;


/**
 * Estrutura para os nos das arvores
 */
typedef struct node {
	/*! Ponteiro para o ninja contido neste no*/
	Ninja *ninja;
	/*! Ponteiro  para o elemento filho à esquerda*/
	struct node *left;
	/*! Ponteiro para o elemento filho à direita*/
	struct node *right;
} t_node;

/**
 * Estrutura para os elementos da lista duplamente encadeada
 */
typedef struct elem_lista{
	/*! Ninja contido no elemento da lista*/
	Ninja* ninja;
	/*! Elemento anterior, na lista. Caso nao tenha, é NULL*/
	struct elem_lista *ant;
	/*! Proximo elemento, na lista. Caso nao tenha, é NULL*/
	struct elem_lista *prox;
} t_elem_lista;

/**
 * Estrutura para a base da lista duplamente encadeada
 */
typedef struct {
	/*! Primeiro elemento da lista*/
	t_elem_lista *first;
	/*! Ultimo elemento da lista*/
	t_elem_lista *last;
	/*! Quantidade de elementos na lista*/
	int qtd;
} t_lista;

t_node* tree_create();
t_node* node_create();
void tree_free(t_node* tree);


Ninja* ninja_create(char* _nome, char* _elemento, int _ninjutsu, int _genjutsu,
	int _taijutsu, int _defesa);
void ninja_free(Ninja* ninja);
/* Obs: funcao Ninja* fight(...) esta no arquivo functions.c */

void tree_print_preorder(t_node* root);

/* Funcoes da lista */
t_lista* list_create();
t_elem_lista* aloc_elem(Ninja* _ninja);
void list_insert(t_lista* lista, Ninja* n);
void remove_lista(t_lista* lista);


#endif
