#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Nota{
    char nome[20];
    int valor, quantidade;
} Nota;

typedef struct LogTransacao{
    int dia, mes, ano, hora, min, seg;
    Nota quantidadeNotasDadas[6];
    
} LogTransacao;

typedef struct Caixa{
    Nota quantidadeNotas[6];
    LogTransacao transacoes[100];
    int totalTransacoes;
} Caixa;


void darNotas(long int valor, Caixa *caixa){
    
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    
    int valorTotalCaixa = 0;
    int transacaoIndex = caixa -> totalTransacoes;
    
    caixa -> transacoes[transacaoIndex].dia = tm.tm_mday;
    caixa -> transacoes[transacaoIndex].mes = tm.tm_mon + 1;
    caixa -> transacoes[transacaoIndex].ano = tm.tm_year + 1900;
    caixa -> transacoes[transacaoIndex].hora = tm.tm_hour;
    caixa -> transacoes[transacaoIndex].min = tm.tm_min;
    caixa -> transacoes[transacaoIndex].seg = tm.tm_sec;
    
    for (int i = 0; i < 6; i++) {
        valorTotalCaixa += caixa -> quantidadeNotas[i].valor * caixa -> quantidadeNotas[i].quantidade;
    }
    
    if(valor > valorTotalCaixa){
        printf("Este caixa nao tem cedulas suficientes para realizar o seu saque, procure outro caixa disponivel.\n\n");
        printf("$== Obrigado pela preferencia e confiança na Think ATM! ==$");
        exit(1);
    }
    
    for (int i = 0; i < 6; i++) {
        if(valor >= caixa -> quantidadeNotas[i].valor && caixa -> quantidadeNotas[i].quantidade > 0){
            
            
            int quantidade = valor / caixa -> quantidadeNotas[i].valor;
            if (quantidade > caixa -> quantidadeNotas[i].quantidade) {
                quantidade = caixa -> quantidadeNotas[i].quantidade;
            }
            
            valor -= quantidade * caixa -> quantidadeNotas[i].valor;
            caixa -> quantidadeNotas[i].quantidade -= quantidade;
            
            caixa -> transacoes[transacaoIndex].quantidadeNotasDadas[i] = (Nota){
                .valor = caixa -> quantidadeNotas[i].valor,
                .quantidade = quantidade
            };
            
            strncpy(caixa -> transacoes[transacaoIndex].quantidadeNotasDadas[i].nome, 
                    caixa -> quantidadeNotas[i].nome, 
                    sizeof(caixa -> transacoes[transacaoIndex].quantidadeNotasDadas[i].nome) - 1);
            caixa -> transacoes[transacaoIndex].quantidadeNotasDadas[i].nome[sizeof(caixa -> transacoes[transacaoIndex].quantidadeNotasDadas[i].nome) - 1] = '\0';
            
        } else {
            caixa -> transacoes[transacaoIndex].quantidadeNotasDadas[i] = (Nota){
                .valor = caixa -> quantidadeNotas[i].valor,
                .quantidade = 0
            };
            
            strncpy(caixa -> transacoes[transacaoIndex].quantidadeNotasDadas[i].nome, 
                    caixa -> quantidadeNotas[i].nome, 
                    sizeof(caixa -> transacoes[transacaoIndex].quantidadeNotasDadas[i].nome) - 1);
            caixa -> transacoes[transacaoIndex].quantidadeNotasDadas[i].nome[sizeof(caixa -> transacoes[transacaoIndex].quantidadeNotasDadas[i].nome) - 1] = '\0';
        }
    }
    
    caixa -> totalTransacoes++;
}

int main()
{
    Caixa caixa = {
        .quantidadeNotas = {
            {"Nota de 100", 100, 4},
            {"Nota de 50", 50, 8},
            {"Nota de 20", 20, 15},
            {"Nota de 10", 10, 20},
            {"Nota de 5", 5, 5},
            {"Nota de 2", 2, 10}
        },
        .totalTransacoes = 0
    };
    
    
    
    darNotas(1346, &caixa);

    
    LogTransacao transacao = caixa.transacoes[0];
    
    printf("Transação em %02d/%02d/%04d %02d:%02d:%02d\n",
           transacao.dia, transacao.mes, transacao.ano,
           transacao.hora, transacao.min, transacao.seg);


    for (int i = 0; i < 6; i++) {
        if (transacao.quantidadeNotasDadas[i].quantidade > 0) {
            printf("Nota usada: %s - Valor: %d, Quantidade: %d\n",
                   transacao.quantidadeNotasDadas[i].nome,
                   transacao.quantidadeNotasDadas[i].valor,
                   transacao.quantidadeNotasDadas[i].quantidade);
        }
    }
    
    printf("\n\n");
    
    for (int i = 0; i < 6; i++) {
        printf("%s - Valor: %d, Quantidade: %d\n", 
            caixa.quantidadeNotas[i].nome, 
            caixa.quantidadeNotas[i].valor, 
            caixa.quantidadeNotas[i].quantidade);
    }

    return 0;
}
