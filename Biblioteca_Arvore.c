#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct livro{
	char titulo[100];
	char autor[100];
	int codigo;
	struct livro *esq,*dir;
}livro;

livro *Insere(livro *aux,int codigo){
	if(aux == NULL){
		aux = (livro*) malloc(sizeof(livro));
		
		fflush(stdin);
		printf("\nDigite o titulo do livro:\n");
		scanf("%[^\n]",aux->titulo);
		fflush(stdin);
		
		printf("\nDigite o autor do livro:\n");
		scanf("%[^\n]",aux->autor);
		fflush(stdin);
		
		aux->codigo = codigo;
		
		aux->esq = NULL;
		aux->dir = NULL;
	}
	else if(codigo < aux->codigo){
		aux->esq = Insere(aux->esq,codigo);
	}
	else{
		aux->dir = Insere(aux->dir,codigo);
	}
	return aux;
}

int Consulta(livro *aux, int codigoC, int encontrado){
	if(aux != NULL && encontrado == 0){
		if(aux->codigo == codigoC) encontrado = 1;
		else if(codigoC < aux->codigo)
			encontrado = Consulta(aux->esq,codigoC,encontrado);
		else
			encontrado = Consulta(aux->dir,codigoC,encontrado);	
	}
	return encontrado;
}

livro *Remove(livro *aux, int codigo){
	livro *p,*p2;
	
	if(aux->codigo == codigo){
		
		//Elemento nao possui filhos
		if(aux->esq == aux->dir){
			free(aux);
			return(NULL);
		}
		
		//Elemento sem filho a esquerda
		else if (aux->esq == NULL){
			p = aux->dir;
			free(aux);
			return(p);
		}
		
		//Elemento sem filho a direita
		else if(aux->dir == NULL){
			p = aux->esq;
			free(aux);
			return(p);
		}
		
		//Elemento tem filhos para todos os lados
		else{
			p2 = aux->dir;
			p = aux->dir;
			while(p->esq != NULL)
				p = p->esq;
			
			p->esq = aux->esq;
			free(aux);
			return(p2);
		}
	}
	else if(aux->codigo < codigo)
		aux->dir = Remove(aux->dir,codigo);
	
	else
		aux->esq = Remove(aux->esq,codigo);
	
	return(aux);
}

void ImprimeEmOrdem(livro *aux){
	if(aux != NULL){
		ImprimeEmOrdem(aux->esq);
		printf("%d",aux->codigo);
		ImprimeEmOrdem(aux->dir);
	}
}

void ImprimeEmPreOrdem(livro *aux){
	if(aux != NULL){
		printf("%d",aux->codigo);
		ImprimeEmPreOrdem(aux->esq);
		ImprimeEmPreOrdem(aux->dir);
	}
}

void ImprimeEmPosOrdem(livro *aux){
	if(aux != NULL){
		ImprimeEmPosOrdem(aux->esq);
		ImprimeEmPosOrdem(aux->dir);
		printf("%d",aux->codigo);
	}
}


int main(){
	livro *raiz = NULL;
	livro *aux;
	
	int codigo,codigoAux,encontrado=0;
	int aux1=0,op;
	
	while(aux1 != 1){
		printf("Digite qual operacao deseja realizar:\n");
		printf("	1-Inserir.\n");
		printf("	2-Consultar.\n");
		printf("	3-Remover.\n");
		printf("	4-Imprimir em ordem.\n");
		printf("	5-Imprimir em pre-ordem.\n");
		printf("	6-Imprimir em pos-ordem.\n");
		printf("	7-Fechar o programa\n");
		
		scanf("%d",&op);
		
		switch(op){
			case 1: //Insere
				printf("Digite o codigo de identificacao do livro:\n");
				scanf("%d",&codigo);
				raiz = Insere(raiz,codigo);
			break;
			
			case 2:	//Consulta 	
				if(raiz == NULL)
					printf("Nao ha livros\n");
				else{
					printf("Digite o codigo de identificacao do livro procurado:\n");
					scanf("%d",&codigoAux);
					
					encontrado = Consulta(raiz,codigoAux,encontrado);
					
					if(encontrado == 0)
						printf("Elemento nao encontrado.\n");
					else
						printf("Elemento encontrado\n");
				}
				encontrado = 0;
			break;
			
			case 3: //Remove
				if(raiz == NULL)
					printf("Arvore vazia");
				
				else{
					printf("Digite o ID do livro a ser removido:\n");
					scanf("%d",&codigoAux);
					encontrado = 0;
					
					encontrado = Consulta(raiz,codigoAux,encontrado);
					
					if(encontrado == 0)
						printf("Numero nao encontrado");
					else
						raiz = Remove(raiz,codigoAux);
				}
			
			break;
			
			case 4:
				if(raiz == NULL)
					printf("Arvore vazia");
				else
					ImprimeEmOrdem(raiz);
			break;
			
			case 5:
				if(raiz == NULL)
					printf("Arvore vazia");
					
				else 
					ImprimeEmPreOrdem(raiz);
			break;
			
			case 6:
				if(raiz == NULL)
					printf("Arvore vazia");
				else
					ImprimeEmPosOrdem(raiz);
			break;
			case 7:
				aux1 = 1;
			break;
			
			default:
				aux1 = 1;
			break;					
		}	
	}
return 0;
}

