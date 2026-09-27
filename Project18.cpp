#include<iostream>
#include<cstring>
 #include<windows.h>


int main(){
//BackedbyRAM/pagefileratherthanadisk file
HANDLE hMap=CreateFileMappingA(INVALID_HANDLE_VALUE,nullptr,
PAGE_READWRITE, 0,256,"Local\\MySharedMem");
if(!hMap)return 1;
 //Mapphysicalmemoryintoourpointerspace
 char*pBuf=(char*)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS,0,0,256);
 if(!pBuf){
 CloseHandle(hMap);
 return 1;
 }

 strcpy_s( pBuf, 256, "Shared memory payload");
 std::cout<<"Datainsharedregion:"<< pBuf<<"\n";

 UnmapViewOfFile(pBuf);
 CloseHandle(hMap);
 return 0;
 }
