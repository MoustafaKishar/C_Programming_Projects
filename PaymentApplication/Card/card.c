#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    printf("Please Enter Cardholder's Name: ");
    gets(cardData->cardHolderName);
    if(strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24){
        return WRONG_NAME;
    }else{
        return OK;
    }
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    char date[6];
    char part1[3];
    char part2[3];
    printf("Please Enter Card Expiry Date (Format MM/YY): ");
    gets(cardData->cardExpirationDate);
    if(strlen(cardData->cardExpirationDate)!=5){
        return WRONG_EXP_DATE;
    }else{
        strcpy(date, cardData->cardExpirationDate);
        strncpy(part1, date, 2);
        strrev(date);
        strncpy(part2, date, 2);
        strrev(part2);
        strrev(date);
        if(atoi(part1)>=1 && atoi(part1)<=12 && isdigit(part2[0]) && isdigit(part2[1]) && date[2]=='/'){
            return OK;
        }else{
            return WRONG_EXP_DATE;
        }
    }
}
EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    printf("Please Enter Primary Account Number (PAN): ");
    gets(cardData->primaryAccountNumber);
    if(strlen(cardData->primaryAccountNumber)<16 || strlen(cardData->primaryAccountNumber)>19){
        return WRONG_PAN;
    }else{
        return OK;
    }
}
