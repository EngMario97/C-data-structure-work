#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "util.h"
#define NOME_ARQ "dados.bin"

void carregaDados(Poltronas *busao, Clientes *cadastros, int tam1, int tam2) // Abre dados.bin para leitura
{
    FILE *arq = fopen(NOME_ARQ,"r+b");
    fread(busao, sizeof(Poltronas), tam1, arq);
    fread(cadastros, sizeof(Clientes), tam2, arq);
    fclose(arq);
}

void salvaDados(Poltronas *busao, Clientes *cadastros, int tam1, int tam2) // Abre dados.bin para gravação
{
    FILE *arq = fopen(NOME_ARQ,"wb");
    fwrite(busao, sizeof(Poltronas), tam1, arq);
    fwrite(cadastros, sizeof(Clientes), tam2, arq);
    fclose(arq);
}

int validarCPF(char *cpf) // Verifica se o CPF é válido
{
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11)
        return 0;
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0))
        return 0; //se o CPF tiver todos os números iguais ele é inválido.
    else
    {
        ///digito 1---------------------------------------------------
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) // multiplica os números de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i]-48) * j;
        digito1 %= 11;
        if(digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cpf[9]-48) != digito1)
            return 0; // se o digito 1 não for o mesmo que o da validação CPF é inválido
        else
            ///digito 2--------------------------------------------------
        {
            for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) // multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                digito2 += (cpf[i]-48) * j;
            digito2 %= 11;
            if(digito2 < 2)
                digito2 = 0;
            else
                digito2 = 11 - digito2;
            if((cpf[10]-48) != digito2)
                return 0; // se o digito 2 não for o mesmo que o da validação CPF é inválido
        }
    }
    return 1; // se for válido
}


void cadastrarCliente(Clientes *cadastro, int n) // função de cadastrar clientes
{
    char nomeCliente[50];
    char cpflido[12];
    char opcaoCadastro = 's';
    int j=0, cpfRepetido=0;

    do
    {
            printf("************| CADASTRO DE CLIENTES |***************"); // entrada de dados de cadastro
            printf("\n\nNome: ");
            scanf(" %[^\n]s", nomeCliente);

            printf("\nCPF: ");
            scanf(" %s", cpflido);

            if(validarCPF(cpflido)==1) // função de validar cpf
            {
                for(j=0; j<n; j++) // busca posição vaga para gravar
                {
                    if(strcmp(cadastro[j].cpf, "") == 0)
                    {
                        break;
                    }
                }
                for(int i = 0; i<n; i++) // verifica se existe CPF repetido
                {
                    if(strcmp(cadastro[i].cpf, cpflido) == 0)
                    {
                        cpfRepetido = 1;
                        break;
                    }
                }
                if(cpfRepetido==0) // Cadastro atende todas as condições para ser efeituado
                {
                strcpy(cadastro[j].cpf, cpflido);
                strcpy(cadastro[j].nome, nomeCliente);
                printf("\n\nCADASTRO REALIZADO COM SUCESSO!\n");
                printf("Deseja cadastrar outro cliente?(S/N)\n");
                scanf(" %c", &opcaoCadastro);
                }
            }
            if(validarCPF(cpflido)== 0 || cpfRepetido==1) // Cadastro não atendeu todas as condições para ser efeituado
            {
                printf("CPF Inválido\n"
                       "Deseja continuar na tela de cadastro de cliente.(S/N)\n");
                scanf(" %c", &opcaoCadastro);
            }
    }
    while(toupper(opcaoCadastro) == 'S');
}


