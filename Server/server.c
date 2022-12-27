/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/*****************************************    Author:  Abanoub Ashraf    ***********************************************/
/*****************************************    Date:    24 OCT 2022       ***********************************************/
/*****************************************    Module:  Server            ***********************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include "../Library/std_typs.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"

uint32_t transIndex=0;
extern uint8_t Index;
/* Global Array to store users' info */
 ST_accountsDB_t accountsDB[MAX_TRANS_DATA]= {2000.0	  , 	RUNNING, 	"8989374615436851",
											  100000.0 	  , 	BLOCKED, 	"5807007076043875",
											  15000.5  	  , 	RUNNING, 	"1234567891524789",
											  5000.0   	  , 	BLOCKED,	"9876543210125987",
											  2000.6	  ,		RUNNING,	"5648972319786453",
											  25000.58 	  ,		RUNNING,	"3126459788529631",
											  50000.36 	  ,		RUNNING,	"9638527410147852",
											  7500.32  	  ,		RUNNING,	"0258741036978245",
											  8000.65  	  ,		RUNNING,	"9875321460123578",
											  45000.98 	  ,		BLOCKED,	"5208963014798561"};

/* Global Array to save the transactions */							 
 ST_transaction_t transactionDB[MAX_TRANS_DATA]={0};
 
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**************************          Function Name:        isValidAccount           ************************************/
/**************************          Input Arguments:      Pointer To Struct        ************************************/
/**************************          Output Arguments:     Object From Enum			************************************/
/**************************         												************************************/
/********************         Function Description: This function iterates on the          *****************************/
/********************							    accounts and checks if the PAN 	       *****************************/
/********************		                        exists in the data base array or not   *****************************/
/********************								by comparing the two arrays with each  *****************************/
/********************						        and saves the index of it for next     *****************************/
/********************						        operations                             *****************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
	uint8_t i;
	uint8_t flag=0;
	
	
	for (i = 0; i < 10 ; i++) 
		{
			/*searching for the entered PAN if it in the accounts DB array or not then raising a flag if it is found */
			if (strcmp((cardData->primaryAccountNumber),(accountsDB[i].primaryAccountNumber))==0) 
			{
				flag = 1;
				Index=i;
				

				break;
			}
			else 
			{
				
			}
		}
		
	//checking if the flag was raised (found the PAN in the accountDB array) or not 
	if (flag == 0) 
	{
		return ACCOUNT_NOT_FOUND;
	}
	else 
	{
		return SERVER_OK;
	}
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**************************          Function Name:        isBlockedAccount         ************************************/
/**************************          Input Arguments:      Pointer To Struct        ************************************/
/**************************          Output Arguments:     Object From Enum			************************************/
/**************************         												************************************/
/********************         Function Description: This function checks if the account    *****************************/
/********************							    is blocked in the accounts data base   *****************************/
/********************		                        array if the account is blocked the    *****************************/
/********************						        function will return blocked account   *****************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
	/*checking the account entered if it is blocked in the accounts DB array depending on its index that have been detected in the pervious function*/
	if (accountsDB[Index].state == RUNNING)
	{
		return SERVER_OK;
	}
	else
	{
		return BLOCKED_ACCOUNT;
	}

}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**************************          Function Name:        isAmountAvailable        ************************************/
/**************************          Input Arguments:      Pointer To Struct        ************************************/
/**************************          Output Arguments:     Object From Enum			************************************/
/**************************         												************************************/
/********************         Function Description: This function checks if the account    *****************************/
/********************							    balance with in the transaction amount *****************************/
/********************		                        range or not if the balance is less    *****************************/
/********************								than the transaction amount the        *****************************/
/********************						        function will return Low Balance       *****************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
	/*checking the current balance in the selected account index if it has enough balance to be deduct or not*/
	/*the index previously intialized in the first function (isValidAccount)*/
	if (accountsDB[Index].balance >= termData->transAmount)
	{
		return SERVER_OK;
	}
	else
	{
		return LOW_BALANCE;
	}
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**************************          Function Name:        saveTransaction          ************************************/
/**************************          Input Arguments:      Pointer To Struct        ************************************/
/**************************          Output Arguments:     Object From Enum			************************************/
/**************************         												************************************/
/********************         Function Description: This function saves every transaction  *****************************/
/********************							    including the transaction number       *****************************/
/********************		                        and the card holder name, the PAN,     *****************************/
/********************								the expiry date and the transaction    *****************************/
/********************						        amount and the transaction date also   *****************************/
/********************						        it stores the transaction state        *****************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{ 
	
	//saving data
	if(SERVER_CONNECTED==1)
	{
		(transData->transactionSequenceNumber) +=1; // intializing the transaction sequance number
		
		transIndex = (transData->transactionSequenceNumber)-1;
		
		//1- saving transaction sequance number
		(transactionDB[transIndex].transactionSequenceNumber) = (transData->transactionSequenceNumber);
		/*2- saving card holder data*/
		strcpy((transactionDB[transIndex].cardHolderData.cardHolderName), 		(transData -> cardHolderData.cardHolderName));
		strcpy((transactionDB[transIndex].cardHolderData.primaryAccountNumber),  (transData -> cardHolderData.primaryAccountNumber));
		strcpy((transactionDB[transIndex].cardHolderData.cardExpirationDate), 	(transData -> cardHolderData.cardExpirationDate));
		//3- saving terminal data
		(transactionDB[transIndex].terminalData.transAmount) = (transData -> terminalData.transAmount);
		(transactionDB[transIndex].terminalData.maxTransAmount)=  (transData -> terminalData.maxTransAmount);
		strcpy((transactionDB[transIndex].terminalData.transactionDate), (transData -> terminalData.transactionDate));
		(transactionDB[transIndex].transState) = (transData->transState) ;
	
	if ( (getTransaction(transactionDB[transIndex].transactionSequenceNumber, transactionDB) ) == SERVER_OK )
		{
			
			return SERVER_OK;
		}
	else 
		{
			return SAVING_FAILED;
		}		
		
	}
	
	else 
	{
		return SAVING_FAILED;
	}
	
}	

