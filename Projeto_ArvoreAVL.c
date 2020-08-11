#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>


//Arvore AVL para armazenar os livros
typedef struct livro{
	char titulo[100];
	char autor[100];
	int codigo,altd,alte;
	int reserva;//A variavel 'reserva' ira receber 1 se estiver reservado e 0 se estiver disponivel
	struct livro *dir,*esq;
}livro;

//Lista de usuarios cadastrados
typedef struct usuario{
	char nome[100];
	int ID;
	int emprestimos[10];
	struct usuario *prox;
}usuario;

livro *RotacaoEsquerda(livro *aux){
	livro *aux1,*aux2;
	
	aux1 = aux->dir;
	aux2 = aux->esq;
	aux->dir = aux2;
	aux1->esq = aux;
	
	if(aux->dir == NULL)
		aux->altd = 0;
	else if(aux->dir->alte > aux->dir->altd)
		aux->altd = aux->dir->alte + 1;
	else
		aux->altd = aux->dir->alte + 1;
	
	
	if(aux1->esq->alte > aux1->esq->altd)
		aux1->alte=aux1->esq->alte + 1;
	else
		aux1->alte = aux1->esq->altd + 1;
	return(aux1);
}

livro *RotacaoDireita(livro *aux){
	livro *aux1,*aux2;
	
	aux1 = aux->esq;
	aux2 = aux1->dir;
	aux->esq = aux2;
	aux1->dir = aux;
	
	if(aux->esq == NULL)
		aux->alte = 0;
	else if(aux->esq->alte > aux->esq->altd)
		aux->alte = aux->esq->alte + 1;
	else
		aux->alte = aux->esq->altd + 1;
	
	if(aux1->dir->alte > aux1->dir->alte + 1)
		aux1->altd = aux1->dir->alte + 1;
	else
		aux1->altd = aux1->dir->altd + 1;
	
	return(aux1);
}

livro *Balanceamento(livro *aux){
	int d,df;
	d = aux->altd - aux->alte;
	if(d == 2){
		df = aux->dir->altd - aux->dir->alte;
		if(df >= 0)
			aux = RotacaoEsquerda(aux);
		else{
			aux->dir = RotacaoDireita(aux->dir);
			aux = RotacaoEsquerda(aux);
		}
	}
	else if(d == -2){
		df = aux->esq->altd - aux->esq->alte;
		if(df <= 0)
			aux = RotacaoDireita(aux);
		else{
			aux->esq = RotacaoEsquerda(aux->esq);
			aux = RotacaoDireita(aux);
		}
	}
	return(aux);
}

livro *Insere(livro *aux, int codigo){
	livro *novo;
	
	//Arvore vazia
	if(aux == NULL){
		novo = (livro*) malloc(sizeof(livro));
		fflush(stdin);
		printf("Digite o titulo do livro:\n");
		scanf("%[^\n]",novo->titulo);
		fflush(stdin);
		
		printf("Digite o nome do autor do livro:\n");
		scanf("%[^\n]",novo->autor);
		fflush(stdin);
		
		novo->codigo = codigo;
		novo->reserva = 0;
		novo->altd = 0;
		novo->alte = 0;
		novo->esq = NULL;
		novo->dir = NULL;
		aux = novo;
	}
	
	//Insere a esquerda
	else if(codigo < aux->codigo){
		aux->esq = Insere(aux->esq,codigo);
		if(aux->esq->altd > aux->esq->alte)
			aux->alte = aux->esq->altd + 1;
		else
			aux->alte = aux->esq->altd + 1;
			
		aux = Balanceamento(aux);
	}
	
	//Insere a Direita
	else{
		aux->dir = Insere(aux->dir,codigo);
		if(aux->dir->altd > aux->dir->alte)
			aux->altd = aux->dir->altd + 1;
		else
			aux->altd = aux->dir->alte + 1;
		
		aux = Balanceamento(aux);
	}
	return(aux);
}

void MostraEmOrdem(livro *aux){
	if(aux != NULL){
		MostraEmOrdem(aux->esq);
		printf("  %s\n",aux->titulo);
		MostraEmOrdem(aux->dir);
	}
}

usuario *InsereU(usuario *user){
	usuario *novo;
	int i;
	
	novo = (usuario*) malloc(sizeof(usuario));
	
	fflush(stdin);
	printf("Digite o nome do usuário:\n");
	scanf("%[^\n]",novo->nome);
	fflush(stdin);
	
	printf("Digite o número de identificação do usuário:\n");
	scanf("%d",&novo->ID);
	
	for(i=0;i<10;i++){
		novo->emprestimos[i] = 0;
	}
	
	if(user == NULL){
		user = novo;
		user->prox = NULL;
	}
	
	else{
		novo->prox = user;
		user = novo;
	}
	return user;
}

