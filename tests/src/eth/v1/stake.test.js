import {processTest} from "../../test.fixture";

const contractName = "Stake";
// https://etherscan.io/tx/0x6d4bc0121319a620e6ca9a9fe54338a48a7f0830dbeee84d71ea9d8322c24208
// https://etherscan.io/getRawTx?tx=0x6d4bc0121319a620e6ca9a9fe54338a48a7f0830dbeee84d71ea9d8322c24208
const rawTxHex =
  "0x02f89001118459682f0085046f5cc20d83033d4894c3160c5cc63b6116dd182faa8393d3ad9313e21380a4a694fc3a000000000000000000000000000000000000000000000049134209fd6a900000c080a0f2e8d2593b6187844aa7441d36df749c667d6e50dc3ff406c9517257dc8dea5ca0644933bb35638d3190718e9608f7dae9e461bda1ee97c10092600765da402a5f";
const testLabel = "stake"; // <= Name of the test
const testDirSuffix = "stake"; // <= directory to compare device snapshots to
const testNetwork = "ethereum";
const testDirPreffix = "v1";
const signedPlugin = false;

const devices = [
  {
    name: "nanos",
    label: "Nano S",
    steps: 6 // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanox",
    label: "Nano X",
    steps: 4 // <= Define the number of steps for this test case and this device
  }
];

devices.forEach((device) =>
  processTest(device, contractName, testLabel, testDirSuffix, testDirPreffix, rawTxHex, signedPlugin,"",testNetwork)
);
