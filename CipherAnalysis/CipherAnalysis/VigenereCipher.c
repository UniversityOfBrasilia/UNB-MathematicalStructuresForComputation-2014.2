//
//  VigenereCipher.c
//  CifraCesar
//
//  Created by Thiago-Bernardes on 12/6/14.
//  Copyright (c) 2014 TMB. All rights reserved.
//
#include "CaesarCipher.c"

#define KEYSIZE 30

char* encryptWithVigenereCipher(char* key, char* messageToEncrypt){
    
    int keyLength = (int)strlen(key);
    int messageToEncryptLength = (int)strlen(messageToEncrypt);
    
    int currentKey;
    char currentChar;
    char *encryptedMessage = malloc(sizeof(char) * messageToEncryptLength);

    for (int messageCharPosition = 0, keyCharPosition = 0; messageCharPosition < messageToEncryptLength; messageCharPosition++,keyCharPosition++) {
        
        if (keyCharPosition == keyLength) {
            keyCharPosition = 0;
        }
        
        currentKey = getKeyValueByChar(key[keyCharPosition]);
        currentChar = *encryptWithCaesarCipher(currentKey, &messageToEncrypt[messageCharPosition]);
        encryptedMessage[messageCharPosition] = currentChar;

    }

    return encryptedMessage;
}

char* decryptWithVigenereCipher(char* key, char* messageToDecrypt){
    
    int keyLength = (int)strlen(key);
    int messageToDecryptLength = (int)strlen(messageToDecrypt);
    
    int currentKey;
    char currentChar;
    char *decryptedMessage = malloc(sizeof(char) * messageToDecryptLength);
    
    for (int messageCharPosition = 0, keyCharPosition = 0; messageCharPosition < messageToDecryptLength; messageCharPosition++,keyCharPosition++) {
        
        if (keyCharPosition == keyLength) {
            keyCharPosition = 0;
        }
        
        currentKey = getKeyValueByChar(key[keyCharPosition]);
        currentChar = *decryptWithCaesarCipher(currentKey, &messageToDecrypt[messageCharPosition]);
        decryptedMessage[messageCharPosition] = currentChar;
        
    }
    
    return decryptedMessage;
}


void vigenereCipherInterface(char *message){
    
    char key[KEYSIZE];
    printf("\nEntre com a chave de criptografia: ");
    fflush(stdin);
    scanf("%s",key);
    
    
    char* encryptedMessage = malloc(sizeof(char) * 120);
    encryptedMessage = encryptWithVigenereCipher(key,message);
    char* decryptedMessage = malloc(sizeof(char) * 120);
    decryptedMessage = decryptWithVigenereCipher(key, encryptedMessage);
    
    printf("Encriptada : %s \n\n Decriptada : %s \n",encryptedMessage,decryptedMessage);
    
}