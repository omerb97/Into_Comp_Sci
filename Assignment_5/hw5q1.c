#include <stdio.h>
#include <math.h>

#define POWER_MULTIPLIER 10
#define TRUE 1
#define FALSE 0

void PrintWellcomeMessage();
void PrintIsPalindrome();
void PrintIsNotPalindrome();
int  digit_count (int num);
int palindrome_check (int num, int length);

// main function that initiates the program
int main (){
    int num = 0;
    PrintWellcomeMessage();
    scanf("%d", &num);
    int returnValue = palindrome_check(num, digit_count(num));
    if (returnValue == TRUE)
        PrintIsPalindrome();
    if (returnValue ==FALSE)
        PrintIsNotPalindrome();
    return 0;

}

//uses recursion to see if its a palindrome
int palindrome_check (int num, int length){
    int howLong = digit_count(num);
    int rightNum = num%POWER_MULTIPLIER;
    if (howLong < length){
        if (rightNum ==0){
            int newNum = num/10;
            return palindrome_check(newNum, length-2);
        } else
            return 0;
    }
    if (howLong == 0){
        return TRUE; // trivial case: zero numbers is a palindrome
    }
    int powerOf = howLong-1;
    int leftNum = (int)(num/(pow(POWER_MULTIPLIER, (double)powerOf)));

    if (leftNum == rightNum){ // if both numbers are equal from both sides
        int newNum = num - (leftNum * (pow(POWER_MULTIPLIER,(double)powerOf)));
        newNum = newNum /POWER_MULTIPLIER;
        return TRUE*palindrome_check(newNum, howLong-2);
    }
    else
        return FALSE;//if they are not equal even once then its not a palindrome and it will return 0

}

//this functions uses recursion to count how many digits are in the number
int digit_count (int num){
    if (num==0)
        return FALSE;
    if (num/10==0){
        return TRUE;
    }

    return digit_count(num/10)+1;
}
void PrintWellcomeMessage()
{
    printf("Please enter a number:\n");
}

void PrintIsPalindrome()
{
    printf("It's a palindrome!");
}
void PrintIsNotPalindrome()
{
    printf("It's not a palindrome!");
}