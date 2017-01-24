#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;
 int main (void){
	int pid=fork();
	if (pid<0){
		cout<<"chiamata fallita\n";
		}
	else if (pid>0){
		cout<<"\nSono il padre il mio pid è ";
		cout<<getpid();
		cout<<"\nIl pid di mio padre è ";
		cout<<getppid()<<endl;
		sleep(5);
		_exit(3);
		}
	else if (pid==0){
		cout<<"\nSono il figlio e il mio pid è ";
		cout<<getpid();
		cout<<"\nIl pid di mio padre è	";
		cout<<getppid()<<endl;
		}
}