void listarClientes(Clientes *cadastros)
{
    printf("CLIENTES CADASTRADOS:\n");
    int i=0;

    while(i<80) //O sistema comporta até 80 cadastros.
    {
        int j=0;
        if(strcmp(cadastros[i].cpf, "")) //Ele irá listar apenas clientes cujo campo CPF é diferente de vazio.
        {
            printf("\nID[%02d] | Nome:%-50s | CPF:%s ", i, cadastros[i].nome, cadastros[i].cpf);
            if(cadastros[i].assentoReservado != -1) //-1 no programa é considerado o nulo, visto que o 0 é um assento válido. Isso é para listar os assentos que a pessoa reservou.
            {
                printf("| Assento Reservado: %d", cadastros[i].assentoReservado+1);
            }
            if(cadastros[i].assentoComprado[j] != -1) /*Mesma lógica do anterior, porém para assentos comprados. Diferentemente dos assentos reservados, os comprados
            são armazenados em um vetor*/
            {
                printf(" | Assentos comprados: ");
                while(cadastros[i].assentoComprado[j] != -1) //Percorre o vetor, enquanto a posição tiver um assento armazenado.
                {
                    printf("%d | ", cadastros[i].assentoComprado[j]+1); /*Sempre ao colocar um assento na interface utiliza-se um mais um, pois o vetor vai de 0 a 39, mas
                    os assentos vão de 1 a 40.*/
                    j++;
                }
            }
        }
        else
        {
            //break; //Sim, esse else não faz nada. Por alguma razão, quando tira isso aqui o código buga. Então deixamos aí, não tá atrapalhando mesmo.
        }
        i++;
    }
    return 0;
}


void pesquisarCliente(Clientes *cadastro) // função usada para pesquisar cliente
{
    int i, existe;
    char nomeCliente[50], cpflido[12], opcaoPesquisa = 'S', opcao;
    while(1)
    {
        fflush(stdin);
        existe=0;
        do
        {
            printf("Deseja pesquisar cliente por:\n" // informa as opções e faz a leitura da mesma
                   "1-Nome\n"
                   "2-CPF\n");
            scanf(" %c", &opcao);
        }
        while(opcao!='1' && opcao!='2');
        if(opcao=='1') // busca por nome
        {
            i=0;
            printf("Digite o Nome:");
            scanf(" %[^\n]s", nomeCliente);
            while(i<80)
            {
                if(strstr(cadastro[i].nome, nomeCliente) != NULL) // se
                {
                    printf("\nID[%2d]  Nome:%-50s  CPF:%s", i, cadastro[i].nome, cadastro[i].cpf); // mostra dados do cliente
                    existe++;
                }
                i++;
            }
        }
        if(opcao=='2') // busca por CPF
        {
            i=0;
            printf("Digite o CPF:");
            scanf(" %s", cpflido);
            while(i<80)
            {

                if(strcmp (cadastro[i].cpf, cpflido)==0)
                {
                    printf("\nID[%2d]  Nome:%-50s  CPF:%s", i, cadastro[i].nome, cadastro[i].cpf); // mostra dados do cliente
                    existe++;
                    break;
                }
                i++;
            }
        }
        if(existe==0) // se o cliente não for achado, mostra mensagem
        {
            printf("\nCliente não cadastrado\n");
        }
        printf("\nDeseja realizar outra pesquisa?(S/N)");
        scanf(" %c", &opcaoPesquisa);
        if(toupper(opcaoPesquisa)=='N')
        {
            break;
        }
    }
}


