#ifndef MBR_READER
#define MBR_READER

// Definições e constantes
#define TAMANHO_MBR 512
#define TAMANHO_ENTRADA_PARTICAO 16
#define TABELA_PARTICOES_OFFSET 446
#define NUM_PARTICOES 4
#define TAMANHO_SETOR_MB 2048  // 1 MB = 2048 setores

// Estrutura para representar uma entrada da tabela de partições
typedef struct {
    unsigned char boot_flag;      // Flag de boot
    unsigned char start_head;     // Cabeça de início
    unsigned char start_sector;   // Setor de início (CHS)
    unsigned char start_cylinder; // Cilindro de início (CHS)
    unsigned char partition_type; // Tipo da partição
    unsigned char end_head;       // Cabeça de fim
    unsigned char end_sector;     // Setor de fim (CHS)
    unsigned char end_cylinder;   // Cilindro de fim (CHS)
    unsigned int start_lba;       // Endereço LBA de início
    unsigned int sectors_count;   // Quantidade total de setores
} PartitionEntry;

// Função para obter o nome do tipo de partição com base no código
const char* obter_tipo_particao(unsigned char partition_type);

// Função para extrair uma entrada de partição da MBR a partir de um deslocamento
void extrair_entrada_particao(const unsigned char *mbr, int offset, PartitionEntry *entry);

// Função para imprimir uma única entrada de partição
void imprimir_entrada_particao(int index, const PartitionEntry *p);

// Função para imprimir a tabela de partições completa
void imprimir_tabela_particoes(const PartitionEntry *partition_table);

#endif
