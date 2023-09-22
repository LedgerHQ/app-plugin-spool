import {processTest} from "../../test.fixture";

const contractName = "RewardManager";
// https://etherscan.io/tx/0xa1dc932acd35359aa8624ad83e3dda986bbd4d825e352ca3f9698bc2cbc9e621
// https://etherscan.io/getRawTx?tx=0xa1dc932acd35359aa8624ad83e3dda986bbd4d825e352ca3f9698bc2cbc9e621
const rawTxHex =
    "0x02f8f1011d84065615c38506900f68ac8301ffc094d8d2c1c3c7982272e3e12dec5af681433fdcf00380b884b02029e0000000000000000000000000fc47b365674b9e94ef890f8cd406fd6fe8f337d3000000000000000000000000dac17f958d2ee523a2206206994597c13d831ec70000000000000000000000000000000000000000000000000000000000a7d8c000000000000000000000000000000000000000000000000000000000650d9fc4c001a0b9fa721cbf312e586c5c5c3a00ccd423061fe11f75c69471f7df7da21309cb07a04bd4ca66d5d0ba45f6b1dd37b5e978ad423521b228227e4d761ee2bce54591c8";
const testLabel = "V2 Extend reward token"; // <= Name of the test
const testDirSuffix = "extend_reward_token"; // <= directory to compare device snapshots to
const testNetwork = "ethereum";
const testDirPreffix = "v2";
const signedPlugin = false;

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 15 // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanox",
        label: "Nano X",
        steps: 7 // <= Define the number of steps for this test case and this device
    }
];

devices.forEach((device) =>
  processTest(device, contractName, testLabel, testDirSuffix, testDirPreffix, rawTxHex, signedPlugin,"",testNetwork)
);
