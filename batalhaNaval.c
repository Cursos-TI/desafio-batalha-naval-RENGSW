#include <stdio.h>
#include <ctype.h>

#define tab_principal 10
#define tab_ataque_linha 3
#define tab_ataque_coluna 5

void Exibir_Tabuleiro_Batalha_Naval(int tabuleiro[tab_principal][tab_principal]){

    char linha1[tab_principal] = {'A','B','C','D','E','F','G','H','I','J'};

    printf("============== Batalha Naval ===============\n\n");

    printf("___|");
    for(int i = 0; i < tab_principal; i++){
        printf("_%c_|", linha1[i]);
    }
    printf("\n");

    for(int i = 0; i < tab_principal; i++){
        if(i == 9) printf("_%d|", i+1);
        else       printf("_%d_|", i+1);

        for(int j = 0; j < tab_principal; j++){
            printf(" %d |", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void Exibir_Tabuleiros_de_Ataque(int ataque_cruz[tab_ataque_linha][tab_ataque_coluna], 
                                 int ataque_cone[tab_ataque_linha][tab_ataque_coluna], 
                                 int ataque_octaedro[tab_ataque_linha][tab_ataque_coluna]){

    printf("=========== Ataques especiais ============\n\n");

    // CRUZ
    printf("======== Cruz =======\n");
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 5; j++)
            printf(" %d |", ataque_cruz[i][j]);
        printf("\n");
    }
    printf("\n");

    // CONE
    printf("======== Cone =======\n");
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 5; j++)
            printf(" %d |", ataque_cone[i][j]);
        printf("\n");
    }
    printf("\n");

    // OCTAEDRO
    printf("====== Octaedro =====\n");
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 5; j++)
            printf(" %d |", ataque_octaedro[i][j]);
        printf("\n");
    }
    printf("\n# Use o meio do ataque como base para lançar no tabuleiro\n\n");
}


char coluna_para_letra(int c){
    return 'A' + c;
}

int letra_para_coluna(char c){
    c = toupper(c);
    if(c >= 'A' && c <= 'J') return c - 'A';
    return -1;
}


int main(){

    int tabuleiro[tab_principal][tab_principal] = {0};
    Exibir_Tabuleiro_Batalha_Naval(tabuleiro);

    char descisao = 'S';

    while(descisao == 'S'){

        int tamanho_navio;

        while(1){
            printf("Quantas casas o seu navio ocupará (1 a 5)? ");
            scanf("%d", &tamanho_navio);
            if(tamanho_navio >= 1 && tamanho_navio <= 5) break;
            printf("Tamanho inválido! Tente novamente.\n\n");
        }

        printf("\nDigite a casa (Ex: Coluna A, Linha 1)\n");

        for(int pos = 1; pos <= tamanho_navio; pos++){

            char letra_coluna;
            int linha, coluna;

            printf("\nQual a %dª casa?\n", pos);

            while(1){
                printf("Coluna: ");
                scanf(" %c", &letra_coluna);

                coluna = letra_para_coluna(letra_coluna);
                if(coluna != -1) break;

                printf("Coluna inválida!\n");
            }

            while(1){
                printf("Linha: ");
                scanf("%d", &linha);

                if(linha >= 1 && linha <= 10) break;

                printf("Linha inválida!\n");
            }

            linha -= 1;

            if(tabuleiro[linha][coluna] == 3){
                printf("Posição %c%d já ocupada! Escolha outra.\n", coluna_para_letra(coluna), linha+1);
                pos--;
                continue;
            }

            tabuleiro[linha][coluna] = 3;
            printf("Navio colocado em %c%d\n", coluna_para_letra(coluna), linha+1);
        }

        while(1){
            printf("Deseja colocar outro navio? (S/N): ");
            scanf(" %c", &descisao);
            descisao = toupper(descisao);
            if(descisao == 'S' || descisao == 'N') break;
            printf("Opção inválida!\n");
        }
    }

    Exibir_Tabuleiro_Batalha_Naval(tabuleiro);

    int ataque_cruz[3][5] = {
        {0,0,1,0,0},
        {1,1,1,1,1},
        {0,0,1,0,0}
    };
    int ataque_cone[3][5] = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {1,1,1,1,1}
    };
    int ataque_octaedro[3][5] = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {0,0,1,0,0}
    };

    char descisao_ataque = 'S';

    while(descisao_ataque == 'S'){

        Exibir_Tabuleiros_de_Ataque(ataque_cruz, ataque_cone, ataque_octaedro);

        int tipo;

        while(1){
            printf("Escolha ataque:\n1 - Cruz\n2 - Cone\n3 - Octaedro\nOpção: ");
            scanf("%d", &tipo);
            if(tipo >= 1 && tipo <= 3) break;
            printf("Opção inválida!\n");
        }

        int linha_ataque, coluna_ataque;
        char letra_coluna;

        printf("\nOnde deseja atacar?\n");

        while(1){
            printf("Coluna: ");
            scanf(" %c", &letra_coluna);

            coluna_ataque = letra_para_coluna(letra_coluna);
            if(coluna_ataque != -1) break;

            printf("Coluna inválida!\n");
        }

        while(1){
            printf("Linha: ");
            scanf("%d", &linha_ataque);
            linha_ataque -= 1;

            if(linha_ataque >= 0 && linha_ataque < 10) break;

            printf("Linha inválida!\n");
        }

        int (*ataque)[5];
        if(tipo == 1) ataque = ataque_cruz;
        else if(tipo == 2) ataque = ataque_cone;
        else ataque = ataque_octaedro;

        printf("\n===== Resultado do ataque =====\n");

        int centro_linha = 1;
        int centro_coluna = 2;

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 5; j++){

                if(ataque[i][j] == 0) continue;

                int lr = linha_ataque - centro_linha + i;
                int cr = coluna_ataque - centro_coluna + j;

                if(lr >= 0 && lr < tab_principal &&
                   cr >= 0 && cr < tab_principal){

                    char col_letra = coluna_para_letra(cr);

                    if(tabuleiro[lr][cr] == 3)
                        printf("Navio atingido em %c%d!\n", col_letra, lr+1);
                    else
                        printf("Posição %c%d vazia.\n", col_letra, lr+1);

                    tabuleiro[lr][cr] = 5;
                }
            }
        }

        printf("=================================\n");

        while(1){
            printf("Deseja atacar novamente? (S/N): ");
            scanf(" %c", &descisao_ataque);
            descisao_ataque = toupper(descisao_ataque);
            if(descisao_ataque == 'S' || descisao_ataque == 'N') break;
            printf("Opção inválida!\n");
        }
    }

    printf("\nFim do jogo!\n");
    return 0;
}