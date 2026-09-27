#include<iostream>
 #include<windows.h>

 int main(){
 //Step1:Reserve1 MBofvirtualaddresses(noRAMallocatedyet)
 void*base=VirtualAlloc(nullptr,1024*1024,
 MEM_RESERVE,PAGE_NOACCESS);
 if(!base)return 1;
 std::cout<<"Reserved1MBaddressspaceat:" <<base<<"\n";

 //Step2:Back the first4KBpagewithactualphysicalRAM
 int*page=(int*)VirtualAlloc(base, 4096,
 MEM_COMMIT, PAGE_READWRITE);
 if(!page)return 1;

 page[0]=42;//Now safetoreadandwrite
 std::cout<<"Committedmemoryvalue:"<<page[0]<<"\n";
 VirtualFree(base, 0,MEM_RELEASE);// Clean upbothatonce
 return 0;
 }
