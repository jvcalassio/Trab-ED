/**
 * @file functions.c
 * @brief Implementacao das funcoes principais
 * Implementacao de funcoes definidas no arquivo functions.h\n
 * Funcoes para a realizacao do jogo
 * @author Joao Victor
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "functions.h"

/**
 * Verifica a existencia de um numero em um vetor de inteiros\n
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
 * Mostra a lista dos personagens escolhidos do arquivo\n
 * Mostra apenas um atributo, escolhido aleatoriamente, para cada personagem
 * @param lista lista dos personagens
 */
void print_participants(t_lista* lista){
	int s = lista->qtd, i;
	t_elem_lista* temp = lista->first;
	printf(C_YELLOW "Escolha seu personagem:\n\n" C_DEFAULT);
	for(i=1;i<=s;i++){
		printf(C_L_BLUE "Personagem " C_BLUE "%d" C_DEFAULT":\n",i);
		int toshow = rand()%4+1; /* gera o atributo, aleatoriamente */
		int chosen_atr_val;

		char ninval[4] = "??";
		char genval[4] = "??";
		char taival[4] = "??";
		char defval[4] = "??";

		char *str = malloc(4);

		/* verifica qual atributo foi escolhido, e troca os '??' pelo valor */
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
 * Inicializa o jogo:\n
 * Le o arquivo ninjas.txt, sorteia os 16 jogadores e os insere na lista
 * @param players lista de todos os competidores
 * @param f arquivo de texto ninjas.txt
 */
void init(t_lista* players, FILE* f){
	int i;
	int j = 1;
	int qtd_l = 0;
	char nome[32], elemento[10];
	int chosen_nums[16];
	int ninjutsu, genjutsu, taijutsu, defesa;

	/*	verifica o tamanho maximo da lista dos ninjas
	 *	torna flexivel a quantidade de ninjas, independente do arquivo de entrada
	 */
	while(fscanf(f, " %*[^,], %*[^,], %*d, %*d, %*d, %*d") != EOF){
		qtd_l++;
	}
	rewind(f);

	for(i=0;i<16;i++)
		chosen_nums[i] = -1;

	/* sorteia 16 numeros diferentes em [1, 32] */
	for(i=0;i<16;i++){
		int k = rand()%qtd_l+1;
		while(indexOf(k, chosen_nums, 16)!=-1){
			k = rand()%qtd_l+1;
		}
		chosen_nums[i] = k;
	}

	/* salva os escolhidos na lista */
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
		if(i==index){
			return aux;
		}
		aux = aux->prox;
	}
}

/** 
 * Realizas comparacoes entre elementos\n
 * Retorna  1 se elem1 ganhar\n
 * Retorna -1 se elem2 ganhar\n
 * Retorna 0 se empatar ou os elementos nao forem adjacentes\n
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
 * Realiza a 'luta' entre dois ninjas, comparando o atributo desejado.\n
 * Retorna o ponteiro para o ninja vencedor\n
 * @param ninja_one primeiro ninja
 * @param ninja_two segundo ninja
 * @param attribute atributo a ser comparado para definir o vencedor
 */ 
Ninja* fight(Ninja* ninja_one, Ninja* ninja_two, int attribute){
	/* atributos do ninja 1 */
	int nj1[] = {0, ninja_one->ninjutsu, ninja_one->genjutsu,
				 ninja_one->taijutsu, ninja_one->defesa};
	/* atributos do ninja 2 */
	int nj2[] = {0, ninja_two->ninjutsu, ninja_two->genjutsu,
				 ninja_two->taijutsu, ninja_two->defesa};

	if(nj2[attribute] > nj1[attribute]){
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
	printf("Seu personagem: " C_BOLD "%s\n" "\e[0m",n->nome);
	
	/* verifica a supremacia (ou inferioridade) elemental */
	int beat = elem_beat(n->elemento, enemy->elemento);
	if(beat == 1){
		printf(C_GREEN "SUPREMACIA ELEMENTAL: " C_DEFAULT "%s > %s\n", n->elemento, enemy->elemento);
		printf(C_GREEN "Todos os atributos foram multiplicados por x1.2\n" C_DEFAULT);
		ninjutsu *= 1.2;
		genjutsu *= 1.2;
		taijutsu *= 1.2;
		defesa *= 1.2;
	} else if(beat == -1){
		printf(C_RED "INFERIORIDADE ELEMENTAL: " C_DEFAULT "%s < %s\n", n->elemento, enemy->elemento);
		printf(C_RED "Todos os atributos foram multiplicados por x0.8\n" C_DEFAULT);
		ninjutsu *= 0.8;
		genjutsu *= 0.8;
		taijutsu *= 0.8;
		defesa *= 0.8;
	}

	/* strings dos atributos do player */
	char str1[30]; sprintf(str1, C_BLUE "1)" C_DEFAULT " Ninjutsu : %d",ninjutsu);
	char str2[30]; sprintf(str2, C_BLUE "2)" C_DEFAULT " Genjutsu : %d",genjutsu);;
	char str3[30]; sprintf(str3, C_BLUE "3)" C_DEFAULT " Taijutsu : %d",taijutsu);;
	char str4[30]; sprintf(str4, C_BLUE "4)" C_DEFAULT " Defesa : %d",defesa);;

	/* troca o texto caso o atributo nao seja permitido na rodada */
	if(chosen_last_round == 1)
		strcpy(str1,C_ROXO "X) XXXXX : XX" C_DEFAULT);
	else if(chosen_last_round == 2)
		strcpy(str2,C_ROXO "X) XXXXX : XX" C_DEFAULT);
	else if(chosen_last_round == 3)
		strcpy(str3,C_ROXO "X) XXXXX : XX" C_DEFAULT);
	else if(chosen_last_round == 4)
		strcpy(str4,C_ROXO "X) XXXXX : XX" C_DEFAULT);

	printf("%s\n", str1);
	printf("%s\n", str2);
	printf("%s\n", str3);
	printf("%s\n", str4);
}

/**
 * Troca dois Ninjas de lugar na lista\n
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
 * Reorganiza os elementos da lista\n
 * Do contrario, o jogador poderia decorar a ordem que os personagens geralmente aparecem\n
 * Baseado no algoritmo Fisher-Yates shuffle
 * @param lista lista a ser reorganizada
 */
void shuffle_list(t_lista* lista){
	int s = lista->qtd, i, j;
	for(i=s-1;i>0;i--){
		j = rand()%i+1;
		if(j != i)
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
			free(l); /* libera os elementos da lista de players original */
		}
		players->qtd--;
	} else {
		insert_players(raiz->left, players);
		insert_players(raiz->right, players);
	}
}

/**
 * Percorre a arvore e verifica o oponente do player\n
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
		/* retorna o ninja inimigo. se t = null, volta na recursao e vai para o proximo no */
		return t;
	}
}

