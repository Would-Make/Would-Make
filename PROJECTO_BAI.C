#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct 
{   int codigo;
    char nome[60], NifBi[14];
    int telefone;
}PESSOA;

typedef struct 
{   int numeroConta; 
    int codigoCliente;
    int tipoConta;
    char estado;
    float saldo;
}CONTA;
// VARIAVEIS GLOBAIS
PESSOA *p[50];
CONTA *a[50];
int quantP=0, quantC=0;
bool verConta;
char arquivoConta[] = {"backup_bai.txt"};
int tam=50, opcao, tamVectorPre;

void imprimir_p(PESSOA **c, int quant){
    int i;
    printf("\n\t LISTA DE PESSOAS\n");
    printf("\n\t --------------------------\n");
    for (i = 0; i < quant; i++)
    {
        printf("\nI%d - Código: %d/Nome: %s/BI Ou NIF: %s/Telefone: %d\n",i+1,c[i]->codigo,c[i]->nome,c[i]->NifBi,c[i]->telefone);
    }
    printf("\n\t --------------------------\n");
}

void imprimir_c(CONTA **d, int quant){
    int i;
    printf("\n\t LISTA DE CONTAS\n");
    printf("\n\t --------------------------\n");
    for (i = 0; i < quant; i++)
    {
        printf("\tI%d - Nº: %d/Código Cliente:%d/Tipo: %d/Estado: %c/Saldo: %.2f\n",i+1,d[i]->numeroConta,d[i]->codigoCliente,d[i]->tipoConta,d[i]->estado,d[i]->saldo);
    }
    printf("\n\t --------------------------\n");
}

bool cadastrar_pessoa(PESSOA **c,int quant, int tam){
    if (quant<tam){
        PESSOA *novo = (PESSOA *)malloc(sizeof(PESSOA));
        novo->codigo = quant;
        printf("\n Digite o nome: ");
        scanf("%60[^\n]",&novo->nome);
        getchar();
        printf("\nDigite o número do BI/NIF: ");
        scanf("%14[^\n]",&novo->NifBi);
        getchar();
        printf("\nDigite o número de Telefone: ");
        scanf("%d",&novo->telefone);
        getchar();
        c[quant]=novo;
        return true;
    }
    else {
        printf("\n Não foi possível cadastrar, tente novamente");
        return false;
    }
    
}

bool alterar_pessoa(PESSOA **c, int quant){
    int id;
    printf("\n\t DIgite o Indice que quer alterar: ");
    scanf("%d",&id);
    getchar();
    id--;
    
    if (id>=0 && id<quant)
    {
         PESSOA *novo = (PESSOA *)malloc(sizeof(PESSOA));
        novo->codigo = p[id]->codigo;
        printf("\n Digite o nome: ");
        scanf("%60[^\n]",&novo->nome);
        getchar();
        printf("\nDigite o número do BI/NIF: ");
        scanf("%14[^\n]",&novo->NifBi);
        printf("\nDigite o número de Telefone: ");
        scanf("%d",&novo->telefone);
        getchar();
        c[id]=novo;
        return true;
    }
    else {
        printf("\n Indice Invalido!\n");
        return false;
    }
}

bool criar_conta(CONTA **d, int quant, int tam){
     if (quant<tam){
        int valorInteiro;
        CONTA *novo = (CONTA *)malloc(sizeof(CONTA));
        novo->numeroConta = quant;
        printf("\n Digite o codigo do cliente: ");
        scanf("%d",&novo->codigoCliente);
        getchar();
        printf("\nTipo de Conta 0-Particular \t 1- Empresa: ");
        scanf("%d",&novo->tipoConta);
        getchar();
       // retorna 1 (empresa) se<>0 e 0 (particular) se=0
        printf("\nEstado A-Activo I-Inactivo: ");
        scanf("%c",&novo->estado);
        getchar();
        printf("\nDigite o saldo Inicial: ");
        scanf("%f",&novo->saldo);
        getchar();
        d[quant]=novo;
        return true;
    }
    else {
        printf("\n Não foi possível criar a conta, tente novamente");
        return false;
    }
}

bool alterar_conta(CONTA **d, int quant){
    int id;
    printf("\n\t DIgite o Indice que quer actualizar: ");
    scanf("%d",&id);
    getchar();
    id--;
    
    if (id>=0 && id<quant)
    {
        int valorInteiro;
        CONTA *novo = (CONTA *)malloc(sizeof(CONTA));
        novo->numeroConta = a[id]->numeroConta;
        printf("\n Digite o codigo do cliente: ");
        scanf("%d",&novo->codigoCliente);
        getchar();
        printf("\nTipo de Conta 0-Particular \t 1- Empresa: ");
        scanf("%d",&novo->tipoConta);
        getchar();
       // retorna 1 (empresa) se<>0 e 0 (particular) se=0
        printf("\nEstado A-Activo I-Inactivo: ");
        scanf("%c",&novo->estado);
        getchar();
        printf("\nDigite o saldo Inicial: ");
        scanf("%f",&novo->saldo);
        getchar();
        d[id]=novo;
        return true;
    }
    else {
        printf("\n Indice Invalido!\n");
        return false;
    }
}

