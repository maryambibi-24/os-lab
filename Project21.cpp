 #include<iostream>
 #include<thread>
 #include<windows.h>

 void pinnedWorker(){
 //Bitmask:bit0= Core0(value1),bit1 = Core1(value2),etc.
 DWORD_PTR mask=1;
 DWORD_PTR prev=SetThreadAffinityMask(GetCurrentThread(),mask);
 if(prev!=0) {
 std::cout<<"ThreadsuccessfullyboundtoCore0.\n";
 } }

 int main(){
 std::cout<<"Availablehardwarecores:"
 <<std::thread::hardware_concurrency() <<"\n";

 std::thread t(pinnedWorker);
 t.join();
 return 0;
 }
