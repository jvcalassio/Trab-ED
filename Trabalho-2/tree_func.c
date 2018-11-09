#include <stdio.h>
#include <stdlib.h>

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

typedef struct node {
	//! ponteiro para o ninja contido neste no
	Ninja *ninja;
	//! ponteiro  para o elemento filho à esquerda
	struct node *left;
	//! ponteiro para o elemento filho à direita
	struct node *right;
} t_node;

t_node* node_create(){
	t_node* no = malloc(sizeof(t_node));
	no->ninja = NULL;
	no->left = NULL;
	no->right = NULL;
	return no;
}

void ger_tree(t_node* raiz, int ntotal){
	ntotal++;
	raiz->left = node_create();
	raiz->right = node_create();
	if(ntotal == 2){
		return;
	} else {
		ger_tree(raiz->left,ntotal);
		ger_tree(raiz->right,ntotal);
	}
	return;
}

t_node* tree_create(){
	t_node* raiz = node_create();
	ger_tree(raiz, 0);
	return raiz;
}

void print2DUtil(t_node *root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += 10; 
  
    // Process right child first 
    print2DUtil(root->right, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = 10; i < space; i++) 
        printf(" "); 
    printf("%d\n",space); 
  
    // Process left child 
    print2DUtil(root->left, space); 
} 

void tree_print_preorder(t_node* root){
	print2DUtil(root,0);
}

int main(){
	t_node* tree = tree_create();
	tree_print_preorder(tree);
	return 0;
}