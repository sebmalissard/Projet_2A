//gcc -pthread main.c menu.c menu.h param.c param.h type.h -o test
//by Sébastien Malissard


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

#include "menu.h"
#include "type.h"
#include "param.h"
#include "com.h"
#include "../typeMessage.h"

int sock = 0;
pthread_mutex_t mutexSocket = PTHREAD_MUTEX_INITIALIZER;

void *mainIhm(void* arg){

    int shut_down = 0;
    int temp, select = 0;
    char c;

    init();
    wait();

    while(!shut_down){

        menu(select);
        printf("\n");

        if(enterChar(1, &c) == -1){
            continue;
            }

        switch(c){
            case 's' :
                if( (temp = selectRobot()) != -1){
                    select = temp;
                    }
                wait();
                break;
            case 'a' :
                addRobot();
                wait();
                break;
            case 'l' :
                displayRobot();
                wait();
                break;
            case 'c' :
                printf("Fonctionalité pas encore disponible\n");
                wait();
                break;
            case 'q' :
                printf("Bye...\n");
                shut_down = 1;
                break;

            //if a robot is select
            case 'i' :
                printf("Fonctionalité pas encore disponible. Utiliser -l pour voir la liste des robots\n");
                break;
            case 'e' :
                sendPoint(select);
                wait();
                break;
            case 'n' :
                printf("Fonctionalité pas encore disponible\n");
                wait();
                break;
            case 'r' :
                rmRobot(select);
                wait();
                break;
            case 'd' :
                printf("Le robot n°%d a été déselectionner\n",select);
                select = 0;
                wait();
                break;
            default :
                printf("Choix invalide\n");
                break;
            }
        }

    pthread_exit(NULL);
    }

void *mainComRecv(void* arg){
    
    pthread_exit(NULL);
    }


void *mainComSend(void* arg){
/*    sMsg msgOut;

    msgOut.type = CMD;
    msgOut.body.cmd.pt.x = 50;

    while(1){
        senMsg(1, &msgOut);
        }
*/
    pthread_exit(NULL);
    }


int main(void){
    pthread_t th1, th2, th3;

   /* if((sock = initCom(IP)) < 0){
        return 0; //FIXME
        }
    robot[1].loc = ACTIVE;
    robot[1].sock = sock;
*/

    if(pthread_create(&th1, NULL, mainIhm, NULL) == -1){
    	perror("pthread_create 1\n");
        return -1;
        }
    if(pthread_create(&th3, NULL, mainComSend, NULL) == -1){
    	perror("pthread_create 3\n");
        return -1;
        }

    if (pthread_join(th1, NULL)) {
	    perror("pthread_join\n");
	    return -1;
        }
    if (pthread_join(th2, NULL)) {
	    perror("pthread_join\n");
	    return -1;
        }
    if (pthread_join(th3, NULL)) {
	    perror("pthread_join\n");
	    return -1;
        }


    return 1;
    }
