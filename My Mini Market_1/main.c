/* Código desenvolvido em plataforma online (OnlineGDB, https://www.onlinegdb.com/),
baseada em LINUX, não sendo possível sua execução em plataforma WINDOWS. Para executar o código em uma IDE rodando em WINDOWS,
é necessária uma alteração na função >>limpaCmd();<< na linha 143 do código, onde a função >>system("clear");<< deve ser substituída
pela função >>system("cls");<<. Para executar o código usando o OnlineGDB, não são necessárias alterações. */

/* É necessário realizar o cadastro de produtos e clientes no sistema, pois inicialmente
os arquivos (banco de dados locais) estão vazios. É preciso alimentar o sistema com cadastros. */


//>>Bibliotecas incluidas
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//===============================================================================================================================

//STRUCTS
//>>Endereço do cliente
typedef struct{
    char torre[20]; //Informa a torre do cliente dentro do condominio
    unsigned int ap; //Informa o número do apartamento dentro da torre do cliente
}Endereco;

//>>Cadastro do clientes
typedef struct{
    char nome[50]; //Nome do cadastrado
    char cpf[20]; //CPF do cadastrado
    Endereco endereco; //Endereço residencial do cadastrado
    char tel[20]; //Telefone para contato do cadastrado
}Cadastro;

//>>Cadastro de produtos
typedef struct{
    unsigned int id;//Indica se a posição no vetor da struct já possui um cadastro ou não
    char nome[50]; //Nome do produto
    float preco; //Preço do produto
}Produto;
//===============================================================================================================================

//>>Produtos escolhidos (carrinho)
typedef struct{
    unsigned int id;//Id do produto colocado no carrinho
    char nome[50]; //Nome do produto
    float preco; //Preço do produto
}Carrinho;
//===============================================================================================================================

//VETORES
Cadastro cadastros[100] = {0};//Inicializando o vetor de structs
Produto produtos[100] = {0};//Inicializando o vetor de structs
Carrinho carrinho[100] = {0};//Inicializando o vetor do carrinho
//===============================================================================================================================

//VARIAVEIS
int qtd1 = 0;//Variável que registra a quantidade de clientes para o arquivo 1(banco de dados locál)
int qtd2 = 0;//Variável que registra a quantidade de clientes para o arquivo 2(banco de dados locál)
float totalCarrinho = 0;//Contem o custo total do carrinho do cliente
int itensCarrinho = 0;//Contador de intens no carrinho do cliente
//===============================================================================================================================

//>>>FUNÇÕES
//>>LEITURA e ESCRITA de arquivo para a struct CADASTRO
//>Leitura de cadastros armazenados
void uploadArquivo1(){

    FILE *a1 = fopen("cadastros.dat", "rb");//Inicialisando o arquivo

    if (a1 == NULL) {
        return;
    }

    Cadastro temp;
    qtd1 = 0;

    while (fread(&temp, sizeof(Cadastro), 1, a1) == 1) {//Descarregando os dados do arquivo no vetor de structs
        cadastros[qtd1] = temp;
        qtd1++;
    }

    fclose(a1);//Fechando o arquivo
}
//>Escrita de cadastros para armazenamento
void downloadArquivo1(){

    FILE *a1 = fopen("cadastros.dat", "wb");//Inicialisando o arquivo

    if (a1 == NULL) {
        printf("Erro ao salvar arquivo!\n");
        return;
    }

    fwrite(cadastros, sizeof(Cadastro), qtd1, a1);//Escrevendo os dados do vetor de structs no arquivo

    fclose(a1);//Fechando o arquivo

    printf("\nDados salvos com sucesso!\n");
}

//>>LEITURA e ESCRITA de arquivo para a struct PRODUTO
//>Leitura de cadastros armazenados
void uploadArquivo2(){

    FILE *a2 = fopen("produtos.dat", "rb");

    if (a2 == NULL) {
        return;
    }

    Produto temp;
    qtd2 = 0;

    while (fread(&temp, sizeof(Produto), 1, a2) == 1) {
        produtos[qtd2] = temp;
        qtd2++;
    }

    fclose(a2);
}
//>Escrita de cadastros para armazenamento
void downloadArquivo2(){

    FILE *a2 = fopen("produtos.dat", "wb");

    if (a2 == NULL) {
        printf("Erro ao salvar arquivo!\n");
        return;
    }

    fwrite(produtos, sizeof(Produto), qtd2, a2);

    fclose(a2);

    printf("\n\nDados salvos com sucesso!\n");
}

