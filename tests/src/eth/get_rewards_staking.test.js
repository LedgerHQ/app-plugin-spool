import { processTest } from "../test.fixture";

const contractName = "Staking";
// https://etherscan.io/tx/0xe6f5dc598e031818dec7d411678fde08ccff6eea4b5267c514c907c9226d27d8
// https://etherscan.io/getRawTx?tx=0xe6f5dc598e031818dec7d411678fde08ccff6eea4b5267c514c907c9226d27d8
const rawTxHex =
  "0x02f8f001348459682f0085039f44920b83035b0794c3160c5cc63b6116dd182faa8393d3ad9313e21380b884f4de10ac00000000000000000000000000000000000000000000000000000000000000400000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000100000000000000000000000040803cea2b2a32bda1be61d3604af6a814e70976c001a07cfe6fe8d705fea190e867019ec1503e1766ff98630a330e5d9594ea6ad259439f6f9184117d0f0074c8f0e3defff4a112a392cfdfdca20e27793038c7aa74b6";
const testLabel = "Get rewards staking"; // <= Name of the test
const testDirSuffix = "get_rewards_staking"; // <= directory to compare device snapshots to
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
