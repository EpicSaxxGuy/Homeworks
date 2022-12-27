#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
/*
This program simulates 2 different games. First option is a guessing game. It is played by one player. The rules of the game are: 
- The player tries to guess the randomly generated number which is between 1-100. Game ends when the player guesses correctly or makes 10 guesses. During the game,  
the player can either ask a question or guess a number. 
Second game is rolling a die, it is played by two players. The rules are: 
- Players throw dice two times consecutively in their turns and collect points. Game ends when the dice sum of the first player is twice the second player's sum in the  
consecutive throws. Here are some of the rules for collecting points: 
  - Players get half of the sum in consecutive throws as their points. However, if the difference between two dices is 4, player doesn't get any points but gets to
  throw the dices until the sum of the dices are greater than 8. If the player throws 3-3 or 6-6, s/he gets 3 consecutive throws but any dices that have the same value 
  are not added into the points of the player.
*/

void randomEvaluation(int, int);//these are the function prototypes 
void guessEvaluation(int, int); 
int randNum100(); 
void guessGame(); 
int randDice(); 
void throwThrice(int *, int *, int, int, int);  
void winCheck(int, int); 
void differenceof4(int *, int *, int, int *);
void throwDice(int *, int *, int *, int); 
void calcSums(int *, int, int, int *); 
void diceGame(); 
void gamePrompt();

int main()
{   
    srand(time(NULL));
    gamePrompt();
    return 0;
}  
void gamePrompt(){//asks which game you want to play and calls the requested game accordingly
    int choice;  
    while(1){
        printf("*****Welcome to Space Track Program*****\n1. Play the number guessing game\n2. Play the dice game\n3. Exit\n\nChoose what to do (1,2,3): "); 
        scanf("\n\n%d", &choice);
        if(choice == 1){ //plays the first game
            guessGame(); 
            printf("**********************************************\n"); 
        }
        else if(choice == 2){ //plays the second game 
            diceGame();  
            printf("**********************************************\n"); 
        }
        else{ //if the value of choice is other than 1 and 2, loop ends
           printf("Bye");
           break; 
        }  
    }
}
void guessGame(){//this is the 'guess the number' game  
    printf("\n*****Welcome to Number Guessing Game*****\n");
    char questOrGuess;
    int guess, guessCount = 0, questCount = 0, random = randNum100(), question, trueOrFalse = 0; 
    while(guessCount <= 9){//game continues until the user makes 10 guesses   
        printf("Make guess or Ask a question(Input M or A): "); 
        scanf("\n%c", &questOrGuess); 
        if(questOrGuess == 'M' || questOrGuess == 'm'){ 
            printf("\nMake your best between for the number between 1-100: "); 
            scanf("%d", &guess); 
            guessCount++;
            if(guess == random){ 
                printf("\nCongratulations!! You guessed the numbers correctly!!!!\nYou have made %d guesses, you asked %d questions", guessCount, questCount); 
                trueOrFalse = 1;
                break; 
            } 
            else 
                guessEvaluation(guess, random);
        } 
        else if(questOrGuess == 'A' || questOrGuess == 'a'){ 
            printf("\nQuestions to add: \n1.Is it even or odd?\n2.Is it >50?\nChoose question: ");   
            scanf("%d", &question);  
            randomEvaluation(question, random);
            questCount++;
        }
    } 
    if(trueOrFalse == 0)//prints out what the random number is if the player couldn't get the number right 
        printf("\nThe number is %d, I hope you'll get it right next time buddy!!\n", random);
} 
int randNum100(){//generates a random number between 1-100
    int num = rand() % 100 + 1; 
    return num;
} 
void guessEvaluation(int a, int b){//compares generated number w/ the guessed number and gives a message 
    if(a > b) 
        printf("It is higher than the number\n"); 
    else if(a < b)
        printf("It is smaller than the number\n"); 
}
void randomEvaluation(int a, int b){//answers the requested questions about the generated number in guessing game
    if(a == 1){ 
        if(b%2 == 0) 
            printf("The number is even\n"); 
        else 
            printf("The number is odd\n");
    } 
    else if(a == 2){ 
        if(b > 50) 
            printf("The number is >50\n"); 
        else 
            printf("The number is not >50\n");
    }
}