//>>Cabeçalho principal
void cabecalho(){
    printf("========================================================================================================================");
    printf("\n                                            >>>>>>>>>> MY MINI MARKET <<<<<<<<<<               \n");
    printf("========================================================================================================================\n");
}
//>>Limpa a tela do usuário de informações antigas
void limpaCmd(){
    system("clear");
    cabecalho();
}
//>>Cadastro de clientes
void cadastro_cliente(){

    printf("\n\n-------------------- Cadastro de >> CLIENTES << --------------------");
            //Verificando se o vetor de structs está sem espaço disponivel
            if (qtd1 >= 100) {
                printf("Limite de clientes cadastrados atingido!\n");
                return;
            }
            //Declarando uma struct temporaria
            Cadastro temp;
            //Coletando dados para cadastro
            printf("\n\nDigite o nome completo (sem acentos ou pontuações: ");
            fgets(temp.nome, sizeof(temp.nome), stdin);
            printf("Digite seu CPF (sem pontuacoes): ");
            scanf("%11s",&temp.cpf);
            getchar();
            printf("Qual seu endereco aqui no condominio??");
            printf("\nTorre: ");
            fgets(temp.endereco.torre, sizeof(temp.endereco.torre), stdin);
            printf("Apartamento: ");
            scanf("%d",&temp.endereco.ap);
            printf("Digite seu Telefone (sem pontuacoes): ");
            scanf("%11s",&temp.tel);
            getchar();
            //Guardando dados coletados no vetor de structs
            cadastros[qtd1] = temp;
            //Somando valor ao contador de clientes cadastrados
            qtd1++;

            puts("\n>>>>>>>>>> CADASTRO FINALIZADO <<<<<<<<<<");
}

//>>Edição dados do clientes
void editarCliente(){
    //Declarando struturas temporarias
    Cadastro temp1 = {0};
    Cadastro temp2 = {0};
    //Variavel auxiliar, para validação de cpf não encontrado
    int x = 0;
    //Coletando o CPF solicitado pelo usuário
    printf("Digite o CPF do cliente (sem pontuacoes): ");
    scanf("%11s",&temp1.cpf);
    getchar();
    //Estrutura que valida o CPF digitado pelo usuário com os CPFs armazenados no bando de daodos local
    for(int e = 0; e < 100; e++){
            temp2 = cadastros[e];
            if(strcmp(temp1.cpf, temp2.cpf) == 0){
                x = 1;
                //Imprimindo os dados salvos no banco de dados
                puts("\n=================ENCONTRADO================");
                puts("===============CADASTRO ATUAL==============");
                printf("---------------");
                printf("\nNome: %s",temp2.nome);
                printf("CPF: %s",temp2.cpf);
                printf("\nTorre: %s",temp2.endereco.torre);
                printf("Ap: %d\n",temp2.endereco.ap);
                printf("Telefone: %s\n",temp2.tel);
                printf("---------------");
                //Coletando os dados para atualização.
                puts("\n===============ATUALISE O CADASTRO==============");
                printf("Digite o nome completo (sem acentos ou pontuações: ");
                fgets(temp1.nome, sizeof(temp1.nome), stdin);
                printf("Digite seu CPF (sem pontuacoes): ");
                scanf("%11s",&temp1.cpf);
                getchar();
                printf("Qual seu endereco aqui no condominio??");
                printf("\nTorre: ");
                fgets(temp1.endereco.torre, sizeof(temp1.endereco.torre), stdin);
                printf("Apartamento: ");
                scanf("%d",&temp1.endereco.ap);
                printf("Digite seu Telefone (sem pontuacoes): ");
                scanf("%11s",&temp1.tel);
                getchar();
                //Atualizando o vetos de structs com as novas informações
                cadastros[e] = temp1;
                //Imprimindo a atualização feita pelo usuário
                puts("\n===============CADASTRO ATUALISADO==============");
                printf("---------------");
                printf("\nNome: %s",cadastros[e].nome);
                printf("CPF: %s",cadastros[e].cpf);
                printf("\nTorre: %s",cadastros[e].endereco.torre);
                printf("Ap: %d\n",cadastros[e].endereco.ap);
                printf("Telefone: %s\n",cadastros[e].tel);
                printf("---------------");
                //Atualizando o arquivo local
                downloadArquivo1();
                break;
            }
    }
    if(x == 0){puts("\n===============CPF NAO ENCONTRADO==============\n");}
}

