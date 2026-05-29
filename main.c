#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    void esperar(int milissegundos) { Sleep(milissegundos); }
#else
    #include <unistd.h>
    void esperar(int milissegundos) { usleep(milissegundos * 1000); }
#endif

#define MAX_HISTORICO 10

typedef struct {
    float temperatura;
    int energia;
    int comunicacao;
    int dados_inseridos;
    int alertas_emitidos;
} MissaoEspacial;

void limparTela();
void limparBuffer();
void rodarAnimacao(const char *mensagem);
void inserirDados(MissaoEspacial *m, MissaoEspacial historico[], int *total);
void visualizarStatus(MissaoEspacial m);
void exibirHistorico(MissaoEspacial historico[], int total);

int main() {
    MissaoEspacial minhaMissao = {0.0, 0, 0, 0, 0};
    MissaoEspacial historicoLeituras[MAX_HISTORICO];
    int totalLeituras = 0;
    int opcao;

    do {
        printf("\n=========================================\n");
        printf("    SISTEMA DE MONITORAMENTO ESPACIAL    \n");
        printf("=========================================\n");
        printf("1 - Inserir Dados dos Sensores\n");
        printf("2 - Visualizar Status Atual\n");
        printf("3 - Visualizar Historico de Leituras\n");
        printf("0 - Encerrar Sistema\n");
        printf("=========================================\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida! Digite um numero.\n");
            limparBuffer();
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1:
                inserirDados(&minhaMissao, historicoLeituras, &totalLeituras);
                break;
            case 2:
                visualizarStatus(minhaMissao);
                break;
            case 3:
                exibirHistorico(historicoLeituras, totalLeituras);
                break;
            case 0:
                printf("\nEncerrando o sistema de monitoramento.\n");
                break;
            case -1:
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void rodarAnimacao(const char *mensagem) {
    printf("%s", mensagem);
    for (int i = 0; i < 4; i++) {
        printf(".");
        fflush(stdout);
        esperar(400);
    }
    printf("\n\n");
}

void inserirDados(MissaoEspacial *m, MissaoEspacial historico[], int *total) {
    limparTela();
    printf("=== CADASTRO DE INFORMACOES DA MISSAO ===\n\n");
    
    printf("Digite a temperatura da nave (em Celsius): ");
    if (scanf("%f", &m->temperatura) != 1) {
        printf("\nTemperatura invalida.\n");
        limparBuffer();
        return; 
    }

    printf("Digite a porcentagem de energia (0 a 100): ");
    if (scanf("%d", &m->energia) != 1) {
        printf("\nEnergia invalida.\n");
        limparBuffer();
        return;
    }

    if (m->energia < 0 || m->energia > 100) {
        printf("Valor de energia invalido.\n");
        if (m->energia < 0) m->energia = 0;
        if (m->energia > 100) m->energia = 100;
    }

    printf("Digite o status da comunicacao (1 - Online / 0 - Offline): ");
    if (scanf("%d", &m->comunicacao) != 1) {
        printf("\nStatus de comunicacao invalido.\n");
        limparBuffer();
        return;
    }

   if (m->comunicacao != 0 && m->comunicacao != 1) {
        printf("\nValor invalido! Digite apenas 0 ou 1 para comunicacao.\n");
        limparBuffer();
        return;
        }

    m->dados_inseridos = 1; 

    m->alertas_emitidos = 0;
    if (m->temperatura > 80.0) m->alertas_emitidos++;
    if (m->energia < 20) m->alertas_emitidos++;
    if (m->comunicacao == 0) m->alertas_emitidos++;

    if (*total < MAX_HISTORICO) {
        historico[*total] = *m;
        (*total)++;
    } else {
        for (int i = 0; i < MAX_HISTORICO - 1; i++) {
            historico[i] = historico[i + 1];
        }
        historico[MAX_HISTORICO - 1] = *m;
    }

    printf("\nDados gravados com sucesso!\n");
}

void visualizarStatus(MissaoEspacial m) {
    limparTela();
    if (!m.dados_inseridos) {
        printf("=== STATUS OPERACIONAL DA MISSAO ===\n\n");
        printf("Nenhum dado foi inserido ainda.\n");
        return;
    }

    rodarAnimacao("Conectando aos sensores orbitais e processando telemetria");
    printf("=== STATUS OPERACIONAL DA MISSAO ===\n\n");

    printf("Temperatura Atual : %.2f Graus Celsius\n", m.temperatura);
    printf("Nivel de Energia   : %d%%\n", m.energia);
    printf("Status Comunicacao : %s\n", (m.comunicacao == 1) ? "ONLINE" : "OFFLINE (FALHA)");

    printf("\n--- ANALISE DE RISCO ATUAL ---\n");
    if (m.alertas_emitidos == 0) {
        printf("Sistemas operando dentro da normalidade. Nenhuma anomalia detectada.\n");
    } else {
        if (m.temperatura > 80.0) {
            printf("Superaquecimento detectado! Temperatura acima de 80 Graus Celsius.\n");
        }
        if (m.energia < 20) {
            printf("Economia de energia ativada! Nivel critico abaixo de 20%%.\n");
        }
        if (m.comunicacao == 0) {
            printf("Falha de comunicacao com a base terrestre!\n");
        }
        printf("\nTotal de alertas ativos nesta leitura: %d\n", m.alertas_emitidos);
    }
}

void exibirHistorico(MissaoEspacial historico[], int total) {
    limparTela();
    printf("=== HISTORICO DAS ULTIMAS LEITURAS ===\n\n");

    if (total == 0) {
        printf("Nenhum registro encontrado no historico.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("Leitura #%d: ", i + 1);
        printf("Temp: %.1f C | ", historico[i].temperatura);
        printf("Energia: %d%% | ", historico[i].energia);
        printf("Com: %s | ", (historico[i].comunicacao == 1) ? "OK" : "FALHA");
        printf("Alertas: %d\n", historico[i].alertas_emitidos);
    }
    printf("\nTotal de registros armazenados: %d/%d\n", total, MAX_HISTORICO);
}