#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void myMessage(char *new, char *str)
{
        int i, j=0;
        for(i=0;i<12;i++)
        {
                if(i==0 || i==1 || i==3 || i==7)
                {
                        str[i]='0';
                }
                else
                {
                        str[i]=new[j++];
                }
        }
        str[i]='\0';
}
void myHammingCode(char *new, char *str)
{
        int i, j, flag=-1, count=0;
        for(i=0;i<12;i++)
        {
                if(i==0 || i==1 || i==3 || i==7)
                {
                        j=i;
                        while(j<12)
                        {
                                if(flag!=i){
                                        if(new[j]=='1'){
                                                count++;
                                        }
                                        j++;
                                        flag++;
				}
                                else{
                                        j=j+i+1;
                                        flag=-1;
                                }
                        }
                        if((count%2)!=0){
                                str[i]='1';
                                count=0;
                        }
                        else{
                                str[i]='0';
                                count=0;
                        }
                }
                else
                {
                        str[i]=new[i];
                }
        }
        str[i]='\0';
}
void myTransmittingCode(float p,char *str)
{
        int rno, rpos;
        srand(time(0));
        rno=rand() % 10;
        printf("The generated random no is %d\n", rno);
        p=p*10;
        if(rno>= 0 && rno<= ((int)p))
        {
                rpos=rand() % 12;
                printf("Bit position to be corrupted is %d.\n", (rpos+1));
                if(str[rpos]=='0')
                {
                        str[rpos]='1';
                }
		else if(str[rpos]=='1')
                {
                        str[rpos]='0';
                }
        }
        else
        {
                printf("NO BIT TO BE CORRUPTED.\n");
        }
}
void sendToServer(char *data, char *ip, char *port)
{
        int sockfd, connectfd;
        struct sockaddr_in serv_addr, cli_addr;

        sockfd=socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd<0)
        {
                printf("Error in creating the socket.\n");
                exit(1);
        }

        bzero((char *)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=INADDR_ANY;
        serv_addr.sin_port=htons(atoi(port));

        connectfd=connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if(connectfd<0)
        {
                printf("Couldn't connect to the Server.\n");
                exit(1);
        }
        send(sockfd, data, strlen(data)+1, 0);
}
int main(int argc, char *argv[])
{
        if(argc!=5)
        {
                printf("Some arguments aren't provided.\n");
                exit(1);
        }
        float p=strtof(argv[2],NULL); //OR USE atof()
        char message[100];
        char HammingCode[100];
        printf("User's data is %s\n", argv[1]);
        myMessage(argv[1], message);
        myHammingCode(message, HammingCode);
        printf("Hamming code is %s\n", HammingCode);
        myTransmittingCode(p, HammingCode);
        printf("Data to be sent to the server is %s\n", HammingCode);
        sendToServer(HammingCode,argv[3],argv[4]);
        return 0;
}