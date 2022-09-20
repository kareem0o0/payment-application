#include "server.h"
ST_accountsDB_t  accounts_database[255] ;
ST_transaction_t transaction_database[255] = { 0 };
ST_fullaccountsDB_t full_account_datbase[255]= { 0 };
int sequence_number = 1;


EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	for (int i = 0; i < 255; i++)
	{
		if (transData->cardHolderData.cardExpirationDate != transaction_database[i].cardHolderData.cardExpirationDate
			|| transData->cardHolderData.cardHolderName != transaction_database[i].cardHolderData.cardHolderName
			|| transData->cardHolderData.primaryAccountNumber != transaction_database[i].cardHolderData.primaryAccountNumber)
		{
			return DECLINED_STOLEN_CARD;
		}
	}
}
EN_transState_t isValidAccount(ST_cardData_t* cardData)
{
	for (int i = 2; i <file_no_of_lines("accounts data.txt")+1; i++)
	{
		if (atof(cardData->primaryAccountNumber) == atof(read_file("accounts data.txt", i, 1)))
		{
			if (!strcmp("block", cardData->cardHolderName)) { card_block(cardData, i, Data); }	////incase of blocking the card			/// incase of blocking the card

			return APPROVED;
		}
		              
	}
	return DECLINED_STOLEN_CARD;
}

EN_serverError_t isAmountAvailable(ST_transaction_t* data1)
{
	for (int i = 1; i < file_no_of_lines("balance data.txt") + 1; i++)
	{
		if (atof(data1->cardHolderData.primaryAccountNumber) == atof(read_file("balance data.txt", i, 0)))
		{
			if (data1->terminalData.transAmount > (data1->balance = atof(read_file("balance data.txt", i, 1)) ) )
			{
				return LOW_BALANCE;
			}
			else
			{
				balance_update(data1, i, Data);
				return OK3;

			}
		}
	}

}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{

	Data = fopen("transaction data.txt", "a");
	check_file(Data);
	
	fprintf(Data, "%s", transData->cardHolderData.cardHolderName);
	space_maker(24 - strlen(transData->cardHolderData.cardHolderName));

	fprintf(Data, "%s", transData->cardHolderData.primaryAccountNumber);
	space_maker(24 - strlen(transData->cardHolderData.primaryAccountNumber));

	fprintf(Data, "%s", transData->cardHolderData.cardExpirationDate);
	space_maker(17 - strlen(transData->cardHolderData.cardExpirationDate));

	fprintf(Data, "%f", transData->terminalData.maxTransAmount );
	space_maker(17-getlen(transData->terminalData.maxTransAmount)-7);

	fprintf(Data, "%f", transData->terminalData.transAmount);
	//gcvt(transData->terminalData.transAmount, getlen(transData->terminalData.transAmount), test);								//convert float to string...
	space_maker(21 - getlen(transData->terminalData.transAmount)-7);

	fprintf(Data, "%s", transData->terminalData.transactionDate);
	space_maker(18 - 10);
	
	switch (transData->transState)
	{
	case APPROVED:
	{fprintf(Data, "%s", "APPROVED"); space_maker(30 - 8); break; }
	case DECLINED_STOLEN_CARD:
	{fprintf(Data, "%s", "DECLINED_STOLEN_CARD"); space_maker(30 - 20); break; }
	case DECLINED_INSUFFECIENT_FUND:
	{fprintf(Data, "%s", "DECLINED_INSUFFECIENT_FUND"); space_maker(30 - 26); break; }
	}
	
	fprintf(Data, "%d\n", transData->transactionSequenceNumber/2);
	
	fclose(Data);
	printf("seq. number = %d\n \n", transData->transactionSequenceNumber / 2);
}
void getTransaction()
{
	int seq_num;
	printf("Enter sequence number : ");
	scanf("%i", &seq_num);
	char line[1000] = {0};
	for (int i = 2; i < file_no_of_lines("transaction data.txt") + 1; i++)
	{
		if (seq_num == atoi(read_file("transaction data.txt", i, 7)))
		{
				Data = fopen("transaction data.txt", "r");
				check_file(Data);

				for (int c = 0; c <i; c++)
				{
					fgets(line, 1000, Data);
				}
				printf("%s", line);
				fclose(Data);
				exit(0);

			
		}

	}
	printf("couldn't find it..."); exit(0);
}