/**
 * Faz o jogador (ou o oponente do jogador) subir na arvore, se ganhar\n
 * Realiza a batalha dos outros personagens, e tambem faz avancar quem ganha
 * @param raiz raiz da arvore
 * @param p_winner quem ganhou no round do jogador
 * @param atr_player atributo utilizado no round do jogador
 * @param vencedores lista dos personagens que ganharam ate entao
 * @param perdedeores lista dos personagens que perderam ate entao
 * @param atributos vetor dos atributos utilizados nas batalhas
 */
t_node* sobe_level(t_node* raiz, Ninja* p_winner, int atr_player, t_lista* perdedores, t_lista* vencedores, int *atributos){
	if(raiz->left == NULL && raiz->right == NULL){
		return NULL;
	} else {
		t_node* l1 = sobe_level(raiz->left, p_winner, atr_player, perdedores, vencedores, atributos); /* chamada recursiva esquerda */
		t_node* l2 = sobe_level(raiz->right, p_winner, atr_player, perdedores, vencedores, atributos); /* chamada recursiva direita */
		if(l1 == NULL && l2 == NULL){
			/* caso o no seja o do player ou o de seu oponente
			   nao realiza a batalha novamente */
			if(raiz->left->ninja == p_winner || raiz->right->ninja == p_winner){
				raiz->ninja = p_winner;
				list_insert(vencedores, p_winner); /* insere nos vencedores */

				/* insere o atributo utilizado */
				atributos[indexOf(0, atributos, 32)] = atr_player;

				Ninja* p_loser;
				if(raiz->left->ninja == p_winner){
					p_loser = raiz->right->ninja;
				} else if(raiz->right->ninja == p_winner){
					p_loser = raiz->left->ninja;
				}
				list_insert(perdedores, p_loser); /* insere nos perdedores */

				free(raiz->left);
				free(raiz->right);
				raiz->left = NULL;
				raiz->right = NULL;
			} else { /* caso o no seja dos outros competidores */
				int atr = rand()%4 + 1;
				/* realiza a luta dos competidores com atributo escolhido aleatoriamente */
				Ninja* t = fight(raiz->left->ninja, raiz->right->ninja, atr);

				/* insere o atributo utilizado */
				atributos[indexOf(0, atributos, 32)] = atr;

				raiz->ninja = t;
				list_insert(vencedores, t); /* insere nos vencedores */

				Ninja* p_loser;
				if(raiz->left->ninja == t){
					p_loser = raiz->right->ninja;
				} else if(raiz->right->ninja == t){
					p_loser = raiz->left->ninja;
				}
				list_insert(perdedores, p_loser); /* insere nos perdedores */

				free(raiz->left);
				free(raiz->right);
				raiz->left = NULL;
				raiz->right = NULL;
			}
		}
	}
}

