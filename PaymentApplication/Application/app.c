#include <stdio.h>
#include <string.h>

#include "app.h"
#include "../Server/server.c"

void appStart(void){
    // Retreiving Card Data
    ST_cardData_t card;
    int nameError;
    int expiryDateError;
    int panError;
    do{
        nameError = getCardHolderName(&card);
        if(nameError == 1){printf("WRONG NAME FORMAT, Please Enter a Valid One.\n");}
    }while(nameError != 0);
    do{
        expiryDateError = getCardExpiryDate(&card);
        if(expiryDateError == 2){printf("WRONG EXPIRY DATE FORMAT, Please Enter a Valid One.\n");}
    }while(expiryDateError != 0);
    do{
        panError = getCardPAN(&card);
        if(panError == 3){printf("WRONG PAN FORMAT, Please Enter a Valid One.\n");}
    }while(panError != 0);
    int transactionFailed = 0;
    int panCheckError = isValidCardPAN(&card);
    if(panCheckError==3){
        printf("Declined Transaction, PAN is NOT a Luhn Number.\n");
        transactionFailed = 1;
    }
    if(transactionFailed == 0){
        // Retreiving Transaction Data
        ST_terminalData_t term;
        term.maxTransAmount = 10000.00;     // Manually Setting Maximum Amount as shouldn't be defined by user.
        int transDateError;
        int transAmountError;
        do{
            transDateError = getTransactionDate(&term);
            if(transDateError == 1){printf("WRONG DATE FORMAT, Please Enter a Valid One.\n");}
        }while(transDateError != 0);
        if(isCardExpired(&card, &term)==2){
            printf("Declined Transaction, Card Expired.\n");
            transactionFailed = 1;
        }
        if(transactionFailed == 0){
            do{
                transAmountError = getTransactionAmount(&term);
                if(transAmountError == 4){printf("WRONG AMOUNT FORMAT, Please Enter a Valid One.\n");}
            }while(transAmountError != 0);
            if(isBelowMaxAmount(&term) == 5){
                printf("Declined Transaction, Amount Exceeding Limit.\n");
                transactionFailed = 1;
            }
            if(transactionFailed == 0){
                ST_transaction_t trans;
                trans.cardHolderData = card;
                trans.terminalData = term;
                int transactionStatus = receiveTransactionData(&trans);
                if(transactionStatus == 2){
                    printf("Declined Transaction, Invalid Account.\n");
                }else if(transactionStatus == 1){
                    printf("Declined Transaction, Insufficient Funds.\n");
                }else if(transactionStatus == 3){
                    printf("Declined Transaction, Internel Server Error while Saving.\n");
                }else{
                    printf("Transaction Approved & Saved.\n");
                    printf("Transaction Sequence Number: %d\n", trans.transactionSequenceNumber);
                    char getTrans = '0';
                    char transSeqChar;
                    int transSeqNum;
                    ST_transaction_t searchTrans;
                    printf("Do yo want to get details of previous Transaction? (Enter 1 if Yes): ");
                    gets(&getTrans);
                    if(getTrans == '1'){
                        printf("Please Enter Transaction Sequence Number: ");
                        gets(&transSeqChar);
                        transSeqNum = transSeqChar - '0';
                        int searchTransError = getTransaction(transSeqNum, &searchTrans);
                        if(searchTransError == 0){
                            int length = strlen(searchTrans.cardHolderData.primaryAccountNumber);
                            uint8_t transPAN[length+1];
                            for(int i = 0; i< length; i++){
                                if(i> (length-5)){
                                    transPAN[i] = searchTrans.cardHolderData.primaryAccountNumber[i];
                                }else{
                                    transPAN[i] = '*';
                                }
                            }
                            transPAN[length] = '\0';
                            printf("Transaction Details Found: \n");
                            printf("Transaction Account Number: %s\n", transPAN);
                            printf("Transaction Date: %s\n", searchTrans.terminalData.transactionDate);
                            printf("Transaction Amount: %f\n", searchTrans.terminalData.transAmount);
                        }else{
                            printf("Transaction Not Found.\n");
                        }
                    }
                }
            }
        }
    }
}

int main(){
    char exit = '1';
    while(1){
        appStart();
        printf("Do you want to perform another transaction? (Enter 0 if No): ");
        gets(&exit);
        if(exit == '0'){
            break;
        }
    }
    return 0;
}