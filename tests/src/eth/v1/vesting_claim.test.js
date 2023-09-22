import {processTest} from "../../test.fixture";

const contractName = "Vesting";
// https://etherscan.io/tx/0x28e132656cae4ff71ce4ec731834206a78aa34c08a3e8f82e8addccc76c2bf05
// https://etherscan.io/getRawTx?tx=0x28e132656cae4ff71ce4ec731834206a78aa34c08a3e8f82e8addccc76c2bf05
const rawTxHex =
  "0x02f870011684773594008504fd72d07583010e809408772c1872c997fec8da3c7f36c1fc28ebe72e9780844e71d92dc001a0c1c71ea53682c603ab5ea8b8ca3b567c7151b20ec6a499b6086fe0ef717f157da0588c7018483dba6433ecfcdb0acfda9d8adc0dbf655ae7ec0a6304600cc0b7d9";
const testLabel = "Vesting Claim"; // <= Name of the test
const testDirSuffix = "vesting_claim"; // <= directory to compare device snapshots to
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