void reservarAssento(Clientes *cadastros, Poltronas *busao)
{
    listarPoltronas(busao); //Lista todas as poltronas para facilitar.

    int sucesso = -1, aux;
    char opcaoReserva, opcaoAux;
    int poltrona;
    char clienteCpf[12];

    aux = 0;
    printf("\nSelecione uma poltrona.\n");
    scanf("%d", &poltrona);

    if(busao[poltrona-1].status == 'L') //Caso a poltrona esteja liberada.
    {
        printf("Informe o CPF do cliente.\n");
        scanf(" %[^\n]s", clienteCpf);
        for(int i=0; i<80; i++)
        {
            if((strcmp (cadastros[i].cpf, clienteCpf) == 0)) //Após ler o CPF digitado, vai percorrer os cadastros vendo se corresponde a algum cadastrado.
            {
                if(cadastros[i].assentoReservado == -1) //A pessoa pode reservar apenas um assento por vez.
                {
                    cadastros[i].assentoReservado = poltrona-1;
                    busao[poltrona-1].status = 'R';
                    sucesso = 1;
                    printf("Assento reservado com sucesso.\n");
                    break; /*Essa parte do código armazena o assento que a pessoa digitou tanto no cadastro dela como na listagem de poltronas. A variável sucesso
                    indica que isso aconteceu, e será usada para controle logo adiante.*/
                }
                else
                {
                    printf("Cliente %s já reservou o assento %d. Deseja substituir? (S/N)\n",
                           cadastros[i].nome, cadastros[i].assentoReservado+1); //Caso a pessoa já tenha reservado um assento, irá pedir pra ela confirmar a troca.
                    scanf(" %c", &opcaoAux);
                    if(toupper(opcaoAux) == 'S')
                    {
                        busao[cadastros[i].assentoReservado].status = 'L';
                        cadastros[i].assentoReservado = poltrona-1;
                        busao[poltrona-1].status = 'R';
                        sucesso = 1;
                        printf("Assento reservado com sucesso.\n");
                        break; //Mesma coisa que aconteceu anteriormente.
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
            if(i==79) /*Caso o vetor dos cadastros seja percorrido e nenhum CPF corresponda ao digitado, acontecerá isso. Anteriormente, a função era capaz de
            redirecionar o usuário para a tela de cadastro, porém isso foi retirado por não ser estritamente necessário ao código e estar gerando um bug absurdo
            em que uma função estava entrando no meio da outra.*/
            {
                printf("CPF Inválido.\n");
                getch();
                return 0;
            }

        }
    }
    else
    {
        printf("Assento indisponível.\n");
    }

    printf("Pressione qualquer tecla para voltar ao menu inicial.\n");
    getch();

    return 0;
}


void venderAssento(Clientes *cadastros, Poltronas *busao)
{
    char cpfLido[12], opcaoLida, opcaoReserva;
    int poltrona, posicaoCpf, i, cpfEncontrado = 0;

    printf("Informe o CPF do cliente:\n");
    scanf(" %s", cpfLido);

    for(i=0; i<80; i++)
    {
        if(strcmp(cadastros[i].cpf, cpfLido) == 0) //Essa parte é só pra facilitar. Ela procura o CPF digitado entre os cadastrados e, se encontrar, armazena a posição.
        {
            posicaoCpf = i;
            cpfEncontrado = 1;
            break;
        }
    }
    if(cpfEncontrado != 1)
    {
        printf("Cliente não encontrado. Deseja cadastrá-lo? (S/N)\n"); //Essa função é capaz de redirecionar o usuário para a tela de cadastro de clientes.
        scanf(" %c", &opcaoReserva);
        if(toupper(opcaoReserva) == 'S')
        {
            cadastrarCliente(cadastros, 80);
        }
        else
        {
            return 0;
        }
    }
    if(cadastros[posicaoCpf].assentoReservado != -1) /*Uma pessoa pode comprar um assento que ela mesma reservou, logicamente. Então, caso a variável esteja
    armazenando um assento válido, irá abrir essa possibilidade.*/
    {
        printf("Você já reservou o assento %d. Deseja comprá-lo? (S/N)\n", cadastros[i].assentoReservado+1);
        scanf(" %c", &opcaoLida);
        if(toupper(opcaoLida) == 'S')
        {
            for(int j=0; j<40; j++)
            {
                if(cadastros[posicaoCpf].assentoComprado[j] == -1)
                {
                    cadastros[posicaoCpf].assentoComprado[j] = cadastros[i].assentoReservado;
                    busao[cadastros[posicaoCpf].assentoComprado[j]].status = 'V';
                    cadastros[posicaoCpf].assentoReservado = -1;
                    printf("Assento %d vendido com sucesso para %s.\n",
                           cadastros[posicaoCpf].assentoComprado[j]+1, cadastros[posicaoCpf].nome);
                    return 0; //Similar ao que ocorreu na função de reservar, simplesmente atualiza nos cadastros de pessoas e de assentos as novas informações.
                }
            }
        }
    }
    if(cadastros[posicaoCpf].assentoReservado == -1 || toupper(opcaoLida) == 'N') //Se a pessoa quiser comprar uma diferente da que ela reservou.
    {
        listarPoltronas(busao);
        int sucesso = -1, aux;
        char opcaoReserva;
        int poltrona;
        char clienteCpf[12];

        do
        {
            aux = 0;
            printf("\nSelecione uma poltrona.\n");
            scanf("%d", &poltrona);

            if(busao[poltrona-1].status == 'L' || poltrona == cadastros[posicaoCpf].assentoReservado) /*Se a pessoa mudar de ideia e resolver comprar a poltrona
            que tinha reservado, ela pode aqui.*/
            {
                for(int j=0; j<40; j++) //Está percorrendo o vetor de assentos comprados procurando uma posição livre para armazenar.
                {
                    if(cadastros[posicaoCpf].assentoComprado[j] == -1)
                    {
                        cadastros[posicaoCpf].assentoComprado[j] = poltrona-1;
                        busao[poltrona-1].status = 'V';
                        sucesso = 1;
                        printf("Assento %d vendido com sucesso para %s.\n",
                               cadastros[posicaoCpf].assentoComprado[j]+1, cadastros[posicaoCpf].nome);
                        break;
                    }
                }
            }
            else
            {
                printf("Assento indisponível.\n");
                printf("Digite qualquer tecla para retornar ao menu principal.\n");
                getch();
                return 0;
            }
        }
        while(sucesso != 1); //Para ficar no menu até a pessoa ter conseguido realizar a compra.
    }
    printf("Pressione qualquer tecla para voltar ao menu inicial.\n");
    getch();
}


void cancelarReserva(Clientes *cadastros, Poltronas *busao)
{
    char cpfLido[12], opcao;
    int posicaoCpf = 0, auxAssentoReservado;
    printf("Digite o CPF do cliente.\n");
    scanf(" %s", &cpfLido);

    if(procuraCpf(cpfLido, cadastros, &posicaoCpf) == 0) //Se achar o cpf lido, ele fará o resto.
    {
        if(cadastros[posicaoCpf].assentoReservado != -1) /*Essa função é simples, apenas confere se o cliente relativo ao CPF digitado possui algum assento reservado,
        se tiver, pede confirmação pra cancelar, se confirmado, cancela a reserva nos dois vetores.*/
        {
            printf("%s reservou a poltrona %d. Deseja cancelar a reserva? (S/N)\n", cadastros[posicaoCpf].nome,
                   cadastros[posicaoCpf].assentoReservado+1);
            auxAssentoReservado = cadastros[posicaoCpf].assentoReservado;
            scanf(" %c", &opcao);;
            if(toupper(opcao) == 'S')
            {
                busao[auxAssentoReservado].status = 'L';
                cadastros[posicaoCpf].assentoReservado = -1;
                printf("Cancelamento realizado com sucesso.\n");
            }
            else
            {
                return 0;
            }
        }
        else
        {
            printf("Cliente não possui nenhum assento reservado.\n");
            getch();
            return 0;
        }
    }
    else
    {
        printf("CPF não encontrado.\n");
        getch();
        return 0;
    }
}


void listarPoltronas(Poltronas *busao)
{
    for(int i=0; i<40; i++) //Função que apenas imprime os assentos, com a formatação abaixo.
    {
        printf("[%02d: %c] ", busao[i].numero, busao[i].status);
        if(i == 9 || i == 29)
        {
            printf("\n");
        }
        if(i == 19)
        {
            printf("\n\n");
        }
    }
}

void excluirCadastro(Clientes *cadastros, Poltronas *busao) // exclui cadastro e seus assentos comprados e reservado.
{
    char opcao;
    int i, j;
    opcao='S';
    listarClientes(cadastros);
    do
    {
        printf("\nInforme o ID do cliente para exclui-lo:\n"); // pede o ID do cliente
        scanf("%d", &i);
        printf("\nTem certeza que deseja excluir?(S/N)\n"); // pergunta de segurança
        scanf(" %c", &opcao);

        if(toupper(opcao)!='S')
        {
            return;
        }
        if(i<80 && toupper(opcao)=='S' && cadastros[i].cpf!='0') // esvazia todos os campos do cliente e seus respectivos assentos
        {
            memset(cadastros[i].nome,'\0',50);
            memset(cadastros[i].cpf,'\0',12);
            busao[cadastros[i].assentoReservado].status = 'L';
            cadastros[i].assentoReservado = -1;
            for(j=0; j<40; j++)
            {
                busao[cadastros[i].assentoComprado[j]].status = 'L';
                cadastros[i].assentoComprado[j] = -1;
            }
            printf("\nExcluído com sucesso!\n");
        }
        else // cliente não encontrado
        {
            printf("\nEsse cadastro não existe\n");
        }
        printf("\nDeseja excluir outro cliente?(S/N)\n");
        scanf(" %c", &opcao);
    }
    while(toupper(opcao)=='S');
}

int procuraCpf(char *cpfLido, Clientes *cadastros, int *posicaoCpf) /*Função criada para auxiliar, ela procura o CPF entre todos os cadastrados e retorna a posição.
Se não achar nada, retorna 0.*/
{
    int achou, i;
    for(i=0; i<80; i++)
    {
        if (strcmp(cadastros[i].cpf, cpfLido) == 0) //Compara o cpf lido com o registrado.
        {
            achou = strcmp(cadastros[i].cpf, cpfLido);
            break;
        }
    }

    *posicaoCpf = i;

    return achou;
}


void alterarVenda(Clientes *cadastros, Poltronas *busao)
{
    char cpfLido[12];
    int posicaoCpf = 0, optVenda, aux, k, optMenu = 0;

    printf("Informe o CPF do cliente:\n");
    scanf(" %s", cpfLido);

    if(procuraCpf(cpfLido, cadastros, &posicaoCpf) == 0)
    {
        if(cadastros[posicaoCpf].assentoComprado[0] != -1)
        {
            printf("Cliente: %s\nAssentos comprados:\n", cadastros[posicaoCpf].nome);
            for(int i=0; cadastros[posicaoCpf].assentoComprado[i] != -1; i++)
            {
                printf("%d - ", cadastros[posicaoCpf].assentoComprado[i]+1); //Lista todos os assentos que o cliente comprou.
            }
            printf("\nDe qual assento deseja alterar a venda?\n");
            scanf("%d", &optVenda);
            if(optVenda > 0 && optVenda < 40)
            {
                for(int i=0; cadastros[posicaoCpf].assentoComprado[i] != -1; i++)
                {
                    if(optVenda-1 == cadastros[posicaoCpf].assentoComprado[i])
                    {
                        k = i;
                        while(optMenu != 1 && optMenu != 2)
                        {
                            printf("Selecione: 1 - Alterar venda / 2 - Excluir venda\n"); //Exibe esse menu até o usuário selecionar opção válida.
                            scanf("%d", &optMenu);
                        }
                        if(optMenu == 1) //Funciona de forma semelhante à de vender assento, apenas difere por estar substituindo no vetor.
                        {
                            listarPoltronas(busao);
                            printf("\nSelecione qual assento deseja comprar.\n");
                            scanf("%d", &optVenda);
                            if(busao[optVenda-1].status == 'L')
                            {
                                busao[cadastros[posicaoCpf].assentoComprado[k]].status = 'L';
                                cadastros[posicaoCpf].assentoComprado[k] = optVenda-1;
                                busao[optVenda-1].status = 'V';
                            }
                            else if(busao[optVenda].status == 'V');
                            {
                                printf("Assento indisponível.\n");
                            }
                            if(busao[optVenda-1].status == 'R')
                            {
                                if(cadastros[posicaoCpf].assentoReservado == optVenda-1)
                                {
                                    busao[cadastros[posicaoCpf].assentoComprado[k]].status = 'L';
                                    cadastros[posicaoCpf].assentoComprado[k] = optVenda;
                                    busao[optVenda-1].status = 'V';
                                    cadastros[posicaoCpf].assentoReservado = -1;
                                }
                                else
                                {
                                    printf("Assento indisponível.\n");
                                }
                            }
                        }
                        if(optMenu == 2)
                        {
                            busao[cadastros[posicaoCpf].assentoComprado[k]].status = 'L';
                            // move os elementos para tampar o elemento retirado
                            for(k ; k < 40 ; k++)
                            {
                                cadastros[posicaoCpf].assentoComprado[k] = cadastros[posicaoCpf].assentoComprado[k+1];
                            }
                            cadastros[posicaoCpf].assentoComprado[39] = -1;
                            /*Funciona como nas listas. Caso deseje excluir uma venda, irá mover todos os elementos para a esquerda no vetor, para "cobrir".*/
                        }
                    }
                }
            }
        }
    }
}
