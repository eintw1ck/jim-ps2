#ifndef _SCACHE_H
#define _SCACHE_H 1

void ps2_memcpy(void* dst, void* src, int size);
int  scache_init(char * param, int sectorSize);
void scache_close();
//int  scache_readSector(unsigned int sector, void* buf) ;
int  scache_readSector(unsigned int sector, void** buf) ;
void scache_getStat(unsigned int* access, unsigned int* hits);
void scache_dumpRecords();
#endif 