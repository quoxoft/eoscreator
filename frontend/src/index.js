import eos from 'eosjs'
import ecc from 'eosjs-ecc'

const CONTRACT_NAME = 'helloeos'
const LOCAL_TESTNET= 'http://127.0.0.1:8888'
const JUNGLE_TESTNET = 'http://dev.cryptolions.io:38888'
const MAINNET = 'http://mainnet.libertyblock.io:8888'

//Eos = require('eosjs')
window.genarateOwnerKey = function() {
    ecc.randomKey().then(privateKey => {
        console.log('Private Key:\t', privateKey) // wif
        console.log('Public Key:\t', ecc.privateToPublic(privateKey)) // EOSkey...
        document.getElementById("owner_prvkey").value = privateKey;
        document.getElementById("owner_pubkey").value = ecc.privateToPublic(privateKey);       
        })
}

window.genarateActiveKey = function() {
    ecc.randomKey().then(privateKey => {
        console.log('Private Key:\t', privateKey) // wif
        console.log('Public Key:\t', ecc.privateToPublic(privateKey)) // EOSkey...
        document.getElementById("active_prvkey").value = privateKey;
        document.getElementById("active_pubkey").value = ecc.privateToPublic(privateKey);       
        })
}

window.createAccount = function() {
    var owner_pubkey = document.getElementById('owner_pubkey').value;    
    var active_pubkey = document.getElementById('active_pubkey').value;
    var account_name = document.getElementById('eos_account').value;

    if((ecc.isValidPublic(owner_pubkey) === true)&&(ecc.isValidPublic(active_pubkey) === true)){
        $("#msg-success").html("Please transfer to <b> newaccount</b> at least <b> 2 EOS</b> with following <b>memo</b>, The smart contract will automatically create your account");
        document.getElementById("msg-memo").value = account_name + "-" + owner_pubkey+ "-" + active_pubkey;

    }else{
        $("#msg-warning").html("Please check, There are something wrong");
    }
}







  