

struct example{
    unsigned char config;
    unsigned short address;
    unsigned char index;
}__attribute__((packed));


int sum_of_three(int arg1,int arg2,int arg3){
    return arg1+arg2+arg3;
}