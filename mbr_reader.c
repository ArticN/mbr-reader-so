#include <stdio.h>
#include "mbr_reader.h"

const char* obter_tipo_particao(unsigned char partition_type) {
    switch (partition_type) {
        case 0x01: return "FAT12";
        case 0x04: return "FAT16 <32M";
        case 0x05: return "Extended";
        case 0x06: return "FAT16";
        case 0x07: return "NTFS/exFAT";
        case 0x0B: return "FAT32 CHS";
        case 0x0C: return "FAT32 LBA";
        case 0x0E: return "FAT16 LBA";
        case 0x83: return "Linux";
        case 0x82: return "Linux swap";
        case 0x0F: return "Extended LBA";
        default: return "Desconhecido";
    }
}

void extrair_entrada_particao(const unsigned char *mbr, int offset, PartitionEntry *entry) {
    entry->boot_flag = mbr[offset];
    entry->partition_type = mbr[offset + 4];
    entry->start_lba = *(unsigned int*)&mbr[offset + 8];
    entry->sectors_count = *(unsigned int*)&mbr[offset + 12];
}

void imprimir_entrada_particao(int index, const PartitionEntry *p) {
    if (p->partition_type == 0) {
        return;
    }

    unsigned int tamanho_mb = (p->sectors_count * TAMANHO_SETOR) / (1024 * 1024);

    printf("/dev/sda%d  %s  %10u %10u %10u  %5uM  %02X  %s\n",
           index + 1,
           (p->boot_flag == 0x80) ? "*" : " ",
           p->start_lba,
           p->start_lba + p->sectors_count - 1,
           p->sectors_count,
           tamanho_mb,
           p->partition_type,
           obter_tipo_particao(p->partition_type));
}

void imprimir_tabela_particoes(const PartitionEntry *partition_table) {
    printf("Device     Boot   Start       End        Sectors  Size   Id  Type\n");
    for (int i = 0; i < NUM_PARTICOES; i++) {
        imprimir_entrada_particao(i, &partition_table[i]);
    }
}
