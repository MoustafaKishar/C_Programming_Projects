#include "server.h"

#include "../Terminal/terminal.c"

ST_accountsDB_t accountsDB[255]= {{100.00, "5411111111111115"}, {15000.00, "5511111111111114"}, {0.55, "4532111111111112"}, 
{1500.12, "4751271111111118"}}; 
// Visa card: starts with 4     // Master card: starts with 5
// Extra Account: 4112456711110008
ST_transaction_t transactionsDone[255];


EN_transState_t receiveTransactionData(ST_transaction_t *transData){
    EN_transState_t currentTransState;
    if(isValidAccount(&transData->cardHolderData) == 0){
        if(isAmountAvailable(&transData->terminalData, &transData->cardHolderData) == 0){
            int foundIndex = linearSearch((&transData->cardHolderData));
            accountsDB[foundIndex].balance = accountsDB[foundIndex].balance - (*(&transData->terminalData.transAmount));  // * to dereference value
            currentTransState = APPROVED;
        }else{
            currentTransState = DECLINED_INSUFFICIENT_FUND;}
    }else{
        currentTransState = DECLINED_STOLEN_CARD;}
    transData->transState = currentTransState;
    int savingState = saveTransaction(transData);
    if(savingState == 1){
        currentTransState = INTERNAL_SERVER_ERROR;
    }
    return currentTransState;
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData){
    int foundIndex = linearSearch(cardData);
    if(foundIndex == -1){
        return ACCOUNT_NOT_FOUND;
    }else{
        return OKAY;
    }
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_cardData_t *cardData){
    int foundIndex = linearSearch(cardData);
    if(foundIndex == -1){
        return ACCOUNT_NOT_FOUND;
    }else{
        if(termData->transAmount<=accountsDB[foundIndex].balance){
            return OKAY;
        }else{
            return LOW_BALANCE;
        }
    }
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){
    int id = -1;
    for(int i=0; i<256; i++){
        if(transactionsDone[i].transactionSequenceNumber == 0){
            id = i;
            break;
        }
    }
    if(id==-1){
        return SAVING_FAILED;
    }else{
        transData->transactionSequenceNumber = id+1;
        transactionsDone[id] = *transData;
        return OK;
    }
}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData){
    for(int i = 0; i< (sizeof(transactionsDone)/sizeof(transactionsDone[0])); i++){
        if(transactionsDone[i].transactionSequenceNumber != 0){
            if(transactionsDone[i].transactionSequenceNumber == transactionSequenceNumber){
                *transData = transactionsDone[i];
                return OKAY;
            }
        }
    }
    return TRANSACTION_NOT_FOUND;
}

int linearSearch(ST_cardData_t *cardData){
    int foundIndex = -1;
    for (int i = 0; i< (sizeof(accountsDB)/sizeof(accountsDB[0])); i++){
        if(strlen(accountsDB[i].primaryAccountNumber)>0){  // checks that cell isn't empty
            if(strcmp(accountsDB[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0){
                foundIndex = i;
            }
        }
    }
    return foundIndex;
}