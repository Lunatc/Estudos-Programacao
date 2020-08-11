#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct livro{
	char titulo[100];
	char autor[100];
	int codigo;
	struct livro *prox;
}livro;

livro *inicio;
livro *fim;

livro *Inserir(livro *inicio){
	livro *novo,*fim;
	
	novo = (livro*) malloc(sizeof(livro));
	
	fflush(stdin);
	printf("\nDigite o titulo do livro:\n");
	scanf("%[^\n]",novo->titulo);
	fflush(stdin);
	
	printf("Digite o autor do livro:\n");
	scanf("%[^\n]",novo->autor);
	fflush(stdin);
	
	printf("Digite o codigo do livro:\n");
	scanf("%d",&novo->codigo);
	
	novo->prox = NULL;
	
	if(inicio == NULL){
		inicio = novo;
	}
	
	else{
		fim = inicio;
		while(fim->prox != NULL){
			fim = fim->prox;
		}
		fim->prox = novo;
	}
	return inicio;
}

void Imprime(livro *inicio,livro *aux){
	
	aux = inicio;
	
	if(inicio == NULL){
		printf("Lista vazia");
	}
	else{
		printf("Titulos disponiveis:\n");
		while(aux != NULL){
			printf("%s\n",aux->titulo);
			aux = aux->prox;
		}
		
		aux = inicio;
		
		printf("Autores disponiveis:\n");
		while(aux != NULL){
			printf("%s\n",aux->autor);
			aux = aux->prox;
		}	
	}
}

void BuscaLivro(livro *inicio,livro *aux,livro *fim){
	int livro_b;
	
	fflush(stdin);
	printf("Digite o codigo do livro a ser buscado:\n");
	scanf("%d",& livro_b);
	
	if(inicio == NULL){
		printf("Lista vazia");
	}
	else{
		aux = inicio;
		while(aux != NULL){
			if(aux->codigo == livro_b){
				printf("Livro encontrado.\n");
				printf("Titulo: %s\n",aux->titulo);
				printf("Autor: %s\n",aux->autor);
				printf("Codigo :%d\n",aux->codigo);
				aux = aux->prox;
			}
			else aux = aux->prox;
		}
	}
}

livro *Remove(livro *inicio,livro *aux,livro *fim){
	int livro_b;
	
	printf("Digite o codigo do livro a ser buscado:\n");
	scanf("%d",&livro_b);

	if(inicio == NULL){
		printf("Lista vazia");
	}
	
	else{
		aux = inicio;
		if(aux->codigo == livro_b){
			inicio = inicio->prox;
			free(aux);
		}
		else
			printf("Nao eh possivel fazer a remocao");
		
	return inicio; 
	}
}


int main(){
	int i,num_livros,opc,repetidor = 0;
	inicio = NULL;
	livro *aux;
	char resp[10];
		
	while(repetidor == 0){
		printf("\n");
		printf("Digite a operacao a ser realizada:\n\n");
		printf("	Para adicionar um livro, digite 1:\n");
		printf("	Para imprimir os titulos e autores disponiveis, digite 2:\n");
		printf("	Para verificar se um livro esta disponivel, digite 3:\n");
		printf("	Para remover um livro, digite 4:\n");
		scanf("%d",&opc);
		
		switch(opc){
			case 1:
				printf("Digite o numero de livros a serem cadastrados:\n");
				scanf("%d",&num_livros);
		
				for(i=0;i<num_livros;i++){
					inicio = Inserir(inicio);
				}
				
				break;
				
			case 2:
				Imprime(inicio,aux);
				break;
				
			case 3:
				BuscaLivro(inicio,aux,fim);	
				break;
			
			case 4:
				inicio = Remove(inicio,aux,fim);
				break;	
		}
		printf("Deseja realizar outra operacao?\n(sim/nao)");
		scanf("%s",resp);
	
		if(strcmp(resp,"sim") == 0){
			repetidor = 0;
		}
		else repetidor = 1;
	}	
		
return 0;	
}
