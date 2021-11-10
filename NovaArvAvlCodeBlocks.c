#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

//estruct do no da arvore
typedef struct no{
	int valor;
	struct no *direita, *esquerda;
	int altura;
}NoArv;

//Fun��o que insere os n�s na arvore
NoArv* inserir(NoArv *raiz, int valor){
	if(raiz == NULL){ //verifica se a raiz � nula
		NoArv *aux = malloc(sizeof(NoArv)); //se a raiz n�o � nula, ent�o aloca mem�ria para o novo n�
		aux->valor = valor;
		aux->esquerda = NULL;
		aux->direita = NULL;
		return aux;
	}else{
		if(valor<raiz->valor){ //verifica se o valor que ser� inserido � menor ou maior que o valor da raiz
			raiz->esquerda = inserir(raiz->esquerda, valor); //chama a fun��o recursivamente passando o valor do n� a esquerda
		}else{
			raiz->direita = inserir(raiz->direita, valor); //chama a fun��o recursivamente passando o valor do n� a direita
		}
		return raiz; //retorna a raiz
	}
}

NoArv *novoNo(int valor){
    NoArv *num = malloc(sizeof(NoArv)); //se a raiz n�o � nula, ent�o aloca mem�ria para o novo n�
		if (num){
            num->valor = valor;
            num->esquerda = NULL;
            num->direita = NULL;
            num->altura = 0;
		}else
            printf("\n\t\tSem mem�ria!\n");
		return valor;
}

int maior(int a, int b){
    return a>b ? a: b;
}

int alturaNo(NoArv *No){
    if(No ==NULL)
        return -1;
    else
        return No->altura;
}

int fatorBalanc(NoArv *No){
    if(No)
        return (alturaNo(No->esquerda) - alturaNo(No->direita));
    else
        return 0;
}

NoArv* buscar(NoArv *raiz, int num){
    if(raiz){ //verifica se a arvore � nula ou se ja percorreu a arvore toda
        if(num == raiz->valor)
            return raiz;
        else if (num<raiz->valor)
            return buscar(raiz->esquerda, num);
        else
            return buscar(raiz->direita, num);
    }
    return NULL;
}

int altura(NoArv *raiz){
    if(raiz == NULL){
        return -1;
    }
    else{
        int esq = altura(raiz->esquerda);
        int dir = altura(raiz->direita);
        if(esq>dir)
            return esq+1;
        else
            return dir+1;
    }
}

int qtd_nos(NoArv *raiz){
    if(raiz == NULL){ //verifica se a raiz � nula ou n�o
        return 0; //caso a raiz seja nula retorna zero pois n�o h� n�s
    }else
        return 1 + qtd_nos(raiz->esquerda) + qtd_nos(raiz->direita); /*se a raiz n�o � nula ja soma 1 por ser a raiz e depois
                                                                                   verifica as subarvores da esquerda e da direita para somar.*/
}

//fun��o para calcular quantas folhas tem na arvore
int qtd_folhas(NoArv *raiz){
    if(raiz == NULL) // se for n�o tiver raiz retorna 0
        return 0;
    else if (raiz->esquerda == NULL && raiz->direita == NULL) //se os dois lados do n� forem vazios, quer dizer que esse n� � um folha, ent�o retorna 1;
        return 1;
    else
        return qtd_folhas(raiz->esquerda) + qtd_folhas(raiz->direita); // chamada recursiva para a fun��o, passando o lado esquerdo somando com a recurs�o pelo lado direito.
}

