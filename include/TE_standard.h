#ifndef TESTANDARD_H_
#define TESTANDARD_H_

#include<stdint.h>

typedef struct TE_DynamicBool
{
    uint64_t* value;
    unsigned int size;
}TE_DynamicBool;

void TE_dynamicBool_setCapacity(TE_DynamicBool* dynamicBool, unsigned int size);
uint8_t TE_dynamicBool_get(TE_DynamicBool* dynamicBool, unsigned int index);
void TE_dynamicBool_set(TE_DynamicBool* dynamicBool, unsigned int index, uint8_t value);
void TE_dynamicBool_free(TE_DynamicBool* dynamicBool);
void TE_dynamicBool_setChunk(TE_DynamicBool* dynamicBool, unsigned int chunkIndex, uint64_t chunkValue);
uint64_t TE_dynamicBool_getChunk(TE_DynamicBool* dynamicBool, unsigned int chunkIndex);
#endif
