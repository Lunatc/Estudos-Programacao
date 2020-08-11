#include<string.h>
#include<stdlib.h>
#include<stdio.h>

//Funcao para declarar lista de livros
typedef struct livro{
	char titulo[100];
	char autor[100];
	struct livro *prox;
}livro;

livro *Insere(livro *l){
	livro *novo, *inicio, *fim;
	int num;

	inicio = l;
	fim = l;
	
	if(l != NULL){
		while(fim->prox != NULL){
			fim = fim->prox;
		}
	}
	else fim = l;
	if(l == NULL){
			novo = (livro*)  malloc(sizeof(livro));
			
			fflush(stdin);
			
			printf("Digite o titulo do livro:\n");
			scanf("%[^\n]",novo->titulo);
			
			fflush(stdin);
			
			printf("Digite o autor do livro:\n");
			scanf("%[^\n]",novo->autor);

			l = novo;
			novo->prox = NULL;
	}
	else{
		printf("Digite 1 para inserir no inicio e 2 para inserir no final:\n");
		scanf("%d",&num);
	
		switch(num){
			case 1://insere inicio
				novo = (livro*)  malloc(sizeof(livro));
			
				fflush(stdin);
			
				printf("Digite o titulo do livro:\n");
				scanf("%[^\n]",novo->titulo);
			
			
				fflush(stdin);
			
				printf("Digite o autor do livro:\n");
				scanf("%[^\n]",novo->autor);
				
				novo->prox = inicio;
				inicio = novo;
				return inicio;
				break;
		
			case 2://insere final
				novo = (livro*)  malloc(sizeof(livro));
				
				fflush(stdin);
				
				printf("Digite o titulo do livro:\n");
				scanf("%[^\n]",novo->titulo);
				
				fflush(stdin);
				
				printf("Digite o autor do livro:\n");
				scanf("%[^\n]",novo->autor);

				
				fim->prox = novo;
				novo->prox = NULL;
				fim = novo;
				return inicio;
				break;	
				
			default: printf("Digito incorreto\n");				
		}
	}
	
}

void Imprime(livro *l){
	livro *aux;
	
	aux = l;
	
	if(l == NULL){
		printf("Lista vazia");
	}
	else{
		printf("Titulos disponiveis:\n");
		while(aux != NULL){
			printf("%s\n",aux->titulo);
			aux = aux->prox;
		}
		
		aux = l;
		
		printf("Autores disponiveis:\n");
		while(aux != NULL){
			printf("%s\n",aux->autor);
			aux = aux->prox;
		}	
	}
}

void BuscaLivro(livro *l){
	livro *aux;
	aux = l;
	char livro_b[100];
	
	fflush(stdin);
	printf("Digite o titulo do livro a ser buscado:\n");
	scanf("%[^\n]",livro_b);
	fflush(stdin);
	
	if(l == NULL){
		printf("Lista vazia");
	}
	else{

		while(aux != NULL){
			if(strcmp(aux->titulo,livro_b) == 0){
				printf("batata");
				printf("Livro encontrado.\n");
				printf("Titulo: %s\n",aux->titulo);
				printf("Autor: %s\n",aux->autor);
				aux = aux->prox;
			}
			else aux = aux->prox;
		}
	}
}

void Remove(livro *l){
	livro *aux,*anterior;
	aux = l;
	char livro_b[100];
	
	fflush(stdin);
	printf("Digite o titulo do livro a ser buscado:\n");
	scanf("%[^\n]",livro_b);
	fflush(stdin);

	if(l == NULL){
		printf("Lista vazia");
	}
	else{
		while(aux != NULL){
			//Remocao no inicio
			if(strcmp(aux->titulo,livro_b) == 0 && aux == l){
				l = aux->prox;
				free(aux);
				aux = l;
			}
			//Remocao no meio
			else if(strcmp(aux->titulo,livro_b) == 0 && aux->prox != NULL){
				anterior->prox = aux->prox;
				free(aux);
				aux = anterior->prox;
			}
			//Remocao no final
			else if(strcmp(aux->titulo,livro_b) == 0 && aux->prox == NULL){
				anterior->prox = NULL;
				free(aux);
				aux = l;
			}
			else{
				anterior = aux;
				aux = aux->prox;
			}
		}	
	} 
}


int main(){
	int i,num_livros,opc,repetidor = 0;
	livro *l;
	char resp[10];
	l = NULL;
	
	
	
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
					l = Insere(l);
				}
				break;
				
			case 2:
				Imprime(l);
				break;
				
			case 3:
				BuscaLivro(l);	
				break;
			
			case 4:
				Remove(l);
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

