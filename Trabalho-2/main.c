#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

/**
 * Verifica a existencia de um numero em um vetor de inteiros
 * Retorna -1 se o vetor nao contem o elemento
 * @param n numero a ser procurado
 * @param vet vetor em que sera realizada a busca
 * @param size tamanho do vetor
 */
int indexOf(int n, int vet[], int size){
	for(int i=0;i<size;i++){
		if(vet[i]==n){
			return i;
		}
	}
	return -1;
}


/**
 * Mostra a lista dos personagens escolhidos do arquivo
 * Mostra apenas um atributo, escolhido aleatoriamente, para cada personagem
 * @param lista lista dos personagens
 */
void print_participants(t_lista* lista){
	int s = lista->qtd;
	t_elem_lista* temp = lista->first;
	printf("Escolha seu personagem:\n\n");
	for(int i=1;i<=s;i++){
		printf("Personagem %d:\n",i);
		int toshow = rand()%4+1;
		int chosen_atr_val;

		char ninval[] = "??";
		char genval[] = "??";
		char taival[] = "??";
		char defval[] = "??";

		switch(toshow){
			case 1: chosen_atr_val = temp->ninja->ninjutsu; break;
			case 2: chosen_atr_val = temp->ninja->genjutsu; break;
			case 3: chosen_atr_val = temp->ninja->taijutsu; break;
			case 4: chosen_atr_val = temp->ninja->defesa; break;
		}

		int convDig1 = (chosen_atr_val/10);
		float aux = (chosen_atr_val-(convDig1*10));
		int convDig2 = (int) aux;
		convDig1 += '0';
		convDig2 += '0';

		switch(toshow){
			case 1: ninval[0] = convDig1; ninval[1] = convDig2; break;
			case 2: genval[0] = convDig1; genval[1] = convDig2; break;
			case 3: taival[0] = convDig1; taival[1] = convDig2; break;
			case 4: defval[0] = convDig1; defval[1] = convDig2; break;
		}

		printf("Ninjutsu: %s Genjutsu: %s Taijutsu: %s Defesa: %s\n\n",ninval,genval,taival,defval);

		temp = temp->prox;
	}
}

/**
 * Inicializa o jogo:
 * Le o arquivo ninjas.txt, sorteia os 16 jogadores e os insere na lista
 * @param players lista de todos os competidores
 * @param f arquivo de texto ninjas.txt
 */
void init(t_lista* players, FILE* f){
	int i;
	int j = 1;
	int chosen_nums[16];
	char nome[32], elemento[10];
	int ninjutsu, genjutsu, taijutsu, defesa;

	for(i=0;i<16;i++)
		chosen_nums[i] = -1;

	// Sorteia 16 numeros diferentes em [1, 32]
	for(i=0;i<16;i++){
		int k = rand()%32+1;
		while(indexOf(k, chosen_nums, 16)!=-1){
			k = rand()%32+1;
		}
		chosen_nums[i] = k;
	}

	// Salva os escolhidos na lista
	while(fscanf(f, " %[^,], %[^,], %d, %d, %d, %d",nome,elemento,&ninjutsu,&genjutsu,&taijutsu,&defesa)!=EOF){
		if(indexOf(j, chosen_nums, 16) != -1){
			//printf("%s - %s - %d - %d - %d - %d\n",nome,elemento,ninjutsu,genjutsu,taijutsu,defesa);
			Ninja* chosen_ninja = ninja_create(nome, elemento, ninjutsu, genjutsu, taijutsu, defesa);
			t_elem_lista* chosen = aloc_elem(chosen_ninja);
			chosen->ant = players->last;

			if(players->qtd==0){
				players->first = chosen;
				players->last = chosen;
			} else {
				players->last->prox = chosen;
			}
			players->last = chosen;
			players->qtd++;
		}
		j++;
	}
}

/**
 * Pega um elemento em um indice especifico, dentro de uma lista
 * @param lista lista a ser percorrida
 * @param index indice procurado
 */
