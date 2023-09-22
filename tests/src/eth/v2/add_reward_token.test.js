import {processTest} from "../../test.fixture";

const contractName = "RewardManager";
// https://etherscan.io/tx/0x41afdd991088b031bd2597aabf57c3edf5fad53f89c2d8e5172403718b34f84a
// https://etherscan.io/getRawTx?tx=0x41afdd991088b031bd2597aabf57c3edf5fad53f89c2d8e5172403718b34f84a
const rawTxHex =
    "0x02f8f1011c8402faf08085036b9388828302f31194d8d2c1c3c7982272e3e12dec5af681433fdcf00380b8842aba2aeb000000000000000000000000fc47b365674b9e94ef890f8cd406fd6fe8f337d3000000000000000000000000dac17f958d2ee523a2206206994597c13d831ec700000000000000000000000000000000000000000000000000000000650c4e4400000000000000000000000000000000000000000000000000000000000f4240c080a06a90c40cd9086170da2653a6479113fd288046df4f6d1b6f3942fb3e8c8146b8a07df2ec7a0861a1876fcb892ba0ea9947fb9b4c8f3d4a1a5efa06d19bf255e71a";
const testLabel = "V2 Add reward token"; // <= Name of the test
const testDirSuffix = "add_reward_token"; // <= directory to compare device snapshots to
const testNetwork = "ethereum";
const testDirPreffix = "v2";
const signedPlugin = false;

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 15 // <= Define the number of steps for this test case and this device
    },
    {
        name: "nanox",
        label: "Nano X",
        steps: 7 // <= Define the number of steps for this test case and this device
    }
];

devices.forEach((device) =>
  processTest(device, contractName, testLabel, testDirSuffix, testDirPreffix, rawTxHex, signedPlugin,"",testNetwork)
);