/** 
 * Printa uma unica batalha ocorrida\n
 * Funcao auxiliar da funcao print_battles
 * @param p1 player ganhador da batalha
 * @param p2 player perdedor da batalha
 * @param c_atr atributo utilizado na batalha
 * @param player_ninja ninja do player (para mostrar comparacao elemental)
 */
void print_single_battle(t_elem_lista* p1, t_elem_lista* p2, int c_atr, Ninja* player_ninja){
	char atr_txt[4][9] = {"Ninjutsu", "Genjutsu", "Taijutsu", "Defesa"};

	/* atributos de combate dos ninjas */
	int atr_p1[] = {p1->ninja->ninjutsu, p1->ninja->genjutsu,
						p1->ninja->taijutsu, p1->ninja->defesa};
	int atr_p2[] = {p2->ninja->ninjutsu, p2->ninja->genjutsu,
						p2->ninja->taijutsu, p2->ninja->defesa};

	/* verifica se o player jogou nessa rodada ou nao, e a supremacia */
	int is_player = 0, p1_supr = elem_beat(p1->ninja->elemento, p2->ninja->elemento);
	if(p1->ninja == player_ninja)
		is_player = 1;
	else if(p2->ninja == player_ninja)
		is_player = 2;

	/* multiplicadores */
	float mulp1 = 1;
	float mulp2 = 1;

	if(is_player == 1){
		/* se o p1 for o player, seta a supremacia */
		if(p1_supr == 1)
			mulp1 = 1.2;
		else if(p1_supr == -1)
			mulp1 = 0.8;
	} else if(is_player == 2){
		if(p1_supr == 1)
			mulp2 = 0.8;
		else if(p1_supr == -1)
			mulp2 = 1.2;
	}

	char* n1 = p1->ninja->nome;
	char* n2 = p2->ninja->nome;

	if(is_player != 0)
		printf(C_BOLD);

	printf("%s (%s %d) x %s (%s %d) ",n1, atr_txt[c_atr], (int) (atr_p1[c_atr]*mulp1), 
		n2, atr_txt[c_atr], (int) (atr_p2[c_atr]*mulp2));

	if(is_player != 0)
		printf(C_DEFAULT);
	/* printa supremacia elemental, se houver e for o player */
	if(is_player == 1 && p1_supr != 0)
		printf(C_BOLD "[x%.1f]" C_DEFAULT,mulp1);
	else if(is_player == 2 && p1_supr != 0)
		printf(C_BOLD "[x%.1f]" C_DEFAULT,mulp2);

	printf("\n");
}

