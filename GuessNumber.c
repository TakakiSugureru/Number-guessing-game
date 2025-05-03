#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
    int number; // For saving the number from user
    int guesses; // The number of guesses
}GN;

void cleanInputbuffer();
void hint(int guess, int secret, int max);

void randomGuess(int max, int level, int maxGuesses){
    GN gn1;
    gn1.guesses = 0;
    int SecretNum = rand() % max + 1;

    while(gn1.guesses < maxGuesses){
        printf("\nEnter your guess (from 1 to %d): ", max);
        // Check if user enters the number or not
        if(scanf("%d",&(gn1.number)) != 1){
            cleanInputbuffer();
            printf("Please enter a valid number!\n");
            continue;
        } else {
            cleanInputbuffer();
        }
        
        if(gn1.number < 1 || gn1.number > max){
            printf("Please enter the number between 1 and %d\n", max);
            continue;
        }
        //increase the number of guesses
        gn1.guesses++;

        if(gn1.number < SecretNum){
            printf("The number you guessed is too low! It'd be <%d. Now, try again.\n", gn1.number);
        } else if (gn1.number > SecretNum){
            printf("The number you guessed is too high! It'd be >%d. Try again.\n", gn1.number);
        } else {
            printf("Congrat! The secret number is %d, you guessed correctly after %d times!\n", SecretNum, gn1.guesses);
            break;
        }

        if(maxGuesses - gn1.guesses == 1){
            printf("WARNING: You have only 1 guess left!!!\n");
        }

        if(gn1.guesses == maxGuesses && gn1.number != SecretNum){
            printf("Game over. The secret number was: %d.\n", SecretNum);
            break;
        }

        int hinted = 0;
        if(level >= 3){
            hint(gn1.guesses, SecretNum, max);
        }
    }
}

void hint(int guess, int secret, int max){
    if(guess > 3){
        printf("Hint 1: The secret number is %s.\n", (secret % 2 == 0) ? "even" : "odd");
    }
    if(guess > 7){
        int lower = secret - 50;
        int upper = secret + 50;

        if(lower < 1) lower = 1;
        if(upper > max) upper = max;
        printf("Hint 2: The number is between %d and %d.\n", lower, upper);
    }
    if(guess > 10){
        int lower = secret - 10;
        int upper = secret + 10;

        if(lower < 1) lower = 1;
        if(upper > max) upper = max;
        printf("Last hint: The number is between %d and %d.\n", lower, upper);
    }
}

void cleanInputbuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int main(){
    GN gn1;
    int level;
    srand(time(NULL));
    char *input = (char*)calloc(100, sizeof(char));
    if (input == NULL){
        return 1;
    }

    while(1){
        printf("\n---Welcome to Guess Number Game!---\n");
        printf("Please select the level:\n");
        printf("1. Easy\n");
        printf("2. Normal\n");
        printf("3. Hard\n");
        printf("4. Hell!!!\n");
        printf("What'll you choose...?: ");
        fgets(input,100,stdin);

        // Remove newline
        size_t len = strlen(input);
        if(len > 0 && input[len - 1] == '\n'){
            input[len - 1] = '\0';
        }

        if(strcmp(input,"q") == 0 || strcmp(input,"Q") == 0){
            printf("Goodbye, have a nice day!\n");
            break;
        }
        level = atoi(input);

        int max;
        switch(level){
            case 1:
                max = 10;
                printf("You chose the easy level, you'll have 5 turn to guess the number from 1 to 10!\n");
                randomGuess(max, level, 5);
                break;
            case 2:
                max = 100;
                printf("You chose the normal level, you'll have 10 turn to guess the number from 1 to 100!\n");
                randomGuess(max, level, 10);
                break;
            case 3:                
                max = 1000;
                printf("You chose the hard level, you'll have 30 turn to guess the number from 1 to 1000!\n");
                randomGuess(max, level, 30);
                break;
            case 4:                
                max = 10000;
                char *choice = (char*)malloc(100 * sizeof(char));

                printf("Are you sure? it'll very hard.\n");
                printf("\tPress 1 for Yes.\n");
                printf("\tPress 2 for No.\n");
                printf("Your decision is? ");
                fgets(choice, 100, stdin);

                int input1 = atoi(choice);
                if(input1 == 1){
                    printf("Let's dance!\n");
                    printf("You chose the HELL level, you'll have 30 turn to guess the number from 1 to 10000!\n");
                    randomGuess(max, level, 30);
                    break;
                } else if (input1 == 2){
                    printf("Whatever.\n");
                    break;
                } else {
                    printf("I guess it as No.\n");
                    break;
                }
                free(choice);
            default:
                printf("Hey! That's invalid, please choose again!\n");
        }
    }

    free(input);
    return 0;
}