#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

//estruct do no da arvore
typedef struct no{
	int valor;
	struct no *direita, *esquerda;
	int altura;
}NoArv;

//Função que insere os nós na arvore
NoArv* inserir(NoArv *raiz, int valor){
	if(raiz == NULL){ //verifica se a raiz é nula
		return NovoNo(valor);
	}else{
		if(valor<raiz->valor){ //verifica se o valor que será inserido é menor ou maior que o valor da raiz
			raiz->esquerda = inserir(raiz->esquerda, valor); //chama a função recursivamente passando o valor do nó a esquerda
		}else{
			raiz->direita = inserir(raiz->direita, valor); //chama a função recursivamente passando o valor do nó a direita
		}
	}
	raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1; //traz a altura da arvore
		
	raiz = balancear(raiz); //faz o balanceamento da arvore logo apóe inserir pois pode ser que ao inserir um elemento a arvore fique desbalanceada.
	
	return raiz; //retorna a raiz
}

NoArv *novoNo(int valor){
    NoArv *num = malloc(sizeof(NoArv)); //se a raiz não é nula, então aloca memória para o novo nó
	if (num){
            num->valor = valor;
            num->esquerda = NULL;
            num->direita = NULL;
            num->altura = 0;
	}else
            printf("\n\t\tSem memória!\n");
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

NoArv* balancear(NoArv *raiz){
    int fb = fatorBalanc(raiz); //busca o fator de balanceamento da arvore
	
    if(fb < -1 && fatorBalanc(raiz->direita) <= 0)
	raiz = rotesq(raiz);
    else if (fb > 1 && fatorBalanc(raiz->esquerda) >= 0)
	raiz = rotdir(raiz);
    else if (fb > 1 && fatorBalanc(raiz->esquerda) < 0)
	raiz = rotesqdir(raiz);
    else if (fb < -1 && fatorBalanc(raiz->direita) > 0)
	raiz = rotdiresq(raiz);
}

NoArv* buscar(NoArv *raiz, int num){
    if(raiz){ //verifica se a arvore é nula ou se ja percorreu a arvore toda
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
    if(raiz == NULL){ //verifica se a raiz é nula ou não
        return 0; //caso a raiz seja nula retorna zero pois não há nós
    }else
        return 1 + qtd_nos(raiz->esquerda) + qtd_nos(raiz->direita); /*se a raiz não é nula ja soma 1 por ser a raiz e depois
                                                                                   verifica as subarvores da esquerda e da direita para somar.*/
}

//função para calcular quantas folhas tem na arvore
int qtd_folhas(NoArv *raiz){
    if(raiz == NULL) // se for não tiver raiz retorna 0
        return 0;
    else if (raiz->esquerda == NULL && raiz->direita == NULL) //se os dois lados do nó forem vazios, quer dizer que esse nó é um folha, então retorna 1;
        return 1;
    else
        return qtd_folhas(raiz->esquerda) + qtd_folhas(raiz->direita); // chamada recursiva para a função, passando o lado esquerdo somando com a recursão pelo lado direito.
}

//função para remover um nó folha
NoArv* remover(NoArv *raiz, int chave){
    if(raiz == NULL){
        printf("Valor nao encontrado!");
        return NULL;
    }else{
        //procura o nó que quer remover
        if(raiz->valor == chave){
            if(raiz->esquerda == NULL && raiz->direita == NULL){ //verifica se não há filhos no nó, portanto ele é uma folha e é removido.
                free(raiz); //remove o nó
                printf("Elemento folha removido %d !\n", chave);
                return NULL; //retorna nulo para o ponteiro do nó pai desse nó.
            }else{
                //Remover nó com 2 filhos
                if(raiz->esquerda != NULL && raiz->direita != NULL){ // se o ponteiro pra direita e pra esquerda do nó não for nulo quer dizer que ele tem 2 filhos.
                    if(raiz->esquerda != NULL && raiz->direita != NULL){
                        NoArv *aux = raiz->esquerda; //decidi percorrer pela esquerda
                        while(aux->direita != NULL) // enquanto tiver filho na direita do nó o aux recebe o ponteiro da direita.
                            aux = aux->direita;
                        raiz->valor = aux->valor;
                        aux->valor = chave;
                        printf("Trocado Elemento: %d !\n", chave);
                        raiz->esquerda = remover(raiz->esquerda, chave);
                        return(raiz);
                    }
                }else{ // aqui quer dizer que o nó tem um filho apenas, um dos dois ponteiros é nulo. Remover nó com 1 filho apenas
                    NoArv *aux; // crio esse ponteiro auxiliar
                    if(raiz->esquerda != NULL) //verifico se a esquerda do nó em questão não é nulo
                        aux = raiz->esquerda; // atribuo o valor da esquerda do nó em questão pro ponteiro auxiliar que criei
                    else //aqui é caso a direita do nó em questão é que tem filho
                        aux = raiz->direita; // atribuo o valor da direita do nó em questão pro ponteiro auxiliar que criei
                        printf("Elemento com 1 filho removido: %d !\n", chave);
                    free(raiz); //elimino o nó que eu queria
                    return aux; // retorno a variavel auxiliar que criei que agora aponta para o filho do nó que eu removi
                }
            }
        }else{
            if(chave < raiz->valor) // se o valor que quero remover é menor que o valor do nó q to veirificando, então vou pra esquerda
                raiz->esquerda = remover(raiz->esquerda, chave); //chama a função recursivamente percorrendo a esquerda até achar o nó que quero remover
            else // se o valor que quero remover é maior que o valor do nó q to veirificando, então vou pra direita
                raiz->direita = remover(raiz->direita, chave); // chama a função recursivamente percorrendo a direita até achar o nó que quero remover
        }
	
	raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
		
	raiz = balancear(raiz);
	    
	return raiz;
    }
}

//imprimir de modo ordenado
void imprimir(NoArv *raiz){
     if(raiz){ // verifica se a raiz é diferente de nulo
	imprimir(raiz->direita. nivel+1);
	printf("\n\n");
		
	for(int i = 0;i<nivel;i++)
	    printf("\t");
		
	printf("%d", raiz->valor);
	imprimir(raiz->esquerda, nivel + 1;
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
				printf("\n\tSegunda impressão:\n");
				imprimir(raiz);
				printf("\n");
				break;
            case 3:
                printf("\n\tInforme um valor a ser buscado: "); scanf("%d", &valor);
                busca = buscar(raiz, valor);
                if(busca)
                    printf("\n\tValor encontrado: %d\n", busca->valor);
                else
                    printf("\n\tValor não encontrado.\n");
                break;
            case 4:
                printf("\n\tAltura da arvore: %d\n\n", altura(raiz));
                break;
            case 5:
                printf("\n\nQuantidade de nós: %d\n", qtd_nos(raiz));
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
					printf("\n\tOpção invalida.");
				break;
		}
	}while(op!=0);
	raiz = inserir(raiz, 50);

	return 0;
}
