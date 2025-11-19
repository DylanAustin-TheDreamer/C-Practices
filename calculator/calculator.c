#include <stdio.h>  // include information about standard input/output library
#include <stdbool.h>

// run commands - cd calculator; gcc calculator.c -o cal.exe; .\cal.exe
//
// make sure - C:\msys64\ucrt64\bin\ - is setup in environment variables
// windows btn -> type environment variables -> click on path in user variables then edit -> click new -> paste C:\msys64\ucrt64\bin\ -> click ok -> click ok on next screen -> restart VScode
// should run cal.exe with run command mentioned above.

void half_adder(int A, int B);
void binary_adder(int A, int B, char operator);
void binary_subtract(int A, int B, char operator);
void binary_times(int A, int B, char operator);
void binary_divide(int A, int B, char operator);

int main()  // a function called main that receives no argument values
{
    // statements of main are enclosed in braces
    bool hasEnded = false;
    int a;
    char operator;
    int b;


    while(hasEnded == false){
        printf("Enter your desired number input: ");
        scanf(" %d %c %d", &a, &operator, &b);
        while(getchar() != '\n');  // Clear the input buffer
        if(operator == '+'){
            binary_adder(a, b, operator);
        }
        else if(operator == '-'){
            binary_subtract(a, b, operator);
        }
        else if (operator == '*'){
            binary_times(a, b, operator);
        }
        else if (operator == '/'){
            binary_divide(a, b, operator);
        }
        else{
            printf("Please use one of the following calculation operators - +, -, * (times), / (divide)\n");
        }

    };

    return 0;  // indicate that the program ended successfully
}

// Below are our functions which do our calculations.
void half_adder(int A, int B){

}
void binary_adder(int A, int B, char operator){

}
void binary_subtract(int A, int B, char operator){

}
void binary_times(int A, int B, char operator){

}
void binary_divide(int A, int B, char operator){

}

