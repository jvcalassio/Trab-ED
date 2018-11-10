/**
 * @file functions.c
 * @brief Contem a implementacao das funcoes para o funcionamento do programa
 * \par
 * Contem a implementacao de funcoes definidas no arquivo functions.h
 * Contem as funcoes para a realizacao do jogo
 * --- adicionar funcoes extras adicionadas aqui ---
 * TO-DO LIST:
 * 		DIZER SUPREMACIA NO HISTORICO DE BATALHAS
 *		MELHORAR UI
 * 		MAINPAGE DOXYGEN
 *		RELATORIO
 * @author Joao Victor
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

/**
 * Verifica a existencia de um numero em um vetor de inteiros
 * Retorna -1 se o vetor nao contem o elemento
 * @param n numero a ser procurado
 * @param vet vetor em que sera realizada a busca
 * @param size tamanho do vetor
 */
int indexOf(int n, int vet[], int size){
	int i;
	for(i=0;i<size;i++){
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
	int s = lista->qtd, i;
	t_elem_lista* temp = lista->first;
	printf("Escolha seu personagem:\n\n");
	for(i=1;i<=s;i++){
		printf("Personagem %d:\n",i);
		int toshow = rand()%4+1; // gera o atributo, aleatoriamente
		int chosen_atr_val;

		char ninval[4] = "??";
		char genval[4] = "??";
		char taival[4] = "??";
		char defval[4] = "??";

		char *str = malloc(4);

		// verifica qual atributo foi escolhido, e troca os '??' pelo valor
		switch(toshow){
			case 1: 
				chosen_atr_val = temp->ninja->ninjutsu;
				sprintf(str, "%d",chosen_atr_val);

				strcpy(ninval, str);
				break;
			case 2: 
				chosen_atr_val = temp->ninja->genjutsu;
				sprintf(str, "%d",chosen_atr_val);

				strcpy(genval, str);
				break;
			case 3: 
				chosen_atr_val = temp->ninja->taijutsu; 
				sprintf(str, "%d",chosen_atr_val);

				strcpy(taival, str);
				break;
			case 4: 
				chosen_atr_val = temp->ninja->defesa; 
				sprintf(str, "%d",chosen_atr_val);

				strcpy(defval, str);
				break;
		}
		free(str);

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
	for(i=0;i<16;i++){
		if(i+1==index){
			return aux;
		}
		aux = aux->prox;
	}
}

/** 
 * Realizas comparacoes entre elementos
 * Retorna  1 se elem1 ganhar
 * Retorna -1 se elem2 ganhar
 * Retorna 0 se empatar ou os elementos nao forem adjacentes
 * @param elem1 string do primeiro elemento
 * @param elem2 string do segundo elemento
 */
int elem_beat(char* elem1, char* elem2){
	if(!strcmp(elem1,"Fogo")){
		if(!strcmp(elem2,"Vento")){
			return 1;
		} else if(!strcmp(elem2,"Agua")){
			return -1;
		}
	} else if(!strcmp(elem1,"Vento")){
		if(!strcmp(elem2,"Relampago")){
			return 1;
		} else if(!strcmp(elem2,"Fogo")){
			return -1;
		}
	} else if(!strcmp(elem1,"Relampago")){
		if(!strcmp(elem2,"Terra")){
			return 1;
		} else if(!strcmp(elem2,"Vento")){
			return -1;
		}
	} else if(!strcmp(elem1,"Terra")){
		if(!strcmp(elem2,"Agua")){
			return 1;
		} else if(!strcmp(elem2,"Relampago")){
			return -1;
		}
	} else if(!strcmp(elem1,"Agua")){
		if(!strcmp(elem2,"Fogo")){
			return 1;
		} else if(!strcmp(elem2,"Terra")){
			return -1;
		}
	}
	return 0;
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

	// verifica a supremacia (ou inferioridade) elemental na luta
	float mul = 1.0;
	int vantagem = elem_beat(ninja_one->elemento, ninja_two->elemento);
	if(vantagem == 1)
		mul = 1.2;
	else if(vantagem == -1)
		mul = 0.8;

	if(nj2[attribute] > nj1[attribute] * mul){
		return ninja_two;
	} else {
		return ninja_one;
	}
}

/**
 * Mostra o personagem escolhido pelo jogador, e os seus atributos
 * @param n Ninja do personagem escolhido pelo jogador
 * @param enemy Ninja do oponente atual do jogador (para verificar supremacia)
 * @param chosen_last_round elemento escolhido na rodada anterior
 */
void show_player_char(Ninja* n, Ninja* enemy, int chosen_last_round){
	int ninjutsu = n->ninjutsu;
	int genjutsu = n->genjutsu;
	int taijutsu = n->taijutsu;
	int defesa = n->defesa;
	printf("Seu personagem: %s\n",n->nome);
	
	// verifica a supremacia (ou inferioridade) elemental
	int beat = elem_beat(n->elemento, enemy->elemento);
	if(beat == 1){
		printf("SUPREMACIA ELEMENTAL: %s > %s\n", n->elemento, enemy->elemento);
		printf("Todos os atributos foram multiplicados por x1.2\n");
		ninjutsu *= 1.2;
		genjutsu *= 1.2;
		taijutsu *= 1.2;
		defesa *= 1.2;
	} else if(beat == -1){
		printf("INFERIORIDADE ELEMENTAL: %s < %s\n", n->elemento, enemy->elemento);
		printf("Todos os atributos foram multiplicados por x0.8\n");
		ninjutsu *= 0.8;
		genjutsu *= 0.8;
		taijutsu *= 0.8;
		defesa *= 0.8;
	}

	char str1[17]; sprintf(str1, "1) Ninjutsu : %d",ninjutsu);
	char str2[17]; sprintf(str2, "2) Genjutsu : %d",genjutsu);;
	char str3[17]; sprintf(str3, "3) Taijutsu : %d",taijutsu);;
	char str4[17]; sprintf(str4, "4) Defesa : %d",defesa);;

	// troca o texto caso o atributo nao seja permitido na rodada
	if(chosen_last_round == 1)
		strcpy(str1,"X) XXXXX : XX");
	else if(chosen_last_round == 2)
		strcpy(str2,"X) XXXXX : XX");
	else if(chosen_last_round == 3)
		strcpy(str3,"X) XXXXX : XX");
	else if(chosen_last_round == 4)
		strcpy(str4,"X) XXXXX : XX");

	printf("%s\n", str1);
	printf("%s\n", str2);
	printf("%s\n", str3);
	printf("%s\n", str4);
}

/**
 * Troca dois Ninjas de lugar na lista
 * Utilizado para reorganizar
 * @param f primeiro elemento da lista a ser trocado
 * @param s segundo elemento da lista a ser trocado
 */
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
	int s = lista->qtd, i, j;
	for(i=s-1;i>0;i--){
		j = rand()%i+1;
		if(j!=i)
			switch_places(get_elem_at(lista, j), get_elem_at(lista, i));
	}
}

/**
 * Move os jogadores que estao na lista, para a arvore
 * @param raiz no raiz da arvore
 * @param players lista dos players
 */
void insert_players(t_node* raiz, t_lista* players){
	if(raiz->left == NULL && raiz->right == NULL){
		t_elem_lista* l = players->first;
		Ninja* n = l->ninja;
		raiz->ninja = n;
		if(l!=NULL){
			players->first = l->prox;
			if(players->first!=NULL)
				players->first->ant = NULL;
			free(l); // libera os elementos da lista de players original
		}
		players->qtd--;
	} else {
		insert_players(raiz->left, players);
		insert_players(raiz->right, players);
	}
}

/**
 * Percorre a arvore e verifica o oponente do player
 * Retorna o ponteiro para o Ninja inimigo
 * @param raiz raiz da arvore
 * @param player_ninja Ninja do player
 */
Ninja* get_enemy(t_node* raiz, Ninja* player_ninja){
	if(raiz->left != NULL && raiz->left->ninja == player_ninja){
		return raiz->right->ninja;
	} else if(raiz->right != NULL && raiz->right->ninja == player_ninja){
		return raiz->left->ninja;
	} else if(raiz->left == NULL && raiz->right == NULL){
		return NULL;
	} else {
		Ninja* t = get_enemy(raiz->left, player_ninja);
		if(t == NULL){
			t = get_enemy(raiz->right, player_ninja);
		}
		// retorna o ninja inimigo. se t = null, volta na recursao e vai para o proximo no
		return t;
	}
}

/**
 * Faz o jogador (ou o oponente do jogador) subir na arvore, se ganhar
 * Realiza a batalha dos outros personagens, e tambem faz avancar quem ganha
 * @param raiz raiz da arvore
 * @param p_winner quem ganhou no round do jogador
 * @param vencedores lista dos personagens que ganharam ate entao
 * @param perdedeores lista dos personagens que perderam ate entao
 * @param atributos vetor dos atributos utilizados nas batalhas
 */
t_node* sobe_level(t_node* raiz, Ninja* p_winner, t_lista* perdedores, t_lista* vencedores, int *atributos){
	if(raiz->left == NULL && raiz->right == NULL){
		return NULL;
	} else {
		t_node* l1 = sobe_level(raiz->left, p_winner, perdedores, vencedores, atributos); // chamada recursiva esquerda
		t_node* l2 = sobe_level(raiz->right, p_winner, perdedores, vencedores, atributos); // chamada recursiva direita
		if(l1 == NULL && l2 == NULL){
			// caso o no seja o do player ou o de seu oponente
			// nao realiza a batalha novamente
			if(raiz->left->ninja == p_winner || raiz->right->ninja == p_winner){
				raiz->ninja = p_winner;
				list_insert(vencedores, p_winner); // insere nos vencedores

				Ninja* p_loser;
				if(raiz->left->ninja == p_winner){
					p_loser = raiz->right->ninja;
				} else if(raiz->right->ninja == p_winner){
					p_loser = raiz->left->ninja;
				}
				list_insert(perdedores, p_loser); // insere nos perdedores

				free(raiz->left);
				free(raiz->right);
				raiz->left = NULL;
				raiz->right = NULL;
			} else { // caso o no seja dos outros competidores
				int atr = rand()%4 + 1;
				// realiza a luta dos competidores com atributo escolhido aleatoriamente
				Ninja* t = fight(raiz->left->ninja, raiz->right->ninja, atr);

				atributos[indexOf(0, atributos, 32)] = atr;

				raiz->ninja = t;
				list_insert(vencedores, t); // insere nos vencedores

				Ninja* p_loser;
				if(raiz->left->ninja == t){
					p_loser = raiz->right->ninja;
				} else if(raiz->right->ninja == t){
					p_loser = raiz->left->ninja;
				}
				list_insert(perdedores, p_loser); // insere nos perdedores

				free(raiz->left);
				free(raiz->right);
				raiz->left = NULL;
				raiz->right = NULL;
			}
		}
	}
}


/** 
 * Printa todas as batalhas ocorridas no jogo
 * @param perdedores lista com os ninjas perdedores
 * @param vencedores lista com os ninjas vencedores
 * @param rodadas ate qual rodada printar
 * @param atributos vetor dos atributos utilizados nas batalhas
 */
void print_battles(t_lista* perdedores, t_lista* vencedores, int rodadas, int *atributos){
	t_elem_lista* p1 = perdedores->first;
	t_elem_lista* p2 = vencedores->first;

	char atr_txt[4][9] = {"Ninjutsu", "Genjutsu", "Taijutsu", "Defesa"};
	int i;
	// printa cada uma das rodadas
	if(rodadas >= 1){
		printf("\n1a ETAPA:\n");
		for(i=0;i<8;i++){
			int atr_p1[] = {p1->ninja->ninjutsu, p1->ninja->genjutsu,
								p1->ninja->taijutsu, p1->ninja->defesa};
			int atr_p2[] = {p2->ninja->ninjutsu, p2->ninja->genjutsu,
								p2->ninja->taijutsu, p2->ninja->defesa};

			int c_atr = atributos[i] - 1;

			char* n1 = p1->ninja->nome;
			char* n2 = p2->ninja->nome;
			printf("%s (%s %d) x %s (%s %d)\n",n1, atr_txt[c_atr], atr_p1[c_atr], 
				n2, atr_txt[c_atr], atr_p2[c_atr]);

			p1 = p1->prox;
			p2 = p2->prox;
		}
	}
	if(rodadas >= 2){
		printf("\n2a ETAPA:\n");
		for(i=8;i<12;i++){
			int atr_p1[] = {p1->ninja->ninjutsu, p1->ninja->genjutsu,
								p1->ninja->taijutsu, p1->ninja->defesa};
			int atr_p2[] = {p2->ninja->ninjutsu, p2->ninja->genjutsu,
								p2->ninja->taijutsu, p2->ninja->defesa};

			int c_atr = atributos[i] - 1;

			char* n1 = p1->ninja->nome;
			char* n2 = p2->ninja->nome;
			printf("%s (%s %d) x %s (%s %d)\n",n1, atr_txt[c_atr], atr_p1[c_atr], 
				n2, atr_txt[c_atr], atr_p2[c_atr]);
			p1 = p1->prox;
			p2 = p2->prox;
		}
	}	
	if(rodadas >= 3){
		printf("\n3a ETAPA:\n");
		for(i=12;i<14;i++){
			int atr_p1[] = {p1->ninja->ninjutsu, p1->ninja->genjutsu,
								p1->ninja->taijutsu, p1->ninja->defesa};
			int atr_p2[] = {p2->ninja->ninjutsu, p2->ninja->genjutsu,
								p2->ninja->taijutsu, p2->ninja->defesa};

			int c_atr = atributos[i] - 1;

			char* n1 = p1->ninja->nome;
			char* n2 = p2->ninja->nome;
			printf("%s (%s %d) x %s (%s %d)\n",n1, atr_txt[c_atr], atr_p1[c_atr], 
				n2, atr_txt[c_atr], atr_p2[c_atr]);
			p1 = p1->prox;
			p2 = p2->prox;
		}
	}	
	if(rodadas >= 4){
		i = 14;

		int atr_p1[] = {p1->ninja->ninjutsu, p1->ninja->genjutsu,
							p1->ninja->taijutsu, p1->ninja->defesa};
		int atr_p2[] = {p2->ninja->ninjutsu, p2->ninja->genjutsu,
							p2->ninja->taijutsu, p2->ninja->defesa};

		int c_atr = atributos[i] - 1;

		printf("\n4a ETAPA:\n");
		char* n1 = p1->ninja->nome;
		char* n2 = p2->ninja->nome;
		printf("%s (%s %d) x %s (%s %d)\n",n1, atr_txt[c_atr], atr_p1[c_atr], 
				n2, atr_txt[c_atr], atr_p2[c_atr]);

		printf("\nVENCEDOR DO TORNEIO: %s\n\n",vencedores->last->ninja->nome);
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
	int chosen_last_round = 0;
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

	setbuf(stdin, NULL);

	// Criacao a arvore com 4 niveis e insercao dos jogadores nos ultimos niveis
	t_node* raiz = tree_create();
	Ninja* player_ninja = (get_elem_at(players,n_player))->ninja;
	insert_players(raiz, players);
	free(players);

	t_lista* perdedores = list_create(); // lista dos perdedores em todas as rodadas
	t_lista* vencedores = list_create(); // lista dos vencedores em todas as rodadas
	int atributos[32]; // lista dos atributos utilizados em todas as rodadas
	for(i=0;i<32;i++) atributos[i] = 0;

	while(step <= 4){
		system("clear");
		printf("%da ETAPA\n\n", step);
		Ninja* enemy_ninja = get_enemy(raiz, player_ninja); // gera oponente do player

		show_player_char(player_ninja, enemy_ninja, chosen_last_round); 
		printf("\nSeu adversario: %s\n\n",enemy_ninja->nome);
		printf("Selecione um atributo: ");
		while(atr_player == chosen_last_round || (atr_player < 1 || atr_player > 4))
			scanf("%d",&atr_player); // leitura do atributo para a batalha

		setbuf(stdin, NULL);

		Ninja* rwinner = fight(player_ninja, enemy_ninja, atr_player); // realiza a batalha entre o player e o oponente gerado
		if(rwinner == player_ninja){ // se o player vencer
			printf("Vencedor!\n");
			printf("Pressione <ENTER> para prosseguir\n");
			getchar();

			atributos[indexOf(0, atributos, 32)] = atr_player;
			// sobe o player de nivel na arvore e realiza a luta dos outros competidores
			sobe_level(raiz, rwinner, perdedores, vencedores, atributos);
			if(step == 4){
				// se for a 4a etapa e o jogador vencer
				print_battles(perdedores, vencedores, step, atributos);
			}
		} else { // se o player perder
			printf("Derrota.\n\n");
			if(rwinner == enemy_ninja)
				atributos[indexOf(0, atributos, 32)] = atr_player;

			// sobe o oponente de nivel na arvore e realiza a luta dos outros competidores
			for(i=0;i<=(4-step);i++)
				sobe_level(raiz, enemy_ninja, perdedores, vencedores, atributos);

			// printa todas as batalhas realizadas ate a etapa atual
			print_battles(perdedores, vencedores, step, atributos);
			step = 5;
		}

		chosen_last_round = atr_player;
		step++;
	}

	printf("\nPressione <ENTER> para voltar ao menu principal\n");
	remove_lista(vencedores);
	remove_lista(perdedores);
	tree_free(raiz);

	setbuf(stdin, NULL);
	getchar();
}
