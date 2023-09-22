import {processTest} from "../../test.fixture";
const contractName = "Vault2";
// https://etherscan.io/tx/0x0035c09847152f5783a68d51f1ad1f1b611fb3befe4573fa1edcb33ba7849bee
// https://etherscan.io/getRawTx?tx=0x0035c09847152f5783a68d51f1ad1f1b611fb3befe4573fa1edcb33ba7849bee
const rawTxHex =
  "0x02f901d2012684773594008504e3b2920083066e369426ac1dba97c1f3f33eea9ad8b3e9d9dc588c023e80b90164084fd9b40000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000006000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000007000000000000000000000000a71a526c962d08206a44b560a4dd67e97bb5fbc0000000000000000000000000f24ebddfe5d73423dec966f14c1ec714f59a6656000000000000000000000000d72320a3dc67d9815a0348199be7ff98d7df3158000000000000000000000000ae0f58c408514e60cc6d844cc80965aeab4bf6ff0000000000000000000000009e177bb9f107bffdc0f9b512f969f6c071d57d76000000000000000000000000e78e22ab9204e36948eff81facd92a7231f40210000000000000000000000000767f653905b82fd88369b8f24bf9ff71e6ba2a7cc001a00375866e0640a2b0e8fd36bf858855db1927a306dfeb2271a0d6066b189c232aa030e1e701f5022e6eb0a75110b08796bb06f59122f8e42bac3a71c6a6f43c52c0";
const testLabel = "Claim from vault"; // <= Name of the test
const testDirPreffix = "v1";
const testDirSuffix = "claim_from_vault"; // <= directory to compare device snapshots to
const testNetwork = "ethereum";

const signedPlugin = false;

const devices = [
  {
    name: "nanos",
    label: "Nano S",
    steps: 4 // <= Define the number of steps for this test case and this device
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
