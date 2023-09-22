import {processTest} from "../../test.fixture";

const contractName = "SmartVaultManager";
// https://etherscan.io/tx/0x86c4020d4a42a80aee2c5bbcda14b5f6d686170987b608a08c7a94c91cfbbe36
// https://etherscan.io/getRawTx?tx=0x86c4020d4a42a80aee2c5bbcda14b5f6d686170987b608a08c7a94c91cfbbe36
const rawTxHex =
    "0x02f901720106843b9aca008505153e8d81830b6abe945f63195445f9949ff2f88c48e3566e4dc156c5d780b90104fa15b91b00000000000000000000000000000000000000000000000000000000000000200000000000000000000000004125416d7cb507b438d1071e89703bc14558a91300000000000000000000000000000000000000000000000000000000000000a00000000000000000000000007da988a04516c2256b17c716b652accc6f45ceee0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000989680c080a06393389e4a2215ff546626299d84b35bbb7e93f94d4466f04fc2334fd13384bba04456699aa1dfa76ea56c81c692f0f650b4d0872391eda3d256465bc2139abfb4";
const testLabel = "V2 Claim Withdrawal"; // <= Name of the test
const testDirSuffix = "deposit"; // <= directory to compare device snapshots to
const testNetwork = "ethereum";
const testDirPreffix = "v2";
const signedPlugin = false;

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 11 // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanox",
        label: "Nano X",
        steps: 5 // <= Define the number of steps for this test case and this device
    }
];

devices.forEach((device) =>
  processTest(device, contractName, testLabel, testDirSuffix, testDirPreffix, rawTxHex, signedPlugin,"",testNetwork)
);
