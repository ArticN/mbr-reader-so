
# MBR Reader - Leitura e Exibição de Tabela de Partições

## Descrição

Este projeto foi desenvolvido para ler e exibir informações de um arquivo MBR (Master Boot Record) a partir de uma imagem de disco binária. O programa fornece uma saída semelhante ao comando `fdisk -l` do Linux, mostrando as partições e informações do disco, como tipo de partição, início e fim dos setores, tamanho e identificador.

## Funcionalidades

- Leitura de MBR de uma imagem binária.
- Exibição das informações do disco, como:
  - Tamanho total do disco.
  - Tamanho de cada setor.
  - Tipo de rótulo do disco.
  - Identificador do disco.
  - Tabela de partições, com informações detalhadas sobre cada partição.
- Identificação do tipo de cada partição, como FAT12, NTFS, Linux, etc.

## Estrutura do Projeto

- **main.c**: Função principal que gerencia a leitura do arquivo MBR e a exibição dos dados.
- **mbr_reader.c**: Funções auxiliares que processam e extraem informações do MBR.
- **mbr_reader.h**: Cabeçalhos e definições usadas no projeto.
  
## Como Rodar

### Pré-requisitos

- Um ambiente Linux ou similar.
- Um compilador C (como `gcc`).
- Uma imagem de MBR (arquivo `.bin`).

### Passo 1: Baixar o Código

Clone ou baixe o código fonte do projeto em seu computador.

```bash
git clone <URL_DO_REPOSITORIO>
```

### Passo 2: Compilar o Código

Dentro do diretório do projeto, compile o código com `gcc`.

```bash
gcc -o mbr_reader main.c mbr_reader.c
```

### Passo 3: Executar o Programa

Para rodar o programa, basta passar o caminho de um arquivo MBR como argumento. Por exemplo:

```bash
./mbr_reader mbr_test.bin
```

### Exemplo de Saída

A saída do programa será semelhante ao seguinte:

```
Disk: 80.00 GiB, 85899345408 bytes, 167772159 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x00000000

Device     Boot      Start         End      Sectors    Size   Id   Type
-------------------------------------------------------------------------
/dev/sda1                  1  167772159  167772159     4095M  EE    0xEE
```