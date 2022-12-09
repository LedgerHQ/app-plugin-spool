import { processTest } from "../test.fixture";

const contractName = "Staking";
// https://etherscan.io/tx/0xb3fe653c9c64d85f92cae10643e1e17fb8428114148dc994997ccc8010610bf0
// https://etherscan.io/getRawTx?tx=0xb3fe653c9c64d85f92cae10643e1e17fb8428114148dc994997ccc8010610bf0
const rawTxHex =
  "0x02f890011a8459682f008503a986a1938303d13d94c3160c5cc63b6116dd182faa8393d3ad9313e21380a4d1e6044a0000000000000000000000000000000000000000000000000000000000000001c080a08522ca493235c3c87f0100492e7145abc72c757fd05f85a51013cff049c58fa5a05e219127017c691700f3faad281425084ec3fc9777a19398b01fab0c686519d8";
const testLabel = "compound"; // <= Name of the test
const testDirSuffix = "compound"; // <= directory to compare device snapshots to
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