float consultar_saldo (CONTA **c, int quant,int numero){
    if (quantC==0)
    {
        return -2;
    }else{
        for (int i = 0; i <quant; i++)
    {
        if (numero==c[i]->numeroConta){
           return c[i]->saldo;
           // printf("\n Conta N: %d, Saldo: %.2f",c[i]->numeroConta,c[i]->saldo);
            break;
        } else if (numero!=c[i]->numeroConta){
            if (i==quant-1)
            {
                //Número da conta nao existe!
                return -1;
            }
        }
    }
    }
}

bool depositar_dinheiro(CONTA **c, int quant, int numero, float valor){
    if (quantC==0)
        {
           printf("\n Nenhuma conta criada!!!");
        }else{
            for (int i = 0; i < quant; i++)
                 { 
            if (numero==c[i]->numeroConta){               
            printf("\n Depósito no valor de %.2f feito com sucesso ",valor);
            printf("\n O saldo da conta é %.2f", c[i]->saldo+=valor);
            return true;
            break;
            }else if (numero!=c[i]->numeroConta){
               if (i==quant-1){
                    printf("\n Conta Inválida!!!");
                    return false;
                }   
            }        
                }  
        }
}

bool levantar_dinheiro(CONTA **c, int quant, int numero, float valor){
    if (quantC==0)
        {
           printf("\n Nenhuma conta criada!!!");
        }else{
            for (int i = 0; i < quant; i++){ 
            if (numero==c[i]->numeroConta && valor<=c[i]->saldo){
            printf("\n Levantamento de %.2f feito com sucesso",valor);               
            printf("\n Saldo da conta é de %.2f", c[i]->saldo-=valor);
            return true;
            break;
            }else if (numero==c[i]->numeroConta && valor>c[i]->saldo)
            {
               printf("\n Saldo insuficiente! !!");
            }
            else if (numero!=c[i]->numeroConta){
               if (i==quant-1){
                    printf("\n Conta Inválida!!!");
                    return false;
                }   
            }        
            }  
        }
}

bool transferir_dinheiro(CONTA **c, int quant, int numeroEnv, int numeroRec, float valor){
    if (quantC==0)
        {
           printf("\n Nenhuma conta criada!!!");
        }else{
            for (int i = 0; i < quant; i++){ 
            if (numeroEnv==c[i]->numeroConta && valor<=c[i]->saldo){
                float saldoReceptor;
                for (int i = 0; i < quant; i++)
                {
                   
                   if (numeroRec==c[i]->numeroConta)
                   {
                    c[i]->saldo+=valor;
                    saldoReceptor=c[i]->saldo;
                    break;
                    /* ENCONTROU E PROCEDA A TRANSFERENCIA */
                   }
                    else if (numeroRec!=c[i]->numeroConta)
                    {
                    if (i==quant-1)
                    {
                    printf("\n Conta do Receptor Inválida!!!");
                    return false;
                     }   
                    }     
                }
          c[i]->saldo-=valor;
          printf("\n Transferência no valor de %.2f feita com sucesso !!!",valor);
          printf("\n Saldo da conta %d : %.2f",numeroEnv,c[i]->saldo);
          printf("\n Saldo da conta %d : %.2f",numeroRec,saldoReceptor);
            return true;
            break;
            }else if (numeroEnv==c[i]->numeroConta && valor>c[i]->saldo)
            {
               printf("\n Saldo insuficiente! !!");
            }
            else if (numeroEnv!=c[i]->numeroConta){
               if (i==quant-1){
                    printf("\n Conta do Emissor Inválida!!!");
                    return false;
                }   
            }        
            }  
        }
}

void copia_de_seguranca (CONTA **c, int quant, char arquivo[]){
    FILE *ficheiro=fopen(arquivo,"w");
    int i;
    if (ficheiro)
    {
       fprintf(ficheiro, "%d\n",quant);
       for ( i = 0; i < quant; i++)
       {
        fprintf(ficheiro,"%d",c[i]->numeroConta);
        fprintf(ficheiro,"\n");
        fprintf(ficheiro,"%d",c[i]->codigoCliente);
        fprintf(ficheiro,"\n");
        fprintf(ficheiro,"%d",c[i]->tipoConta);
        fprintf(ficheiro,"\n");
        fprintf(ficheiro,"%c",c[i]->estado);
        fprintf(ficheiro,"\n");
        fprintf(ficheiro,"%.2f",c[i]->saldo);
        fprintf(ficheiro,"\n");
       }
       fclose(ficheiro);
    }
    else
        printf("\n\t NAO FOI POSSIVEL ABRIR/CRIAR O ARQUIVO \n");
}

