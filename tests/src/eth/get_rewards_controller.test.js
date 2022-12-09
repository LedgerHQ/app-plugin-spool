import { processTest } from "../test.fixture";

const contractName = "Controller";
// https://etherscan.io/tx/0xe2f0f29c2904f00c63bedd7d151ad87cebcedae55f1a4039d4d8e0ea23270e84
// https://etherscan.io/getRawTx?tx=0xe2f0f29c2904f00c63bedd7d151ad87cebcedae55f1a4039d4d8e0ea23270e84
const rawTxHex =
  "0x02f8d30182010d8459682f00850306dc420083026b0e94dd4051c3571c143b989c3227e8eb50983974835c80b864510ccb4300000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000001000000000000000000000000cf4cf54f1f9fc1a88c1b4d85d4eee5cdd8ed254bc080a0a5c298da381368fb1a2ca2f3f8ed279b78c756c8ebcc05251ee5e0900676c44da0322840b43249e0a50946169c94046e9879c3a7f788f834158d405436a705b383";
const testLabel = "Get rewards from controller"; // <= Name of the test
const testDirSuffix = "get_rewards_from_controller"; // <= directory to compare device snapshots to
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
