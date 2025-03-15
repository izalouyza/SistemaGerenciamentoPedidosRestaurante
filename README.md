# Sistema de Gerenciamento de Pedidos de Restaurante

Esse repositório refere-se ao trabalho da disciplina de Estrutura de Dados I, ministrada pelo professor George Felipe Fernandes Vieira. O projeto é destinado a desenvolver um sistema de gerenciamento de pedidos de restaurante. Dessa forma, este sistema terá como objetivo principal a gestão de pedidos e do cardápio de um restaurante, permitindo o controle eficiente dos pedidos e a administração dos itens disponíveis.

## 1. Funcionalidades

O sistema de Gerenciamento de Pedidos para Restaurante terá as seguintes funcionalidades:

| Funcionalidade              | Características                                                   |
|-----------------------------|-------------------------------------------------------------------|
| Cadastro de Itens           | Permite cadastrar um novo item no cardápio.                     |
| Exibir Cardápio             | Exibe todos os itens cadastrados no cardápio.                   |
| Atualizar Cardápio          | Permite atualizar as informações de um item já cadastrado.      |
| Remover Item do Cardápio    | Permite que o usuário remova um item do cardápio pelo código.   |
| Criar Pedido                | Permite criar um novo pedido.                                   |
| Gerenciar Pedidos           | Exibe todos os pedidos realizados.                              |
| Alterar Status do Pedido    | Permite alterar o status de um pedido.                         |
| Alterar Pedido              | Permite modificar os itens de um pedido já existente.          |
| Remover Pedido              | Remove um pedido com base no código informado.                 |
| Sair                        | Encerra a execução do sistema.                                  |

## 2. Como o sistema funciona?

O usuário terá acesso a uma interface interativa onde poderá visualizar as funcionalidades disponíveis e interagir com o sistema. 

### 2.1 Exemplo de Fluxo de Uso

- **Cadastre alguns itens no cardápio** (opção 1).
- **Crie um pedido para um cliente**, selecionando os itens desejados (opção 5).
- **Acompanhe o status do pedido** e altere-o conforme necessário (opção 6 e 7, respectivamente).
- **Exiba o cardápio ou a lista de pedidos** para verificar as informações (opções 2 e 6).
- **Ao finalizar, saia do sistema** (opção 10).

### 2.2 Estrutura de pastas

```
SistemaGerenciamentoPedidosRestaurante/
│
├── ManualdeUso/
│   └── ManualdeUso.pdf
│
├── Relatorio/
│   └── Relatorio.pdf
│
├── gerenciamento-restaurante/
│   ├── cardapio_pedidos/
│   │   ├── cardapio.c
│   │   ├── cardapio.h
│   │   ├── main.c
│   │   ├── pedidos.c
│   │   ├── pedidos.h
│   │   ├── utilitarios.c
│   │   └── utilitarios.h
│   │
│   └── codigo-fonte.c
│
└── README.md

```
- **ManualdeUso.pdf**: arquivo que contém o documento com o manual de uso do sistema.
- **Relatorio.pdf**: arquivo que contém o documento com o relatório geral do sistema.
- **cardapio.c**: arquivo que contém a implementação das funções relacionadas ao cardápio.
- **cardapio.h**: arquivo que contém a declaração das funções relacionadas ao cardápio.
- **main.c**: arquivo que contém a função principal do sistema.
- **pedidos.c**: arquivo que contém a implementação das funções relacionadas aos pedidos.
- **pedidos.h**: arquivo que contém a declaração das funções relacionadas aos pedidos.
- **utilitarios.c**: arquivo que contém a implementação de funções utilitárias.
- **utilitarios.h**: arquivo que contém a declaração das funções utilitárias.
- **codigo-fonte.c**: arquivo que contém o código-fonte do sistema.

### 2.3 Estruturas de dados utilizadas

#### 2.3.1 Ponteiros
Os ponteiros são variáveis que armazenam o endereço de memória de outras variáveis. Dizemos que um ponteiro “aponta” para uma variável quando contém o endereço da mesma. Eles são muito úteis quando uma variável precisa ser acessada em qualquer parte do programa, proporcionando maior flexibilidade para quem os manuseia.

#### 2.3.2 Strings com Ponteiros
Ponteiros podem “apontar” para qualquer tipo de variável e string é uma delas. No sistema, strings são manipuladas utilizando ponteiros, especialmente nas funções que recebem e retornam strings. O uso de `fgets` para ler strings e `strcspn` para remover quebras de linha são exemplos de operações básicas com strings e estão presentes no código.

