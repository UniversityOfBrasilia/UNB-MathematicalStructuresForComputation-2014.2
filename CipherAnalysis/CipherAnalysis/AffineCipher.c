#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>

#define ALPHABETRANGE 26

int getKeyValueByChars(char keyB){
    
    int keyValueB;
    
    if( keyB >= 'a' && keyB <= 'z'){
        keyValueB = keyB - 'a';
        return keyValueB;

    }else if (keyB >= 'A' && keyB <= 'Z'){
            keyValueB = keyB - 'A';

        return keyValueB;
    }

        return keyB;
         
}

bool validationKeyA(int keyA){
	
    int n1 = ALPHABETRANGE;
    int n2 = keyA;
	
    if (keyA > 0 ) {
        
        int rest = n1%n2;
        
        while(rest!=0)
        {
            n1    = n2;
            n2    = rest;
            rest = n1%n2;
        }
        
        if (n2==1)
            return true;

    }
    
    return false;
}

char* encryptWithAffineCipher(int encryptKeyA, int encryptKeyB , char* messageToEncrypt){
    
    
    int menssageToEncryptLength = (int)strlen(messageToEncrypt);
    
    char* encryptedMessage = (char*)malloc(sizeof (char)*(menssageToEncryptLength+1));
    
    for (int i = 0; i < menssageToEncryptLength; i++) {
        
        if( messageToEncrypt[i] >= 'a' && messageToEncrypt[i] <= 'z'){
            encryptedMessage[i] = (((messageToEncrypt[i]- 'a')*encryptKeyA+encryptKeyB)%ALPHABETRANGE)+'a';

           }else
                if (messageToEncrypt[i] >= 'A' && messageToEncrypt[i] <= 'Z'){
                    encryptedMessage[i] = (((messageToEncrypt[i]- 'A')*encryptKeyA+encryptKeyB)%ALPHABETRANGE)+'A';
                }else{
                    
                    encryptedMessage[i] = messageToEncrypt[i];
                }

        
    }

    return encryptedMessage;
}

char* decryptWithAffineCipher(int descryptKeyA, int descryptKeyB, char* messageToDecrypt){
    

    int menssageToDecryptLength = (int)strlen(messageToDecrypt);
    
    char* decryptedMessage = (char*)malloc(sizeof (char)*(menssageToDecryptLength+1));
    
    for (int i = 0; i < menssageToDecryptLength; i++) {
        
        if( messageToDecrypt[i] >= 'a' && messageToDecrypt[i] <= 'z'){
           decryptedMessage[i] = (((messageToDecrypt[i]-'a'-descryptKeyB)/descryptKeyA)%ALPHABETRANGE)+'a';
            
            if (decryptedMessage[i] < 'a') {
                decryptedMessage[i] = 'a' + ALPHABETRANGE - ('a' - decryptedMessage[i]);
            }
            
           }else
           if (messageToDecrypt[i] >= 'A' && messageToDecrypt[i] <= 'Z'){
                decryptedMessage[i] = (((messageToDecrypt[i]-'A'-descryptKeyB)/descryptKeyA)%ALPHABETRANGE)+'A';
               
               if (decryptedMessage[i] < 'A') {
                   decryptedMessage[i] = 'A' + ALPHABETRANGE - ('A' - decryptedMessage[i]);
               }
               
           }else{
               
               decryptedMessage[i] = messageToDecrypt[i];
           }
        
        
        }
    
    return decryptedMessage;
}


void hackingAffineCipherWithBruteForce(char* messageToHack){
    
    char* hackedMessageTest = (char*)malloc (sizeof(char) * (strlen(messageToHack) +1));

    clock_t start_time;
    start_time = clock();
    
    for (int i = 0; i <= ALPHABETRANGE; i++) {
        
        for (int j = 0; j<= ALPHABETRANGE; j++){
        	
        	if(validationKeyA(j) && j > 0){
        		hackedMessageTest = decryptWithAffineCipher(j, i, messageToHack);
        		printf("\nChave Testada = %c,\nResultado = %s",i+'A',hackedMessageTest);
        		printf("\n\n=========================================================\n\n");
        	}
		}

    }
    
    double time_in_seconds = (clock() - start_time) / (double)CLOCKS_PER_SEC;

    printf("\nA quebra demorou %.10f segundos\n",time_in_seconds);

    
}

void affineCipherInterface(char* text){
    
    int keyA;
    char keyB;
    printf("\nEntre com a chave A (número) e a chave B (letra) de criptografia: ");
    fflush(stdin);
    scanf("%d%c",&keyA, &keyB);
    
    while (!validationKeyA(keyA)){
    	printf("Chave A invalida. Entre novamente com a chave A: ");
    	scanf("%d", &keyA);
	}
    int keyValueB = getKeyValueByChars(keyB);
    
    
    char *encryptedMessage;
    
    encryptedMessage = encryptWithAffineCipher(keyA, keyValueB, text);
    hackingAffineCipherWithBruteForce(encryptedMessage);
    
}

