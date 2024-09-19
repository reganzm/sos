#pragma once
#include "include/types.h"

void* memset(void* s,char c,uint64_t n);

void memcpy(void* dest,const void* src,int n);

int strcmp(const uint8_t* s1,const uint8_t* s2);
int strlen(const uint8_t* s );

