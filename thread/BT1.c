#include<stdio.h> 
#include<fcntl.h>
#include<unistd.h> 
#include<string.h> 

int main(){
	int fd = open("log.txt", O_WRONLY, 0667); 
	char buf[20] = "Chien";
	if(fd == -1){
		printf("open failed"); 
  	}
	int num_w = write(fd, buf, strlen(buf)); 
	lseek(fd, 0 , SEEK_SET);
	write(fd,"Hello",strlen("Hello")); 	
	close(fd);

}	

