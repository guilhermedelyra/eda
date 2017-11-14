#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define malc(x) (x *) malloc(sizeof(x))
#define nl ; printf("\n")
#define max(a, b) ((a > b) ? (a) : (b))

/* #### ESTRUTURAS DE DADOS PILHA E ARVORE #### */


typedef struct arv {
	int conteudo, h;
	struct arv *esq, *dir;
} noh; noh *raiz;


typedef struct stk {
   noh *endereco; 
   struct stk *prox;
} pilha; pilha *front, *rear;



/* #### PSEUDO-FUNÇÕES PARA MANIPULAÇÃO DE PILHA #### */


void empilha (noh * y); 
noh * desempilha ();
void liberapilha ();



/* #### PSEUDO-FUNÇÕES PARA MANIPULAÇÃO DE ARVORE BINÁRIA DE BUSCA #### */


void pre_ordem (noh * raiz);
void em_ordem (noh * raiz);
void pos_ordem (noh * raiz);
void largura ();
noh * busca (noh * raiz, int el);
void liberaraiz (noh * ra);
int height (noh * temp);
int diff (noh * temp);
noh * rr (noh * parent);
noh * ll (noh * parent);
noh * lr (noh * parent);
noh * rl (noh * parent);
noh * balance (noh * temp);
noh * insert (noh * root, int conteudo);
void set_height (noh * root, int height); 
noh * delete (noh * root, int conteudo);
noh * min_node (noh * node);

/* ############################################################# */

int main(){
	raiz = insert(raiz, 9);
    raiz = insert(raiz, 5);
    raiz = insert(raiz, 10);
    raiz = insert(raiz, 0);
    raiz = insert(raiz, 6);
    raiz = insert(raiz, 11);
    raiz = insert(raiz, -1);
    raiz = insert(raiz, 1);
    raiz = insert(raiz, 2);

	set_height (raiz, 0);

	pre_ordem (raiz) nl;
	em_ordem (raiz) nl;
	pos_ordem (raiz) nl;

	largura () nl;

	raiz = delete (raiz, 10) nl nl nl;

	pre_ordem (raiz) nl;
	em_ordem (raiz) nl;
	pos_ordem (raiz) nl;

	largura () nl;

	liberaraiz(raiz);

	return 0;
}

/* #### FUNÇÕES PARA MANIPULAÇÃO DE PILHA #### */



void empilha (noh * y) { 
	pilha *tmp = malc(pilha);
	tmp->endereco = y;
	tmp->prox = NULL;
	if (front == NULL && rear == NULL) {
		front = rear = tmp;
		return;
	}
	rear->prox = tmp;
	rear = tmp;
}


noh * desempilha () {
	if (front != NULL) {
		pilha *tmp = front;
		noh *z = tmp->endereco;
		front = front->prox;
		free(tmp);
		return z;
	} else return NULL;
}


void liberapilha () {
	while (front != NULL) {
		desempilha();
	}
}


/* ########################################### */


/* #### FUNÇÕES PARA MANIPULAÇÃO DE ARVORE BINÁRIA DE BUSCA #### */


void pre_ordem (noh * raiz) {
	if(raiz != NULL){
		printf ("%d [%d] - ", raiz->conteudo, raiz->h);
		pre_ordem (raiz->esq);
		pre_ordem (raiz->dir);
	}
}


void em_ordem (noh * raiz) {
	if(raiz != NULL){
		pre_ordem (raiz->esq);
		printf ("%d [%d] - ", raiz->conteudo, raiz->h);
		pre_ordem (raiz->dir);
	}
}


void pos_ordem (noh * raiz) {
	if(raiz != NULL){
		pre_ordem (raiz->esq);
		pre_ordem (raiz->dir);
		printf ("%d [%d] - ", raiz->conteudo, raiz->h);
	}
}


void largura () {
	noh *tmp = raiz;
	while (tmp != NULL) {
		printf ("%d [%d] - ", tmp->conteudo, tmp->h);
		if (tmp->esq != NULL) empilha (tmp->esq);
		if (tmp->dir != NULL) empilha (tmp->dir);
		tmp = desempilha ();
	}
	liberapilha (); 
}


noh * busca (noh * raiz, int el) {
	if (raiz != NULL) {
		if (raiz->conteudo > el) return busca (raiz->esq, el);
		if (raiz->conteudo < el) return busca (raiz->dir, el);
		return raiz;
	} else return NULL;
}


void liberaraiz (noh * ra) {
	if (ra == NULL) return;
	liberaraiz (ra->esq);
	liberaraiz (ra->dir);
	free (ra);	
	return;
}


void set_height (noh * root, int height) {
   if (root != NULL) {
      root->h = height;
      set_height (root->esq, height+1);
      set_height (root->dir, height+1);
   }
}


int height (noh * temp) {
    int h = 0;
    if (temp != NULL) {
        int l_height = height(temp->esq), r_height = height(temp->dir);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}


int diff (noh * temp) {
	if (temp == NULL) return 0;
    return height (temp->esq) - height (temp->dir);
}


noh * rr (noh * parent) {
    noh * temp = parent->dir;
    parent->dir = temp->esq;
    temp->esq = parent;
    return temp;
}


noh * ll (noh * parent) {
    noh * temp = parent->esq;
    parent->esq = temp->dir;
    temp->dir = parent;
    return temp;
}


noh * lr (noh * parent){
    noh * temp = parent->esq;
    parent->esq = rr (temp);
    return ll (parent);
}


noh * rl (noh *parent) {
    noh * temp;
    temp = parent->dir;
    parent->dir = ll (temp);
    return rr (parent);
}


noh * balance (noh *temp) {
    int bal_factor = diff (temp);
    if (bal_factor > 1) {
        if (diff(temp->esq) > 0) temp = ll (temp);
        else temp = lr (temp);
    } else if (bal_factor < -1) {
        if (diff(temp->dir) > 0) temp = rl (temp);
        else temp = rr (temp);
    }
    return temp;
}


noh * insert (noh * root, int conteudo) {
    if (root == NULL) {
        root = malc(noh);
        root->conteudo = conteudo;
        root->esq = NULL;
        root->dir = NULL;
        return root;
    } else if (conteudo < root->conteudo) {
        root->esq = insert (root->esq, conteudo);
        root = balance (root);
    } else if (conteudo > root->conteudo) {
        root->dir = insert(root->dir, conteudo);
        root = balance (root);
    }
    return root;
}


noh * delete (noh * root, int conteudo) {
    if (root == NULL) return root;

    if (conteudo < root->conteudo) root->esq = delete (root->esq, conteudo);
    else if (conteudo > root->conteudo) root->dir = delete (root->dir, conteudo);
    else {
        if ((root->esq == NULL) || (root->dir == NULL)) {
            noh * temp = root->esq ? root->esq : root->dir;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else *root = *temp;
            free(temp);
        } else {
            noh * temp = min_node (root->dir);
            root->conteudo = temp->conteudo;
            root->dir = delete (root->dir, temp->conteudo);
        }
    }

    if (root == NULL) return root;

    root->h = 1 + max(height (root->esq), height (root->dir));

    if (diff (root) > 1 && diff (root->esq) >= 0) return ll (root);
    if (diff (root) > 1 && diff (root->esq) < 0) return lr (root);
    if (diff (root) < -1 && diff (root->dir) <= 0) return rr (root);
    if (diff (root) < -1 && diff (root->dir) > 0) return rl (root);
    
    return root;
}

noh * min_node (noh * node) {
    noh * current = node;
    while (current->esq != NULL) current = current->esq;
    return current;
}