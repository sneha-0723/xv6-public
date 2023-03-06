#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"
#include "spinlock.h"


int main(int argc,char* argv[]){
    int fd;
    int fd1;
    int prev_offset=0;
      
   if(argc<2){
        printf(1,"Please enter a valid file offset\n");
        exit();
    }
    int offset=atoi(argv[1]);
    fd=open("file.txt",O_CREATE|O_WRONLY);

    char* str="In a fast-changing world, the fate of the country can be moulded through our ability to harness modern science and technology, which is a road to boost the development programs of the country. Rapid technological advances have reduced the dependency on natural resources or the factors in proportion to it. Man is performing precisely by machines with a regular improvement in his work because of quick technological changes by virtue of scientific advancement all around the world. We have accomplished desired scientific and technological advancement and have succeeded in boosting various important international activities like information and telecommunication, television, meteorological services, medical advancement, industrial development, nuclear research, Space Research Oceanographic Research, etc.";
    write(fd,str,strlen(str));
    printf(1,"Content of file: \n");
     printf(1,"_____________________\n");
    printf(1,str);
    printf(1,"\n");
     printf(1,"*******************************************************\n");
   

    fd1=open("file.txt",O_RDONLY);
  
    int ans=lseek(fd,offset,SEEK_SET);
    char* buf;
    
    if(ans==offset){
         prev_offset=ans;
         buf=(char*)sbrk(sizeof(char)+ans);
        
         read(fd1,buf,ans);
       
         printf(1,"Testing seek set\n");
         printf(1,buf);
         printf(1,"\n");
        lseek(fd1,ans,SEEK_SET);

        

    }
    else{
     printf(1,"Seek set failed for this file\n");
     exit();
    }
    printf(1,"***********************************************************\n");
    ans=lseek(fd,offset,SEEK_CUR);
    if(ans==prev_offset+offset){
       buf=(char*)sbrk(sizeof(char)+offset);
        
         read(fd1,buf,offset);
       
         printf(1,"Testing seek cur\n");
         printf(1,buf);
         printf(1,"\n");


    }
    else{
     printf(1,"Seek cur failed for this file\n");
     exit();
     
    }
    printf(1,"************************************************************\n");
    int offset1=-1*offset;
    ans=lseek(fd,offset1,SEEK_END);
    
    if(ans==strlen(str)+offset1){
          
         lseek(fd1,ans,SEEK_SET);
          buf=(char*)sbrk(sizeof(char)+offset);
        
         read(fd1,buf,offset);
       
         printf(1,"Testing seek end\n");
         printf(1,buf);
         printf(1,"\n");
    }
    else{
     printf(1,"Seek end failed for this file\n");
     exit();
    }
    printf(1,"********************************************************************\n");

    lseek(fd,0,SEEK_SET);
    lseek(fd,0,SEEK_CUR);   
    close(fd);
    close(fd1);
   

    
   

    exit();

}
