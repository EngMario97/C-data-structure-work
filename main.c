#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "util.h"
#define NOME_ARQ "dados.bin"

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao=0;

    Poltronas *busao;

    Clientes *cadastros;

    cadastros = calloc(80, sizeof(Clientes));

    busao = calloc(40, sizeof(Poltronas));

    FILE *arq;

    for(int i=0; i<40; i++)
    {
        busao[i].numero = i+1;
        busao[i].status = 'L';
    }

    for(int i = 0; i<80; i++)
    {
        cadastros[i].assentoReservado = -1;
        for(int j=0; j<40; j++)
        {
            cadastros[i].assentoComprado[j] = -1;
        }
    }

    while(1)
    {
        opcao = 0;
        printf("\nMENU INICIAL\n\n1 - Cadastrar Cliente\n2 - Reservar Assento\n3 - Vender Assento\n4 - Excluir"
               " Cadastro\n5 - Cancelar Reserva\n6 - Alterar Venda\n7 - Pesquisar Cliente"
               "\n8 - Listar Clientes\n9 - Listar Poltronas\n0 - Sair\nPRESSIONE OUTRA TECLA PARA FECHAR\n");
        scanf("%d", &opcao);

        switch(opcao)
        {
        case 1:
            carregaDados(busao, cadastros, 40, 80); // Abre dados.bin para leitura
            cadastrarCliente(cadastros, 80);
            salvaDados(busao, cadastros, 40, 80); // Abre dados.bin para gravação
            break;
        case 2:
            carregaDados(busao, cadastros, 40, 80);
            reservarAssento(cadastros, busao);
            salvaDados(busao, cadastros, 40, 80);
            break;
        case 3:
            carregaDados(busao, cadastros, 40, 80);
            venderAssento(cadastros, busao);
            salvaDados(busao, cadastros, 40, 80);
            break;
        case 4:
            carregaDados(busao, cadastros, 40, 80);
            excluirCadastro(cadastros, busao);
            salvaDados(busao, cadastros, 40, 80);
            break;
        case 5:
            carregaDados(busao, cadastros, 40, 80);
            cancelarReserva(cadastros, busao);
            salvaDados(busao, cadastros, 40, 80);
            break;
        case 6:
            carregaDados(busao, cadastros, 40, 80);
            alterarVenda(cadastros, busao);
            salvaDados(busao, cadastros, 40, 80);
            break;
        case 7:
            carregaDados(busao, cadastros, 40, 80);
            pesquisarCliente(cadastros);
            break;
        case 8:
            carregaDados(busao, cadastros, 40, 80);
            listarClientes(cadastros);
            printf("\nPressione qualquer tecla para voltar ao menu inicial.\n");
            getch();
            break;
        case 9:
            carregaDados(busao, cadastros, 40, 80);
            listarPoltronas(busao);
            printf("\nPressione qualquer tecla para voltar ao menu inicial.\n");
            getch();
            break;
        case 0:
            return 0;
            break;
        default:
            return 0;
            break;
        }
    }
}