/** 
 * Printa todas as batalhas ocorridas no jogo
 * @param perdedores lista com os ninjas perdedores
 * @param vencedores lista com os ninjas vencedores
 * @param rodadas ate qual rodada printar
 * @param atributos vetor dos atributos utilizados nas batalhas
 */
void print_battles(t_lista* perdedores, t_lista* vencedores, int rodadas, int *atributos, Ninja* player_ninja){
	t_elem_lista* p1 = vencedores->first;
	t_elem_lista* p2 = perdedores->first;

	int i;
	/*
	 	Printa todas as batalhas
	 	Vencedor x Perdedor
	 */
	if(rodadas >= 1){
		printf(C_YELLOW "\n1a ETAPA:\n" C_DEFAULT);
		for(i=0;i<8;i++){
			int c_atr = atributos[i] - 1;
			print_single_battle(p1,p2,c_atr,player_ninja);

			p1 = p1->prox;
			p2 = p2->prox;
		}
	}
	if(rodadas >= 2){
		printf(C_YELLOW "\n2a ETAPA:\n" C_DEFAULT);
		for(i=8;i<12;i++){
			int c_atr = atributos[i] - 1;
			print_single_battle(p1,p2,c_atr,player_ninja);

			p1 = p1->prox;
			p2 = p2->prox;
		}
	}	
	if(rodadas >= 3){
		printf(C_YELLOW "\n3a ETAPA:\n" C_DEFAULT);
		for(i=12;i<14;i++){
			int c_atr = atributos[i] - 1;
			print_single_battle(p1,p2,c_atr,player_ninja);

			p1 = p1->prox;
			p2 = p2->prox;
		}
	}	
	if(rodadas >= 4){
		printf(C_YELLOW "\n4a ETAPA:\n" C_DEFAULT);
		int c_atr = atributos[14] - 1;
		print_single_battle(p1,p2,c_atr,player_ninja);

		printf(C_YELLOW "\nVENCEDOR DO TORNEIO: " C_BOLD "%s\n\n" C_DEFAULT,vencedores->last->ninja->nome);
	}	
}

/**
 * Funcao principal de jogo\n
 * Retorna 1 se o jogador escolher voltar ao menu, ou 2 se escolher sair do jogo
 */
