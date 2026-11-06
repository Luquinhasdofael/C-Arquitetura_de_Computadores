#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

// Macros para cross-platform (Windows / POSIX)
#ifdef _WIN32
    #include <windows.h>
    #define sleep_ms(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define sleep_ms(ms) usleep((ms) * 1000)
#endif

#define LARGURA 80
#define ALTURA 25

int main(void) {
    // Verifica se o compilador suporta pelo menos o C99
    #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
        // C99 ou superior detectado com sucesso!
    #else
        #warning "Para melhor compatibilidade, utilize um compilador compatível com C99."
    #endif

    srand((unsigned int)time(NULL));

    // Arrays de comprimento fixo e tipos C99 para controlar a chuva digital
    int colunas_topo[LARGURA];
    bool coluna_ativa[LARGURA];

    // Inicializa o estado das colunas utilizando declaração interna do loop (recurso C99)
    for (int i = 0; i < LARGURA; i++) {
        colunas_topo[i] = rand() % ALTURA;
        coluna_ativa[i] = (rand() % 3 == 0); 
    }

    // Limpa a tela e esconde o cursor usando sequências de escape ANSI
    printf("\033[2J\033[?25l");

    // Loop principal de animação
    for (uint32_t frame = 0; frame < 1500; frame++) { // Executa por 300 frames (~15 segundos)
        
        for (int x = 0; x < LARGURA; x++) {
            if (coluna_ativa[x]) {
                int y = colunas_topo[x];
                
                // Posiciona o cursor na coordenada (x, y) do terminal
                printf("\033[%d;%dH", y + 1, x + 1);

                // Alterna entre tons de verde usando ANSI escape codes
                if (rand() % 5 == 0) {
                    printf("\033[1;37m%c", (char)(33 + rand() % 93)); // Caractere brilhante (branco) no topo
                } else {
                    printf("\033[32m%c", (char)(33 + rand() % 93));   // Caractere verde normal
                }

                // Avança a linha da chuva
                colunas_topo[x]++;

                // Se a chuva passou do limite da tela, reinicia no topo com chance aleatória
                if (colunas_topo[x] >= ALTURA) {
                    colunas_topo[x] = 0;
                    coluna_ativa[x] = (rand() % 4 == 0);
                }
            } else if (rand() % 20 == 0) {
                // Ativa colunas inativas aleatoriamente para dar dinamismo
                coluna_ativa[x] = true;
                colunas_topo[x] = 0;
            }

            // Cria o efeito de rastro apagando caracteres antigos aleatoriamente
            if (rand() % 10 == 0) {
                int apagar_y = rand() % ALTURA;
                printf("\033[%d;%dH ", apagar_y + 1, x + 1);
            }
        }

        fflush(stdout);
        sleep_ms(50); // Controla a velocidade da animação
    }

    // Restaura as configurações originais do terminal (cor padrão e cursor visível)
    printf("\033[0m\033[2J\033[?25h");
    printf("Simulação Matrix finalizada. Código C99 executado com sucesso!\n");

    return 0;
}