//>>Edição dados do clientes
void excluirCliente(){
    //Declarando struturas temporarias
    Cadastro temp1 = {0};
    Cadastro temp2 = {0};
    //Variavel auxiliar, para validação de cpf não encontrado
    int x = 0;
    //Coletando o CPF solicitado pelo usuário
    printf("Digite o CPF do cliente (sem pontuacoes): ");
    scanf("%11s",&temp1.cpf);
    getchar();
    //Estrutura que valida o CPF digitado pelo usuário com os CPFs armazenados no bando de daodos local
    for(int e = 0; e < 100; e++){
            temp2 = cadastros[e];
            if(strcmp(temp1.cpf, temp2.cpf) == 0){
                x = 1;

                puts("\n=================ENCONTRADO================");
                puts("===============CADASTRO ATUAL==============");
                printf("---------------");
                printf("\nNome: %s",temp2.nome);
                printf("CPF: %s",temp2.cpf);
                printf("\nTorre: %s",temp2.endereco.torre);
                printf("Ap: %d\n",temp2.endereco.ap);
                printf("Telefone: %s\n",temp2.tel);
                printf("---------------");
                //Excluindo os dados solicitados
                Cadastro temp3 = {0};
                //Atualizando vetor de structs
                cadastros[e] = temp3;

                puts("\n===============CADASTRO EXCLUIDO==============");
                printf("---------------");
                printf("\nNome: %s",cadastros[e].nome);
                printf("\nCPF: %s",cadastros[e].cpf);
                printf("\nTorre: %s",cadastros[e].endereco.torre);
                printf("\nAp: %d",cadastros[e].endereco.ap);
                printf("\nTelefone: %s\n",cadastros[e].tel);
                printf("---------------");
                //Decrementando do contados de cadastros após a exclusão solicitada
                qtd1--;
                //Atualisando o arquivo local
                downloadArquivo1();
                break;
            }
    }
    if(x == 0){puts("\n===============CPF NAO ENCONTRADO==============\n");}
}

