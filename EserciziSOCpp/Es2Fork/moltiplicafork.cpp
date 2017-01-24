#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;
int main(void){
	for (int i=0;i<5;i++){
		int padre=fork();
		cout<<"\nSono il padre e il mio pid è: "<<getpid()<<endl;
		sleep(2);
		if(!padre){
			cout<<"\nSono il figlio di :"<<getppid()<<endl;
			i=5;
			sleep(5);
			}
	}
}
