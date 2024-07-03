#include <stdio.h>

int main() {
    char R1, R2, R3, R4, R5;

    printf("Voce foi acusado de um crime e agora ira responder algumas perguntas\n");
    printf("Baseado em suas respostas voce passara de inocente para suspeito/cumplice/assasino\n\n");

    printf("Na ultima noite voce telefonou para a vitima? (S/N)\n\n");
    scanf(" %c", &R1);
    printf("Mas voce mora proximo da vitima? (S/N)\n\n");
    scanf(" %c", &R2);
    printf("Voce ja pegou algum dinheiro emprestado e alguma hipotese nao pode pagar a quantia e ficou devendo para a vitima? (S/N)\n\n");
    scanf(" %c", &R3);
    printf("Voce esteve no local do crime? (S/N)\n\n");
    scanf(" %c", &R4);
    printf("Certo, ultima pergunta.\n");
    printf("Voce ja trabalhou com a vitima?\n\n");
    scanf(" %c", &R5);

    int pontuacao = 0;

    // Verifica cada resposta e pontua
    if (R1 == 'S' || R1 == 'n') { // Verifica se R1 é 'S' ou 'n'
        pontuacao++;
    }
    if (R2 == 'S' || R2 == 'n') {
        pontuacao++;
    }
    if (R3 == 'S' || R3 == 'n') {
        pontuacao++;
    }
    if (R4 == 'S' || R4 == 'n') {
        pontuacao++;
    }
    if (R5 == 'S' || R5 == 'n') {
        pontuacao++;
    }

    printf("\n\nResultado final: %d/5\n", pontuacao);

    if (pontuacao == 2) {
        printf("Voce passou a ser suspeito! Agora, precisamos de mais informacoes para concluir o caso.\n");
    } else if (pontuacao > 2 && pontuacao < 5) {
        printf("Diante de suas respostas voce acabou sendo um cumplice!\n");
    } else if (pontuacao == 5) {
        printf("Apos intensos testes os resultados chegaram e constatamos que voce eh o ASSASINO!!!\n");
        printf("Diante disso, voce sera indiciado e preso ate o dia de seu julgamento por seus atos profanos.\n");
        printf("Voce tem o direito de ficar calado. Tudo o que disser pode e sera usado contra voce no tribunal.\n");
        printf("Se voce nao puder pagar por um advogado o estado te fornecera um.\n");
    } else {
        printf("Voce eh inocente!\n");
    }

    return 0;
}
