#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{ 
	printf("card holder name : ");

	fgets(cardData->cardHolderName, 26, stdin); //size is 26 to catch the first character of the >24 sequence

	cardData->cardHolderName[strcspn(cardData->cardHolderName, "\n")] = 0;// to delete the last new line (\n)


	if (!strcmp("block", cardData->cardHolderName)) { return OK; }			//// IN CASE of blocking the card
	if (!strcmp("get transaction", cardData->cardHolderName)) { getTransaction(); }			//// IN CASE of wanting a transaction
	if (!strcmp("add account", cardData->cardHolderName)) { return OK; }				//// IN CASE OF ADDING AN ACCOUNT

	if ((strlen(cardData->cardHolderName) > 24))
		scanf("%*[^\n]%*c");                       //to clear the buffer for the next input incase user entered
												   //more than 24 characteres
	
	if (strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24)
		return WRONG_NAME;
	else  return  OK; 
	
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) // ex. 02/25
{
	printf("card expiration date : ");

	fgets(cardData->cardExpirationDate, 7, stdin);
	
	cardData->cardExpirationDate[strcspn(cardData->cardExpirationDate, "\n")] = 0;
	
	
	if ((strlen(cardData->cardExpirationDate) > 5))
		scanf("%*[^\n]%*c");

	if (strlen(cardData->cardExpirationDate) != 5 || isdigit(cardData->cardExpirationDate[0] ==0)
		|| isdigit(cardData->cardExpirationDate[1]) == 0 || cardData->cardExpirationDate[2] != '/'
		|| isdigit(cardData->cardExpirationDate[3]) == 0 || isdigit(cardData->cardExpirationDate[4]) == 0)

		return WRONG_EXP_DATE;
	else return OK;

}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("card Primary Account Number : ");

	fgets(cardData->primaryAccountNumber, 21, stdin);
	cardData->primaryAccountNumber[strcspn(cardData->primaryAccountNumber, "\n")] = 0;

	if ((strlen(cardData->primaryAccountNumber) > 19))
		scanf("%*[^\n]%*c");


	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19)
		return WRONG_PAN;
	else  return  OK;
}




