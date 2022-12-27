#include <stdio.h>
#include "../Library/std_typs.h"
#include "../Card/card.h"
#include "terminal.h"
#include "test.h"




int main()
{
	getTransactionDateTest();
	isCardExpiredTest();
	getTransactionAmountTest();
	isBelowMaxAmountTest();
	setMaxAmountTest();
}

/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
void getTransactionDateTest(void)
{
	ST_terminalData_t terminalData;
	EN_terminalError_t terminalError;
	
	
	printf("**************************************************\n");
	printf("Tester Name: Abanoub Ashraf\n");
	printf("Function Name: getTransactionDateTest\n");
	printf("Test Case 1: Date is less than 10 characters\n");
	printf("Input Data: 23/12/202\n");
	terminalError = getTransactionDate(&terminalData);
	printf("Expected Result: Wrong Transaction Date\n");
	printf("Actual Result: ");
	if (terminalError == WRONG_DATE) 
	{
		printf("Wrong Transaction Date \n \n");
	}
	printf("**************************************************\n");
	printf("Test Case 2: Date is more than 10 characters\n");
	printf("Input Data: 23/12/20222\n");
	terminalError = getTransactionDate(&terminalData);
	printf("Expected Result: Wrong Transaction Date\n");
	printf("Actual Result: ");
	if (terminalError == WRONG_DATE) 
	{
		printf("Wrong Transaction Date \n \n");
	}
	printf("**************************************************\n");
	printf("Test Case 3: Date is in wrong format\n");
	printf("Input Data: 23-12-2022\n");
	terminalError = getTransactionDate(&terminalData);
	printf("Expected Result: Wrong Transaction Date\n");
	printf("Actual Result: ");
	if (terminalError == WRONG_DATE) 
	{
		printf("Wrong Transaction Date \n \n");
	}
	printf("**************************************************\n");
	printf("Test Case 4: Date is not the current date\n");
	printf("Input Data: 25/12/2022\n");
	terminalError = getTransactionDate(&terminalData);
	printf("Expected Result: Wrong Transaction Date\n");
	printf("Actual Result: ");
	if (terminalError == WRONG_DATE) 
	{
		printf("Wrong Transaction Date \n \n");
	}
	printf("**************************************************\n");
	printf("Test Case 5: Date is in correct format\n");
	printf("Input Data: 23/12/2022\n");
	terminalError = getTransactionDate(&terminalData);
	printf("Expected Result: Terminal Ok\n");
	printf("Actual Result: ");
	if (terminalError == TERMINAL_OK) 
	{
		printf("Terminal Ok \n \n");
	}
}
/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
void isCardExpiredTest(void)
{
	ST_cardData_t cardData;
	EN_cardError_t cardError;
	ST_terminalData_t terminalData;
	EN_terminalError_t terminalError;
	
	printf("**************************************************\n");
	printf("Tester Name: Abanoub Ashraf\n");
	printf("Function Name: isCardExpiredTest\n");
	printf("Test Case 1: Card is expired\n");
	printf("Input Data: (Expiry date) 10/22\n");
	printf("Input Data: (Transaction date) 23/12/2022\n");
	cardError = getCardExpiryDate(&cardData);
	terminalError = getTransactionDate(&terminalData);
	terminalError = isCardExpired(&cardData, &terminalData);
	printf("Expected Result: Declined Process (Expired Card)\n");
	printf("Actual Result: ");
	if (terminalError == EXPIRED_CARD) {
		printf("Declined Process (Expired Card)\n");
	}
	printf("**************************************************\n");
	printf("Test Case 2: Card is not expired\n");
	printf("Input Data: (Expiry date) 01/23\n");
	printf("Input Data: (Transaction date) 23/12/2022\n");
	cardError = getCardExpiryDate(&cardData);
	terminalError = getTransactionDate(&terminalData);
	terminalError = isCardExpired(&cardData, &terminalData);
	printf("Expected Result: Terminal Ok \n");
	printf("Actual Result: ");
	if (terminalError == TERMINAL_OK) {
		printf("Terminal Ok \n");
	}
		
}
/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
void getTransactionAmountTest(void)
{
	ST_terminalData_t terminalData;
	EN_terminalError_t terminalError;
	printf("**************************************************\n");
	printf("Tester Name: Abanoub Ashraf\n");
	printf("Function Name: getTransactionAmountTest\n");
	printf("Test Case 1: Transaction amount is zero\n");
	printf("Input Data: 0\n");
	terminalError = getTransactionAmount(&terminalData);
	printf("Expected Result: Invalid Amount\n");
	printf("Actual Result: ");
	if (terminalError == INVALID_AMOUNT) {
			printf("Invalid Amount\n");
		}
	printf("**************************************************\n");
	printf("Test Case 2: Transaction amount is bigger than zero\n");
	printf("Input Data: 5000\n");
	terminalError = getTransactionAmount(&terminalData);
	printf("Expected Result: Amount is ok\n");
	printf("Actual Result: ");
	if (terminalError == TERMINAL_OK) {
			printf("Amount is ok\n");
		}
			
}
/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
void isBelowMaxAmountTest(void)
{
	ST_terminalData_t terminalData;
	EN_terminalError_t terminalError;
	printf("**************************************************\n");
	printf("Tester Name: Abanoub Ashraf\n");
	printf("Function Name: isBelowMaxAmountTest\n");
	printf("Test Case 1: Transaction amount is larger than the maximum allowed amount\n");
	printf("Input Data: 5000 (Maximum Allowed Amount)\n");
	printf("Input Data: 7000 (Transaction Amount)\n");
	terminalError = setMaxAmount(&terminalData);
	terminalError = getTransactionAmount(&terminalData);
	terminalError = isBelowMaxAmount(&terminalData);
	printf("Expected Result: Declined Process (Amount Exceeding Limit)\n");
	printf("Actual Result: ");
	if (terminalError == EXCEED_MAX_AMOUNT) 
	{
		printf("Declined Process (Amount Exceeding Limit)\n");
	}
	printf("**************************************************\n");
	printf("Test Case 2: Transaction amount is smaller than the maximum allowed amount\n");
	printf("Input Data: 5000 (Maximum Allowed Amount)\n");
	printf("Input Data: 4000 (Transaction Amount)\n");
	terminalError = setMaxAmount(&terminalData);
	terminalError = getTransactionAmount(&terminalData);
	terminalError = isBelowMaxAmount(&terminalData);
	printf("Expected Result: Amount is ok\n");
	printf("Actual Result: ");
	if (terminalError == TERMINAL_OK) 
	{
		printf("Amount is ok\n");
	}
	
}

/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
void setMaxAmountTest(void)
{
	ST_terminalData_t terminalData;
	EN_terminalError_t terminalError;
	printf("**************************************************\n");
	printf("Tester Name: Abanoub Ashraf\n");
	printf("Function Name: setMaxAmountTest\n");
	printf("Test Case 1: Maximum amount is zero\n");
	printf("Input Data: 0\n");
	terminalError = setMaxAmount(&terminalData);
	printf("Expected Result: Invalid Amount\n");
	printf("Actual Result: ");
	if (terminalError == INVALID_MAX_AMOUNT) 
	{
	printf("Invalid Maximum Amount\n");
	}
	printf("**************************************************\n");
	printf("Test Case 2: Maximum amount is bigger than zero\n");
	printf("Input Data: 8000\n");
	terminalError = setMaxAmount(&terminalData);
	printf("Expected Result: Max amount is ok\n");
	printf("Actual Result: ");
	if (terminalError == OK) 
	{
			printf("Max amount is ok\n");
	}
}










