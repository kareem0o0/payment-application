#include "app.h"

int main()

				
{			//files creation...
	create_file("accounts data.txt", "CARD HOLDER NAME      |PRIMARY ACCOUNT NUMBER  |EXPIRATION DATE  ");
	create_file("balance data.txt", "PRIMARY ACCOUNT NUMBER  |BALANCE  ");
	create_file("transaction data.txt", "CARD HOLDER NUMBER      |PRIMARY ACCOUNT NUMBER  |EXPIRATION DATE  |maximum ammount  |transaction ammount  |transaction date  |transaction state             |sequence number  \n");

			//initial declarations...
	ST_transaction_t account1;
	account1.terminalData.maxTransAmount = 100000;				//as a default maximum amount...
	welcome();
	while (1)
	{	  
		account1.transState = APPROVED;
			// card stage...
		while (getCardHolderName(&account1.cardHolderData))			{ printf("WRONG NAME, please try again....\n"); }

		while (getCardExpiryDate(&account1.cardHolderData))			{ printf("WRONG EXP DATE, please try again....\n"); }

		while (getCardPAN(&account1.cardHolderData) || isValidCardPAN(&account1.cardHolderData))
		
		{ printf("WRONG PAN, please try again....\n"); }

		if (!strcmp("add account", account1.cardHolderData.cardHolderName)) { add_account(&account1, &account1.balance); exit(0); }
		
			//terminal stage...
		while (getTransactionDate(&account1.terminalData))			{ printf("WRONG DATE, please try again....\n"); }

		if (isCardExpired(account1.cardHolderData, account1.terminalData)) { printf("CARD IS EXPIRED...\n"); exit(0); }

		while (getTransactionAmount(&account1.terminalData)) 			{ printf("INVALID AMOUNT, please try again....\n"); }
	
		if (isBelowMaxAmount(&account1.terminalData))					{ printf("EXCEED MAX_AMOUNT....\n"); exit(0); }
		 
			//server stage...
		if (isValidAccount(&account1.cardHolderData)) { printf("INVALID CARD,STOLEN....\n"); account1.transState = DECLINED_STOLEN_CARD; }
		
		else if (isAmountAvailable(&account1))	    	{ printf("DECLINED ,INSUFFECIENT FUNDS....\n");account1.transState = DECLINED_INSUFFECIENT_FUND; }
		
		account1.transactionSequenceNumber = file_no_of_lines("transaction data.txt");

		saveTransaction(&account1);
	}
	
}


