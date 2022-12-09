import { processTest } from "../test.fixture";

const contractName = "Vault2";
// https://etherscan.io/tx/0xc79aa181ec03d0bf366aac016fdb031ea2654f59df4862468ce8dfe177f65d65
// https://etherscan.io/getRawTx?tx=0xc79aa181ec03d0bf366aac016fdb031ea2654f59df4862468ce8dfe177f65d65
const rawTxHex =
  "0x02f8d1017e845e3c25408502df7f1c258301cf669426ac1dba97c1f3f33eea9ad8b3e9d9dc588c023e80b864510ccb430000000000000000000000000000000000000000000000000000000000000020000000000000000000000000000000000000000000000000000000000000000100000000000000000000000040803cea2b2a32bda1be61d3604af6a814e70976c080a095fac5c77babea3566eec1029a37d9ccd622b75c4fba7303817c5f5bdae702b0a004de3120959bd04b01d9b38cbdc4c0bc7ff4ae0c6c82f10993cc0c9af01b26c1";
const testLabel = "Get rewards"; // <= Name of the test
const testDirSuffix = "get_rewards"; // <= directory to compare device snapshots to
const testNetwork = "ethereum";

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
  processTest(device, contractName, testLabel, testDirSuffix, rawTxHex, signedPlugin,"",testNetwork)
);
