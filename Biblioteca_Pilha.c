#include<string.h>
#include<stdlib.h>
#include<stdio.h>

//Funcao para declarar lista de livros
typedef struct livro{
	char titulo[100];
	char autor[100];
	int codigo;
	struct livro *prox;
}livro;

livro *Insere(livro *topo){
	livro *novo;
	int num;

	novo = (livro*)  malloc(sizeof(livro));
				
	fflush(stdin);
				
	printf("Digite o titulo do livro:\n");
	scanf("%[^\n]",novo->titulo);
				
	fflush(stdin);
				
	printf("Digite o autor do livro:\n");
	scanf("%[^\n]",novo->autor);
				
	printf("Digite o codigo de identificacao do livro:\n");
	scanf("%d",&novo->codigo);
				
			
	//Insere pilha vazia
	if(topo == NULL){
		topo = novo;
		novo->prox = NULL;
	}
	else{
		novo->prox = topo;
		topo = novo;		
	}
}

void Imprime(livro *topo,livro *aux){
	
	aux = topo;
	
	if(topo == NULL){
		printf("Lista vazia");
	}
	else{
		printf("Titulos disponiveis:\n");
		while(aux != NULL){
			printf("%s\n",aux->titulo);
			aux = aux->prox;
		}
		
		aux = topo;
		
		printf("Autores disponiveis:\n");
		while(aux != NULL){
			printf("%s\n",aux->autor);
			aux = aux->prox;
		}	
	}
}

void BuscaLivro(livro *topo,livro *aux){
	int livro_b;
	
	fflush(stdin);
	printf("Digite o codigo do livro a ser buscado:\n");
	scanf("%d",& livro_b);
	fflush(stdin);
	
	if(topo == NULL){
		printf("Lista vazia");
	}
	else{
		aux = topo;
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

livro *Remove(livro *topo,livro *aux){
	int livro_b;
	livro *pilhaAux = NULL;
	
	printf("Digite o codigo do livro a ser buscado:\n");
	scanf("%d",&livro_b);


	if(topo == NULL){
		printf("Lista vazia");
	}
	
	else{
		aux = topo;
		while(aux != NULL){
			if(aux->codigo == livro_b){
				topo = topo->prox;
				free(aux);
				aux = topo;
			}
		
			//Os livros sao movidos para uma pilha auxiliar se nao forem o livro buscado 
			else{
				aux = topo->prox;
				topo->prox = pilhaAux;
				pilhaAux = topo;
				topo = aux;	
			}
		}
		
		//Reorganiza a pilha original
		while(pilhaAux != NULL){
			aux = pilhaAux;
			pilhaAux = pilhaAux->prox;
			aux->prox = topo;
			topo = aux;
		}	
	}
	return topo; 
}


int main(){
	int i,num_livros,opc,repetidor = 0;
	livro *topo = NULL;
	livro *aux;
	char resp[10];
	topo = NULL;
		
	while(repetidor == 0){
		printf("\n");
		printf("Digite a operacao a ser realizada:\n");
		printf("Para adicionar um livro, digite 1:\n");
		printf("Para imprimir os titulos e autores disponiveis, digite 2:\n");
		printf("Para verificar se um livro esta disponivel, digite 3:\n");
		printf("Para remover um livro, digite 4:\n");
		scanf("%d",&opc);
		
		switch(opc){
			case 1:
				printf("Digite o numero de livros a serem cadastrados:\n");
				scanf("%d",& num_livros);
		
				for(i=0;i<num_livros;i++){
					topo = Insere(topo);
				}
				break;
				
			case 2:
				Imprime(topo,aux);
				break;
				
			case 3:
				BuscaLivro(topo,aux);	
				break;
			
			case 4:
				topo = Remove(topo,aux);
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
