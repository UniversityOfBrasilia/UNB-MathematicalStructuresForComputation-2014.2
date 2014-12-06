//
//  main.c
//  CifraCesar
//
//  Created by Thiago-Bernardes on 11/29/14.
//  Copyright (c) 2014 TMB. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define ALPHABETUPPERFIRSTCHAR 65 //Correspods to letter "A" in ASC2 table
#define ALPHABETLOWERFIRSTCHAR 97 //Correspods to letter "a" in ASC2 table

#define ALPHABETRANGE 25

int getKeyValueByChar(char key){
    
    int keyValue;
    
    if( key >= 'a' && key <= 'z'){
        keyValue = key - 65;
        
    }else
        if (key >= 'A' && key <= 'Z'){
            keyValue = key - 97;
            
        }else{
            
            keyValue = key;
        }
    
    return keyValue;
    
}

char* encryptWithCaesarCipher(int encryptKey, char* messageToEncrypt){
    
    
    int menssageToEncryptLength = (int)strlen(messageToEncrypt);
    
    char* encryptedMessage = malloc(sizeof (char)*(menssageToEncryptLength+1));
    
    for (int i = 0; i < menssageToEncryptLength; i++) {
        
        if( messageToEncrypt[i] >= 'a' && messageToEncrypt[i] <= 'z'){
            encryptedMessage[i] = ((messageToEncrypt[i]-ALPHABETLOWERFIRSTCHAR+encryptKey)%ALPHABETRANGE)+ALPHABETLOWERFIRSTCHAR;

           }else
                if (messageToEncrypt[i] >= 'A' && messageToEncrypt[i] <= 'Z'){
                    encryptedMessage[i] = ((messageToEncrypt[i]-ALPHABETUPPERFIRSTCHAR+encryptKey)%ALPHABETRANGE)+ALPHABETUPPERFIRSTCHAR;
                }else{
                    
                    encryptedMessage[i] = messageToEncrypt[i];
                }

        
    }

    return encryptedMessage;
}

char* decryptWithCaesarCipher(int decryptKey, char* messageToDecrypt){
    

    int menssageToDecryptLength = (int)strlen(messageToDecrypt);
    
    char* decryptedMessage = malloc(sizeof (char)*(menssageToDecryptLength+1));
    
    for (int i = 0; i < menssageToDecryptLength; i++) {
        
        if( messageToDecrypt[i] >= 'a' && messageToDecrypt[i] <= 'z'){
           decryptedMessage[i] = ((messageToDecrypt[i]-ALPHABETLOWERFIRSTCHAR-decryptKey)%ALPHABETRANGE)+ALPHABETLOWERFIRSTCHAR;
           }else
           if (messageToDecrypt[i] >= 'A' && messageToDecrypt[i] <= 'Z'){
               decryptedMessage[i] = ((messageToDecrypt[i]-ALPHABETUPPERFIRSTCHAR-decryptKey)%ALPHABETRANGE)+ALPHABETUPPERFIRSTCHAR;
           }else{
               
               decryptedMessage[i] = messageToDecrypt[i];
           }
        
        
        }
    
    return decryptedMessage;
}

void hackingCaesarCipherWithBruteForce(char* messageToHack){
    
    char* hackedMessageTest = malloc (sizeof(char) * (strlen(messageToHack) +1));

    clock_t start_time;
    start_time = clock();
    
    for (int i = 0; i <= ALPHABETRANGE; i++) {
        
        hackedMessageTest = decryptWithCaesarCipher(i, messageToHack);
        printf("\nChave Testada = %d,\nResultado = %s",i,hackedMessageTest);
        printf("\n\n=========================================================\n\n");


    }
    
    double time_in_seconds = (clock() - start_time) / (double)CLOCKS_PER_SEC;

    printf("\nA quebra demorou %.10f segundos",time_in_seconds);

    
}

void caesarCipherInterface(char* text){
    
    char key;
    printf("\nEntre com a chave de criptografia: ");
    fflush(stdin);
    scanf("%c",&key);
    
    int keyValue = getKeyValueByChar(key);
    
    char *encryptedMessage;
    
    encryptedMessage = encryptWithCaesarCipher(keyValue,text);
    hackingCaesarCipherWithBruteForce(encryptedMessage);
    
}

