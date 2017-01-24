#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"header.h"
void Inizializza(MonitorElaborazioni * m){
	pthread_mutex_init(&(m->mutex),NULL);
	pthread_cond_init(&(m->ok_prod),NULL);
	pthread_cond_init(&(m->ok_cons),NULL);
	m->elem_disp=0;
	for(int i=0;i<N;i++){
		m->stato[i]=LIBERO;
		m->elaborazioni[i].operandi[i]=0;
		m->elaborazioni[i].totale_operandi=0;	
	}
}
int ricerca(MonitorElaborazioni* m){
	int i=0,k=0;
	int index,min,temp;
	while((k<N)&&(m->elaborazioni[k].totale_operandi==0)&&(m->stato[k]!=OCCUPATO)){
			k++;
	}
	min=m->elaborazioni[k].totale_operandi;
	index=k;
	while(i<N){
		if((m->stato[i]==OCCUPATO)&&(m->elaborazioni[i].totale_operandi!=0)){
			temp=m->elaborazioni[i].totale_operandi;
			if(min>temp){
				min=temp;
				index=i;			
			}		
		}
		i++;
	}

	return index;
}
void inserisci_buffer(MonitorElaborazioni* m,int operandi){
	pthread_mutex_lock(&(m->mutex));
	int i=0;
	while(m->elem_disp==N)
		pthread_cond_wait(&(m->ok_prod),&m->mutex);
	while((i<N)&&( (m->stato[i]!=LIBERO)||(m->stato[i]!=ESEGUITO)) )
		i++;
	m->stato[i]=IN_USO;
	m->elem_disp=m->elem_disp+1;
	pthread_cond_signal(&(m->ok_cons));
	pthread_mutex_unlock(&(m->mutex));
	m->elaborazioni[i].totale_operandi=operandi;
	for(int k=0;k<operandi;k++)
		m->elaborazioni[i].operandi[k]=rand()%11;
	printf("[Richiendente]Ho inserito %d operandi in posizione %d\n",operandi,i);
	for(int k=0;k<operandi;k++)
		printf("[Richiedente]operando[%d]=%d\n",k,m->elaborazioni[i].operandi[k]);
	pthread_mutex_lock(&(m->mutex));
	m->stato[i]=OCCUPATO;
	pthread_mutex_unlock(&(m->mutex));
}
void preleva_buffer(MonitorElaborazioni* m){
	pthread_mutex_lock(&(m->mutex));
	while(m->elem_disp==0)
		pthread_cond_wait(&(m->ok_cons),&m->mutex);
	int index=ricerca(m);
	m->stato[index]=IN_USO;
	m->elem_disp=m->elem_disp-1;
	pthread_cond_signal(&(m->ok_prod));
	pthread_mutex_unlock(&(m->mutex));
	sleep(m->elaborazioni[index].totale_operandi);
	int somma;
	for(int i=0;i<m->elaborazioni[index].totale_operandi;i++)
		somma=somma+(m->elaborazioni[index].operandi[i]);
	printf("[Elaboratore] Somma=%d numero totale operandi=%d posizione=%d\n",somma,m->elaborazioni[index].totale_operandi,index);
	pthread_mutex_lock(&(m->mutex));
	m->stato[index]=ESEGUITO;
	pthread_mutex_unlock(&(m->mutex));

}
void Rimuovi(MonitorElaborazioni * m){
	pthread_mutex_destroy(&(m->mutex));
	pthread_cond_destroy(&(m->ok_prod));
	pthread_cond_destroy(&(m->ok_cons));
	free(m);
}
