#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
int gradeconv(char* grade)
{
	if(strcmp(grade,"AS")==0) return 10;
	else if(strcmp(grade,"AA")==0) return 10;
	else if(strcmp(grade,"AB")==0) return 9;
	else if(strcmp(grade,"BB")==0) return 8;
	else if(strcmp(grade,"BC")==0)return 7;
	else if(strcmp(grade,"CC")==0)return 6;
	else if(strcmp(grade,"CD")==0)return 5;
	else if(strcmp(grade,"DD")==0)return 4;
	else return 0;
}

int main()
{
    int studentsFd,gradesFd;
    int outputFilePermissions = S_IRUSR | S_IWUSR | S_IXUSR |S_IRGRP|S_IWGRP;
    studentsFd=open("students03.csv", O_RDONLY);   
    int num=0;
    while(num<19)
    {
    	int studread,outputFd,graderead;
   		char sname[24];
		char sroll[10];
		studread=read(studentsFd,sname,23);
		sname[23]='\0';
		char comma;
		studread=read(studentsFd,&comma,1);
		studread=read(studentsFd,sroll,9);
		sroll[9]='\0';
    	char endline;
    	studread=read(studentsFd,&endline,1);
    	printf("%s ",sname);
    	printf("%s\n",sroll);
    	char filename[14];
        for(int i=0;i<9;i++) filename[i]=sroll[i];
        filename[9]='.';
        filename[10]='t';
        filename[11]='x';
        filename[12]='t';
        filename[13]='\0';
        //printf("%s\n",sroll);
    	printf("FILENAME--%s\n",filename);
        printf("SROLL--%s\n",sroll);
   	    outputFd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,outputFilePermissions);
        write(outputFd, "Name: ", 6);
        write(outputFd,sname,23);
        write(outputFd, "\nRoll Number: ",14);
		write(outputFd,sroll,9);
		write(outputFd,"\n\n",2);
		float spi[9],cpi[9];
		int sem=1;
		int cpimycred=0,cpitotcred=0;
		while(sem<=8)
		{
			int mycred=0,totcred=0;
			printf("SEM-%d",sem);
			char semAsStr=sem+'0';
			write(outputFd,"Semester ",9);
			write(outputFd,&semAsStr,1);
			write(outputFd,"\n",1);
			
            // write(outputFd,tempcour,5);
			// write(outputFd,"  ",2);
			// write(outputFd,courname,39);
			// write(outputFd," ",1);
            
			// write(outputFd,&cr,1);
		    // write(outputFd," ",1);
			// write(outputFd,tempgrade,2);
			// write(outputFd,"\n",1);
			gradesFd=open("grades03.csv", O_RDONLY);
			int filelen=0;
			while(filelen<21)
			{
    		char temproll[10],tempcour[6],space,comma,endline,tempgrade[3];
			graderead=read(gradesFd,temproll,9);
			temproll[9]='\0';
			printf("%s\n",temproll);
           
			graderead=read(gradesFd,&comma,1);
			graderead=read(gradesFd,tempcour,5);
			tempcour[5]='\0';
			//printf("%s\n",tempcour);
			graderead=read(gradesFd,&space,1);
			graderead=read(gradesFd,&comma,1);
			graderead=read(gradesFd,tempgrade,2);
			tempgrade[2]='\0';
			printf("%s\n",tempgrade);
			graderead=read(gradesFd,&endline,1);
			if(strcmp(temproll,sroll)==0)
			{
				printf("YES\n");
				int courseread,courseFd;
			//	printf("%s---%s---%s\n",temproll,tempcour,tempgrade);
				courseFd=open("courses03.csv", O_RDONLY);
				int cfllen=0;
				while(cfllen<20)
				{
					
				char seme,comma,actcour[6],courname[40],l,t,p,cr,cendline;
				courseread=read(courseFd,&seme,1);
			//	printf("%c ",seme);
				courseread=read(courseFd,&comma,1);
				courseread=read(courseFd,actcour,5);
				actcour[5]='\0';
			//	printf("%s ",actcour);
				courseread=read(courseFd,&comma,1);
				courseread=read(courseFd,courname,39);
				courname[39]='\0';
				//printf("%s \n",courname);
				courseread=read(courseFd,&comma,1);
				courseread=read(courseFd,&l,1);
				courseread=read(courseFd,&comma,1);
				courseread=read(courseFd,&t,1);
				courseread=read(courseFd,&comma,1);
				courseread=read(courseFd,&p,1);
				courseread=read(courseFd,&comma,1);
				courseread=read(courseFd,&cr,1);
				//printf("%c\n",cr);
				courseread=read(courseFd,&cendline,1);
				int semni=seme-'0';
				//printf("%d\n",semni);
				if(semni==sem && strcmp(actcour,tempcour)==0)
				{
					write(outputFd,tempcour,5);
					write(outputFd,"  ",2);
					write(outputFd,courname,39);
				    write(outputFd," ",1);
                    //printf("%s\n",courname);
					write(outputFd,&cr,1);
					write(outputFd," ",1);
					write(outputFd,tempgrade,2);
					write(outputFd,"\n",1);
					// printf("YES\n");
					printf("%c--",seme);
					printf("%s--",courname);
					printf("%s--",tempgrade);
					printf("%d--",gradeconv(tempgrade));
					printf("%c\n",cr);
					int cri=(cr-'0');
					mycred=mycred+gradeconv(tempgrade)*cri;
					totcred=totcred+cri*10;
					
				}
					cfllen++;
				}
				
			close(courseFd);
			}
			filelen++;
			}
			//printf("%d\n",mycred);
			//printf("%d\n",totcred);
			float tempspi=0.0;
			if(totcred>0)tempspi=(float)mycred*10/(float)totcred;
			//printf("%0.2f\n",tempspi*10);
			cpimycred=cpimycred+mycred;
			cpitotcred=cpitotcred+totcred;
//			printf("%d\n",cpimycred);
//			printf("%d\n",cpitotcred);
			float cpisem=(float)cpimycred*10/(float)cpitotcred;
			spi[sem]=tempspi;
			cpi[sem]=cpisem;	
			sem++;
			write(outputFd,"\n",1);
		}
		printf("SPI:\n");
		for(int i=1;i<=8;i++) printf("%0.2f\n",spi[i]);
		//cout<<endl<<"CPI:"<<endl;
		//for(int i=1;i<=8;i++) cout<<cpi[i]<<" ";
    	num++;
    	//cout<<endl;
    	//cout<<"--------------------------------"<<endl;
    	
    	write(outputFd,"\nSPI:\n",6);
    	for(int i=1;i<=8;i++)
		{
			char buf[4];
			snprintf(buf, sizeof(buf), "%g", spi[i]);
			 write(outputFd," ",1);
			 write(outputFd,buf,strlen(buf));
			 write(outputFd," ",1);
		 }
    	write(outputFd,"\nCPI:\n",6);
    	for(int i=1;i<=8;i++)
		{
			char buf2[4];
			snprintf(buf2, sizeof(buf2), "%g", cpi[i]);
			 write(outputFd," ",1);
			 write(outputFd,buf2,strlen(buf2));
			 write(outputFd," ",1);
		 }
			
    }
    
    
}