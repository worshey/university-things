#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <Windows.h>  // Gustavo: Foi a unica biblioteca que funcionou o ' ~ ' obg lanera isabelation tmj so progresso cria

// Gustavo: Definindo nmro de perguntas, tentativas e o total de jogadores que apareceram no ranking

#define NUM_PERGUNTAS  20
#define MAX_TENTATIVAS 2
#define MAX_JOGADORES 5

// Gustavo: Definição das estruturas para Perguntas e Jogadores

typedef struct {
    char pergunta[256];      // Texto da pergunta
    char opcoes[4][256];     // Opções de resposta (A, B, C, D)
    char resposta_correta;   // Letra da resposta correta
} Pergunta;

typedef struct {
    char nome[50];           // Nome do jogador
    int pontuacao;           // Pontuação do jogador
} Jogador;

Jogador ranking[MAX_JOGADORES];
int num_jogadores = 0;

//  Gustavo: Função para limpar a tela, adaptada para diferentes sistemas operacionais ps: deixando so o system cls o codigo n compilava???
void limpar_tela() {
    #ifdef _WIN32
        system("cls");       // Gustavo: p windows
    #else
        system("clear");     // Gustavo: p Linux/Mac
    #endif
}

// Gustavo: Função para embaralhar as perguntas usando o algoritmo de Fisher-Yates
void embaralhar_perguntas(Pergunta perguntas[], int num_perguntas) {
    for (int i = 0; i < num_perguntas; i++) {
        int j = rand() % num_perguntas;
        Pergunta temp = perguntas[i];
        perguntas[i] = perguntas[j];
        perguntas[j] = temp;
    }
}

// Gustavo: Função para ler e validar a resposta do usuário
char ler_resposta() {
    char resposta;
    do {
        printf("Digite a letra da sua resposta (A, B, C, D): ");
        scanf(" %c", &resposta);
        resposta = toupper(resposta); // Converte a resposta para maiúscula usando o toupper
    } while (resposta < 'A' || resposta > 'D'); // Garante que a resposta é válida
    return resposta;
}

// Gustavo: Função para exibir o ranking dos jogadores
void exibir_ranking() {
    printf("\n========== Ranking ==========\n");
    for (int i = 0; i < num_jogadores; i++) {
        printf("%d. %s - %d pontos\n", i + 1, ranking[i].nome, ranking[i].pontuacao);
    }
    printf("=============================\n");
}

//Gustavo:  Função para adicionar o jogador ao ranking, substituindo o jogador com menor pontuação, se necessário
void adicionar_ao_ranking(char nome[], int pontuacao) {
    if (num_jogadores < MAX_JOGADORES) {
        strcpy(ranking[num_jogadores].nome, nome);
        ranking[num_jogadores].pontuacao = pontuacao;
        num_jogadores++;
    } else {
        int menor_indice = 0;
        for (int i = 1; i < MAX_JOGADORES; i++) {
            if (ranking[i].pontuacao < ranking[menor_indice].pontuacao) {
                menor_indice = i;
            }
        }
        if (pontuacao > ranking[menor_indice].pontuacao) {
            strcpy(ranking[menor_indice].nome, nome);
            ranking[menor_indice].pontuacao = pontuacao;
        }
    }
}

