import Eos from 'eosjs'
import ecc from 'eosjs-ecc'

const CONTRACT_NAME = 'newaccount'
const SYSTEM_CONTRACT_NAME = 'eosio'
const LOCAL_TESTNET = 'http://127.0.0.1:8888'
const JUNGLE_TESTNET = 'http://dev.cryptolions.io:38888'
const MAINNET = 'http://mainnet.libertyblock.io:8888'
var ramKBPrice = 0;

getRamKBPrice()

function getEos() {
    var privateKey = document.getElementById('transfer_key').value;
    var config = {
        keyProvider: [privateKey],
        httpEndpoint: JUNGLE_TESTNET,
        broadcast: true,
        sign: true,
        chainId: '038f4b0fc8ff18a4f0842a8f0564611f6e96e8535901dd45e43ac8691a1c4dca',
        expireInSeconds: 60
    }
    return Eos(config);
}

window.genarateOwnerKey = function () {
    ecc.randomKey().then(privateKey => {
        console.log('Private Key:\t', privateKey) // wif
        console.log('Public Key:\t', ecc.privateToPublic(privateKey)) // EOSkey...
        document.getElementById("owner_prvkey").value = privateKey;
        document.getElementById("owner_pubkey").value = ecc.privateToPublic(privateKey);
    })
}

window.genarateActiveKey = function () {
    ecc.randomKey().then(privateKey => {
        console.log('Private Key:\t', privateKey) // wif
        console.log('Public Key:\t', ecc.privateToPublic(privateKey)) // EOSkey...
        document.getElementById("active_prvkey").value = privateKey;
        document.getElementById("active_pubkey").value = ecc.privateToPublic(privateKey);
    })
}

window.createAccount = function () {
    var owner_pubkey = document.getElementById('owner_pubkey').value;
    var active_pubkey = document.getElementById('active_pubkey').value;
    var account_name = document.getElementById('eos_account').value;

    if (ecc.isValidPublic(owner_pubkey) && ecc.isValidPublic(active_pubkey) && (account_name.length == 12)) {
        console.log(getCreatingAccountPrice())
        $("#msg-success").html("Please transfer to <b> newaccount</b> at least <b>" + getCreatingAccountPrice() + " EOS</b> with following <b>memo</b>, The smart contract will automatically create your account");
        document.getElementById("msg-memo").value = account_name + "-" + owner_pubkey + "-" + active_pubkey;
    } else if (account_name.length != 12) {
        $("#msg-warning").html("Please check your account name");
    } else {
        $("#msg-warning").html("Please check the key pair");
    }
}

window.transfer = function () {
    var transfer_from = document.getElementById('transfer_from').value;
    var transfer_key = document.getElementById('transfer_key').value;
    //var transfer_to = document.getElementById('transfer_to').value;
    var transfer_amount = document.getElementById('transfer_amount').value;
    var transfer_amount_eos = transfer_amount + " EOS";
    console.log(transfer_amount_eos)
    var transfer_memo = document.getElementById('transfer_memo').value;

    var eos = getEos();

    eos.transfer(transfer_from, CONTRACT_NAME, transfer_amount_eos, transfer_memo, (error, result) => {console.log(error, result)})
}

function getCreatingAccountPrice() {
    var netPrice = 0.1; // 0.1 EOS
    var cpuPrice = 0.1; // 0.1 EOS
    // to make sure we add more than 10%, the remain value will be added to your account
    return (ramKBPrice * 4 + netPrice + cpuPrice) * 1.1;
}

function getRamKBPrice() {
    var eos = getEos();
    var params = {
        json: true,
        scope: SYSTEM_CONTRACT_NAME,
        code: SYSTEM_CONTRACT_NAME,
        table: "rammarket",
    }

    eos.getTableRows(params).then(resp => {
        var ramBaseBalance = resp.rows[0].base.balance; // Amount of RAM bytes in use
        ramBaseBalance = ramBaseBalance.substr(0, ramBaseBalance.indexOf(' '));
        var ramQuoteBalance = resp.rows[0].quote.balance; // Amount of EOS in the RAM collector
        ramQuoteBalance = ramQuoteBalance.substr(0, ramQuoteBalance.indexOf(' '));
        ramKBPrice = (ramQuoteBalance / ramBaseBalance).toFixed(8) * 1024; // Price in kb
    });

    return ramKBPrice;
}






