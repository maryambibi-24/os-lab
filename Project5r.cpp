#include<iostream>
using namespace std;
int main()
{
	const char* user=std::getenv("USERNAME");
	if(user !=nullptr){
		std::cout<<"current user is:"<<user<<"\n";
	}
}
