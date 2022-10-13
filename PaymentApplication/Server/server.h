#ifndef SERVER_H
#define SERVER_H

#include "../Card/card.h"
#include "../Terminal/terminal.h"

typedef unsigned int uint32_t;

typedef enum EN_transState_t
{
    APPROVED,
    DECLINED_INSUFFICIENT_FUND,
    DECLINED_STOLEN_CARD,
    INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef struct ST_accountsDB_t
{
    float balance;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

typedef enum EN_serverError_t
{
    OKAY,
    SAVING_FAILED,
    TRANSACTION_NOT_FOUND,
    ACCOUNT_NOT_FOUND,
    LOW_BALANCE
}EN_serverError_t;

EN_transState_t receiveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_cardData_t *cardData); //Added secound argument
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);

// Helper Function for search 
int linearSearch(ST_cardData_t *cardData);

#endif
