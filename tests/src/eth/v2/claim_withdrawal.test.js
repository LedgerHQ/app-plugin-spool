import {processTest} from "../../test.fixture";

const contractName = "SmartVaultManager";
// https://etherscan.io/tx/0x2bb429b374c44915ddfed199758613168ca0338712f81ba558f9332b86f47fc4
// https://etherscan.io/getRawTx?tx=0x2bb429b374c44915ddfed199758613168ca0338712f81ba558f9332b86f47fc4
const rawTxHex =
    "0x02f9017201048405f5e1008503a3e92fd383083e4f945f63195445f9949ff2f88c48e3566e4dc156c5d780b90104f8a70486000000000000000000000000c6bfa21025636c1d116697fb3c815e1dc754b559000000000000000000000000000000000000000000000000000000000000008000000000000000000000000000000000000000000000000000000000000000c000000000000000000000000024f35b57e3e415adbf5a3733c3b4338aed4105a600000000000000000000000000000000000000000000000000000000000000018000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000f4240c001a0b54af042d44463079046384ab75d71097cfcbbaaded2664440e132f8305d16b1a05ac4ba3499b8a6cd76a34716f88eb8e331d341281b5f3ba69920c425bb6a3a54";
const testLabel = "V2 Claim Withdrawal"; // <= Name of the test
const testDirSuffix = "claim_withdrawal"; // <= directory to compare device snapshots to
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
