# Documentação - Leitor de MBR (Master Boot Record)

## Sumário
- [Documentação - Leitor de MBR (Master Boot Record)](#documentação---leitor-de-mbr-master-boot-record)
  - [Sumário](#sumário)
  - [Introdução](#introdução)
  - [Estrutura dos Arquivos](#estrutura-dos-arquivos)
    - [`mbr_reader.h`](#mbr_readerh)
    - [`mbr_reader.c`](#mbr_readerc)
    - [`main.c`](#mainc)
  - [Definições de Constantes](#definições-de-constantes)
  - [Estruturas](#estruturas)
    - [`PartitionEntry`](#partitionentry)
  - [Funções](#funções)
    - [`obter_tipo_particao`](#obter_tipo_particao)
    - [`extrair_entrada_particao`](#extrair_entrada_particao)
    - [`imprimir_entrada_particao`](#imprimir_entrada_particao)
    - [`imprimir_tabela_particoes`](#imprimir_tabela_particoes)
    - [Compilação](#compilação)
    - [Execução](#execução)
      - [Saída Esperada](#saída-esperada)
      - [Detalhes da Saída](#detalhes-da-saída)

---

## Introdução
Este conjunto de arquivos permite a leitura e interpretação da Master Boot Record (MBR) de um dispositivo de armazenamento. A MBR contém informações essenciais sobre as partições do disco, como o endereço de início e o tipo de sistema de arquivos. O programa lê a MBR de um arquivo, extrai as entradas da tabela de partições e exibe essas informações de forma legível.

---

## Estrutura dos Arquivos

### `mbr_reader.h`
Contém as definições das constantes, a estrutura para a tabela de partições e os protótipos das funções utilizadas para manipular e exibir as informações da MBR.

### `mbr_reader.c`
Implementa as funções definidas no arquivo de cabeçalho. Lida diretamente com a interpretação e exibição das entradas da tabela de partições.

### `main.c`
Arquivo principal que executa a leitura de um arquivo MBR, utiliza as funções definidas para extrair as partições e imprimir as informações.

---

## Definições de Constantes

- **TAMANHO_MBR**: Tamanho padrão da MBR (512 bytes).
- **TAMANHO_ENTRADA_PARTICAO**: Tamanho de cada entrada da tabela de partições (16 bytes).
- **DESLOCAMENTO_TABELA_PARTICOES**: Deslocamento dentro da MBR onde a tabela de partições começa (446 bytes).
- **NUM_PARTICOES**: Número máximo de partições na tabela de partições (4).
- **TAMANHO_SETOR**: Tamanho de um setor em bytes (512 bytes).
- **TAMANHO_SETOR_MB**: Quantidade de setores equivalentes a 1 MB (2048 setores).

---

## Estruturas

### `PartitionEntry`
Representa uma entrada da tabela de partições com os seguintes campos:
- **boot_flag**: Indica se a partição é bootável (0x80) ou não (0x00).
- **partition_type**: Tipo da partição (código hexadecimal).
- **start_lba**: Endereço LBA (Logical Block Addressing) de início da partição.
- **sectors_count**: Número total de setores ocupados pela partição.

---

## Funções

### `obter_tipo_particao`
```c
const char* obter_tipo_particao(unsigned char partition_type);
```
Retorna uma string que representa o nome do tipo de partição com base no código hexadecimal fornecido.

    Parâmetro:
        partition_type: Código hexadecimal do tipo de partição.
    Retorno: Nome do tipo de partição.
### `extrair_entrada_particao`
```c
void extrair_entrada_particao(const unsigned char *mbr, int offset, PartitionEntry *entry);
```
Extrai uma entrada de partição da MBR a partir de um deslocamento específico e armazena as informações em uma estrutura PartitionEntry.

    Parâmetros:
        mbr: Array de bytes contendo a MBR.
        offset: Posição dentro da MBR onde a entrada de partição começa.
        entry: Ponteiro para a estrutura onde as informações da partição serão armazenadas.
### `imprimir_entrada_particao`
```c
void imprimir_entrada_particao(int index, const PartitionEntry *p);
```
Imprime as informações de uma entrada de partição, como o endereço inicial e final, o número de setores, o tamanho em MB, e o tipo da partição.

    Parâmetros:
        index: Índice da partição (ex: 1 para /dev/sda1).
        p: Ponteiro para a estrutura PartitionEntry contendo as informações da partição.
### `imprimir_tabela_particoes`
```c
void imprimir_tabela_particoes(const PartitionEntry *partition_table);
```
Imprime a tabela completa de partições, iterando sobre as entradas e chamando imprimir_entrada_particao para cada uma.

    Parâmetro:
        partition_table: Array contendo as entradas de partição.

        Exemplo de Uso

### Compilação

Para compilar o programa, use o seguinte comando:

```bash
gcc -std=c99 -o mbr_reader main.c mbr_reader.c mbr_reader.h
```
### Execução

Para executar o programa, forneça um arquivo binário que contenha a MBR como argumento:

```bash
./mbr_reader mbr.bin
```
#### Saída Esperada

O programa imprime uma tabela com as informações das partições, similar à saída do comando fdisk:

```yaml

Device     Boot   Start       End        Sectors  Size   Id  Type
/dev/sda1  *      2048       4096       2048     1M     07  NTFS/exFAT
/dev/sda2         4097       8192       4096     2M     83  Linux
...
```
#### Detalhes da Saída

    Device: Nome do dispositivo e partição (ex: /dev/sda1, /dev/sda2).
    Boot: Indica se a partição é bootável (* para sim, em branco para não).
    Start: Endereço LBA inicial da partição.
    End: Endereço LBA final da partição.
    Sectors: Número total de setores que a partição ocupa.
    Size: Tamanho da partição em megabytes (calculado com base no número de setores).
    Id: Código hexadecimal do tipo de partição.
    Type: Nome do tipo de partição (ex: NTFS, Linux, FAT32).