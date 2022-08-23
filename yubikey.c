#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yubikey.h"

#define CODE_SIZE   45
#define ID_SIZE     13
#define OTP_SIZE    33
#define BIN_SIZE    129

int main(){
    char yubikey_code[CODE_SIZE];
    char yubikey_id[ID_SIZE];
    char otp[OTP_SIZE]; 
    int i, j; 

    printf("Touchez votre yubikey: ");
    scanf("%s", yubikey_code);

    for (i = 0; i < ID_SIZE-1; i++){
        yubikey_id[i] = yubikey_code[i]; 
    }

    yubikey_id[i] = '\0';

    for(i=ID_SIZE-1, j=0; i < CODE_SIZE-1; i++, j++){
        otp[j] = yubikey_code[i];
    }

    otp[j] = '\0';

    char *hex = modhexToHex(otp, OTP_SIZE); 
    char *bin = hexToBin(hex);

    printf("Yubikey code: %s\n", yubikey_code);
    printf("Yubikey ID: %s\n", yubikey_id);
    printf("Yubikey OTP: %s\n", otp);
    printf("Yubikey OTP hexadecimal: %s\n", hex);
    printf("Yubikey OTP binaire: %s\n", bin);

    return 0;
}

/*
* Convertion de modHexadecimal a hexadecimal. 
*
*/
char * modhexToHex(char *s, int len){
    char *hex = malloc(len * sizeof(char)); 
    int i, j, k;
    char mh[4][8] = {
        '0', 'c', '4', 'f', '8', 'j', 'c', 'r',
        '1', 'b', '5', 'g', '9', 'k', 'd', 't', 
        '2', 'd', '6', 'h', 'a', 'l', 'e', 'u', 
        '3', '3', '7', 'i', 'b', 'n', 'f', 'v'
    };

    for(k=0; k < len; k++){
        for(i=0; i < 4; i++){
            for(j=0; j < 8; j++){
                if(s[k] == mh[i][j] && ((j+1)% 2 == 0)){
                    hex[k] = mh[i][j-1];
                }
            }
        }
    }
    hex[k] = '\0'; 

    return hex;
}

/*
*  Convertion hexa-binaire simplifiée.
**/
char * hexToBin(char *s){
    static char bin[BIN_SIZE]; 
    int i = 0;

    while(s[i]){
        switch(s[i]){
            case '0':
                strcat(bin, "0000"); 
                break;
            case '1':
                strcat(bin, "0001"); 
                break;
            case '2':
                strcat(bin, "0010"); 
                break;
            case '3':
                strcat(bin, "0011"); 
                break;
            case '4':
                strcat(bin, "0100"); 
                break;
            case '5':
                strcat(bin, "0101"); 
                break;
            case '6':
                strcat(bin, "0110"); 
                break;
            case '7':
                strcat(bin, "0111"); 
                break;
            case '8':
                strcat(bin, "1000"); 
                break;
            case '9':
                strcat(bin, "1001"); 
                break;
            case 'A':
            case 'a':
                strcat(bin, "1010"); 
                break;
            case 'B':
            case 'b':
                strcat(bin, "1011"); 
                break;
            case 'C':
            case 'c':
                strcat(bin, "1100"); 
                break;
            case 'D':
            case 'd':
                strcat(bin, "1101"); 
                break;
            case 'E':
            case 'e':
                strcat(bin, "1110"); 
                break;
            case 'F':
            case 'f':
                strcat(bin, "1111"); 
                break;
            default:
                printf("\nInvalid hexadecimal digit: %c", s[i]); 
        }
        i++;
    }
    bin[i*4] = '\0';

    return bin; 
}