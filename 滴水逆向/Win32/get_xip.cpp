#include <stdio.h>

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char ___get_xip[] = {
   0xE8,0x00,0x00,0x00,0x00,
   0x58,//pop  rax / eax
   0x58,//pop  rax / eax
   0x50,//push rax / eax
   0xC3 //ret
};

int main()
{
    typedef void* (*__get_xip)();
    __get_xip _get_xip = (__get_xip)&___get_xip;

    printf("%p\n", _get_xip());
    printf("%p\n", ((void* (__stdcall*)())(&___get_xip))());
    printf("%p\n", reinterpret_cast<void* (__stdcall*)()>(&___get_xip)());
    return 0;
}
