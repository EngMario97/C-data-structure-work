#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED



#endif // UTIL_H_INCLUDED

typedef struct Poltronas
{
    int numero;
    char status;
} Poltronas;


typedef struct Clientes
{
    char cpf[12];
    char nome[50];
    int assentoReservado;
    int assentoComprado[40];
} Clientes;

void carregaDados(Poltronas *busao, Clientes *cadastros, int tam1, int tam2);
void salvaDados(Poltronas *busao, Clientes *cadastros, int tam1, int tam2);

int validarCPF(char *cpf);
void cadastrarCliente(Clientes *cadastro, int n);
void listarClientes(Clientes *cadastros);
void pesquisarCliente(Clientes *cadastro);

void reservarAssento(Clientes *cadastros, Poltronas *busao);
void venderAssento(Clientes *cadastros, Poltronas *busao);
void cancelarReserva(Clientes *cadastros, Poltronas *busao);
void listarPoltronas(Poltronas *busao);

void excluirCadastro(Clientes *cadastros, Poltronas *busao);

int procuraCpf(char *cpfLido, Clientes *cadastros, int *posicaoCpf);

void alterarVenda(Clientes *cadastros, Poltronas *busao);
