 #include<iostream>
 #include<future>
 #include<chrono>
 #include<thread>

 int main(){
//Dispatchworktorunin thebackground
 std::future<double>task =std::async(std::launch::async,[](){
 std::this_thread::sleep_for(std::chrono::seconds(1));
 return 3.14159;
 });

 std::cout<<"Mainthreadcontinuesworkwhileasynctaskcomputes...\n";

 //.get()pausesexecutiononlyuntiltheresultis ready
 double result=task.get();
 std::cout<<"Resultreceived:"<<result<<"\n";
 return 0;
 }
