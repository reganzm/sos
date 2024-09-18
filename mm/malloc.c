#include "include/types.h"
#include "include/mm.h"

struct bucket_desc{
    void* freeptr;
    struct bucket_desc* next;
    uint16_t refcnt;
};

struct bucket_dir{
    uint16_t size;
    struct bucket_desc* bdesc;
};

struct bucket_dir bucket_dir[] = {
    {32,NULL},
    {64,NULL},
    {128,NULL},
    {256,NULL},
    {512,NULL},
    {1024,NULL},
    {2048,NULL},
    {0,NULL}
};


void* malloc(uint32_t size){
    void* va = NULL;

    struct bucket_dir* bdir = NULL;
    struct bucket_desc* bdesc = NULL;

    for(bdir=bucket_dir;bdir->size!=0;bdir++){
        if(bdir->size >= size){
            break;
        }
    }

    if(bdir->size == 0){
        return NULL;
    }

    for(bdesc=bdir->bdesc;bdesc;bdesc=bdesc->next){
        if (bdesc->freeptr){
            break;
        }
    }

    if(bdesc == NULL){
        bdesc  = VA(alloc_page());
        bdesc->freeptr = (void*)((uint64_t)bdesc + sizeof(struct bucket_desc));

        bdesc->next = NULL;
        bdesc->refcnt = 0;

        uint64_t* p = bdesc->freeptr;
        int i = 0;
        while(++i < ((PAGE_SIZE - sizeof(struct bucket_desc)) / bdir->size)){
            *p = (uint64_t)p + bdir->size;
            p = (uint64_t*)((uint64_t)p + bdir->size);
        }
        // last block
        *p = 0;

        bdesc->next =  bdir -> bdesc;
        bdir->bdesc = bdesc;
    }

    va = bdesc->freeptr;

    // next block
    bdesc->freeptr = (void*)(*((uint64_t*)va));
    bdesc->refcnt ++;

    return va;
}


void free(void* va){
    uint64_t page = (uint64_t)va & ~0xfff;

    struct bucket_dir* bdir = bucket_dir;
    struct bucket_desc* bdesc = NULL;

    for(;bdir->size!=0;bdir++){
        bdesc = bdir->bdesc;
        for(;bdesc;bdesc->next){
            if((uint64_t)bdesc == page){
                // find it
                *((uint64_t*)va) = (uint64_t) bdesc->freeptr;
                bdesc->freeptr = va;
                bdesc->refcnt--;
                break;
            }
        }
    }

    // free page
    if(bdesc && bdesc->refcnt==0){
        struct bucket_desc* tmp = bdir->bdesc;
        struct bucket_desc* prev = NULL;

        for(;;tmp=tmp->next){
            if((uint64_t)tmp == (uint64_t)bdesc){
                // find it
                break;
            }
            prev = tmp;
        }

        if(!prev){
            bdir->bdesc = tmp->next;
        }else{
            prev->next = tmp->next;
        }
        free_page(PA(bdesc));
        
    }

}