 #include<iostream>
 #include<windows.h>

 int main(){
 int x= 10; //Variableallocated onthestack
 MEMORY_BASIC_INFORMATION mbi{};

 //Askthekernelfor metadataabout the pageholdingvariable x
 if(VirtualQuery(&x,&mbi,sizeof(mbi)) != 0){
 std::cout<<"Address: "<<mbi.BaseAddress<<"\n";
 std::cout<<"RegionSize:"<<mbi.RegionSize<<" bytes\n";

 std::cout<<"State: "
 <<(mbi.State ==MEM_COMMIT ? "MEM_COMMIT" :"OTHER")
 <<"\n";
 }
 return 0;
 }