#### 2.3.3 Alocação Dinâmica de Memória
A alocação dinâmica de memória nos permite alocar espaços na memória do computador durante a execução de um programa e é de grande utilidade pois o espaço é alocado apenas quando necessário. Além disso, a alocação de memória é bastante flexível, permitindo aumentar ou diminuir a quantidade de memória alocada. O sistema utiliza alocação dinâmica de memória para gerenciar o armazenamento de itens do cardápio e pedidos. As funções `malloc` e `realloc` são empregadas para alocar e redimensionar a memória conforme a necessidade.

#### 2.3.4 Vetores Dinâmicos
Um vetor dinâmico é uma estrutura de dados que possui um espaço contínuo na memória, no entanto, quando a capacidade chega em seu limite, o vetor é realocado para um tamanho maior que o anterior em tempo de execução, ou seja, quando o código está sendo executado. No sistema, vetores dinâmicos são utilizados para armazenar listas de itens do cardápio e pedidos, utilizando funções para redimensionar a memória e reorganizar os dados.

#### 2.3.5 Structs
As structs são variáveis especiais que contém outras variáveis de tipos iguais ou diferentes. Podemos associar as structs da linguagem C aos denominados registros em outras linguagens de programação. No sistema de gerenciamento de pedidos para restaurante, as structs são definidas para representar os itens do cardápio e os pedidos, facilitando a manipulação dos dados. Cada struct contém campos que armazenam informações relevantes, como nome, descrição, preço e status.

#### 2.3.6 Enumerações
Enum em C é um tipo de dado definido previamente pelo usuário que recebe apenas um conjunto restrito de valores. Ele pode ser usado para definir um conjunto de nomes simbólicos que representam valores inteiros. Essas enumerações são utilizadas no sistema para definir categorias de pratos e status dos pedidos, garantindo maior clareza e organização do código.

### 2.4 Funcionamento do sistema

O sistema de Gerenciamento de Pedidos para Restaurante permite que o usuário realize as seguintes ações:

```
========================================== Gerenciamento do Restaurante ===================================

(1) Cadastrar item  
(2) Exibir cardápio  
(3) Atualizar cardápio  
(4) Remover itens do cardápio  
(5) Criar pedido  
(6) Gerenciar pedidos  
(7) Alterar status de pedidos  
(8) Alterar pedido  
(9) Remover pedido  
(10) Sair  

<< Informe a opção:

```
#### Menu principal do sistema:
- **Cadastrar item**: o sistema permite cadastrar um novo item no cardápio.  
- **Exibir cardápio**: o sistema exibe todos os itens cadastrados no cardápio.  
- **Atualizar cardápio**: o sistema permite atualizar as informações de um item já cadastrado.  
- **Remover itens do cardápio**: o sistema permite remover um item do cardápio com base no código informado.  
- **Criar pedido**: o sistema permite criar um novo pedido.  
- **Gerenciar pedidos**: o sistema exibe todos os pedidos realizados.  
- **Alterar status de pedidos**: o sistema permite alterar o status de um pedido.  
- **Alterar pedido**: o sistema permite modificar os itens de um pedido já existente.  
- **Remover pedido**: o sistema remove um pedido com base no código informado.  
- **Sair**: o usuário encerra o sistema.  


### 3. Como compilar e executar o sistema

Para compilar e executar o sistema, siga os passos abaixo:

1. Primeiramente, certifique-se de ter um ambiente que suporte a linguagem C e um compilador (por exemplo, GCC).
   
2. Clone o repositório do projeto:

```
git clone https://github.com/whorshe/SistemaGerenciamentoPedidosRestaurante
```

3. Acesse a pasta do projeto e siga até o diretório onde os códigos estão alocados:
   
```
cd SistemaGerenciamentoPedidosRestaurante
```

```
cd gerenciamento-restaurante
```

```
cd cardapio_pedidos
```

4. Compile o programa:

```
gcc -o restaurante main.c cardapio.c pedidos.c utilitarios.c
```

5. Execute o programa:
   
```
.\restaurante
```

### 4. Participantes

🔹 **Izadora Louyza Silva Figueiredo**  
🔹 **Lívian Maria Lucena Gomes Pinheiro**  
🔹 **Maria Vitória Fernandes Rocha**  
🔹 **Renato Vitor Juvêncio Leite**  
🔹 **Victor Hugo de Oliveira**
