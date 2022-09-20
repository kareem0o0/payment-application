#ifndef APPLICATION  //header file guard
#define APPLICATION
#include "server.h"	

													//my additional functions


void check_file(FILE* data)
{
	if (data == NULL)
	{
		printf("Trouble reading file...\nprogram terminating");
		exit(0);
	}
}
void create_file(char name[20],char first_line[100])
{
	if (access(name,0) == 0) {/* do nothing */ }
	else 
	{
		Data = fopen(name, "w");										
		check_file(Data);
		fprintf(Data, first_line);
		fclose(Data);
	}
}
char* read_file(char name[], int line_number, int order)
{
	char* p;
	char line[1000]={0};
	Data = fopen(name, "r"); 
	check_file(Data);

	for (int i = 0; i < line_number; i++)
	{
		fgets(line, 1000, Data);
	}
	//we no longer need the file, so close it
	fclose(Data);

	p = strtok(line, "|");

	for (int i = 0; i < order; i++)
	{
		p = strtok(NULL, "|");
	}
	return p;
}
void append_to_file(char name[], char added[],char string_format)
{
	Data = fopen(name, "a");
	check_file(Data);
	//fputs(added, Data);
	fprintf(Data, string_format, added);
	fclose(Data);
}
int file_no_of_lines(char name[])
{
	char line[1000];
	int counter=0;
	Data = fopen(name, "r");
	check_file(Data);
	while (fgets(line, 100, Data) != NULL) { counter++; }
	fclose(Data);
	return counter;
}
void space_maker(int num)
{
	for (int i = 0; i < num; i++)
	{
		fprintf(Data," ");
	}
	fprintf(Data, "|");
}
int getlen(int x) {
	if (x >= 1000000000) return 10;
	if (x >= 100000000)  return 9;
	if (x >= 10000000)   return 8;
	if (x >= 1000000)    return 7;
	if (x >= 100000)     return 6;
	if (x >= 10000)      return 5;
	if (x >= 1000)       return 4;
	if (x >= 100)        return 3;
	if (x >= 10)         return 2;
	return 1;
}
int balance_update(ST_transaction_t* transData,int line_number,FILE *fp)
{
	

	FILE * fc;

	int count = 0;  //count number lines in source file.
	int ch;   //temporary place to store character of source file(one at a time).
	int edited = 0;  //0=false and 1=true
	


	fp = fopen("balance data.txt", "r");
	fc = fopen("balance data temp.txt", "w");

	check_file(fp);
	check_file(fc);

	while ((ch = fgetc(fp)) != EOF)
	{

		if (ch == '\n')  //counts number of lines
			count++;
		if (count == line_number - 1 && edited == 0) 
		{

			  //stores input at error line in file fc(target.txt) from variable t.


			fprintf(fc, "\n%s", transData->cardHolderData.primaryAccountNumber);
			 
																											// same as space_maker function...
			for (int i = 0; i < 24 - strlen(transData->cardHolderData.primaryAccountNumber); i++)
			{
				fprintf(fc, " ");
			}
			fprintf(fc, "|");


			fprintf(fc, "%f\n", transData->balance - transData->terminalData.transAmount);

			edited = 1;  //this prevents loop to execute more than once(as error is already edited)

			while ((ch = fgetc(fp)) != EOF)  //Actually this loop will skips the existing line in source.txt(see below)
			{                           //we want to skip this line because this is error line.
				if (ch == '\n')//this will break when next new line(after error line is skipped) is found.
					break;
			}
		}
		else
			fprintf(fc, "%c", ch);
	}
	fclose(fp);
	fclose(fc);

	if (edited == 0)
		printf("\nLine Not Found");
	remove("balance data.txt");
	rename("balance data temp.txt", "balance data.txt");
	return 0;
}
int card_block(ST_cardData_t* transData, int line_number, FILE* fp)
{


	FILE* fc;

	int count = 0;  //count number lines in source file.
	int ch;   //temporary place to store character of source file(one at a time).
	int edited = 0;  //0=false and 1=true


	fp = fopen("accounts data.txt", "r");
	fc = fopen("temp.txt", "w");

	check_file(fp);
	check_file(fc);

	while ((ch = fgetc(fp)) != EOF)
	{

		if (ch == '\n')  //counts number of lines
			count++;
		if (count == line_number - 1 && edited == 0)
		{

			//stores input at error line in file fc(target.txt) from variable t.


			fprintf(fc, "\n%sed", transData->cardHolderName);

			// same as space_maker function...
			for (int i = 0; i < 24 - strlen(transData->cardHolderName)-2; i++)
			{
				fprintf(fc, " ");
			}
			fprintf(fc, "|");
			fprintf(fc, "b%sblkd", transData->primaryAccountNumber);
			for (int i = 0; i < 24 - strlen(transData->primaryAccountNumber)-5; i++)
			{
				fprintf(fc, " ");
			}
			fprintf(fc, "|");
			fprintf(fc, "%s\n", transData->cardExpirationDate);
			

			edited = 1;  //this prevents loop to execute more than once(as error is already edited)

			while ((ch = fgetc(fp)) != EOF)  //Actually this loop will skips the existing line in source.txt(see below)
			{                           //we want to skip this line because this is error line.
				if (ch == '\n')//this will break when next new line(after error line is skipped) is found.
					break;
			}
		}
		else
			fprintf(fc, "%c", ch);
	}
	fclose(fp);
	fclose(fc);

	if (edited == 0)
		printf("\nLine Not Found");
	remove("accounts data.txt");
	rename("temp.txt", "accounts data.txt");
	printf("Card is blocked successfully...");
	exit(0);
}
int add_account(ST_transaction_t* transData,float* balance)
{
	if (!isValidAccount(&transData->cardHolderData)) { printf("card PAN number already exist !"); return 0; }
	while (getCardHolderName(&transData->cardHolderData)) { printf("WRONG NAME, please try again....\n"); }
	printf("Balance : ");
	scanf("%i",&balance);

	Data = fopen("accounts data.txt", "a");
	check_file(Data);

	fprintf(Data, "\n%s", transData->cardHolderData.cardHolderName);
	space_maker(24 - strlen(transData->cardHolderData.cardHolderName));

	fprintf(Data, "%s", transData->cardHolderData.primaryAccountNumber);
	space_maker(24 - strlen(transData->cardHolderData.primaryAccountNumber));

	fprintf(Data, "%s", transData->cardHolderData.cardExpirationDate);

	fclose(Data);

	Data = fopen("balance data.txt", "a");
	check_file(Data);

	fprintf(Data, "\n%s", transData->cardHolderData.primaryAccountNumber);
	space_maker(24 - strlen(transData->cardHolderData.primaryAccountNumber));

	fprintf(Data, "%i", balance);

	fclose(Data);
	printf("account added successfully...");
}
void welcome()
{
	printf("welcome to the payment application...\n\n"
		"After reading ,scroll down for writing freedom  ^^\n\n"
		"please consider these rule :\n\n"
		"		-card holder name must be 20-24 characters long \n"
		"		-card expiry date must follow this format ---> mm/yy     ex. 02/25 \n"
		"		-card PAN must follow the luhn number algorithm and be 16-20 characters long \n"
		"		-transaction Date must follow this format ----> dd/mm/yyyy    ex.17/09/2022 \n"
		"										\n"
		"other modes :\n"
		"\n"
		"	-if you want to block the card :\n"
		"					1- write 'block' when asked for the card holder name  \n"
		"					2- fill in the card data\n"
		"					3-fill valid any transaction amount\n"
		"		\n\n"
		"	-if you want to get a certain transaction by the sequence number :\n"
		"					1- write 'get transaction' when asked for the card holder name\n"
		"					2- write the sequence number of your transaction\n\n\n"
		"	-if you want to add an account	:\n"																    
		"					1- write 'add account' when asked for the card holder name\n"
		"					2- write the card expiry date,PAN number and balance\n"

	);
}

#endif 