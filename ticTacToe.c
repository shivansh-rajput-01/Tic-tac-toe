#include<stdio.h>
#include<string.h>

void board(char tictactoe[][3]);//for printing tictactoe board

int checkwin(char tictactoe[][3]);//for checking win 

void conditionBoxChoosed(char tictactoe[][3],int *index1,int *index2,int chance);//to return on which array index players move is to be displayed

int checkdublicate(char tictactoe[][3],int chance,int index1,int index2);//checks whether the move has chooses before or not

int main()
{
//takes user's name and assigns symbol
    char playerone[100],playertwo[100];
    printf("Enter name of player 1:");
    fgets(playerone,sizeof(playerone),stdin);
    printf("Enter name of player 2:");
    fgets(playertwo,sizeof(playertwo),stdin);
    //replaces \n from end of string so that no new line appears after name as input from fgets  include \n at end
    int l1,l2;
    l1=strlen(playerone);
    l2=strlen(playertwo);
    playerone[l1-1]='\0';
    playertwo[l2-1]='\0';
    printf("%s has symbol x\n",playerone);
    printf("%s has symbol 0\n",playertwo);
    printf("***Demo board***\n");
    printf("type the number where you want mark\n");
    int index1,index2;
    int player1=0,player2=0;
    char tictactoe[3][3]= {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
    };
    char demotictactoe[3][3]= {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'}
    };
    int winner=checkwin(tictactoe);
    board(demotictactoe);//print demoboard for users reference
    int a=0;//for tracking which player has chance
    int chance;//take value from user from 1 to 9
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            a++;
            if(a%2!=0) {//if odd then chance given to player one and all moves equal x
                printf("%s's chance:",playerone);
                scanf("%d",&chance);
                if(chance>=1&&chance<=9) {//validates user input
                    conditionBoxChoosed(demotictactoe,&index1,&index2,chance);//return index at which x is to be placed
                    if(checkdublicate(tictactoe,chance,index1,index2)) {//if true that is return 1 the non dublicate move
                        tictactoe[index1][index2]='x';//the choosne index is given x
                        board(tictactoe);
                    } else {//duplicate move decreases the iterator and asks user hain to enter a valid input
                        printf("duplicate move\n");
                        j--;
                        a--;
                    }
                } else {
                    printf("invalid move\n");
                    j--;
                    a--;
                }
                int win= checkwin(tictactoe);//win is checked after every move
                if(win==1) {//returns 1 for player one win
                    player1=1;
                    break;
                } else if(win==2) {//returns 2 for player two win
                    player2=1;
                    break;
                }
            } else if(a%2==0) {//if even then chance given to player two and all moves equal 0
                printf("%s's chance:",playertwo);
                scanf("%d",&chance);
                if(chance>=1&&chance<=9) {
                    conditionBoxChoosed(demotictactoe,&index1,&index2,chance);
                    if(checkdublicate(tictactoe,chance,index1,index2)) {
                        tictactoe[index1][index2]='0';
                        board(tictactoe);
                    } else {
                        printf("dublicate move\n");
                        j--;
                        a--;
                    }
                } else {
                    printf("invalid move\n");
                    j--;
                    a--;
                }
                int win= checkwin(tictactoe);
                if(win==1) {
                    player1=1;
                    break;
                } else if(win==2) {
                    player2=1;
                    break;
                }
            }
        }
        if(player1||player2) {//breaks from outer loop if player one win or player win is true
            break;
        }
    }
    //displays result message
    if(player1) {
        printf("**Congratulations %s has won****\n",playerone);
    } else if(player2) {
        printf("**Congratulations %s has won****\n",playertwo);
    } else {
        printf("drawn\n");
    }
    return 0;
}
void board(char tictactoe[][3]) {//prints board
    printf(" ____________________________\n");
    for(int i=0; i<3; i++) {
        printf("|         |         |        |\n");
        printf("|   %c     |    %c    |   %c    |\n",tictactoe[i][0],tictactoe[i][1],tictactoe[i][2]);
        printf("|_________|_________|________|\n");
    }
}

int checkwin(char tictactoe[][3]) {
    int awin=0,bwin=0;
    for(int i=0; i<3; i++) {
        if(tictactoe[0][i]=='x'&&tictactoe[1][i]=='x'&&tictactoe[2][i]=='x') {
            awin++;
        } else if(tictactoe[i][0]=='x'&&tictactoe[i][1]=='x'&&tictactoe[i][2]=='x') {
            awin++;
        } else if(tictactoe[0][0]=='x'&&tictactoe[1][1]=='x'&&tictactoe[2][2]=='x') {
            awin++;
        } else if(tictactoe[0][2]=='x'&&tictactoe[1][1]=='x'&&tictactoe[2][0]=='x') {
            awin++;
        }
    }
    for(int i=0; i<3; i++) {
        if(tictactoe[0][i]=='0'&&tictactoe[1][i]=='0'&&tictactoe[2][i]=='0') {
            bwin++;
        } else if(tictactoe[i][0]=='0'&&tictactoe[i][1]=='0'&&tictactoe[i][2]=='0') {
            bwin++;
        } else if(tictactoe[0][0]=='0'&&tictactoe[1][1]=='0'&&tictactoe[2][2]=='0') {
            bwin++;
        } else if(tictactoe[0][2]=='0'&&tictactoe[1][1]=='0'&&tictactoe[2][0]=='0') {
            bwin++;
        }
    }
    if(awin>0) {
        return 1;
    } else if(bwin>0) {
        return 2;
    } else {
        return 0;
    }
}

void conditionBoxChoosed(char tictactoe[][3],int *index1,int *index2,int chance) {
    int a,b;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if((int)tictactoe[i][j]-48==chance) {
                a=i;
                b=j;
            }
        }
    }
    *index1=a;
    *index2=b;
}

int checkdublicate(char tictactoe[][3],int chance,int index1,int index2) {
    if(tictactoe[index1][index2]!=' ') {
        return 0;
    } else {
        return 1;
    }
}