//fun��o para remover um n� folha
NoArv* remover(NoArv *raiz, int chave){
    if(raiz == NULL){
        printf("Valor nao encontrado!");
        return NULL;
    }else{
        //procura o n� que quer remover
        if(raiz->valor == chave){
            if(raiz->esquerda == NULL && raiz->direita == NULL){ //verifica se n�o h� filhos no n�, portanto ele � uma folha e � removido.
                free(raiz); //remove o n�
                printf("Elemento folha removido %d !\n", chave);
                return NULL; //retorna nulo para o ponteiro do n� pai desse n�.
            }else{
                //Remover n� com 2 filhos
                if(raiz->esquerda != NULL && raiz->direita != NULL){ // se o ponteiro pra direita e pra esquerda do n� n�o for nulo quer dizer que ele tem 2 filhos.
                    if(raiz->esquerda != NULL && raiz->direita != NULL){
                        NoArv *aux = raiz->esquerda; //decidi percorrer pela esquerda
                        while(aux->direita != NULL) // enquanto tiver filho na direita do n� o aux recebe o ponteiro da direita.
                            aux = aux->direita;
                        raiz->valor = aux->valor;
                        aux->valor = chave;
                        printf("Trocado Elemento: %d !\n", chave);
                        raiz->esquerda = remover(raiz->esquerda, chave);
                        return(raiz);
                    }
                }else{ // aqui quer dizer que o n� tem um filho apenas, um dos dois ponteiros � nulo. Remover n� com 1 filho apenas
                    NoArv *aux; // crio esse ponteiro auxiliar
                    if(raiz->esquerda != NULL) //verifico se a esquerda do n� em quest�o n�o � nulo
                        aux = raiz->esquerda; // atribuo o valor da esquerda do n� em quest�o pro ponteiro auxiliar que criei
                    else //aqui � caso a direita do n� em quest�o � que tem filho
                        aux = raiz->direita; // atribuo o valor da direita do n� em quest�o pro ponteiro auxiliar que criei
                        printf("Elemento com 1 filho removido: %d !\n", chave);
                    free(raiz); //elimino o n� que eu queria
                    return aux; // retorno a variavel auxiliar que criei que agora aponta para o filho do n� que eu removi
                }
            }
        }else{
            if(chave < raiz->valor) // se o valor que quero remover � menor que o valor do n� q to veirificando, ent�o vou pra esquerda
                raiz->esquerda = remover(raiz->esquerda, chave); //chama a fun��o recursivamente percorrendo a esquerda at� achar o n� que quero remover
            else // se o valor que quero remover � maior que o valor do n� q to veirificando, ent�o vou pra direita
                raiz->direita = remover(raiz->direita, chave); // chama a fun��o recursivamente percorrendo a direita at� achar o n� que quero remover
            return raiz;
        }
    }
}

//imprimir de modo ordenado
void imprimir(NoArv *raiz){
	if(raiz){ // verifica se a raiz � diferente de nulo
		imprimir(raiz->esquerda); //chama recursivamente pra imprimir a esquerda
		printf("%d ", raiz->valor); //ap�s n�o ter mais nenhum n� a esquerda imprime o valor que est� no n�
		imprimir(raiz->direita); //chama recursivamente pra imprimir a direita
	}
}

int main(){
    setlocale(LC_ALL, "Portuguese");

	NoArv *busca, *raiz = NULL;
	int op, valor;

	do{
		printf("\n\t0- Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Buscar\n\t4 - Altura\n\t5 - Tamanho\n\t6 - Folhas\n\t7 - Remover Folha\n\t"); scanf("%d", &op);

		switch(op){
			case 1:
				printf("\n\tInforme um valor: "); scanf("%d", &valor);
				raiz = inserir(raiz, valor);
				break;
			case 2:
				printf("\n\tSegunda impress�o:\n");
				imprimir(raiz);
				printf("\n");
				break;
            case 3:
                printf("\n\tInforme um valor a ser buscado: "); scanf("%d", &valor);
                busca = buscar(raiz, valor);
                if(busca)
                    printf("\n\tValor encontrado: %d\n", busca->valor);
                else
                    printf("\n\tValor n�o encontrado.\n");
                break;
            case 4:
                printf("\n\tAltura da arvore: %d\n\n", altura(raiz));
                break;
            case 5:
                printf("\n\nQuantidade de n�s: %d\n", qtd_nos(raiz));
                break;
            case 6:
                printf("\n\n\t Quantidade de folhas: %d\n", qtd_folhas(raiz));
                break;
            case 7:
                printf("\t");
                imprimir(raiz);
                printf("\n\tDigite o valor a ser removido: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                break;
			default:
				if(op != 0)
					printf("\n\tOp��o invalida.");
				break;
		}
	}while(op!=0);
	raiz = inserir(raiz, 50);

	return 0;
}