int restaurar_copia_de_seguranca(CONTA **c, char arquivo[]){
  FILE *ficheiro=fopen(arquivo, "r");
  int quant=0, i;
  CONTA *novo=(CONTA *)malloc(sizeof(CONTA));

  if(ficheiro){
    fscanf(ficheiro, "%d\n", &quant);
    for (i = 0; i < quant; i++)
    {
        fscanf(ficheiro,"%d\n", &novo->numeroConta);
        fscanf(ficheiro,"%d\n", &novo->codigoCliente);
        fscanf(ficheiro, "%d\n", &novo->tipoConta);
        fscanf(ficheiro, "%c\n", &novo->estado);
        fscanf(ficheiro, "%f\n", &novo->saldo);
        c[i]=novo;
       novo=(CONTA*)malloc(sizeof(CONTA));
    }
    fclose(ficheiro);
  } else{
    printf("\n NAO FOI POSSIVEL CRIAR/ABRIR O ARQUIVO");
  }
  return quant;
}
int main(){

   quantC=restaurar_copia_de_seguranca(a,arquivoConta);

    do
    {
        printf("\n 1- Cadastrar Pessoa \t 2- Alterar Pessoa \t 3- Criar Conta \n 4- Alterar Conta\t 5- Listar Pessoas \t\t 6- Listar Contas \n 7- Consultar Saldo \t 8- Depositar Dinheiro \t 9- Levantar Dinheiro \t 10- Transferir Dinheiro \n 0- Sair\n");
        scanf("%d", &opcao);
        system("clear");
        getchar();
        switch (opcao)
        {
            bool verifica;
        case 1:
        // Criar Pessoa
        
        verifica=cadastrar_pessoa(p,quantP,tam);
        if (cadastrar_pessoa)
        {
            quantP+=1;
        }else{
            quantP+=0;
        }
        break;
        case 2:
        // Atualizar Pessoa
            imprimir_p(p,quantP);
            alterar_pessoa(p,quantP);
            break;
        case 3:
        //Criar Conta
        verifica=criar_conta(a,quantC,tam);
        if (criar_conta)
        {
            quantC+=1;
        }else{
            quantC+=0;
        } 
            break;
        case 4:
        // Atualizar Conta
            imprimir_c(a,quantC);
            alterar_conta(a,quantC);
            break;
        case 5:
         //   Imprimir Pessoas
            imprimir_p(p,quantP);
            break;
        case 6:
        //   Imprimir contas
            imprimir_c(a,quantC);
            break;
        case 7:
        // Consultar Saldo
            imprimir_c(a,quantC);
            int numConta;
            printf("\n Digite o número da conta: ");
            scanf("%d",&numConta);
            getchar();
            float consulta;
            consulta=consultar_saldo(a,quantC,numConta);
            if (consulta==-1)
            {
                printf("\n *** Número da conta nao existe!!! ***");
            } else if (consulta==-2)
            {
                printf("\n Nao ha contas no sistema");
            } else {
                printf("\n O saldo da conta: %.2f",consultar_saldo(a,quantC,numConta));
            }
            
            break;
        case 8:
        // Depositar Dinheiro
            int numeroD; float valorD;
            printf("\n Digite o número da conta a depositar: ");
            scanf("%d",&numeroD);
            getchar();
            printf("\n Digite a quantia a depositar: ");
            scanf("%f",&valorD);
            getchar();
            depositar_dinheiro(a,quantC,numeroD,fabs(valorD));
            break;
        case 9:
        // Levantar Dinheiro
            int numeroL; float valorL;
            printf("\n Digite o número da conta para o levantamento: ");
            scanf("%d",&numeroL);
            getchar();
            printf("\n Digite a quantia a levantar: ");
            scanf("%f",&valorL);
            getchar();
            levantar_dinheiro(a,quantC,numeroL,fabs(valorL));
            break;
        case 10:
        // Transferir Dinheiro
            int numeroE,numeroR; float valor;
            printf("\n Digite o número da conta emissora: ");
            scanf("%d",&numeroE);
            getchar();
            printf("\n Digite o número da conta receptora: ");
            scanf("%d",&numeroR);
            getchar();
            printf("\n Digite o valor a transferir: ");
            scanf("%f",&valor);
            getchar();
            transferir_dinheiro(a,quantC,numeroE,numeroR,valor);
            break;
        default:
            break;
        }
    } while (opcao!=0);
    if (opcao==0)
    {
      copia_de_seguranca(a,quantC,arquivoConta);
    }
    
    
    return 0;
}

