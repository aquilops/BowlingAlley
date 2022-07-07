#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>

void error(const char *msg) {
    perror(msg);
    exit(0);
}
int main(int argc , char *argv[]) { int choice=-1,choice_2=-1;
        int socket_desc;
        struct sockaddr_in server;
        char *message , server_reply[2000];
        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("Could not create socket");
        }
        server.sin_addr.s_addr = inet_addr("192.168.56.102"); //Please enter the ip address >
        server.sin_family = AF_INET;
        server.sin_port = htons(8888);
        //Connect to remote server
        if (connect(socket_desc , (struct sockaddr *)&server , 
sizeof(server)) < 0)
        {
                puts("connect error");
                return 1;
	}
        puts("Connected \n");
        //Send some data
        message = "connect";
        if( send(socket_desc , message , strlen(message) , 0) < 0)
        {
                puts("Send failed");
                return 1;
        }
        puts("Data Send\n");
                    //Receive a reply from the server
        if( recv(socket_desc, server_reply , 2000 , 0) < 0)
        {
                puts("recv failed");
        }
        puts("Reply received\n");
        puts(server_reply);

 int opt;
        system("clear");
        printf("\t\t\t******WELCOME TO WANGSA BOWL******\n");
        printf("Choose One Of The Three Option\n");
        printf("1. See Our Branch\n");
        printf("2. Booking\n");
        printf("3. Exit\n");

        scanf("%d", &opt);
        write(socket_desc, &opt, sizeof(opt));
        if(opt==1){

          printf("\t\t\t******WELCOME TO WANGSA BOWL******\n");
          printf("\t\t\tBranch         -------------> Location\n");
          printf("\t\t\tSetia City Mall-------------> Setia Alam\n");
          printf("\t\t\tOne Utama      -------------> Petaling Jaya\n");
          printf("\t\t\tIoi City Mall  -------------> Putrajaya\n");
          printf("\t\t\tWangsa Walk    -------------> Kuala Lumpur\n");

            }

        else if(opt==2){

    printf(" choose Your Bowling Place\n");
    printf("\t 1. Setia City Mall \n \t 2. One Utama \n \t 3.Wangsa Walk \n\t 4. IoI City");
    scanf("%d",&choice);
     printf("\tYour Bowling Place is : ");

    if(choice <1 || choice >4)
    {
        printf(" wrong choice entered, try again ...\n");
        return 1;
    }
    if(choice==5) exit(0);
     printf(" You Choose : %d", choice);
        return 0;
}

