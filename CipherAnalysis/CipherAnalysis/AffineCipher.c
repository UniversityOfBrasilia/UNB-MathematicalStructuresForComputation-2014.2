#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>

#define ALPHABETRANGE 26

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
            encryptedMessage[i] = ((((messageToEncrypt[i]- 'a')*encryptKeyA)+encryptKeyB)%ALPHABETRANGE)+'a';

           }else
                if (messageToEncrypt[i] >= 'A' && messageToEncrypt[i] <= 'Z'){
                    encryptedMessage[i] = ((((messageToEncrypt[i]- 'A')*encryptKeyA)+encryptKeyB)%ALPHABETRANGE)+'A';
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
            
            
            
           decryptedMessage[i] = ((descryptKeyA*(messageToDecrypt[i] - 'a' - descryptKeyB))%ALPHABETRANGE)+'a';
            
            if (decryptedMessage[i] < 'a') {
                decryptedMessage[i] = 'a' + ALPHABETRANGE - ('a' - decryptedMessage[i]);
            }
        
           }else
           if (messageToDecrypt[i] >= 'A' && messageToDecrypt[i] <= 'Z'){
                decryptedMessage[i] = ((descryptKeyA*(messageToDecrypt[i] - 'A' - descryptKeyB))%ALPHABETRANGE)+'A';
               
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
    
    printf("\nEntre com a chave B (letra) de criptografia: ");
    scanf("%c",&keyB);
    
    printf("\nEntre com a chave A (número)");
    scanf("%d",&keyA);
    
    while (!validationKeyA(keyA)){
        printf("Chave A invalida. Entre novamente com a chave A: ");
        fflush(stdin);
        scanf("%d", &keyA);
    }
    

    

    int keyValueB = getKeyValueByChars(keyB);

    
    char *encryptedMessage = encryptWithAffineCipher(keyA, keyValueB, text);
    printf("\nEncrypted %s\n",encryptedMessage);
    
    int decryptKeyA = euclidesExtendedAlgorithm(keyA, ALPHABETRANGE, 1);
    printf("decrypt : %d\n",decryptKeyA);

    
    char *decryptedMessage = decryptWithAffineCipher(decryptKeyA, keyValueB, encryptedMessage);
    printf("\nDecrypted %s",decryptedMessage);
    
   // hackingAffineCipherWithBruteForce(encryptedMessage);
    
}

