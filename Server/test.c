#include <stdio.h>
#include <string.h>
#include "../Library/std_typs.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"
#include "test.h"

int main()
{
	/*uncomment the function you want to test*/
	// isValidAccountTest();
	// isBlockedAccountTest();
	// isAmountAvailableTest();
    // recieveTransactionDataTest();
	// saveTransactionTest();
	listSavedTransactionsTest();
}
/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/
void isValidAccountTest(void)
{
	
	ST_cardData_t cardData;
	EN_cardError_t cardError;
	EN_serverError_t serverError;
	
	printf("****************************************************************************************************\n");
	printf("Tester Name: Abanoub Ashraf\n");
	printf("Function Name: isValidAccountTest\n");
	printf("Test Case 1: Primary account number does not exist in the database\n");
	printf("Input Data: 8989374615436852\n");
	cardError = getCardPAN(&cardData);
	serverError = isValidAccount(&cardData);
	printf("Expected Result: Declined Process (Invalid Account)\n");
	printf("Actual Result: ");
	if (serverError == ACCOUNT_NOT_FOUND) 
	{
		printf("Declined Process (Invalid Account)\n");
	}
	printf("****************************************************************************************************\n");
	printf("Test Case 2: Primary account number exists in the database\n");
	printf("Input Data: 8989374615436851\n");
	cardError = getCardPAN(&cardData);
	serverError = isValidAccount(&cardData);
	printf("Expected Result: Server Ok\n");
	printf("Actual Result: ");
	if (serverError == SERVER_OK) 
	{
		printf("Server Ok\n");
	}
	printf("****************************************************************************************************\n");
}
/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/
void isBlockedAccountTest(void)
{
	ST_cardData_t cardData;
	EN_cardError_t cardError;
	EN_serverError_t serverError;
	ST_accountsDB_t accountRefrence;
	
	printf("****************************************************************************************************\n");
	printf("Tester Name: Abanoub Ashraf\n");
	printf("Function Name: isBlockedAccountTest\n");
	printf("Test Case 1: Primary account number is blocked in the database\n");
	printf("Input Data: 5807007076043875\n");
	cardError = getCardPAN(&cardData);
	serverError = isValidAccount(&cardData);
	serverError = isBlockedAccount(&accountRefrence);
	printf("Expected Result: Declined Process (Blocked Account)\n");
	printf("Actual Result: ");
	if (serverError == BLOCKED_ACCOUNT) 
	{
		printf("Declined Process (Blocked Account)\n");
	}
	printf("****************************************************************************************************\n");
	printf("Test Case 2: Primary account number is running in the database\n");
	printf("Input Data: 9875321460123578\n");
	cardError = getCardPAN(&cardData);
	serverError = isValidAccount(&cardData);
	serverError = isBlockedAccount(&accountRefrence);
	printf("Expected Result: Server Ok\n");
	printf("Actual Result: ");
	if (serverError == SERVER_OK) 
	{
		printf("Server Ok\n");
	}
	printf("****************************************************************************************************\n");
}
/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/
void isAmountAvailableTest(void)
{
	ST_cardData_t cardData;
	EN_cardError_t cardError;
	ST_terminalData_t terminalData;
	EN_terminalError_t terminalError;
	EN_serverError_t serverError;
	EN_transState_t transactionError;
	ST_accountsDB_t accountRefrence;
	
	printf("****************************************************************************************************\n");
	printf("Tester Name: Abanoub Ashraf\n");
	printf("Function Name: isAmountAvailableTest\n");
	printf("Test Case 1: Amount is greater than the balance in the database (Balance 15000.50)\n");
	printf("Input Data: 1234567891524789\n");
	printf("Input Data: 16000\n");
	cardError = getCardPAN(&cardData);
	serverError = isValidAccount(&cardData);
	serverError = isBlockedAccount(&accountRefrence);
	terminalError = getTransactionAmount(&terminalData);
	serverError = isAmountAvailable(&terminalData);
	printf("Expected Result: Declined Process (Insuffecient Funds)\n");
	printf("Actual Result: ");
	if (serverError == LOW_BALANCE) 
	{
		printf("Declined Process (Insuffecient Funds)\n");
		
	}
	printf("****************************************************************************************************\n");
	printf("Test Case 2: Amount is less than the balance in the database (Balance 15000.50)\n");
	printf("Input Data: 14000\n");
	terminalError = getTransactionAmount(&terminalData);
	serverError = isAmountAvailable(&terminalData);
	printf("Expected Result: Approved Transaction\n");
	printf("Actual Result: ");
	if (serverError == SERVER_OK) 
	{
		printf("Approved Transaction\n");
		
	}
	printf("****************************************************************************************************\n");	
}
/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/
void recieveTransactionDataTest(void)
{
	ST_cardData_t cardData;
	EN_cardError_t cardError;
	ST_terminalData_t terminalData;
	EN_terminalError_t terminalError;
	EN_serverError_t serverError;
	EN_transState_t transactionError;
	ST_accountsDB_t accountRefrence;
	printf("****************************************************************************************************\n");
	printf("Tester Name: Abanoub Ashraf\n");
	printf("Function Name: recieveTransactionDataTest\n");
	printf("Test Case 1: happy-case scenarios (All data are in the database and correct)\n");
	printf("Input Data 1: Abanoub Ashraf Ragae\n");
	printf("Input Data 2: 12/22 \n");
	printf("Input Data 3: 1234567891524789 \n");
	printf("Input Data 4: 23/12/2022 \n");
	printf("Input Data 5: 10000 \n");
	printf("Input Data 6: 8000 \n");
	
	printf("Please Enter Your Card Holder Name\n");
	cardError = getCardHolderName(&cardData);
	printf("Please Enter Your Card Expiry Date in Format MM/YY\n");
	cardError = getCardExpiryDate(&cardData);
	printf("Please Enter Your Primary Account Number\n");
	cardError = getCardPAN(&cardData);
	serverError = isValidAccount(&cardData);
	serverError = isBlockedAccount(&accountRefrence);
	printf("Please Enter The Current Date In Format DD/MM/YYYY\n");
	terminalError = getTransactionDate(&terminalData);
	terminalError = isCardExpired(&cardData, &terminalData);
	terminalError = setMaxAmount(&terminalData);
	terminalError = getTransactionAmount(&terminalData);
	terminalError = isBelowMaxAmount(&terminalData);
	serverError = isAmountAvailable(&terminalData);
	ST_transaction_t transactionData = {
		cardData,
		terminalData
	};
	printf("Expected Result: Your Current Balance is: 15000.50 \n");
	printf("	         Approved Transaction, and your new balance is: 7000.50\n\n");
	
	
	printf("Actual Result: ");
	printf("Your Current Balance is: %.2f \n", accountsDB[Index].balance);
	transactionError = recieveTransactionData(&transactionData);
	if (transactionError == APPROVED) {
		saveTransaction(&transactionData);
		printf("	       Approved Transaction, and your new balance is: %.2f \n", accountsDB[Index].balance);
	}
	else
	{
		printf("Worng Data\n");
	}
	
	printf("****************************************************************************************************\n");
	printf("Test Case 2: Worst-case scenarios (one of the data is not correct) (Blocked Account)\n");

	printf("Input Data 1: 12/22 \n");
	printf("Input Data 2: 5807007076043875 (Blocked Account)\n");
	printf("Input Data 3: 23/12/2022 \n");
	printf("Input Data 4: 10000 \n");
	printf("Input Data 5: 8000 \n");
	
	cardError = getCardHolderName(&cardData);
	printf("Please Enter Your Card Expiry Date in Format MM/YY\n");
	cardError = getCardExpiryDate(&cardData);
	printf("Please Enter Your Primary Account Number\n");
	cardError = getCardPAN(&cardData);
	serverError = isValidAccount(&cardData);
	serverError = isBlockedAccount(&accountRefrence);
	printf("Please Enter The Current Date In Format DD/MM/YYYY\n");
	terminalError = getTransactionDate(&terminalData);
	terminalError = isCardExpired(&cardData, &terminalData);
	terminalError = setMaxAmount(&terminalData);
	terminalError = getTransactionAmount(&terminalData);
	terminalError = isBelowMaxAmount(&terminalData);
	serverError = isAmountAvailable(&terminalData);
	
	printf("Expected Result: Recieving not completed successfully\n");
	printf("Actual Result: ");
	transactionError = recieveTransactionData(&transactionData);
	if (transactionError == APPROVED) {
		saveTransaction(&transactionData);
		printf("	       Approved Transaction, and your new balance is: %.2f \n", accountsDB[Index].balance);
	}
	else
	{
		printf("Recieving not completed successfully\n");
	}
}
/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/
void saveTransactionTest(void)
{
	ST_cardData_t cardData;
	EN_cardError_t cardError;
	ST_terminalData_t terminalData;
	EN_terminalError_t terminalError;
	EN_serverError_t serverError;
	EN_transState_t transactionError;
	ST_accountsDB_t accountRefrence;
	printf("****************************************************************************************************\n");
	printf("Tester Name: Abanoub Ashraf\n");
	printf("Function Name: saveTransactionTest\n");
	printf("Test Case 1: happy-case scenarios (All data are in the database and correct)\n");
	printf("Input Data 1: Abanoub Ashraf Ragae\n");
	printf("Input Data 2: 12/22 \n");
	printf("Input Data 3: 1234567891524789 \n");
	printf("Input Data 4: 23/12/2022 \n");
	printf("Input Data 5: 10000 \n");
	printf("Input Data 6: 8000 \n");
	
	printf("Please Enter Your Card Holder Name\n");
	cardError = getCardHolderName(&cardData);
	printf("Please Enter Your Card Expiry Date in Format MM/YY\n");
	cardError = getCardExpiryDate(&cardData);
	printf("Please Enter Your Primary Account Number\n");
	cardError = getCardPAN(&cardData);
	serverError = isValidAccount(&cardData);
	serverError = isBlockedAccount(&accountRefrence);
	printf("Please Enter The Current Date In Format DD/MM/YYYY\n");
	terminalError = getTransactionDate(&terminalData);
	terminalError = isCardExpired(&cardData, &terminalData);
	terminalError = setMaxAmount(&terminalData);
	terminalError = getTransactionAmount(&terminalData);
	terminalError = isBelowMaxAmount(&terminalData);
	serverError = isAmountAvailable(&terminalData);
	ST_transaction_t transactionData = {
		cardData,
		terminalData
	};
	printf("Expected Result: Data saved successfully \n");

	
	
	printf("Actual Result: ");

	transactionError = recieveTransactionData(&transactionData);
	serverError=saveTransaction(&transactionData);
	if (serverError == SERVER_OK)
	{
		printf("Data saved successfully\n");
	}
	else
	{
		printf("failed to save data \n");
	}
	printf("\n****************************************************************************************************\n");
}

