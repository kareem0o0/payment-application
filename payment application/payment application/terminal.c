#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) //ex. 12/10/2022
{
														
	printf("transaction date : ");
	fgets(termData->transactionDate, 12, stdin);
	termData->transactionDate[strcspn(termData->transactionDate, "\n")] = 0;
	if ((strlen(termData->transactionDate) > 10))
	{
		scanf("%*[^\n]%*c");
		return WRONG_DATE;																//length validation
	}

	
	for (int i = 0; i < 10; i++)
	{	
		if (i == 2 || i == 5)
		{
			if(termData->transactionDate[i] != '/')
				return WRONG_DATE;
		}																				//FORMAT VALIDATION
		else
		{
			if (!isdigit(termData->transactionDate[i]) != 0)
				return WRONG_DATE;
		}
	}
	 return OK1;

	
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	//printf("%s\n%s\n", cardData.cardExpirationDate, termData.transactionDate);
	int exp_date_month, exp_date_year,trm_date_day, trm_date_month, trm_date_year;

	exp_date_month = (cardData.cardExpirationDate[0] - '0' )*10 +(cardData.cardExpirationDate[1] -'0');
	exp_date_year = (cardData.cardExpirationDate[3] - '0') * 10 + (cardData.cardExpirationDate[4] - '0') + 2000;
	trm_date_day = (termData.transactionDate[0] - '0') * 10 + (termData.transactionDate[1] - '0'); //not usefull but for demonstration 
	trm_date_month = (termData.transactionDate[3] - '0') * 10 + (termData.transactionDate[4] - '0');
	trm_date_year = (termData.transactionDate[6] - '0') * 1000 + (termData.transactionDate[7] - '0') *100 + (termData.transactionDate[8] - '0') * 10 + (termData.transactionDate[9] - '0');
	
	//printf("%d\n%d\n%d\n%d\n%d\n", exp_date_month, exp_date_year, trm_date_day, trm_date_month, trm_date_year);
	
	if (exp_date_year > trm_date_year || (exp_date_year == trm_date_year && exp_date_month > trm_date_month))
		return OK1;
	else 
		return EXPIRED_CARD;
	
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	char bait[50];
	printf("transaction amount : ");
	fgets(bait,100,stdin);

	termData->transAmount = atof(bait);								//if entry is an alphabet ,,it will be = 0
	for (int i = 0; i < strlen(bait)-1; i++) {

		if (!isdigit(bait[i])) 
		return INVALID_AMOUNT;
	
	}
	if ((strlen(bait) == 1) || termData->transAmount ==0)
	{
		return INVALID_AMOUNT;
	}																							
	else return OK1;

}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else return OK1;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	char bait[50];
	printf("Maximum ammount : ");
	fgets(bait, 100, stdin);

	termData->maxTransAmount = atof(bait);								//if entry is an alphabet ,,it will be = 0
	for (int i = 0; i < strlen(bait) - 1; i++) {

		if (!isdigit(bait[i]))
		{
			printf("invaid\n");
			return INVALID_AMOUNT;
		}

	}
	if ((strlen(bait) == 1) || termData->maxTransAmount == 0)
	{
		printf("invaid\n");
		return INVALID_AMOUNT;
	}
	else return OK1;

}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	int PAN[20]={0};
	for (int i = 0; i < strlen(cardData->primaryAccountNumber); i++)
	{
		PAN[i] = (int)(cardData->primaryAccountNumber[i])-48;                //convert array of uint8_t array to int 
	}

	for (int i = 0; i < strlen(cardData->primaryAccountNumber); i = i+2)
	{
		PAN[i] = PAN[i] * 2;
	}

	for (int i = 0; i < strlen(cardData->primaryAccountNumber); i++)				//10653122181120990
	{
		if (PAN[i] > 9)
			PAN[i] = PAN[i] - 9;
	}

	int sum=0;
	for (int i = 0; i < strlen(cardData->primaryAccountNumber); i++)
	{
		sum += PAN[i] ;
	}
	if (sum % 10 == 0)
		return OK1;
	else return INVALID_CARD;
}