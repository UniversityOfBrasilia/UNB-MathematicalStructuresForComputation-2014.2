//
//  main.c
//  RSACrypt
//
//  Created by Thiago-Bernardes on 12/9/14.
//  Copyright (c) 2014 TMB. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Calc the length of the set chosen for the RSA key
int calcSetLength(int firstPrimeFactor, int secondPrimeFactor){
    
    int setLength;
    
    setLength = secondPrimeFactor * firstPrimeFactor;
    
    return setLength;
}

//Calc the amount of co-primes of an number,(Euler phi).
int totient(int firstPrimeFactor, int secondPrimeFactor){
    
    int amountOfCoPrimeFactors;
    
    amountOfCoPrimeFactors = ((firstPrimeFactor - 1) * (secondPrimeFactor -1));
    
    return amountOfCoPrimeFactors;
}

//The euclides algorithm calc the greatest common divisor
int euclidesAlgorithm(int firstFactor, int secondFactor) {
    
    int residue;
    
    residue = firstFactor%secondFactor;
    
    while (residue != 0) {
        
        firstFactor = secondFactor;
        secondFactor = residue;
        residue = firstFactor % secondFactor;
        
    }
    
    return secondFactor;
}


//Generate public key, just is the number that satisfy the greatest commom divisor with the amountOfCoPrimes
int generatePublicKey(int amountOfCoPrimes){
    
    int publicKey;
    publicKey = 2;
    
    while ( euclidesAlgorithm(amountOfCoPrimes, publicKey) != 1 ) {
        
        publicKey++;
    }
    
    return publicKey;
    
}

int cipherChar(char character,int publicKey, int setLength){
    
    int encryptedChar;
    
    encryptedChar = ( (int)pow(character,publicKey) % setLength );
    
    return encryptedChar;
    
}

int* cipherMessage(char *messageToEncrypt, int publicKey, int setLength){
    
    int messageToCryptLength = (int)strlen(messageToEncrypt);
    
    
    
    int *encryptedMessage = malloc(sizeof (char) * (messageToCryptLength) );
    
    
    for (int i = 0; i < messageToCryptLength; i++) {
        
        if( (messageToEncrypt[i] >= 'a' && messageToEncrypt[i] <= 'z') || (messageToEncrypt[i] >= 'A' && messageToEncrypt[i] <= 'Z') ){
            
            encryptedMessage[i] = cipherChar(messageToEncrypt[i], publicKey, setLength) ;
            
        }else{
                encryptedMessage[i] = messageToEncrypt[i];
        }
            }
    
    return encryptedMessage;
}


//Corrigir bug do -2
void printMessage(int* message){
    
    for (int i = 0; i < sizeof(message) - 2 ; i++) {
        
        printf("%d ",message[i]);
        
    }
    
    
}
int main(int argc, const char * argv[]) {
    
    // insert code here...
    int firstPrimeFactor;
    int secondPrimeFactor;
    int setLength;
    int amountOfCoPrimes;
    int publicKey;
    
    firstPrimeFactor = 17;
    secondPrimeFactor = 41;
    
    setLength = calcSetLength(firstPrimeFactor, secondPrimeFactor);
    amountOfCoPrimes = totient(firstPrimeFactor, secondPrimeFactor);
    publicKey = generatePublicKey(amountOfCoPrimes);
    
    char* message = "TURING";
    

    int* encrypted = cipherMessage(message, publicKey, setLength);
    
    printMessage(encrypted);
    

    
    return 0;
}