t_elem_lista* get_elem_at(t_lista* lista, int index){
	t_elem_lista* aux = lista->first;
	int i;
	for(int i=0;i<16;i++){
		if(i+1==index){
			return aux;
		}
		aux = aux->prox;
	}
}

/**
 * Mostra o personagem escolhido pelo jogador, e os seus atributos
 * @param players lista de todos os competidores
 * @param n_player numero do competidor escolhido pelo jogador
 */
void show_player_char(t_lista* players, int n_player){ 
	t_elem_lista* aux = get_elem_at(players, n_player);
	Ninja* n = aux->ninja;
	printf("Seu personagem: %s\n",n->nome);
	printf("1) Ninjutsu : %d\n",n->ninjutsu);
	printf("2) Genjutsu : %d\n",n->genjutsu);
	printf("3) Taijutsu : %d\n",n->taijutsu);
	printf("4) Defesa : %d\n",n->defesa);
}

void switch_places(t_elem_lista* f, t_elem_lista* s){
	Ninja* aux = f->ninja;
	f->ninja = s->ninja;
	s->ninja = aux;
}

/**
 * Reorganiza os elementos da lista
 * Do contrario, o jogador poderia decorar a ordem que os personagens geralmente aparecem
 * Baseado no algoritmo Fisher-Yates shuffle
 * @param lista lista a ser reorganizada
 */
void shuffle_list(t_lista* lista){
	int s = lista->qtd;
	int i, j;
	for(i=s-1;i>0;i--){
		j = rand()%i+1;
		if(j!=i)0
			switch_places(get_elem_at(lista, j), get_elem_at(lista, i));
	}
}

/**
 * Move os jogadores que estao na lista, para a arvore
 * @param raiz no raiz da arvore
 * @param players lista dos players
 * @param indice indice do player a ser retirado da lista
 */
void insert_players(t_node* raiz, t_elem_lista* elem){
	if(raiz->left == NULL && raiz->right == NULL){
		// inserir player
		Ninja* n = elem->ninja;
		raiz->ninja = n;
		elem = elem->proximo;
	} else {
		insert_players(raiz->left, elem);
		insert_players(raiz->right, elem);
	}
}

/**
 * Funcao principal de jogo
 */
void start(){
	system("clear");
	system("clear");
	FILE* f = fopen("ninjas.txt","r");
	int i, n_player = 0, atr_player = 0;
	int step = 1;
	t_lista* players = list_create();


	if(f==NULL)
		return; // se arquivo nao existe/erro na leitura

	// Pega os jogadores do arquivo, e insere 16 aleatoriamente na lista
	init(players, f);
	fclose(f);

	// Reorganiza os ninjas na lista. Para o jogo nao ficar 'vicioso'
	shuffle_list(players);	

	// Printa para o jogador cada um dos escolhidos, mostrando somente um atributo cada
	print_participants(players);
	// Escolha do jogador
	while(n_player < 1 || n_player > 16)
		scanf("%d",&n_player);

	// Criacao a arvore com 4 niveis e insercao dos jogadores nos ultimos niveis
	t_node* raiz = tree_create();
	t_elem_lista* start_index = players->first;
	insert_players(raiz, start_index);

	// resumao:
	// char do player = n_player
	// rodada = step
	// atributo escolhido pelo player = atr_player
	// fazer loop para todas as rodadas DO PLAYER
	// fazer loop para todas as rodadas do resto
	// fazer lista para salvar todas as rodadas e printar no final
	// mudar a "show_player_char" para considerar os atributos


	printf("%da ETAPA\n\n", step);
	show_player_char(players, n_player);
	printf("\nSeu adversario: A ESCOLHER\n\n");
	printf("Selecione um atributo: ");
	scanf("%d",&atr_player);
	// E mostrar a tela de primeira etapa
	// E pedir a escolha de atributo
}

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