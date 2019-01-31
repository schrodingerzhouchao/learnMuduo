#include <endian.h>
#include <stdint.h>
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    union {
        int32_t i32;
        int8_t arr[4];
    } x;
    x.arr[0]=0x11;
    x.arr[1]=0x22;
    x.arr[2]=0x33;
    x.arr[3]=0x44;

    printf("int32_t x=0x%x\n",x.i32);
    //printf("htobe32(x)=0x%x\n",htobe32(x.i32));
    printf("be32toh(x)=0x%x\n",be32toh(x.i32));
    //printf("htole32(x)=0x%x\n",htole32(x.i32));
    //printf("le32toh(x)=0x%x\n",le32toh(x.i32));

    return 0;
}
