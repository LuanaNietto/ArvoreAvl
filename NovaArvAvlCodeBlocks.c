#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

//estruct do no da arvore
typedef struct no{
	int valor;
	struct no *direita, *esquerda;
}NoArv;

//Fun��o que insere os n�s na arvore
NoArv* inserir_versao1(NoArv *raiz, int valor){
	if(raiz == NULL){ //verifica se a raiz � nula
		NoArv *aux = malloc(sizeof(NoArv)); //se a raiz n�o � nula, ent�o aloca mem�ria para o novo n�
		aux->valor = valor;
		aux->esquerda = NULL;
		aux->direita = NULL;
		return aux;
	}else{
		if(valor<raiz->valor){ //verifica se o valor que ser� inserido � menor ou maior que o valor da raiz
			raiz->esquerda = inserir_versao1(raiz->esquerda, valor); //chama a fun��o recursivamente passando o valor do n� a esquerda
		}else{
			raiz->direita = inserir_versao1(raiz->direita, valor); //chama a fun��o recursivamente passando o valor do n� a direita
		}
		return raiz; //retorna a raiz
	}
}

NoArv* buscar_versao_1(NoArv *raiz, int num){
    if(raiz){ //verifica se a arvore � nula ou se ja percorreu a arvore toda
        if(num == raiz->valor)
            return raiz;
        else if (num<raiz->valor)
            return buscar_versao_1(raiz->esquerda, num);
        else
            return buscar_versao_1(raiz->direita, num);
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

int quantidade_nos(NoArv *raiz){
    if(raiz == NULL){ //verifica se a raiz � nula ou n�o
        return 0; //caso a raiz seja nula retorna zero pois n�o h� n�s
    }else
        return 1 + quantidade_nos(raiz->esquerda) + quantidade_nos(raiz->direita); /*se a raiz n�o � nula ja soma 1 por ser a raiz e depois
                                                                                   verifica as subarvores da esquerda e da direita para somar.*/
}

//imprimir de modo n�o ordenado
void imprimir_versao1(NoArv *raiz){
	if(raiz){ // verifica se a raiz � diferente de nulo
		printf("%d ", raiz->valor); //imprime o valor que est� no n�
		imprimir_versao1(raiz->esquerda); //chama recursivamente pra imprimir a esquerda
		imprimir_versao1(raiz->direita); //chama recursivamente pra imprimir a direita
	}
}
//imprimir de modo ordenado
void imprimir_versao2(NoArv *raiz){
	if(raiz){ // verifica se a raiz � diferente de nulo
		imprimir_versao2(raiz->esquerda); //chama recursivamente pra imprimir a esquerda
		printf("%d ", raiz->valor); //ap�s n�o ter mais nenhum n� a esquerda imprime o valor que est� no n�
		imprimir_versao2(raiz->direita); //chama recursivamente pra imprimir a direita
	}
}

int main(){
    setlocale(LC_ALL, "Portuguese");

	NoArv *busca, *raiz = NULL;
	int op, valor;

	do{
		printf("\n\t0- Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Buscar\n\t4 - Altura\n\t5 - Tamanho\n\t"); scanf("%d", &op);

		switch(op){
			case 1:
				printf("\n\tInforme um valor: "); scanf("%d", &valor);
				raiz = inserir_versao1(raiz, valor);
				break;
			case 2:
				printf("\n\tPrimeira Impress�o: \n");
				imprimir_versao1(raiz);
				printf("\n");
				printf("\n\tSegunda impress�o:\n");
				imprimir_versao2(raiz);
				printf("\n");
				break;
            case 3:
                printf("\n\tInforme um valor a ser buscado: "); scanf("%d", &valor);
                busca = buscar_versao_1(raiz, valor);
                if(busca)
                    printf("\n\tValor encontrado: %d\n", busca->valor);
                else
                    printf("\n\tValor n�o encontrado.\n");
                break;
            case 4:
                printf("\n\tAltura da arvore: %d\n\n", altura(raiz));
                break;
            case 5:
                printf("\n\nQuantidade de n�s: %d\n", quantidade_nos(raiz));
                break;
			default:
				if(op != 0)
					printf("\n\tOp��o invalida.");
				break;
		}
	}while(op!=0);
	raiz = inserir_versao1(raiz, 50);

	return 0;
}
