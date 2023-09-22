import {processTest} from "../../test.fixture";
const contractName = "Vault2";
// https://etherscan.io/tx/0xcbe52a909176f5f6c5d8ef78fdc10b6d573ce99743a1a9dfe3b357350abe26e7
// https://etherscan.io/getRawTx?tx=0xcbe52a909176f5f6c5d8ef78fdc10b6d573ce99743a1a9dfe3b357350abe26e7
const rawTxHex =
  "0x02f8d3018201138459682f00850bd9f1dcde8302be649426ac1dba97c1f3f33eea9ad8b3e9d9dc588c023e80b86473c2ad9c00000000000000000000000040803cea2b2a32bda1be61d3604af6a814e709760000000000000000000000000000000000000000000000000000000000278d0000000000000000000000000000000000000000000000221eb355e8fce6994a90c001a0971a809c13a8395a5103fb8501d7a453e65986c0ff8ad3775eec5b1355fe9f75a03a82b95d8378856004d48c7b369270cf827be81a9d2eaeb8ace6716ad5742fa2";
const testLabel = "Add reward token"; // <= Name of the test
const testDirPreffix = "v1";
const testDirSuffix = "add_token"; // <= directory to compare device snapshots to
const testNetwork = "ethereum";

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
  processTest(device, contractName, testLabel, testDirSuffix, testDirPreffix, testDirPreffix, rawTxHex, signedPlugin,"",testNetwork)
);
