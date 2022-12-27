#include <stdio.h>
#include "../Library/std_typs.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "app.h"


extern uint8_t Index;

int appStart(void) {
	
	ST_cardData_t cardData;
	EN_cardError_t cardError;
	ST_terminalData_t terminalData;
	EN_terminalError_t terminalError;
	EN_serverError_t serverError;
	EN_transState_t transactionError;
	ST_accountsDB_t accountRefrence;
	
	 //Getting the card holder name
	printf("Please Enter Your Card Holder Name\n");
	do
	{
		cardError = getCardHolderName(&cardData);
		if (cardError == WRONG_NAME) {
			printf("Wrong Card Name \n \n");
		}
	} while (cardError != OK);
	
	//Getting the expiry card date
	printf("Please Enter Your Card Expiry Date in Format MM/YY\n");
	do
	{
		cardError = getCardExpiryDate(&cardData);
		if (cardError == WRONG_EXP_DATE) {
			printf("Wrong Expiration Date \n");
		}
	} while (cardError != OK);

	//Getting the card Primary Account Number
	printf("Please Enter Your Primary Account Number\n");
	do
	{
		cardError = getCardPAN(&cardData);
		if (cardError == WRONG_PAN) {
			printf("Wrong Primary Account Number \n \n");
		}
	} while (cardError != OK);
	
	//checking if the account exists in the database of the server
	serverError = isValidAccount(&cardData);
	if (serverError == ACCOUNT_NOT_FOUND) {
		printf("Declined Process (Invalid Account)");
		return 0;
	}
	
	//checking if the account is blocked in the database of the server
	serverError = isBlockedAccount(&accountRefrence);
	if (serverError == BLOCKED_ACCOUNT) {
		printf("Declined Process (Blocked Account)");
		return 0;
	}
	
	//Getting the transaction date and the function will internally check if the date the user entered matches with the current date or not
	printf("Please Enter The Current Date In Format DD/MM/YYYY\n");
	do {
		terminalError = getTransactionDate(&terminalData);
		if (terminalError == WRONG_DATE) {
			printf("Wrong Transaction Date \n \n");
		}
	} while (terminalError != OK);

	//checking if the card is expired or not
	terminalError = isCardExpired(&cardData, &terminalData);
	if (terminalError == EXPIRED_CARD) {
		printf("Declined Process (Expired Card)\n");
		return 0;
	}
	
	//getting the maximum transaction amount
	do {
		terminalError = setMaxAmount(&terminalData);
		if (terminalError == INVALID_MAX_AMOUNT) {
			printf("Invalid Maximum Amount");
		}
	} while (terminalError != OK);
	
	//getting the transaction amount from the user
	do {
		terminalError = getTransactionAmount(&terminalData);
		if (terminalError == INVALID_AMOUNT) {
			printf("Invalid Amount");
		}
	} while (terminalError != OK);

	

	//checking if the transaction amount below the maximum amount
	terminalError = isBelowMaxAmount(&terminalData);
	if (terminalError == EXCEED_MAX_AMOUNT) {
		printf("Declined Process (Amount Exceeding Limit)\n");
		return 0;
	}
	
	//checking if the account has below or equal to his current balance in the database of the server
	serverError = isAmountAvailable(&terminalData);
	if (serverError == LOW_BALANCE) {
		printf("Declined Process (Insuffecient Funds)");
		return 0;
	}
	
	ST_transaction_t transactionData = {
		cardData,
		terminalData
	};
	
	//printong the current balance of the user befor and after the transaction and save the transaction data
	printf("Your Current Balance is: \n%.2f \n", accountsDB[Index].balance);
	transactionError = recieveTransactionData(&transactionData);
	if (transactionError == APPROVED) {
		saveTransaction(&transactionData);
		printf("Approved Transaction, and your new balance is: \n%.2f \n", accountsDB[Index].balance);
	}

	
	return 0;

	
}


