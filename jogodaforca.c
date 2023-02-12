#include <stdio.h>
#include <string.h>
#include "forca.h"
#include <time.h>
#include <stdlib.h>

/*variáveis globais*/
char palavrasecreta[20];
int chutesdados = 0;
char chutes[26];

void abertura(){
    printf("/*****BEM VINDO****/\n");
    printf("/****************/\n");
    printf("/* Jogo de Forca */\n");
    printf("/****************/\n\n");
}

void adicionapalavra(){

    char quer;

    printf("Voce deseja adicionar uma nova palavra? (S/N)");
    scanf(" %c", &quer);

    if(quer == 'S'){
        char novapalavra[20];
        printf("\nDigite a palavra que deseja adicionar: ");
        scanf("%s", novapalavra);

    FILE* f;

    f = fopen("palavra.txt", "r+");

    if(f == 0){
        printf("Desculpe, banco de dados nao disponivel");
        exit(1);
    }

    int qntpalavras;
    fscanf(f, "%d", &qntpalavras);

    qntpalavras++;
    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", qntpalavras);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", novapalavra);

    fclose(f);
    }
}

void escolhapalavra(){
    FILE* f;

    f = fopen("palavra.txt", "r");

    if(f == 0){
        printf("Desculpe, banco de dados nao disponivel");
        exit(1);
    }

    int qntpalavras;
    fscanf(f, "%d", &qntpalavras);

    srand(time(0));
    int randomico = rand() % qntpalavras;

    for(int i = 0; i <= randomico; i++){
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

int jachutou(char letra){
    int achou = 0;
    for (int j = 0; j < chutesdados; j++) {
        if (chutes[j] == letra) {
            achou = 1;
            break;
        }
    }
    return achou;
}

void desenhaforca(){
    
    int erros = chuteserrados();

    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");
    
    for (int i = 0; i < strlen(palavrasecreta); i++) {

        int achou = jachutou(palavrasecreta[i]);

        if (achou) {
            printf(" %c", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
    }

    printf("\n");
}

void chuta (){
    char chute;
    printf("Chute uma palavra: ");
    scanf(" %c", &chute);
    chutes[chutesdados] = chute;
    chutesdados++;

}

int chuteserrados(){
    int erros = 0;
    for(int i=0; i < chutesdados; i++){
        int existe = 0;
        for(int j = 0; j < strlen(palavrasecreta); j++){
            if(chutes[i] == palavrasecreta[j]){
                existe = 1;
                break;
            }
        }
        if(!existe) erros++;
    }
    return erros;
}

int enforcou(){
    return chuteserrados() >= 5;
}

int acertou(){
    for(int i=0; i < strlen(palavrasecreta); i++){
        if(!jachutou(palavrasecreta[i])){
            return 0;
        }
    }
    return 1;
}

int main() {

    abertura();

    escolhapalavra();
    
    do {

        desenhaforca();
        chuta();

    }while (!acertou() && !enforcou());
    if (acertou()){
        printf("Parabens!!!!!! Voce GANHOOOU!\n");
    }else{
        printf("Voce perdeu! A palavra era %s\n", palavrasecreta);
        printf("Tente novamente!");
    }
    adicionapalavra();
}

