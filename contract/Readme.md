New account smart contract on EOS
-------
#### Prerequisites
* Wallet must be unlock and have at least the following private keys



##### Create newaccount account
````bash

````

##### Cset contract
````bash
cleos set contract newaccount ./new_account -p newaccount
````

##### Make a transaction with memo follow rule: AccountName-OwnerPubKey-AcvitePubKey
````bash
$ cleos transfer helloeos newaccount "2 EOS" "helloeos1234-EOS68sM3gfTtxjBawvCBDnCxWgG1EN1jEGcqCD2H7mRJDJkmamu7R-EOS4zf7TVoYbsxFXpSc1J9HPkMn1r86jjpEVg6BnKL9SUMeJ7ThSt" -p helloeos
````

##### Get result
$ cleos get account helloeos1234

````bash
permissions: 
     owner     1:    1 EOS4zf7TVoYbsxFXpSc1J9HPkMn1r86jjpEVg6BnKL9SUMeJ7ThSt
        active     1:    1 EOS68sM3gfTtxjBawvCBDnCxWgG1EN1jEGcqCD2H7mRJDJkmamu7R
memory: 
     quota:     4.227 KiB    used:     3.365 KiB  

net bandwidth: 
     staked:          0.1000 EOS           (total stake delegated from account to self)
     delegated:       0.0000 EOS           (total staked delegated to account from others)
     used:                 0 bytes
     available:        19.23 KiB  
     limit:            19.23 KiB  

cpu bandwidth:
     staked:          0.1000 EOS           (total stake delegated from account to self)
     delegated:       0.0000 EOS           (total staked delegated to account from others)
     used:                 0 us   
     available:        3.752 ms   
     limit:            3.752 ms   

EOS balances: 
     liquid:            0.9967 EOS
     staked:            0.2000 EOS
     unstaking:         0.0000 EOS
     total:             1.1967 EOS

producers:     <not voted>
````

