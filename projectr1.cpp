#include<iostream>
using namespace std;
int main()
{
	std::ofstream file("diary.txt");
	file<<"hello OS\n";
	file.close();
}
