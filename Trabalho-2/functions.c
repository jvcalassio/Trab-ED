/**
 * @file functions.c
 * @brief Contem a implementacao das funcoes para o funcionamento do programa
 * \par
 * Contem a implementacao das funcoes definidas no arquivo functions.h
 * --- adicionar funcoes extras adicionadas aqui ---
 * @author Joao Victor
 */
#include <stdlib.h>
#include <string.h>
#include "functions.h"

/**
 * Cria um no para a arvore
 * Retorna o ponteiro para o no criado
 */
t_node* node_create(){
	t_node* no = malloc(sizeof(t_node));
	no->ninja = NULL;
	no->left = NULL;
	no->right = NULL;
	return no;
}

/**
 * Cria a arvore completa, com os 4 niveis gerados
 * Retorna o ponteiro para o nó raiz
 */
t_node* tree_create(){

}

/**
 * Cria um Ninja com os valores desejados
 * Retorna o ponteiro para o Ninja criado
 * @param _nome nome do ninja
 * @param _elemento elemento utilizado
 * @param _ninjutsu pontos de ninjutsu
 * @param _genjutsu pontos de genjutsu
 * @param _taijutsu pontos de taijutsu
 * @param _defesa pontos de defesa
 */
Ninja* ninja_create(char* _nome, char* _elemento, int _ninjutsu, int _genjutsu,
	int _taijutsu, int _defesa)
{
	Ninja* n = malloc(sizeof(Ninja));

	// aloca a memoria necessaria e copia a string para o Ninja
	n->nome = malloc(strlen(_nome)+1);
	strcpy(n->nome, _nome);
	// aloca a memoria necessaria e copia a string para o Ninja
	n->elemento = malloc(strlen(_elemento)+1);
	strcpy(n->elemento, _elemento);

	// copia os outros valores
	n->ninjutsu = _ninjutsu;
	n->genjutsu	= _genjutsu;
	n->taijutsu = _taijutsu;
	n->defesa = _defesa;

	return n;
}

/** 
 * Realiza a 'luta' entre dois ninjas, comparando o atributo desejado.
 * Retorna o ponteiro para o ninja vencedor
 * @param ninja_one primeiro ninja
 * @param ninja_two segundo ninja
 * @param attribute atributo a ser comparado para definir o vencedor
 */ 
Ninja* fight(Ninja* ninja_one, Ninja* ninja_two, int attribute){
	// atributos do ninja 1
	int nj1[] = {0, ninja_one->ninjutsu, ninja_one->genjutsu,
				 ninja_one->taijutsu, ninja_one->defesa};
	// atributos do ninja 2;
	int nj2[] = {0, ninja_two->ninjutsu, ninja_two->genjutsu,
				 ninja_two->taijutsu, ninja_two->defesa};

	if(nj2[attribute] > nj1[attribute]){
		return ninja_two;
	} else {
		return ninja_one;
	}
}

/**
 * Libera um ninja da memoria
 * @param ninja ponteiro para o ninja a ser removido
 */
void ninja_free(Ninja* ninja){
	free(ninja->nome);
	free(ninja->elemento);
	free(ninja);
}

/**
 * Cria uma lista
 * Retorna o ponteiro para a lista criada
 */
t_lista* list_create(){
	t_lista* l = malloc(sizeof(t_lista));
	l->first = NULL;
	l->last = NULL;
	l->qtd = 0;
	return l;
}

/**
 * Aloca um elemento para a lista
 * Retorna o ponteiro para o elemento criado
 * @param _ninja ninja contido no elemento
 */
t_elem_lista* aloc_elem(Ninja* _ninja){
	t_elem_lista* elem = malloc(sizeof(t_elem_lista));
	elem->ninja = _ninja;
	elem->ant = NULL;
	elem->prox = NULL;
	return elem;
}

/** 
 * Remove um elemento da lista
 * @param elem elemento a ser removido
 */
void remove_elemento(t_elem_lista* elem, t_lista* lista){
	if(elem->ant != NULL){
		elem->ant->prox = elem->prox;
	} else {
		lista->first = elem->prox;
	}
	if(elem->prox != NULL){
		elem->prox = elem->ant;
	} else {
		lista->last = elem->ant;
	}
	free(elem);
}

/**
 * Remove uma lista
 * @param lista lista a ser removida
 */
void remove_lista(t_lista* lista){
	t_elem_lista* t = lista->first;
	while(t != NULL){
		t_elem_lista* temp = t->prox;
		remove_elemento(t, lista);
		t = temp;
	}
}