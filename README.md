# payment-application
a simple payment application that's very versatile and works in multiple scenarios.

offers you three main files :
1) bank accounts (CARD HOLDER NAME      |PRIMARY ACCOUNT NUMBER  |EXPIRATION DATE)
2) balance (PRIMARY ACCOUNT NUMBER  |BALANCE)
3) transaction data (CARD HOLDER NUMBER|PRIMARY ACCOUNT NUMBER  |EXPIRATION DATE  |maximum ammount  |transaction ammount  |transaction date  |transaction state |sequence number)

PS. you can can append on the existing files or you can delete them and the the program will automatically recreate them without all the previous data and ready to use...

you can link to it any payment transaction made and it withdraw the payment from the balance of the account given if it was registered in th data...
after completing the transaction , a sequence number will be given in case you want any details from that transaction later as it will be saved with that sequence number in the transaction data file 

you will have four modes for the application:

1) payment withdrawl 
2) get transaction
3) block card
4) add an account

-payment withdrawl mode will ask you about :

card holder name-------primary account number-------card expiry datetransaction date-------payment transaction amount-----

after filling those with valid inputs , transaction will be saved in transaction data file and balance will be decremented in the balance file 


please consider these rule :

                -card holder name must be 20-24 characters long
                -card expiry date must follow this format ---> mm/yy     ex. 02/25
                -card PAN must follow the luhn number algorithm and be 16-20 characters long
                -transaction Date must follow this format ----> dd/mm/yyyy    ex.17/09/2022

other modes :

        -if you want to block the card :
                                        1- write 'block' when asked for the card holder name
                                        2- fill in the card data
                                        3-fill valid any transaction amount and the card will be blocked


        -if you want to get a certain transaction by the sequence number :
                                        1- write 'get transaction' when asked for the card holder name
                                        2- write the sequence number of your transaction 


        -if you want to add an account  :
                                        1- write 'add account' when asked for the card holder name
                                        2- write the card expiry date,PAN number and balance
                                        
              

![payment-flowchart](https://user-images.githubusercontent.com/111197951/191336951-5a52e5f2-6aec-4e48-b9c6-b949a24dc883.jpg)