//>>Cadastro de produtos
void cadastro_produto(){

    printf("\n\n-------------------- Cadastro de >> PRODUTOS << --------------------");
            //Validando o limite de cadastros
            if (qtd2 >= 100) {
                printf("Limite de produtos cadastrados atingido!\n");
                return;
            }
            //estrutura auxiliar
            Produto temp;
            //Coletando informações do produto a ser cadastrado
            printf("\n\nDigite o nome do produto(Usar UNDERLINE para espaços): ");
            scanf("%20s",&temp.nome);
            getchar();
            printf("Digite o preco do produto(Usar PONTO no lugar de VIRGULA): R$");
            scanf("%f",&temp.preco);
            getchar();
            printf("Digite o ID do produto com 4 digitos(Somente números INTEIROS: ");
            scanf("%d",&temp.id);
            getchar();
            //Atualizando o vetor de produtos
            produtos[qtd2] = temp;
            //Somando uma unidade no contador de produtos cadastrados
            qtd2++;
            //Limpando o cmd
            limpaCmd();
            puts("\n>>>>>>>>>> CADASTRO FINALIZADO <<<<<<<<<<");
}
//>>Imprime a lista de clientes cadastrados
void listarCadastros(){
    //Validando a existencia de informações cadastradas
    if (qtd1 == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    //Imprimindo a lista de clientes cadastrados
    printf("\n--- LISTA DE CLIENTES ---\n");
    for (int i = 0; i < qtd1; i++) {

        printf("\n---------------");
        printf("\nNome: %s",cadastros[i].nome);
        printf("CPF: %s",cadastros[i].cpf);
        printf("\nTorre: %s",cadastros[i].endereco.torre);
        printf("Ap: %d\n",cadastros[i].endereco.ap);
        printf("---------------");

    }
}
//>>Imprime a lista de produtos cadastrados
void listarProdutos(){
    if (qtd2 == 0) {
        printf("Nenhum produto cadastrado.\n");
        puts("===== 2 para Administrador >> 1 para Cadastrar Produto =====");
        exit(0);
        return;
    }

    printf("\n--- LISTA DE PRODUTOS ---\n");
    for (int i = 0; i < qtd2; i++) {

        printf("\n---------------");
        printf("\nProduto: %s <<<",produtos[i].nome);
        printf("\nPreco: R$%.2f <<<",produtos[i].preco);
        printf("\nID: %d <<<",produtos[i].id);
        printf("\n---------------");
    }
}
//>>Imprime a lista com os produtos guardados no carrinhho pelo cliente
void listarCarrinho(){
    //Verificando o carrinho do cliente
    if (itensCarrinho == 0){
        limpaCmd();
        puts("\n--- CARRINHO VAZIO ---");
        printf("--- Nenhuma Compra Realizada ---\n");
        exit(0);
        return;
    }
    //Imprindo os produtos encontrados no carrinho
    printf("\n--- PRODUTOS NO SEU CARRINHO ---\n");
    for (int i = 0; i < itensCarrinho; i++){

        printf("\n---------------");
        printf("\nProduto: %s <<<",carrinho[i].nome);
        printf("\nPreco: R$%.2f <<<",carrinho[i].preco);
        printf("\nID: %d <<<",carrinho[i].id);
        printf("\n---------------");
    }
}

//>>Trasfere os informações do vetor de produtos cadastrados para o carrinho do cliente, somente as informações dos produtos selecionados
void addCarrinho(Carrinho *c, Produto *p){
    strcpy(c->nome, p->nome);
    c -> preco = p -> preco;
}
//>>Função reponsavel por gerenciar os escolhas de produto do usuário
void escolherProduto(){
    int a3 = 0;
    //Laço responsavel por realizar a escolha continua de produtos pelo usuário
    while(true){
        Carrinho tempC = {0};
        Produto tempP = {0};

        puts("\n>>> ESCOLHA SEU PRODUTO <<<");
        listarProdutos();
        printf("\nDigite o >> ID << do produto escolhido: ");
        scanf("%d",&tempC.id);
        //Verificando os codigos de produto de acordo ao código fornecido pelo usuário
        for(int e = 0; e < 100; e++){
            tempP = produtos[e];
            if(tempC.id == tempP.id){
                addCarrinho(&tempC, &tempP);
                carrinho[e] = tempC;
                totalCarrinho += tempP.preco;
                itensCarrinho ++;
                break;
            }
        }
        //Validando a continuidade das compras do cliente ou não
        while(true){
            puts("Continuar Comprando??");
            puts("Digite >> 1 << para sim ou >> 2 << para não!!");
            scanf("%d...:", &a3);
            if(a3 != 1 && a3 != 2){limpaCmd();printf("\nOpção >>INVALIDA<<, tente novamente!!\n");a3 = 0;}
            else{break;}
        }
        if(a3 == 2){break;}

        else{limpaCmd();puts("\nShow, continue comprando!!");}
    }
    limpaCmd();
    puts("\n>>> OBRIGADO POR SUA COMPRA <<<");
    listarCarrinho();
    itensCarrinho = 0;
    puts("\n>>> VAMOS AO PAGAMENTO <<<");

}
//>>Validando a etapa de pagamento
void pagamento(){
    Cadastro temp = {0};;
    int a4 = 0;
    char fpc [20] = {0};
    //Validando o forma de compra do cliente
    while(true){
        puts("Digite >> 1 << para ENTRAGA");
        puts("Digite >> 2 << para RETIRADA");
        scanf("%d...:", &a4);
        if(a4 != 1 && a4 != 2){limpaCmd();printf("\nOpção >> INDISPONIVEL <<, tente novamente!!\n");a4 = 0;}
        else{break;}
    }
    //Validando as informações para a opção de entrega
    if(a4 == 1){
        limpaCmd();
        a4 = 0;
        while(true){
            puts("Digite seu CPF (Sem pontuacoes):");
            scanf("%14s", &fpc);
            getchar();
            int tamanho = strlen(fpc);

            if(tamanho == 11){
                int x = 0;
                for(int e = 0; e < 100; e++){
                    temp = cadastros[e];

                    if(strcmp(fpc, temp.cpf) == 0){
                    //limpaCmd();
                    puts("\n<<<<< CONFIRME SEU ENDERECO >>>>>");
                    printf("Torre: %s",&temp.endereco.torre);
                    printf("Ap: %d\n\n",&temp.endereco.ap);
                    break;
                    }
                    x++;
                }
                if(x == 100){
                    limpaCmd();
                    puts("\nCPF NAO ENCONTRADO VERIFIQUE SEU CADASTRO");
                    puts("OPCAO DE ENTREGA INDISPONIVEL");
                    puts("===============RETIRE SUAS COMPRAS==============\n");
                }
                break;
            }
            else{limpaCmd();puts("<<<<< CPF INVALIDO, TENTE NOVAMENTE >>>>>");}
        }
    }
    //Validando o pagamento do cliente e encerrando as compras
    while(true){
        puts("<<<<< FORMA DE PAGAMENTO >>>>>");
        puts("Digite >> 1 << para CARTAO");
        puts("Digite >> 2 << para PIX");
        scanf("%d...:", &a4);
        if(a4 != 1 && a4 != 2){limpaCmd();printf("\nOpção >> INDISPONIVEL <<, tente novamente!!\n");a4 = 0;}
        else{a4 = 0;break;}
    }

     while(true){
        limpaCmd();
        puts("\nDigite 1 para confirmar o <<< PAGAMENTO >>>");
        scanf("%d...:", &a4);
        if(a4 != 1){limpaCmd();printf("\nOpção >>INDISPONIVEL<<, tente novamente!!\n");a4 = 0;}
        else{break;}
    }
    printf("========================================================================================================================");
    printf("\n                                               >>>>>>>>>> OBRIGADO <<<<<<<<<<               \n");
    printf("========================================================================================================================");
}
//===============================================================================================================================

int main(){
//>Funções para leitura dos arquivos que guardam os dados das principais Structs
uploadArquivo1();
uploadArquivo2();
//===============================================================================================================================

    int a = 0;
    cabecalho();
    //Loop que garante a escolha correta entre as opções do sistema
    while(true){
        //Entendendo quem é o usúario para o sistema
        puts("\n>>> BEM VINDO!! <<<");
        puts("Digite >>1<< para >>CLIENTE<<");
        puts("Digite >>2<< para >>ADMINISTRADOR<<");
        scanf("%d...:", &a);

        if(a != 1 && a != 2){limpaCmd();printf("\nOpção >>INVALIDA<<, tente novamente!!\n");a = 0;}
        else{break;}
    }
    //Área do sistema destinada ao cliente
    if(a == 1){
        int b = 0;
        limpaCmd();
        //Loop que garante a escolha correta entre as opções do sistema
        while(true){
            puts("\n>>> VAMOS AS COMPRAS?? <<<");
            puts("Digite >>1<< se ja possui >>CADASTRO<<");
            puts("Digite >>2<< se precisa se >>CADASTRAR<<");
            scanf("%d...:", &b);

            if(b != 1 && b != 2){limpaCmd();printf("\nOpção >>INVALIDA<<, tente novamente!!\n");b = 0;}
            else{break;}
        }
        //Condições que verificam se o usuario já tem cadastro ou precisa se cadastrar
        if(b == 1){
            limpaCmd();
            //Funções validas para clientes já cadastrados
            //Exibindo as opções de produtos disponiveis
            escolherProduto();
            //iniciando a etapa de pagamento
            pagamento();
        }
        else{
            limpaCmd();
            getchar();
            //Funções validas para clientes não cadastrados
            //Cadastrando clientes
            cadastro_cliente();
            //Salvando o cadastro realisado
            downloadArquivo1();
        }
    }
    //Área do sistema destinada ao administrador
    else{
        int c = 0;
        limpaCmd();
        //Loop que garante a escolha correta entre as opções do sistema
        while(true){
            //Funções disponiveis para o administrador
            puts("\n>>> BEM VINDO ADM <<<");
            puts("Digite >>1<< para cadastrar >>PRODUTOS<<");
            puts("Digite >>2<< para gerar >>RELATORIOS<<");
            puts("Digite >>3<< para editar >>CLIENTES<<");
            puts("Digite >>4<< para excluir >>CLIENTES<<");
            scanf("%d...:",&c);

            if(c != 1 && c != 2 && c != 3 && c != 4){limpaCmd();printf("\nOpcao >>INDISPONIVEL<<, tente novamente!!\n");c = 0;}
            else{break;}
        }
        //Condições que verificam se o ADM quer cadastrar novos produtos
        if(c == 1){
            limpaCmd();
            getchar();
            //Cadastrando produtor
            cadastro_produto();
            //Listando produtos
            listarProdutos();
            //Atualisando o arquivo referente aos produtos
            downloadArquivo2();
        }
        //Opções de relatório disponiveis ao administrador
        else if(c == 2){
            limpaCmd();
            int opcao = 0;
            int d = 0;

            while(true){
                puts("\n===============ESCOLHA SEU RELATORIO==============\n");
                puts("Digite >> 1 << para estoque!");
                puts("Digite >> 2 << para clientes cadastrados!");
                scanf("%d...:",&opcao);
                switch (opcao) {
                    case 1:
                        limpaCmd();
                        puts("\n===============PRODUTOS EM ESTOQUE==============\n");
                        listarProdutos();
                        d = 1;
                        break;

                    case 2:
                        limpaCmd();
                        puts("\n===============CLIENTES CADASTRADOS==============\n");
                        listarCadastros();
                        d = 1;
                        break;

                    default:
                        limpaCmd();
                        printf("\nOpção inválida!");
                        break;
                }if(d == 1){d = 0;break;}
            }
        }
        //Editando dados de clientes
        else if(c == 3){
            limpaCmd();
            editarCliente();
        }
        //excluindo dados de clientes
        else{
            limpaCmd();
            excluirCliente();
        }
    }
    return 0;
}
