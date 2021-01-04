#include"TE_standard.h"

#include<stdlib.h>

inline void TE_dynamicBool_setCapacity(TE_DynamicBool* dynamicBool, unsigned int size)
{
    dynamicBool->size = size;
    unsigned int arrayLength = size/(8*sizeof(uint64_t)) + 1;
    dynamicBool->value = (uint64_t*)calloc(arrayLength, sizeof(uint64_t));
}

inline uint8_t TE_dynamicBool_get(TE_DynamicBool* dynamicBool, unsigned int index)
{
    unsigned int arrayIndex = index/(8*sizeof(uint64_t));
    unsigned int newIndex = index%(8*sizeof(uint64_t));
    return dynamicBool->value[arrayIndex] & (1UL<<newIndex);
}

inline void TE_dynamicBool_set(TE_DynamicBool* dynamicBool, unsigned int index, uint8_t value)
{
    unsigned int arrayIndex = index/(8*sizeof(uint64_t));
    unsigned int newIndex = index%(8*sizeof(uint64_t));
    dynamicBool->value[arrayIndex] &= (~(value<<index));
}

inline void TE_dynamicBool_free(TE_DynamicBool* dynamicBool)
{
    free(dynamicBool->value);
    dynamicBool->size = 0;
}

inline void TE_dynamicBool_setChunk(TE_DynamicBool* dynamicBool, unsigned int chunkIndex, uint64_t chunkValue)
{
    dynamicBool->value[chunkIndex] = chunkValue;
}

inline uint64_t TE_dynamicBool_getChunk(TE_DynamicBool* dynamicBool, unsigned int chunkIndex)
{
    return dynamicBool->value[chunkIndex];
}