usuario *ConsultarU(usuario *user, int ID){
	
	int achou = 0;
	usuario *auxU, *auxU2;
	
	auxU = user;
	
	//Procura o usuario e um ponteiro eh apontado para ele
	while(auxU != NULL){
		if(auxU->ID == ID){
			achou = 1;
			auxU2 = auxU;
		}					
		auxU = auxU->prox;
	}
					
	if(achou == 1){
		printf("Nome: %s\n",auxU2->nome);
		printf("ID: %d\n",auxU2->ID);
		return auxU2;
	}
	else{
		printf("Usuário não encontrado.\n");	
		return NULL;
	}
		
}

int ConsultarL(livro *aux, int codigo, int achou){
	int ID;
	
	if(aux != NULL && achou == 0){
		if(aux->codigo == codigo){
			achou = 1;
			printf("Titulo: %s\n",aux->titulo);
			printf("Autor: %s\n",aux->autor);
			printf("Reservado:");
			if(aux->reserva != 0){
				printf("Sim\n");
			}
			else
				printf("Não\n");
		}
		//Procura a Esquerda
		else if(codigo < aux->codigo)
			achou = ConsultarL(aux->esq,codigo,achou);
		
		//Procura a Direita
		else
			achou = ConsultarL(aux->dir,codigo,achou);
	}
	return achou;
}

