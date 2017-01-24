#include"header.h"
void inizializza(Gestore* g){
	g->stop=0;
	g->spazio=N*N;
	g->nlettori=0;
	g->nscrittori=0;
	g->codalett=0;
	g->codascritt=0;
	g->msg=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			g->m[i][j]=0;		
		}	
	}
}
void wait_cond(int idsem,int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num=numsem;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=-1;
	semop(idsem,&sem_buf,0);
}
void signal_cond(int idsem,int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num=numsem;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=1;
	semop(idsem,&sem_buf,0);
}
void genera(Gestore* g,int idsem){
	wait_cond(idsem,mutex);
	if((g->spazio==0)&&(g->nlettori>0)&&(g->nscrittori>0)){
		g->codascritt++;
		wait_cond(idsem,ok_scrittura);
		g->codalett--;
	}
	g->nscrittori++;
	for(int i=0;i<N;i++){
		printf("\n");
		for(int j=0;j<N;j++){
			g->m[i][j]=rand()%10;
			printf("- %d - \n",g->m[i][j]);		
		}	
	}
	if(g->codascritt>0)
		signal_cond(idsem,ok_scrittura);
	
	g->nscrittori--;
	if(g->nscrittori==0)
		signal_cond(idsem,ok_lettura);
	signal_cond(idsem,mutex);
}
void analizza(Gestore* g,int idsem){
	wait_cond(idsem,mutex);
	if((g->msg==0)&&(g->nscrittori>0)){
		g->codalett++;
		wait_cond(idsem,ok_lettura);
		g->codalett--;
	}
	g->nlettori++;
	signal_cond(idsem,mutex);
	int prod;
for(int i=0;i<N;i++){
		printf("\n");
		for(int  j=0;j<N;j++){
			g->m[i][j]=rand()%10;
			printf("- %d - \n",g->m[i][j]);	
		}	
	}
	for(int i=0;i<N;i++){
		for(int  j=0;j<N;j++){
			g->m[i][j]=g->m[i][j]*2;
			prod=prod*(g->m[i][j]);		
		}	
	}
	printf("[ANALIZZATORE]Il risultato del prodotto è %d \n",prod);
	wait_cond(idsem,mutex);
	if(g->codalett>0)
		signal_cond(idsem,ok_lettura);
	g->nlettori--;
	if(g->nlettori==0)
		signal_cond(idsem,ok_scrittura);
	signal_cond(idsem,mutex);
}
void elabora(Gestore* g,int idsem){
	wait_cond(idsem,mutex);
	if((g->msg==0)&&(g->nscrittori>0)){
		g->codalett++;
		wait_cond(idsem,ok_lettura);
		g->codalett--;
	}
	g->nlettori++;
	signal_cond(idsem,mutex);
	int sum;
	for(int i=0;i<N;i++){
		printf("\n");
		for(int  j=0;j<N;j++){
			g->m[i][j]=rand()%10;
			printf("- %d - \n",g->m[i][j]);	
		}	
	}
	for(int i=0;i<N;i++){
		for(int  j=0;j<N;j++){
			g->m[i][j]=g->m[i][j];
			sum=sum+(g->m[i][j]);		
		}	
	}
	printf("[ANALIZZATORE]Il risultato del prodotto è %d \n",sum/2);
	wait_cond(idsem,mutex);
	if(g->codalett>0)
		signal_cond(idsem,ok_lettura);
	g->nlettori--;
	if(g->nlettori==0)
		signal_cond(idsem,ok_scrittura);
	signal_cond(idsem,mutex);
}