void diceGame(){//this is the dice game
    printf("\n*****Welcome to Dice Game*****\n"); 
    int throw1_p1, throw2_p1, throw1_p2, throw2_p2, totalsum1 = 0, totalsum2 = 0, points1 = 0, points2 = 0, throwCount = 0;  
    int tempsum1 = 0, tempsum2 = 0, playernum1 = 1, playernum2 = 2; 
    //srand(time(NULL));
    do{  
//////////////////////////////////// All functions performed by player 1
        throwDice(&throw1_p1, &throw2_p1, &throwCount, playernum1);
        differenceof4(&throw1_p1, &throw2_p1, playernum1, &throwCount); 
        throwThrice(&throwCount, &totalsum1, throw1_p1, throw2_p1, playernum1); 
        calcSums(&tempsum1, throw1_p1, throw2_p1, &totalsum1);
//////////////////////////////////// All functions performed by player 2
        throwDice(&throw1_p2, &throw2_p2, &throwCount, playernum2);
        differenceof4(&throw1_p2, &throw2_p2, playernum2, &throwCount); 
        throwThrice(&throwCount, &totalsum2, throw1_p2, throw2_p2, playernum2); 
        calcSums(&tempsum2, throw1_p2, throw2_p2, &totalsum2);
    }while(tempsum1!=2*tempsum2); 
    points1 = totalsum1/2; 
    points2 = totalsum2/2;
    printf("Player 1: %d\nPlayer 2: %d\nTotal of %d throws are performed.\n",points1, points2, throwCount); 
    winCheck(points1, points2);
}
int randDice(){//generates a random number between 1-6 which is throwing a six-sided die 
    int num = rand() % 6 + 1; 
    return num;
} 
void throwDice(int *th_1, int *th_2, int *th_cnt, int plyrnum){//throws the dice consecutively for the player 
        printf("Throw the dice for player %d: ", plyrnum);
        int a = *th_1, b = *th_2, c = *th_cnt;//passing the addresses and assigning them to some temporary variables
        a = randDice();
        b = randDice(); 
        c += 2; 
        *th_1 = a; //assigning these temporary values to the addresses that i've took from the calling function 
        *th_2 = b; 
        *th_cnt = c;
        printf("%d %d\n", a, b);
}
void throwThrice(int *count, int *sum, int ogThrow1, int ogThrow2, int playernum){ //if the dices are 3-3 or 6-6, player throw 3 consecutive dices 
    //i want count and sum of the diceGame function to change, that is why i sent them with their addresses
    if((ogThrow1 == 3 && ogThrow2 == 3)||(ogThrow1 == 6 & ogThrow2 == 6)){ 
    int tempCount = *count, tempSum = *sum, throw1, throw2, throw3;
    printf("Throw the dice for player %d: ", playernum);
    throw1 = randDice(); 
    throw2 = randDice(); 
    throw3 = randDice(); 
    tempCount += 3; 
    *count = tempCount;
    printf("%d %d %d\n", throw1, throw2, throw3); 
    if(throw1 == throw2)//if 1st and 2nd throw are equal, only add the last throw to the sum 
        tempSum += throw3;
    else if(throw1 == throw3) 
        tempSum += throw2;
    else if(throw2 == throw3) 
        tempSum += throw1; 
    else if(throw1 == throw2 == throw3)//all are equal, add zero(nothing) 
        tempSum = tempSum + 0; 
    else//all throws are different, add all to the sum
        tempSum += throw1 + throw2 + throw3; 
    *sum = tempSum;//at the end, change the value of sum
    }
}
void winCheck(int p1, int p2){//checks the points of both players and decides whoever won 
    if(p1 > p2)//if player1 has more points than player 2. s/he's the winner
        printf("\t+*+*+*+*+*\tWinner is Player 1\t+*+*+*+*+*\n"); 
    else if(p1 == p2)//if they have the same score, they draw
        printf("\t+*+*+*+*+*\tDraw\t+*+*+*+*+*"); 
    else//if player2 has more points, s/he is the winner
        printf("\t+*+*+*+*+*\tWinner is Player 2\t+*+*+*+*+*\n");
} 
void differenceof4(int *throw1, int *throw2, int playernum, int *count){//if the difference between the throws is 4, same player throws until a certain condition
    int tempTh1 = *throw1, tempTh2 = *throw2, tempCount = *count;
    if((tempTh1 - tempTh2 == 4)||(tempTh2-tempTh1==4)){ 
        while(1){ 
            printf("Throw the dice for player %d: ", playernum);
            tempTh1 = randDice(); 
            tempTh2 = randDice(); 
            printf("%d %d\n", tempTh1, tempTh2);
            tempCount += 2; 
            if(tempTh1+tempTh2 > 8){//if the sum of two throws are greater than 8, loop ends. player passes their turn 
                *count = tempCount; 
                *throw1 = tempTh1; 
                *throw2 = tempTh2;
                break; 
                /*sending the addresses of the variables(throw1, throw2 and count) is essential because i 
                want the variables that i've send to change in the diceGame function too 
                for instance, if i didn't send the 'count' variable with it's address, increasing it
                inside this function wouldn't make a difference in the diceGame*/
            }
        }
    }
} 
 void calcSums(int *tempsum, int th_1, int th_2, int *totalsum){//calculates the temporary and total sum of dices for a player
    int a = *tempsum, b = *totalsum; 
    a = th_1 + th_2; 
    b += a; 
    *tempsum = a; 
    *totalsum = b;
}
