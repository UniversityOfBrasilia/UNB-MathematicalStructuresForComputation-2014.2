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
#include <ctype.h>

//O operador de módulo do C (operador %) computa apenas o resto da divisão e gera números negativos. Entao Nesta versão em C deve-se fazer uma pequena correção na resposta dada pelo operador de módulo, pois o algoritmo de euclides precisa do módulo positivo.
int module(int firstFactor, int secondFactor)
{
    
    int residue = firstFactor % secondFactor;
    
    /* Uma correçã é necessária se r e b não forem do mesmo sinal */
    
    /* se r for negativo e b positivo, precisa corrigir */
    if ((residue < 0) && (secondFactor > 0))
        return (secondFactor + residue);
    
    /* Se ra for positivo e b negativo, nova correcao */
    if ((residue > 0) && (secondFactor < 0))
        return (secondFactor + residue);
    
    return (residue);
}

int powerModule(int base, int power, int setLength){
    
    base = module(base,setLength);
    int result = 1;
    for (int i = 1; i <= power; i++) {
        
        result *= base;
        result = module(result,setLength);
    }
    
    return result;
    
}

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
    
    residue = module(firstFactor,secondFactor);
    
    while (residue != 0) {
        
        firstFactor = secondFactor;
        secondFactor = residue;
        residue = module(firstFactor,secondFactor);
        
    }
    
    return secondFactor;
}


//The euclides extended algorithm calc the inverse of firstFactor MOD(secondFactor)
int euclidesExtendedAlgorithm(int firstFactor, int secondFactor, int inverse)
{
    int residue;
    
    residue = module(secondFactor, firstFactor);
    
    if (residue == 0) {
        return (module((inverse / firstFactor), (secondFactor / firstFactor)));
    }
    
    return ((euclidesExtendedAlgorithm(residue, firstFactor, -inverse) * secondFactor + inverse) / (module(firstFactor, secondFactor)));
}


//Generate public key, just is the number that satisfy the greatest commom divisor with the amountOfCoPrimes
int generatePublicKey(int amountOfCoPrimes){
    
    int publicKey;
    publicKey = 2;
    
    while (euclidesAlgorithm(amountOfCoPrimes, publicKey) != 1 ) {
        
        publicKey++;
    }
    
    return publicKey;
    
}

int cipherChar(char character,int publicKey, int setLength){
    
    int encryptedChar;
    
    encryptedChar = powerModule(character, publicKey, setLength);
   // printf("\nchar: %d\ncryp: %d \n",character,encryptedChar);
    return encryptedChar;
    
}

int* encryptMessage(char *messageToEncrypt, int publicKey, int setLength){
    
    int messageToCryptLength = (int)strlen(messageToEncrypt) ;
    
    int *encryptedMessage = malloc(sizeof (int) * (messageToCryptLength) * 200 );
    
    
    for (int i = 0; messageToEncrypt[i] ; i++) {
            
            encryptedMessage[i] = cipherChar(messageToEncrypt[i], publicKey, setLength) ;
        
            }
    
    return encryptedMessage;
}

int decipherChar(int number,int privateKey, int setLength){
    
    int decryptedChar;
    
    decryptedChar = powerModule(number, privateKey, setLength);
    // printf("\nchar: %d\ncryp: %d \n",character,encryptedChar);
    return decryptedChar;
    
}

char *decryptMessage(int* messageToDecrypt, int privateKey, int setLength){
    
    
    int messageToDecryptLength = sizeof(messageToDecrypt) ;
    
    char *decryptedMessage = malloc(sizeof (char) * (messageToDecryptLength)  );
    
    
    for (int i = 0; messageToDecrypt[i]; i++) {

            decryptedMessage[i] = decipherChar(messageToDecrypt[i], privateKey, setLength) ;

    }
    
    return decryptedMessage;
}

void printMessage(int* message){
    
    for (int i = 0; message[i] ; i++) {
        
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
    
    firstPrimeFactor = 19;
    secondPrimeFactor = 23;
    
    setLength = calcSetLength(firstPrimeFactor, secondPrimeFactor);
    amountOfCoPrimes = totient(firstPrimeFactor, secondPrimeFactor);
    publicKey = 13;// generatePublicKey(amountOfCoPrimes);
    
    char* message = "t es tando esse trem";
    
    int* encrypted = encryptMessage(message, publicKey, setLength);
    
    printMessage(encrypted);
    
    int privateKey = euclidesExtendedAlgorithm(publicKey, amountOfCoPrimes, 1);
    
    char* decrypted = decryptMessage(encrypted, privateKey, setLength);
    
   printf("%s",decrypted);

    
    return 0;
}
