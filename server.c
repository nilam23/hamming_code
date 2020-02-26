#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#define SIZE 1000
#define MAX_CLIENT 1

int sum=0;

void errorPosition(int );
void ErrorCorrection(char *str)
{
        int i, j, flag=-1, count=0;
        for(i=0;i<12;i++)
        {
                if(i==0 || i==1 || i==3 || i==7)
                {
                        j=i;
                        while(j<12)
                        {
                                if(flag!=i)
                                {
                                        if(str[j]=='1')
                                        {
                                                count++;
                                        }
                                        j++;
                                        flag++;
                                }
                                else
                                {
                                        j=j+i+1;
                                        flag=-1;
                                }
                        }
                        if((count%2)!=0)
			{
                                errorPosition(1);
                                count=0;
                        }
                        else
                        {
                                errorPosition(0);
                                count=0;
                        }
                }
        }
}
void errorPosition(int value)
{
        static int arr[4]={-1,-1,-1,-1}, count=0;
        int i;
        for(i=0; i<4; i++)
        {
                if(arr[i]==-1)
                {
                        arr[i]=value;
                        break;
                }
        }
        count++;
        int e=3;
        if(count==4)
        {
                for(i=3; i>=0; i--)
                {
                        sum+=(arr[i] * pow(2,e));
                        e--;
                }
		count=0;
        }
}
int main(int argc, char *argv[])
{
        if(argc!=3)
        {
                printf("Some arguments are missing.\n");
                exit(1);
        }
        int sockfd, newsockfd, clilen;
        char buffer[SIZE];
        struct sockaddr_in serv_addr, cli_addr;

        sockfd=socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd<0)
        {
                printf("Error in creating the socket.\n");
                exit(1);
        }

        bzero((char *)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
        serv_addr.sin_port=htons(atoi(argv[2]));

        if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
        {
                printf("Couldn't bind to the Socket.\n");
                exit(1);
        }

        listen(sockfd, MAX_CLIENT);
	 while(1){
                clilen=sizeof(cli_addr);
                newsockfd= accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
                if(newsockfd<0) {
                        printf("Error in accepting the Client's request.\n");
                        exit(1);
                }
                memset((char *)&buffer, 0x0, sizeof(buffer));
                recv(newsockfd, buffer, sizeof(buffer), 0);
                printf("Received data from client is %s\n", buffer);
                ErrorCorrection(buffer);
                printf("Bit Error Position is %d\n", sum);
                if(buffer[sum-1]=='1')
                        buffer[sum-1]='0';
                else
                        buffer[sum-1]='1';
                printf("Data after error correction is %s\n", buffer);
                close(newsockfd);
        }
                close(sockfd);
        return 0;
}