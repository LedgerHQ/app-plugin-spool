import { processTest } from "../test.fixture";

const contractName = "Vault2";
// https://etherscan.io/tx/0xdce9beaf43948d9540c8cfe1a70530b9753d0b46ca857be66605b66d9545c9ba
// https://etherscan.io/getRawTx?tx=0xdce9beaf43948d9540c8cfe1a70530b9753d0b46ca857be66605b66d9545c9ba
const rawTxHex =
  "0x02f901d20122847735940085046c7cfe0083078fae9426ac1dba97c1f3f33eea9ad8b3e9d9dc588c023e80b90164fd3c11a800000000000000000000000000000000000000000000000000000000000000600000000000000000000000000000000000000000033fde122d3e8a96a4bac31600000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000007000000000000000000000000a71a526c962d08206a44b560a4dd67e97bb5fbc0000000000000000000000000f24ebddfe5d73423dec966f14c1ec714f59a6656000000000000000000000000d72320a3dc67d9815a0348199be7ff98d7df3158000000000000000000000000ae0f58c408514e60cc6d844cc80965aeab4bf6ff0000000000000000000000009e177bb9f107bffdc0f9b512f969f6c071d57d76000000000000000000000000e78e22ab9204e36948eff81facd92a7231f40210000000000000000000000000767f653905b82fd88369b8f24bf9ff71e6ba2a7cc001a01ba36d31100f75dde1632a3397e6674b47817a0a8c8c17922875a26221c1c4fca06bd7ca16d939abab07338fc8c727251e511a79a6ef63dcbe94c11e25423fd8e8";
const testLabel = "Withdraw from vault"; // <= Name of the test
const testDirSuffix = "withdraw_from_vault"; // <= directory to compare device snapshots to
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
  processTest(device, contractName, testLabel, testDirSuffix, rawTxHex, signedPlugin,"",testNetwork)
);
