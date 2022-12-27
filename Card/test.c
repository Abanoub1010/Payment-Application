#include <stdio.h>
#include "../Library/std_typs.h"
#include "card.h"
#include "test.h"




int main ()
	{
		getCardHolderNameTest();
		getCardExpiryDateTest ();
		getCardPANTest ();
	}
		
/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
void getCardHolderNameTest(void)
{
	ST_cardData_t cardData;
	EN_cardError_t cardError;
		
	printf("**************************************************\n");
	printf("Tester Name: Abanoub Ashraf\n");
	printf("Function Name: getCardHolderName\n");
	printf("Test Case 1: Name is less than 20 letter\n");
	printf("Input Data: Abanoub\n");
	cardError = getCardHolderName(&cardData);
	printf("Expected Result: Wrong Card Name\n");
	printf("Actual Result: ");
	if (cardError == WRONG_NAME) 
		{
			printf("Wrong Card Name \n \n");
		}
		
	printf("**************************************************\n");
	printf("Test Case 2: Name is more than 24 letter\n");
	printf("Input Data: Abanoub Ashraf Ragaee Neguib\n");
	cardError = getCardHolderName(&cardData);
	printf("Expected Result: Wrong Card Name \n");
	printf("Actual Result: ");
	if (cardError == WRONG_NAME) 
		{
			printf("Wrong Card Name \n \n");
		}
		
	printf("**************************************************\n");
	printf("Test Case 3: Name is not letters (special characters and numbers\n");
	printf("Input Data: Ab123 #$%^af 4589ee\n");
	cardError = getCardHolderName(&cardData);
	printf("Expected Result: Wrong Card Name \n");
	printf("Actual Result: ");
	if (cardError == WRONG_NAME) 
		{
			printf("Wrong Card Name \n \n");
		}
		
	printf("**************************************************\n");
	printf("Test Case 4: : Name is between 20 and 24 letter\n");
	printf("Input Data: Abanoub Ashraf Ragaee\n");
	cardError = getCardHolderName(&cardData);
	printf("Expected Result: Card OK\n");
	printf("Actual Result: ");
	if (cardError == OK) 
		{
			printf("Card OK \n \n");
		}
}

/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
void getCardExpiryDateTest (void)
{
	ST_cardData_t cardData;
	EN_cardError_t cardError;
	printf("**************************************************\n");
	printf("Tester Name: Abanoub Ashraf\n");
	printf("Function Name: getCardExpiryDateTest\n");
	printf("Test Case 1: Date in a wrong format\n");
	printf("Input Data: 12-22\n");
	cardError = getCardExpiryDate(&cardData);
	printf("Expected Result: Wrong Expiration Date\n");
	printf("Actual Result: ");
	if (cardError == WRONG_EXP_DATE) {
			printf("Wrong Expiration Date \n");
		}
	printf("**************************************************\n");
	printf("Test Case 2: Date in a wrong format\n");
	printf("Input Data: 20/12/2022\n");
	cardError = getCardExpiryDate(&cardData);
	printf("Expected Result: Wrong Expiration Date\n");
	printf("Actual Result: ");
	if (cardError == WRONG_EXP_DATE) 
		{
			printf("Wrong Expiration Date\n \n");
		}	
	printf("**************************************************\n");
	printf("Test Case 3: Wrong month and year number\n");
	printf("Input Data: 20/23\n");
	cardError = getCardExpiryDate(&cardData);
	printf("Expected Result: Wrong Expiration Date \n");
	printf("Actual Result: ");
	if (cardError == WRONG_EXP_DATE) {
			printf("Wrong Expiration Date \n");
		}
		
	printf("**************************************************\n");
	printf("Test Case 4: correct format, month and year numbers \n");
	printf("Input Data: 12/22\n");
	cardError = getCardExpiryDate(&cardData);
	printf("Expected Result: Card OK \n");
	printf("Actual Result: ");
	if (cardError == OK) 
		{
			printf("Card OK \n \n");
		}
		
}
/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
void getCardPANTest (void)
{
	ST_cardData_t cardData;
	EN_cardError_t cardError;
	printf("**************************************************\n");
	printf("Tester Name: Abanoub Ashraf\n");
	printf("Function Name: getCardPANTest\n");
	printf("Test Case 1: PAN is less than 16 characters \n");
	printf("Input Data: 123458\n");
	cardError = getCardPAN(&cardData);
	printf("Expected Result: Wrong Primary Account Number \n");
	printf("Actual Result: ");
	if (cardError == WRONG_PAN) {
			printf("Wrong Primary Account Number \n \n");
		}
	printf("**************************************************\n");
	printf("Test Case 2: PAN is more than 20 characters \n");
	printf("Input Data: 253698741258963254789632 \n");
	cardError = getCardPAN(&cardData);
	printf("Expected Result: Wrong Primary Account Number\n");
	printf("Actual Result: ");
	if (cardError == WRONG_PAN) {
			printf("Wrong Primary Account Number \n \n");
		}
	printf("**************************************************\n");
	printf("Test Case 3: PAN has special characters \n");
	printf("Input Data: 25369874*&1852364 \n");
	cardError = getCardPAN(&cardData);
	printf("Expected Result: Wrong Primary Account Number\n");
	printf("Actual Result: ");
	if (cardError == WRONG_PAN) {
			printf("Wrong Primary Account Number \n \n");
		}
	printf("**************************************************\n");
	printf("Test Case 4: PAN is between 16 and 20 characters \n");
	printf("Input Data: 253698741852364798 \n");
	cardError = getCardPAN(&cardData);
	printf("Expected Result: Card Ok\n");
	printf("Actual Result: ");
	if (cardError == OK) {
			printf("Card Ok \n \n");
		}
}