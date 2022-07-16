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

void mainMenu(); //Main menu
void branchList(); //List of branch
void booking(); //Make a booking
int socket_desc, back, opt, b, d, player, numShoes;
int duration[] = {30, 60};
char place[100];
char buffer [1024];


int main(int argc , char *argv[])
{
        int socket_desc;
        struct sockaddr_in server;
        char *message , server_reply[2000];
        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("Could not create socket");
        }
	
	memset(&server, '\0', sizeof(server));
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
	
	mainMenu();
        return 0;
}

void mainMenu() //function for the main menu
{
	do{
        	system("clear");
        	printf("\t\t\t******WELCOME TO WANGSA BOWL******\n");
        	printf("Choose One Of The Three Option\n");
        	printf("1. See Our Branch\n");
        	printf("2. Booking\n");
        	printf("3. Exit\n");

        	scanf(" %d", &opt);
		
		switch(opt)
		{
			case 1:
                                branchList();
                                break;
                        case 2:
                                booking();
                                break;
                        case 3:
                                printf("Thank you! Bye!\n");
                                exit(0);
                        default:
                                printf("Oops, Wrong Choice Entered! Try Again!\n");
                                break;
                }
        }
	while(opt!=3);
}

void branchList() //function for list of branch
{
          printf("\t\t\t******WELCOME TO WANGSA BOWL******\n");
          printf("\t\t\tBranch         -------------> Location\n");
          printf("\t\t\tSetia City Mall-------------> Setia Alam\n");
          printf("\t\t\tOne Utama      -------------> Petaling Jaya\n");
          printf("\t\t\tIoi City Mall  -------------> Putrajaya\n");
          printf("\t\t\tWangsa Walk    -------------> Kuala Lumpur\n");
	  printf("\nPress 0 to go back to Main Menu\n");
	  scanf(" %d", &back);
	  mainMenu();	  
}

void booking() //function to make a booking
{
    printf("Choose Your Bowling Place\n");
    printf("\t 1. Setia City Mall \n \t 2. One Utama \n \t 3. Wangsa Walk \n\t 4. IoI City Mall\n");
    scanf(" %d", &b);
    if (b > 0 || b < 5)
    {
        if(b==1){
		strcpy(place, "Setia City Mall");
	}e
	else if(b==2){
		strcpy(place, "One Utama");
	}
        else if(b==3){
		strcpy(place, "Wangsa Walk");
	}
	else{
		strcpy(place, "Ioi City Mall");
	}
	
	printf("Choose the duration\n");
	printf("\t 1. 30 minutes \n \t 2. 60 minutes\n");
	scanf(" %d" , &d);
  
	int period = duration[d-1]; //because index in array starts with 0
	write(socket_desc,&period,sizeof(period));
	    
	printf("Enter number of player\n");
	scanf(" %d" , &player);
	write(socket_desc,&player,sizeof(player));

	    
	printf("How many shoes do you want? (Enter 0 if you don't want any)\n");
	scanf(" %d" , &numShoes);
	write(socket_desc,&numShoes,sizeof(numShoes));

	
	printf("\t\t\t***Receipt***\t\t\t\n");
	printf("Place: %s\n", place);
	printf("Duration: %d minutes\n", period);
	printf("Number of player: %d\n", player);
	printf("Number of shoes: %d\n", numShoes);
	printf("Total: RM \n");
	printf("Press 0 to go to Main Menu\n");
	scanf(" %d", &back);
	mainMenu();
    }
    else if(b==0){
    	mainMenu();
    }
    else{
    	printf("Invalid Choice ! Try Again\n");
    }
}