int start(){
	system("clear");
	system("clear");
	FILE* f = fopen("ninjas.txt","r");
	int i, n_player = 0, atr_player = 0;
	int chosen_last_round = 0;
	int step = 1;
	t_lista* players = list_create();


	if(f==NULL)
		return; /* se arquivo nao existe/erro na leitura */

	/* Pega os jogadores do arquivo, e insere 16 aleatoriamente na lista */
	init(players, f);
	fclose(f);

	/* Reorganiza os ninjas na lista. para diversificar as batalhas possiveis */
	shuffle_list(players);	

	/* Printa para o jogador cada um dos escolhidos, mostrando somente um atributo cada */
	print_participants(players);
	/* Escolha do jogador */
	while(n_player < 1 || n_player > 16)
		scanf("%d",&n_player);

	setbuf(stdin, NULL);

	/* Criacao a arvore com 4 niveis e insercao dos jogadores nos ultimos niveis */
	t_node* raiz = tree_create();
	Ninja* player_ninja = (get_elem_at(players,n_player))->ninja;
	insert_players(raiz, players);
	free(players);

	t_lista* perdedores = list_create(); /* lista dos perdedores em todas as rodadas */
	t_lista* vencedores = list_create(); /* lista dos vencedores em todas as rodadas */
	int atributos[32]; /* lista dos atributos utilizados em todas as rodadas */
	for(i=0;i<32;i++) atributos[i] = 0;

	while(step <= 4){
		system("clear");
		printf(C_YELLOW "%da ETAPA\n\n" C_DEFAULT, step);
		Ninja* enemy_ninja = get_enemy(raiz, player_ninja); /* gera oponente do player */

		show_player_char(player_ninja, enemy_ninja, chosen_last_round); 
		printf("\nSeu adversario: " C_BOLD "%s\n\n" C_DEFAULT,enemy_ninja->nome);
		printf(C_L_BLUE "Selecione um atributo: " C_DEFAULT);
		while(atr_player == chosen_last_round || (atr_player < 1 || atr_player > 4))
			scanf("%d",&atr_player); /* leitura do atributo para a batalha */

		setbuf(stdin, NULL);

		/* se o player tiver superioridade elemental contra o oponente, seta o mul */
		float mul = 1.0;
		int v_elem = elem_beat(player_ninja->elemento, enemy_ninja->elemento);
		if(v_elem == 1)
			mul = 1.2;
		else if(v_elem == -1)
			mul = 0.8;

		/* modifica temporariamente o valor dos atributo escolhido do player, se superior ou inferior */
		int temp_elem;
		switch(atr_player){
			case 1:
				temp_elem = player_ninja->ninjutsu;
				player_ninja->ninjutsu = (int) temp_elem * mul;
				break;
			case 2:
				temp_elem = player_ninja->genjutsu;
				player_ninja->genjutsu = (int) temp_elem * mul;
				break;
			case 3:
				temp_elem = player_ninja->taijutsu;
				player_ninja->taijutsu = (int) temp_elem * mul;
				break;
			case 4:
				temp_elem = player_ninja->defesa;
				player_ninja->defesa = (int) temp_elem * mul;
				break;
		}

		/* retorna o vencedor da batalha do player */
		Ninja* rwinner = fight(player_ninja, enemy_ninja, atr_player); /* realiza a batalha entre o player e o oponente gerado */

		/* retorna o valor do atributo do player para o padrao */
		switch(atr_player){
			case 1:
				player_ninja->ninjutsu = temp_elem;
				break;
			case 2:
				player_ninja->genjutsu = temp_elem;
				break;
			case 3:
				player_ninja->taijutsu = temp_elem;
				break;
			case 4:
				player_ninja->defesa = temp_elem;
				break;
		}

		if(rwinner == player_ninja){ /* se o player vencer */
			printf(C_GREEN "VENCEDOR!\n\n" C_DEFAULT);
			printf("Pressione " C_BLUE "<ENTER>" C_DEFAULT " para prosseguir\n");
			getchar();

			/* sobe o player de nivel na arvore e realiza a luta dos outros competidores */
			sobe_level(raiz, rwinner, atr_player, perdedores, vencedores, atributos);
			if(step == 4){
				/* se for a 4a etapa e o jogador vencer */
				print_battles(perdedores, vencedores, step, atributos, player_ninja);
			}
		} else { /* se o player perder */
			printf(C_RED "DERROTA.\n\n" C_DEFAULT);

			/* sobe o oponente de nivel na arvore e realiza a luta dos outros competidores */
			sobe_level(raiz, enemy_ninja, atr_player, perdedores, vencedores, atributos);

			/* printa todas as batalhas realizadas ate a etapa atual */
			print_battles(perdedores, vencedores, step, atributos, player_ninja);
			step = 5;
		}

		chosen_last_round = atr_player;
		step++;
	}

	printf("\n" C_BLUE "1)" C_DEFAULT " Voltar ao menu principal\n");
	printf(C_BLUE "2)" C_DEFAULT " Sair\n");
	remove_lista(vencedores);
	remove_lista(perdedores);
	tree_free(raiz);

	int btn_escolha;
	setbuf(stdin, NULL);
	scanf("%d",&btn_escolha);
	return btn_escolha;
}