// Gustavo: Função principal para iniciar o quiz
void iniciar_quiz(Pergunta perguntas[], int num_perguntas) {
    int pontos = 0, acertos = 0, ultima_pontuacao = 2;
    char nome[50];

    limpar_tela();
    printf("Digite o seu nome de usuario: ");
    scanf(" %49[^\n]", nome); // Lê o nome do usuário, permitindo espaços

    srand(time(NULL)); // Gustavo: Inicializa o gerador de números aleatórios para efetuar o embaralhamento das perguntas
    embaralhar_perguntas(perguntas, num_perguntas);

    for (int i = 0; i < num_perguntas; i++) {
        int tentativas_restantes = MAX_TENTATIVAS;
        char resposta_usuario;

        limpar_tela();
        printf("Pergunta %d:\n%s\n", i + 1, perguntas[i].pergunta);

        // Exibe as opções de resposta
        for (int j = 0; j < 4; j++) {
            printf("%c) %s\n", 'A' + j, perguntas[i].opcoes[j]);
        }

        // Gustavo: Lê a resposta e verifica se está correta
        while (tentativas_restantes > 0) {
            resposta_usuario = ler_resposta();
            if (resposta_usuario == perguntas[i].resposta_correta) {
                pontos += ultima_pontuacao;
                ultima_pontuacao *= 2;
                acertos++;
                printf("\nResposta correta!\n");
                break;
            } else {
                tentativas_restantes--;
                if (tentativas_restantes > 0) {
                    printf("\nResposta errada! Você ainda tem %d tentativa(s) restante(s).\n", tentativas_restantes);
                } else {
                    printf("\nResposta errada! A resposta correta era %c\n", perguntas[i].resposta_correta);
                    ultima_pontuacao = 2; // Reinicia a pontuação
                }
            }
        }

        printf("\nPontuação atual: %d\n", pontos);
        printf("\nPressione Enter para continuar...");
        getchar(); // Limpa o buffer do teclado
        getchar(); // Aguarda o usuário pressionar Enter
    }

    // Exibe o resultado final do quiz
    limpar_tela();
    printf("========== Resultado do Quiz ==========\n");
    printf("\nPontuação final: %d\n", pontos);
    printf("\nPerguntas corretas: %d de %d\n", acertos, num_perguntas);

    // Mensagens personalizadas com base no desempenho
    if (acertos == num_perguntas) {
        printf("\nParabéns %s! Você acertou todas as perguntas. Você é um expert no meio ambiente!\n", nome);
        printf("\n\n");
        printf("       ___________      \n");
        printf("      '.=====.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         .' '.        \n");
        printf("        '-------'       \n\n");
    } else if (acertos >= 16) {
        printf("\nMuito bem %s! Você acertou %d perguntas. Você tem um bom conhecimento sobre o meio ambiente.\n", nome, acertos);
    } else if (acertos >= 10) {
        printf("\nBom trabalho %s! Você acertou %d perguntas. Continue estudando para melhorar ainda mais!\n", nome, acertos);
    } else {
        printf("\nVocê acertou %d perguntas %s. Continue estudando e tente novamente!\n", acertos, nome);
    }

    // Adiciona o jogador ao ranking e o exibe
    adicionar_ao_ranking(nome, pontos);
    exibir_ranking();

    printf("\nPressione Enter para voltar ao menu...");
    getchar(); // Aguarda o usuário pressionar Enter
}

// Função para exibir o menu principal
void exibir_menu() {
    limpar_tela();
    printf("========== Quiz sobre o Meio Ambiente ==========\n");
    printf("1. Iniciar Quiz\n");
    printf("2. Instruções\n");
    printf("3. Ver Ranking\n");
    printf("4. Sair\n");
    printf("===============================================\n");
    printf("\nEscolha uma opção: ");
}

// Função para exibir as instruções do jogo
void exibir_instrucoes() {
    limpar_tela();
    printf("========== Instruções do Quiz ==========\n");
    printf("1. Você terá 20 perguntas de múltipla escolha.\n");
    printf("2. Para cada resposta correta, sua pontuação dobrará.\n");
    printf("3. A pontuação é reiniciada a cada resposta errada.\n");
    printf("4. Você tem %d tentativas para responder cada pergunta.\n", MAX_TENTATIVAS);
    printf("\nPressione Enter para voltar ao menu...");
    getchar(); // Aguarda o usuário pressionar Enter
    getchar(); // Aguarda o usuário pressionar Enter
}

