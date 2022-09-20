#ifndef SERVER //header file guard
#define SERVER
#include "terminal.h"
typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;
typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
	float balance;
}ST_transaction_t;

typedef struct ST_fullaccountsDB_t													//my contribution 
{
	ST_cardData_t cardHolderData;
	float balance;
}ST_fullaccountsDB_t;

typedef enum EN_serverError_t
{
	OK3, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t;

typedef struct ST_accountsDB_t
{
	float balance;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;


EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_transState_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t* ammount);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
void getTransaction();
char* read_file(char name[], int line_number, int order);
int file_no_of_lines(char name[]);
void space_maker(int num);
int getlen(int x);
int balance_update(ST_transaction_t* transData, int line_number, FILE* fp);

#endif 