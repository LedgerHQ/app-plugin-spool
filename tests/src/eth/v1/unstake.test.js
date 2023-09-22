import {processTest} from "../../test.fixture";

const contractName = "Stake";
// https://etherscan.io/tx/0x0fd1e1d587884d61a129073685ed3f38946dff0b71e40aae44717d5d22ebf8d6
// https://etherscan.io/getRawTx?tx=0x0fd1e1d587884d61a129073685ed3f38946dff0b71e40aae44717d5d22ebf8d6
const rawTxHex =
  "0x02f89001068459682f00850354de94918302e39f94c3160c5cc63b6116dd182faa8393d3ad9313e21380a42e17de7800000000000000000000000000000000000000000000390bc5035c033f400000c001a085b4761f1190b7684742c4ae0ceaefe5c9d3de4688f7f25e1abb825866e2acf2a0480ba6eea5f2b335abd8cb73392a25a63bea009268399ebae496449948b29a32";
const testLabel = "unstake"; // <= Name of the test
const testDirSuffix = "unstake"; // <= directory to compare device snapshots to
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