// Função principal que controla o menu e a execução do jogo
int main() {
	SetConsoleOutputCP(CP_UTF8);
    Pergunta perguntas[NUM_PERGUNTAS] = {
        {"If a tree absorbs 20 kg of CO2 per year and a hectare of forest has 500 trees, how much CO2 is absorbed per year per hectare?", {"10,000 kg", "5,000 kg", "20,000 kg", " 1,000 kg"}, 'A'},
        {"O que é o efeito estufa?", {"Um fenômeno natural que aquece a Terra", "Um efeito causado pela falta de chuva", "Um tipo de poluição sonora", "Uma técnica agrícola para aumentar a produtividade"}, 'A'},
        {"Qual gás é o principal responsável pelo efeito estufa?", {"Oxigênio", "Dióxidio de carbono (CO2)", "Nitrogênio", "Hidrogênio"}, 'B'},
        {"O que é 'biodegradável'?", {"Um material que pode ser quebrado por organismos vivos", "Um material que nunca se decompõe", "Um material que é reciclado infinitamente", "Um material que se transforma em plástico"}, 'A'},
        {"Qual é o objetivo da reciclagem?", {"Produzir mais lixo", "Reduzir a quantidade de resíduos", "Aumentar a produção de produtos descartáveis", "Poluir o ambiente"}, 'B'},
        {"O que significa 'pegada ecológica'?", {"A marca deixada pelos animais no solo", "A quantidade de CO2 que uma pessoa emite", "A quantidade de recursos naturais que uma pessoa consome", "A quantidade de água usada na agricultura"}, 'C'},
        {"Se uma lâmpada de LED consome 10 watts por hora e uma lampada incandescente consome 60 watts por hora, quantos watts são economizados em 10 horas usando a lampada de LED?", {"50 watts", "500 watts", "600 watts", "550 watts"}, 'B'},
        {"Um carro elétrico percorre 200 km com 40 kWh de energia. Quantos kWh são necessários para percorrer 500 km?", {"80 kWh", "100 kWh", "120 kWh", "140 kWh"}, 'B'},
        {"Uma floresta de 1.000 hectares absorve 2 toneladas de CO2 por hectare por ano. Quantas toneladas de CO2 essa floresta absorve em 3 anos?", {"2.000 toneladas", "3.000 toneladas", "6.000 toneladas", "5.000 toneladas"}, 'C'},
        {"Uma fazenda de energia solar produz 150.000 kWh por mês. Quantos kWh essa fazenda produz em 2 anos?", {"1.800.000 kWh", "3.600.000 kWh", "3.000.000 kWh", "1.200.000 kWh"}, 'B'},
        {"What is the main cause of deforestation?", {"Planting more trees", "Cutting down forests for agriculture and urbanization", "Protecting wildlife", "Creating national parks"}, 'B'},
        {"Which gas is known as the greenhouse gas?", {"Oxygen", "Carbon dioxide (CO2)", "Nitrogen", "Hydrogen"}, 'B'},
        {"What is a renewable energy source?", {"Coal", "Natural gas", "Solar energy", "Petroleum"}, 'C'},
        {"What is the purpose of the ozone layer?", {"To protect the Earth from harmful solar radiation", "To provide oxygen to the atmosphere", "To increase global warming", "To reduce volcanic activity"}, 'A'},
        {"What is a consequence of deforestation?", {"Increased biodiversity", "Increased rainfall", "Soil erosion", "Decreased global temperatures"}, 'C'},
        {"Qual dos seguintes fatores é o mais significativo na aceleração da erosão do solo em áreas agrícolas intensivamente cultivadas?", {"Aumento da cobertura vegetal de gramíneas", "Uso contínuo de monoculturas sem rotação de culturas", "Estabelecimento de áreas de preservação permanente ao redor dos campos", "Plantio de árvores para reforestamento"}, 'B'},
        {"O que é o 'deserto verde'?", {"Uma área de floresta tropical", "Uma região desertica onde nada cresce", "Uma monocultura que reduz a biodiversidade", "Um deserto coberto por musgos"}, 'C'},
        {"Uma cidade pretende plantar 50.000 árvores em 5 anos. Quantas árvores ela deve plantar em um ano para atingir essa meta?", {"8.000 árvores", "10.000 árvores", "12.000 árvores", "15.000 árvores"}, 'B'},
        {"Qual é o principal mecanismo pelo qual as mudanças no uso do solo contribuem para o aumento das concentrações de gases de efeito estufa na atmosfera, especificamente no contexto das áreas de desmatamento tropical?", {"Redução da capacidade de fotossíntese das plantas nativas", "Aumento da mineralização do carbono orgânico no solo devido ao aumento da temperatura", "Emissão direta de CO2 devido à decomposição da biomassa florestal removida", "Mudança no albedo da superfície terrestre, refletindo mais radiação solar de volta para a atmosfera"}, 'C'},
        {"What is 'greenwashing'?", {"The practice of improving a company's environmental image without substantial changes", "The process of creating more green spaces in urban areas", "The act of recycling plastic waste into new products", "The promotion of renewable energy sources"}, 'A'}
    };

    int opcao;
    do {
        exibir_menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                iniciar_quiz(perguntas, NUM_PERGUNTAS);
                break;
            case 2:
                exibir_instrucoes();
                break;
            case 3:
                exibir_ranking();
                printf("\nPressione Enter para voltar ao menu...");
                getchar(); // Limpa o buffer
                getchar(); // Aguarda o usuário pressionar Enter
                break;
            case 4:
                printf("\nSaindo....\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}