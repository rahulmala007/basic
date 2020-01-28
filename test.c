#include<stdio.h> 
#include <fcntl.h> 
#include <string.h> 
#include <stdlib.h>
struct course
{
    char* cname;
    char* sem;
	char* C; 
};
struct map1{
    char* roll;
    char* name;
};
struct map2{
    char* id;
    struct course coursedet;
};

struct map4{
    char* id;
    char* grade; 
};
struct map3{
    char* roll;
    struct map4 details;
};

int main()
{
    
    int fd,sz;
    char str[10000];
    char str1[1000000];
    char str2[20000];
    int m1s=0;
    struct map1 stud[158];
    struct map2 cour[1000];
    fd = open("students.csv", O_RDONLY); 
    sz = read(fd,str,9999); 
    str[sz]='\0';
    //  printf("%s\n",str);
    char *token = strtok(str,",\n"); 
    int i=0;
    while (token != NULL) 
    { 
        printf("%s\n", token);
        stud[i].roll=token;
        token = strtok(NULL,",\n"); 
        stud[i].name=token;
        token = strtok(NULL,",\n"); 
        i++;
    }
    // close(fd);
    // printf("%d\n",i);
    // for(int k=0;k<158;k++)
    // {
    //     printf("%s\n",stud[k].roll);
    //     printf("%s---\n",stud[k].name);

    // }
    int fd2,sz2;
    fd2=open("courses.csv", O_RDONLY);
    sz2 =read(fd2,str1,999999); 
    str1[sz2]='\0';
    i=0; 
    char *token1 = strtok(str1,",\n"); 
    while (token1 != NULL) 
    { 
        printf("%s\n", token1);
        token = strtok(NULL,",\n"); 
        cour[i].coursedet.sem=token1;
        token = strtok(NULL,",\n"); 
        cour[i].id=token1;
        token = strtok(NULL,",\n");
        cour[i].coursedet.cname=token1;
        token = strtok(NULL,",\n");
        token = strtok(NULL,",\n"); 
        token = strtok(NULL,",\n");
        token = strtok(NULL,",\n"); 
        cour[i].coursedet.C=token1;
        i++;
    }
    for(int k=0;k<63;k++)
    {
        printf("%s\n",cour[k].coursedet.sem);
        printf("%s\n",cour[k].id);
        printf("%s\n",cour[k].coursedet.cname);
        printf("%s\n",cour[k].coursedet.C);
        printf("----------------\n");

    }
    while (token != NULL) 
    { 
        // printf("%s\n", token);
        stud[i].roll=token;
        token = strtok(NULL,",\n"); 
        stud[i].name=token;
        token = strtok(NULL,",\n"); 
        i++;
    }

    
  
    return 0; 



}