EN_serverError_t listSavedTransactions(ST_transaction_t *transData)
{
	printf("Transaction Sequence Number: %d",transactionDB[transIndex].transactionSequenceNumber);
	printf("\nCardholder Name: ");
	puts(transactionDB[transIndex].cardHolderData.cardHolderName);
	printf("PAN: ");
	puts(transactionDB[transIndex].cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date: ");
	puts(transactionDB[transIndex].cardHolderData.cardExpirationDate);
	printf("Transaction Amount: %.2f",transactionDB[transIndex].terminalData.transAmount);
	printf("\nTerminal Max Amount: %.2f",transactionDB[transIndex].terminalData.maxTransAmount);
	printf("\nTransaction Date: ");
	puts(transactionDB[transIndex].terminalData.transactionDate);
	printf("Transaction State: %d",transactionDB[transIndex].transState);
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**************************          Function Name:        getTransaction           ************************************/
/**************************          Input Arguments:  Pointer To Struct & variable ************************************/
/**************************          Output Arguments:     Object From Enum			************************************/
/**************************         												************************************/
/********************         Function Description: This function checks if transaction    *****************************/
/********************							    sequence number equal to the one       *****************************/
/********************		                        stored in the transaction data base    *****************************/
/********************								and returns server ok if the state is  *****************************/
/********************						        true                                   *****************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	for( int i=0 ; i < MAX_TRANS_DATA ; i++)
	{
		
		if ( (transactionDB[i].transactionSequenceNumber) == transactionSequenceNumber)
		{
			
			transData = &transactionDB[transactionSequenceNumber-1];
			return SERVER_OK;
		}
	}
	return TRANSACTION_NOT_FOUND;
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/**************************          Function Name:        recieveTransactionData   ************************************/
/**************************          Input Arguments:      Pointer To Struct        ************************************/
/**************************          Output Arguments:     Object From Enum			************************************/
/**************************         												************************************/
/********************         Function Description: This function will take all            *****************************/
/********************							    transaction data and validate its data *****************************/
/********************		                        it contains all server logic           *****************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND) 
	{
		transData->transState = DECLINED_STOLEN_CARD;
		
		return FRAUD_CARD;
	}
	
	else if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE) 
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		
		return DECLINED_INSUFFECIENT_FUND;
	}
	
	else if (accountsDB[Index].state== BLOCKED_ACCOUNT) 
	{
		return DECLINED_STOLEN_CARD;
	}
	
	else if ((saveTransaction(transData)) == SAVING_FAILED)
			{
				return INTERNAL_SERVER_ERROR;
			}
		
	else 
	{
		accountsDB[Index].balance -= transData->terminalData.transAmount;
		return APPROVED;
	}	
}