/**************************************************************************************************************/
/**************************************************************************************************************/
/**************************************************************************************************************/
void listSavedTransactionsTest(void)
{
	ST_cardData_t cardData;
	EN_cardError_t cardError;
	ST_terminalData_t terminalData;
	EN_terminalError_t terminalError;
	EN_serverError_t serverError;
	EN_transState_t transactionError;
	ST_accountsDB_t accountRefrence;
	printf("****************************************************************************************************\n");
	printf("Tester Name: Abanoub Ashraf\n");
	printf("Function Name: listSavedTransactionsTest\n");
	printf("Test Case 1: happy-case scenarios (All data are in the database and correct)\n");
	printf("Input Data 1: Abanoub Ashraf Ragae\n");
	printf("Input Data 2: 12/22 \n");
	printf("Input Data 3: 1234567891524789 \n");
	printf("Input Data 4: 23/12/2022 \n");
	printf("Input Data 5: 10000 \n");
	printf("Input Data 6: 8000 \n");
	
	printf("Please Enter Your Card Holder Name\n");
	cardError = getCardHolderName(&cardData);
	printf("Please Enter Your Card Expiry Date in Format MM/YY\n");
	cardError = getCardExpiryDate(&cardData);
	printf("Please Enter Your Primary Account Number\n");
	cardError = getCardPAN(&cardData);
	serverError = isValidAccount(&cardData);
	serverError = isBlockedAccount(&accountRefrence);
	printf("Please Enter The Current Date In Format DD/MM/YYYY\n");
	terminalError = getTransactionDate(&terminalData);
	terminalError = isCardExpired(&cardData, &terminalData);
	terminalError = setMaxAmount(&terminalData);
	terminalError = getTransactionAmount(&terminalData);
	terminalError = isBelowMaxAmount(&terminalData);
	serverError = isAmountAvailable(&terminalData);
	ST_transaction_t transactionData = {
		cardData,
		terminalData
	};
	printf("*********************************************\n");
	printf("Expected Result: \n");
	printf("Transaction Sequence Number: 2\n");
	printf("Cardholder Name: Abanoub Ashraf Ragae\n");
	printf("PAN: 1234567891524789\n");
	printf("Card Expiration Date: 12/22\n");
	printf("Amount: 8000.00\n");
	printf("Terminal Max Amount: 10000.00\n");
	printf("Transaction Date: 22/12/2022\n");
	printf("Transaction State: 0\n");
	printf("*********************************************\n");	
	printf("Actual Result: \n");
	transactionError = recieveTransactionData(&transactionData);
	serverError=saveTransaction(&transactionData);
	
	listSavedTransactions(&transactionData);

	
	printf("\n****************************************************************************************************\n");
}















