/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/*****************************************    Author:  Abanoub Ashraf    ***********************************************/
/*****************************************    Date:    24 OCT 2022       ***********************************************/
/*****************************************    Module:  Card              ***********************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "../Library/std_typs.h"
#include "../Card/card.h"
#include "terminal.h"


/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**************************          Function Name:        getTransactionDate       ************************************/
/**************************          Input Arguments:      Pointer To Struct        ************************************/
/**************************          Output Arguments:     Object From Enum			************************************/
/**************************         												************************************/
/********************         Function Description: This function asks for the             *****************************/
/********************							    transaction date and store it in 	   *****************************/
/********************		                        terminal data which is a pointer  	   *****************************/
/********************								to a structure has an array of		   *****************************/
/********************						        characters named (transactionDate)     *****************************/
/********************						        a temporary array made just to         *****************************/
/********************						        check if the user wrote the current    *****************************/
/********************						        date before saving,if the date is      *****************************/
/********************						        correct the temp array will be         *****************************/
/********************						        saved in the main array                *****************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	uint8_t day=tm.tm_mday;
	uint8_t mon=(tm.tm_mon + 1);
	int year=(tm.tm_year + 1900);
	// printf("D%d\n",day);
	// printf("D%d\n",mon);
	// printf("D%d\n",year);
	
	uint8_t aday[2]; 			//array holds the two digits of the current day
	uint8_t amon[2]; 			//array holds the two digits of the current month
	uint8_t ayear[4];			//array holds the four digits of the current month
	itoa (day,aday,10);   		//converting the intger values of the day to strings (ASCII) to save the it into array of characters 
	itoa (mon,amon,10);   		//converting the intger values of the month to strings (ASCII)to save the it into array of characters
	itoa (year,ayear,10);		//converting the intger values of the year to strings (ASCII) to save the it into array of characters
	
	//getting the transaction date from the user
	uint8_t i=0;
	uint8_t temptransactionDate[10];
	gets(temptransactionDate);
	uint8_t temptransactionDateLength = strlen(temptransactionDate);
	
	//checking the date format [DD/MM/YYYY] and comparing the input date from the user with the current date of transaction 
	//Every individule digit in the temptransactionDate[10] array should be equal to the current date that has been intialized in (aday[2],amon[2] and ayear[4]) arrays  
	if(temptransactionDateLength==10)
		{
			if (temptransactionDate[0]==aday[0]  && 
				temptransactionDate[1]==aday[1]  &&
				temptransactionDate[2]=='/'      && 
				temptransactionDate[3]==amon[0]  && 
				temptransactionDate[4]==amon[1]  &&
				temptransactionDate[5]=='/'      &&
				temptransactionDate[6]==ayear[0] && 
				temptransactionDate[7]==ayear[1] &&
				temptransactionDate[8]==ayear[2] && 
				temptransactionDate[9]==ayear[3] )
			{
				for (i=0;i<temptransactionDateLength;i++)
				{
					//saving the transaction date into the transactionDate[] array after making sure that the input date from the user is OK
					termData -> transactionDate[i] = temptransactionDate[i]; 
				}
				
				return TERMINAL_OK; 				 
			}
			else 
			{
				return WRONG_DATE;
			}
		}
	else 
	{
		return WRONG_DATE;
	}
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**************************          Function Name:        isCardExpired            ************************************/
/**************************          Input Arguments:      Two Pointers To Struct   ************************************/
/**************************          Output Arguments:     Object From Enum			************************************/
/**************************         												************************************/
/********************         Function Description: This function compares the card        *****************************/
/********************							    expiry date with the currennt     	   *****************************/
/********************		                        transaction date if the expiry date    *****************************/
/********************								befor the current the function will	   *****************************/
/********************						        return EXPIRED_CARD if not the card    *****************************/
/********************						        is ok to complete the transaction.     *****************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
EN_terminalError_t 	isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
	//saving the expiration date of the card in an two arrays month and year as ASCII values
	uint8_t MonthExpirationArr[2]={(cardData->cardExpirationDate[0]),(cardData->cardExpirationDate[1])} ;
	uint8_t YearExpirationArr[4]={'2','0',(cardData->cardExpirationDate[3]),(cardData->cardExpirationDate[4])};
	
	//intializing two variables of month and year to save the values of MonthExpirationArr and YearExpirationArr after converting them into integers
	uint8_t ExpirationMonth=0; 
	int ExpirationYear=0;
	
	//getting the current date 
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);	
	uint8_t CurrentMonth=(tm.tm_mon + 1);
	int Currentyear=(tm.tm_year + 1900);
	
	//converting MonthExpirationArr and YearExpirationArr to integers to easily compare between them 
	ExpirationMonth=atoi(MonthExpirationArr);	
	ExpirationYear=atoi(YearExpirationArr);
	
	//checking if the card is expired or not 
	if (ExpirationYear>=Currentyear)
	{
		if(ExpirationYear==Currentyear)
		{
			if(ExpirationMonth>=CurrentMonth)
			{
				return TERMINAL_OK;
			}
			else
			{
				return EXPIRED_CARD;
			}
		}
		else
		{
			return 	TERMINAL_OK; 
		}
	}
	else
	{
		return  EXPIRED_CARD;
	}	
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**************************          Function Name:        getTransactionAmount     ************************************/
/**************************          Input Arguments:      Pointer To Struct        ************************************/
/**************************          Output Arguments:     Object From Enum			************************************/
/**************************         												************************************/
/********************         Function Description: This function asks for the             *****************************/
/********************							    transaction amount needed and save 	   *****************************/
/********************		                        it into terminal data which is a   	   *****************************/
/********************								pointer to a structure has a 		   *****************************/
/********************						        variable named (transAmount)           *****************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
EN_terminalError_t 	getTransactionAmount(ST_terminalData_t *termData)
{
	//getting the transaction amount from the user
	printf("Please Enter The Transaction Amount:\n");
	scanf("%f", &termData->transAmount);	
	
	if ((termData->transAmount)<=0)
	{
		return INVALID_AMOUNT;
	}
	else 
	{
		return OK;
	}		
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**************************          Function Name:        setMaxAmount             ************************************/
/**************************          Input Arguments:      Pointer To Struct        ************************************/
/**************************          Output Arguments:     Object From Enum			************************************/
/**************************         												************************************/
/********************         Function Description: This function asks for the             *****************************/
/********************							    maximum amount per day and save 	   *****************************/
/********************		                        it into terminal data which is a   	   *****************************/
/********************								pointer to a structure has a 		   *****************************/
/********************						        variable named (maxTransAmount)        *****************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
EN_terminalError_t 	setMaxAmount(ST_terminalData_t *termData)
{
	//setting the maximum allowed amount
	printf("Please Enter The Transaction Maximum Allowed Amount:\n");
	scanf("%f", &termData->maxTransAmount);	
	
	if ((termData->maxTransAmount)<=0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else 
	{
		return OK;
	}		
	
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**************************          Function Name:        isBelowMaxAmount         ************************************/
/**************************          Input Arguments:      Pointer To Struct        ************************************/
/**************************          Output Arguments:     Object From Enum			************************************/
/**************************         												************************************/
/********************         Function Description: This function compares the             *****************************/
/********************							    transaction amount with the    	       *****************************/
/********************		                        terminal max allowed amount.  	       *****************************/
/********************								If the transaction amount is           *****************************/
/********************						        larger than the terminal max           *****************************/
/********************						        allowed amount will return             *****************************/
/********************						        EXCEED_MAX_AMOUNT, else it will        *****************************/
/********************						        return TERMINAL_OK.                    *****************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
EN_terminalError_t 	isBelowMaxAmount(ST_terminalData_t *termData)
{
	//checking if transaction amount is more than the allowed amount 
	if ((termData->maxTransAmount) > (termData->transAmount)) 
	{
		return OK;
	}
	else 
	{
		return EXCEED_MAX_AMOUNT;
	}
	
}


