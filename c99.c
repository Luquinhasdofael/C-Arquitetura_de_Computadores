#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void menu() {
    printf("1. Ver Saldo, 2. Depositar, 3. Sacar e 4. Sair: ");

}

void sacar(int *saldo) {
    int saque;
    printf("Insira a quantidade que deseja sacar: ");
    scanf("%d", &saque);
    if (saque > *saldo) {
        printf("Quantidade invalida.\n\n");
    } else {
        *saldo = *saldo - saque;
        printf("Feito!");
    }
}
void depositar(int *saldo) {
    int deposito;
    printf("Insira a quantidade que deseja depositar: ");
    scanf("%d", &deposito);
    *saldo = *saldo + deposito;
    printf("Saldo: %d\n\n", *saldo);


}

int main(void) {

    int saldo = 1000;

    int escolha;
    escolha = 0;

    menu();
    while (escolha != 4) {
        
    scanf(" %d", &escolha);
    if (escolha == 1) {
        printf("Saldo: %d\n\n", saldo);
        menu();
    }
    else if (escolha == 2) {
        depositar(&saldo);
    }
    else if (escolha == 3) {
        sacar(&saldo);
    }
    else if (escolha == 4) {
        printf("tchau!");
        break;
    } else {
        printf("Opção Invalida!");
    }
    }
    return 0;
}