#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "terminal.h"
#include "../Card/card.c"

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){
    uint8_t x[20];
    strcpy(x, cardData->primaryAccountNumber);
    int checkdigit =  atoi(&x[(strlen(x)-1)]);
    int sum;
    for(int i=0; i<(strlen(x)-1); i++){
        int x1 = x[i] - '0';
        int x2;
        if(i%2 == 0){
            x2 = x1*2;
        }else{
            x2=x1;
        }
        if(x2>=10){
            x2 = (x2/10) + (x2%10);
        }
        sum += x2;
    }
    if(checkdigit == ((10- sum%10))){
        return NONE;
    }else{ 
        return INVALID_CARD;
    }
}

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    char date[11], part1[3], part2[3], part3[5];
    printf("Please Enter Transaction Date (Format DD/MM/YYYY): ");
    gets(termData->transactionDate);
    if(strlen(termData->transactionDate)!=10){
        return WRONG_DATE;
    }else{
        strcpy(date, termData->transactionDate);
        memcpy(part1, &date[0], 2);
        part1[2] = '\0';
        memcpy(part2, &date[3], 2);
        part2[2] = '\0';
        memcpy(part3, &date[6], 4);
        part3[4] = '\0';
        if(atoi(part1)>=1 && atoi(part1)<=31 && atoi(part2)>=1 && atoi(part2)<=12 && atoi(part3)>=1 && atoi(part3)<=9999 && date[2]=='/' && date[5]=='/'){
            return NONE;
        }else{
            return WRONG_DATE;
        }
    }
}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
    char cardMonth[3], cardYear[3], transMonth[3], transYear[3];
    memcpy(cardMonth, &cardData->cardExpirationDate[0], 2);
    cardMonth[2] = '\0';
    memcpy(cardYear, &cardData->cardExpirationDate[3], 2);
    cardYear[2] = '\0';
    memcpy(transMonth, &termData->transactionDate[3], 2);
    transMonth[2] = '\0';
    memcpy(transYear, &termData->transactionDate[8], 2);   // Assuming all years are after 2000 as Expiry date is 2 digits
    transYear[2] = '\0';
    if(atoi(cardYear)>atoi(transYear)){
        return NONE;
    }else if(atoi(cardYear)==atoi(transYear)){
        if(atoi(cardMonth)>atoi(transMonth)){
            return NONE;
        }else{
            return EXPIRED_CARD;
        }
    }else{
        return EXPIRED_CARD;
    }
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    printf("Please Enter Transaction Amount: ");
    scanf("%f", &termData->transAmount);
    scanf("%*1[\n]");   // Discards the newline character that the previous scanf reads 
    if(termData->transAmount<=0){
        return INVALID_AMOUNT;
    }else{
        return NONE;
    }
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
    printf("Please Set Maximum Transaction Amount: ");
    scanf("%f", &termData->maxTransAmount);
    scanf("%*1[\n]");   // Discards the newline character that the previous scanf reads 
    if(termData->maxTransAmount<=0){
        return INVALID_MAX_AMOUNT;
    }else{
        return NONE;
    }
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    if(termData->transAmount > termData->maxTransAmount){
        return EXCEED_MAX_AMOUNT;
    }else{
        return NONE;
    }
}