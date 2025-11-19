#include <stdio.h>  // include information about standard input/output library
#include <stdbool.h>

// run command in terminal - cd calculator; gcc calculator.c -o cal.exe; .\cal.exe
//
// make sure - C:\msys64\ucrt64\bin\ - is setup in environment variables
// windows btn -> type environment variables -> click on path in user variables then edit -> click new -> paste C:\msys64\ucrt64\bin\ -> click ok -> click ok on next screen -> restart VScode
// should run cal.exe with run command mentioned above.

// These functions at the top are called prototype functions. Where we call them at the top, to be called in int main - But the logic is declared later
// The functions represent 'Gates'. When the first digital calculator was created in the 1960's (after a tab of acid - jk), they were created using gates.
// basically, how in binary 1 is true and 0 is false - We get the same effect, with high voltage (true) and low voltage (false).
// so we end up with binary logic, and they are built up bit by bit from these voltage gates below. In real life the gates are made with silicon.
// silicon is a semiconductor and it can conduct or block electricity. So imagine the silicon in different forms/structures determining electrical behaviour.
// combining them in specific patterns creates transistors - Transistors act as voltage-controlled switches
// Arrange transistors in patterns and we get logic gates that behave a certain way (AND, OR, XOR, etc.)
int AND(int A, int B);
int OR(int A, int B);
int XOR(int A, int B);
int NOT(int A);
// these functions represent adders which are made up of a combination of gates mentioned above - but not all of them at once because they serve different functionality.
int half_adder(int A, int B, int *sum, int *carry);
int full_adder(int A, int B, int carry, int *sum, int *Cout);

// Also, what you may be able to identify, is that the bits form a code that represent a number in binary. Where each decimal place is to the power of 2.
// lets take the lucky number 7 - does 8 go in 7? nah: 0 - does 4 go in 7? ye: 1 then 7 - 4 = 3 does 2 go in 3? yeah: 1 then 3 - 2 = 1 does 1 go in 1? yeah: 1 - otherwise if it was zero we would have 0
// so 0111 would be 7. Now, there are types of formatting like ASCII that take binary codes and represent them as characters in the way we see them. letters etc.
// a letter will represent a number in binary code. And that's how this works. So lets make a calculator knowing what we know now (given you didn't already know).

// fun fact - In the same way we are simulating a calculator in binary - A conceptual simulation has been used to simulate neural networks to develop AI.


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
        printf("DEBUG: a=%d, operator='%c', b=%d\n", a, operator, b);

        if (operator == '+'){
            // set up the binary extraction
            int result = 0;   // Will hold the final answer
            int carry = 0;    // Start with no carry
        
            // we make a for loop here to increment i 32 times. 32 to represent 32 bit positions.
            // note that i++ is not mathematical addition used in our calculation. i++ is just a counter increment to move through bit positions (0, 1, 2, 3...)
            // We dont have the functionality to create binary code on the hardware level - like a calculator sends signals when a button is pressed.
            for (int i = 0; i < 32; i++){
                // we use >> operator for bit shifting in C
                int bit_a = (a >> i) & 1;
                int bit_b = (b >> i) & 1;
                int sum_bit;
                int carry_out;
                // Call full_adder
                full_adder(bit_a, bit_b, carry, &sum_bit, &carry_out);
                // note the addresses trick again. it will wire the pointer in full_adder to our variable set before calling full_adder. Cool stuff.
                // Store the sum_bit in the result at position i - note the | (upward slash) is a bitwise OR operator.
                //What it does:
                // Takes the current result
                // ORs it with the new bit shifted to position i
                // This "sets" bit i in the result without destroying other bits
                result = result | (sum_bit << i);
                // Update carry for next iteration
                carry = carry_out;
            }
            printf("Result: %d\n", result);
        }
        else if (operator == '-'){
            // set up the binary extraction
            int result = 0;   // Will hold the final answer
            int carry = 1;    // Start with no carry

            for (int i = 0; i < 32; i++){
                int bit_a = (a >> i) & 1;
                int bit_b = (b >> i) & 1;
                int sum_bit;
                int carry_out;

                // flipping the bits of b
                int flip_b = NOT(bit_b);

                full_adder(bit_a, flip_b, carry, &sum_bit, &carry_out);
                result = result | (sum_bit << i);
                carry = carry_out;
            }
            printf("Result: %d\n", result);
        }

    }

    return 0;  // indicate that the program ended successfully
}

// here we have our adder functions
// note the pointers in the function parameters. We assign the change in values to the memory address of those variables.
// no returns
int half_adder(int A, int B, int *carry, int *sum){
    *sum = XOR(A, B);
    *carry = AND(A, B);
    // We are using assign and no incrementation because we can only have 0s and 1s
    // How each iteration takes affect after we chain multiple adders together, is that we build up a list of 0s and 1s
    // the next bit position is defined by whether we have a carry over for the next iteration.
}
int full_adder(int A, int B, int carry, int *sum, int*Cout){
    // two half adders
    int temp_sum1;
    int temp_carry1;
    // this is horrific - but you declare the variables you want to store, and assign their address in the carry and sum field for half_adder
    // AI isn't giving me code but is acting as a teacher. I don't actually know C so I'm kinda learning it as we go. Makes me think I don't know programming at all though as well
    half_adder(A, B, &temp_carry1, &temp_sum1);
    // recap - The function modifies temp_sum1 and temp_carry1 through the pointers.

    int temp_sum2;
    int temp_carry2;
    half_adder(temp_sum1, carry, &temp_carry2, &temp_sum2);

    *Cout = OR(temp_carry1, temp_carry2);
    *sum = temp_sum2;
}


// Below are our function gates which pass our bits.
int AND(int A, int B){
  if (A == 1 && B == 1){
    return 1;
  }
  else{
    return 0;
  }
}
int OR(int A, int B){
   if (A == 1 || B == 1){
    return 1;
  }
  else{
    return 0;
  }
}
int XOR(int A, int B){
   if (A != B){
    return 1;
  }
  else{
    return 0;
  }
}
// for two's complement - my first understanding is subtraction
int NOT(int A){
   if(A == 1){
    return 0;
   }
   else{
    return 1;
   }
}