livro *Remove(livro *aux, int codigo){
	livro *aux1;
	livro *p,*p2;
	int achou = 0;

	if(aux->codigo == codigo){
		
		//Sem filhos
		if(aux->esq == aux->dir){
			free(aux);
			return NULL;		
		}
	
		//Elemento sem filho a esquerda
		else if(aux->esq == NULL){
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
		
		//Elemento tem filhos para os dois lados
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
	
	return aux;
}

livro *EmprestimoL(livro *aux, int codigo){
	
	livro *aux2;
	
	if(aux != NULL){
		if(aux->codigo == codigo){
			if(aux->reserva != 0)
				printf("Livro já está reservado.\n");
			else{
				aux->reserva = 1;
			}	
		}
		//Faz emprestimo a Esquerda
		else if(codigo < aux->codigo)
			aux2 = EmprestimoL(aux->esq,codigo);
		
		//Faz emprestimo a Direita		
		else
			aux2 = EmprestimoL(aux->dir,codigo);
	}
	
	return aux2;	
}

int MostraEmprestados(livro *aux, int achou){
	if(aux != NULL){
		MostraEmprestados(aux->esq,achou);
		
		//Livro esta reservado
		if(aux->reserva != 0){
			printf(" %s\n",aux->titulo);
			achou = 1;
		}
			
		MostraEmprestados(aux->dir,achou);
	}
	return achou;
}

livro *DevolveL(livro *aux, int codigo){
	livro *aux2;
	
	if(aux != NULL){
		if(aux->codigo == codigo){
			aux->reserva = 0;
		}	
			
		//Procura e devolve livro a esquerda
		else if(codigo < aux->codigo)
			aux2 = EmprestimoL(aux->esq,codigo);
		
		//Procura e devolve livro a direita
		else
			aux2 = EmprestimoL(aux->dir,codigo);
	}
	return aux;	
}

int main(){
	setlocale (LC_ALL, "Portuguese");
	
	int aux1 = 0, op, quant, i;
	int codAux, achou = 0, ID, achou2 = 0;
	
	livro *raiz = NULL;
	livro *aux;
	
	usuario *user = NULL;
	usuario *auxU;
	
	printf("Biblioteca\n\n");
	
	
	while(aux1 != 1){
		
		//Menu
		printf("\n\nDigite qual operação gostaria de realizar.\n");
		printf("  1-Inserir novo(s) livro(s).\n");
		printf("  2-Consultar um livro especifico.\n");
		printf("  3-Remover um livro.\n");
		printf("  4-Consultar todos os livros da biblioteca.\n");
		printf("  5-Consultar todos os livros emprestados.\n");
		printf("  6-Inserir um novo usuário.\n");
		printf("  7-Consultar livros reservados pelo usuário.\n");
		printf("  8-Fazer empréstimo de um livro:\n");
		printf("  9-Consultar um usuário.\n");
		printf("  10-Devolver um livro.\n");
		printf("  11-Limpar a tela.\n");
		printf("  0-Sair do programa.\n");
		scanf("%d",&op);
		
		switch(op){
			//Inserir livro
			case 1:{
				printf("Quantos livros gostaria de inserir?\n");
				scanf("%d",&quant);
				for(i=0;i<quant;i++){
					printf("\nDigite o codigo do (%dº) livro:\n",i+1);
					scanf("%d",&codAux);
					raiz = Insere(raiz,codAux);	
				}
				break;
			}
			
			//Consultar um livro 
			case 2:{
				if(raiz == NULL){
						printf("Biblioteca vazia\n");
					}
					else{
						printf("Digite o codigo do livro que gostaria de consultar:\n");
						scanf("%d",&codAux);
						achou = ConsultarL(raiz,codAux,achou);
						
						if(achou == 0){
							printf("Livro não encontrado.\n");
						}
					}
					achou = 0;
				break;
			}
			
			//Remover um livro
			case 3:{
				if(raiz == NULL)
						printf("Biblioteca vazia\n");
						
					else{
						printf("Digite o codigo do livro a ser removido:\n");
						scanf("%d",&codAux);
						
						//Procura o livro
						achou = ConsultarL(raiz,codAux,achou);
	
						if(achou == 0)
							printf("Livro não encontrado.\n");
	
						else
							raiz = Remove(raiz,codAux);
							
						achou = 0;
					}
				break;
			}
			
			//Consultar todos os livros
			case 4:{
				printf("Os livros disponíveis na biblioteca são:\n");
					if(raiz == NULL)
						printf("Biblioteca vazia\n");
					else
						MostraEmOrdem(raiz);
				break;
			}
			
			//Consultar os livros emprestados
			case 5:{
				printf("Os livros emprestados são:\n");
				achou = MostraEmprestados(raiz,achou);
				
				if(achou == 0)
					printf("Não há livros emprestados.\n");
				achou = 0;
				break;
			}
			
			//Inserir um novo usuario
			case 6:{
				user = InsereU(user);
				break;
			}
			
			//Consultar livros reservados por um usuario
			case 7:{
				printf("Digite o ID do usuário:\n");
				scanf("%d",&ID);
				
				auxU = user;
				
				//Recebe o usuario desejado
				auxU = ConsultarU(user,ID);
				
				printf("Os livros emprestados pelo usuário são:\n");
				achou2 = 0;
				
				//Verifica o vetor de emprestimos do usuario
				for(i=0;i<10;i++){
					if(auxU->emprestimos[i] != 0){
						achou = 0;
						codAux = auxU->emprestimos[i];
						achou = ConsultarL(raiz,codAux,achou);
						printf("\n");
					}
						
					else{
						achou2 += 1;	
					}
				}
				
				if(achou2 == 10)
					printf("O usuario não possui reservas.\n");
				
					
				achou = 0;
				break;
			}
			
			//Fazer emprestimo de um livro
			case 8:{
				printf("Digite o código do livro que gostaria de reservar:\n");
				scanf("%d",&codAux);
				
				aux = raiz;
				
				//Busca o livro
				achou = ConsultarL(aux, codAux, achou);			
				
				if(achou == 0)
					printf("Livro não encontrado\n");
					
				else{
						
					if(user == NULL)
						printf("Não é possível reservar livros pois não há usuários cadastrados.\n");
					
					else{
						printf("Digite o ID do usuário que irá reservar o livro:\n");
						scanf("%d",&ID);
							
						auxU = user;
						
						//Recebe o usuario desejado
						auxU = ConsultarU(user, ID);
							
						achou2 = 0;
						if(auxU != NULL){
							
							//Faz a reserva do livro desejado
							aux = EmprestimoL(aux,codAux);							
	
							//Faz a reserva para o usuario desejado
							for(i=0;i<10;i++){
								if(auxU->emprestimos[i] == 0 && achou2 != 1){
									auxU->emprestimos[i] = codAux;
									achou += 1;
									achou2 = 1;
								}
							}
		
							//Usuario ja possui 10 emprestimos
							if(achou == 0)
									printf("O usuário ultrapassou o limite de reservas");
								
						}
						
					}	
						
				}
				
				achou = 0;
				break;
			}
			
			//Consultar um usuario
			case 9:{
				printf("Digite o número de identificação do usuário:\n");
				scanf("%d",&ID);
				
				ConsultarU(user, ID);
				break;
			}
			
			//Devolver um livro
			case 10:{
				printf("Digite o código do livro que gostaria de devolver:\n");
				scanf("%d",&codAux);
				
				aux = raiz;
				achou = 0;
				
				//Procura livro
				achou = ConsultarL(raiz, codAux, achou);
				
				if(achou == 0)
					printf("Livro não encontrado\n");
				
				else{
					
					if(user == NULL)
						printf("Não é possível devolver livros pois não há usuários cadastrados.\n");
					
					else{
						printf("Digite o ID do usuário que irá devolver o livro:\n");
						scanf("%d",&ID);
						
						
						auxU = user;
						auxU = ConsultarU(user, ID);
						
						aux = DevolveL(aux, codAux);
						
						achou2 = 0;									
						
						for(i=0;i<10;i++){
							if(auxU->emprestimos[i] == codAux && achou2 != 1){
								auxU->emprestimos[i] = 0;
								achou2 = 1;
							}
						}
					}
				}
				achou = 0;
				break;
			}
			
			
			//Limpar a tela
			case 11:{
				system("cls");
				break;
			}
			
			//Sair do programa
			case 0:{
				aux1 = 1;
				break;
			}
			
			default:{
				aux1 = 1;
				break;
			}
			
		}
	}
}
