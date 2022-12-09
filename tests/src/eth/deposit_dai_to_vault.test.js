import { processTest } from "../test.fixture";

const contractName = "Vault2";
//https://etherscan.io/tx/0x59b345c4657447c7e6eb9290e2f4be2144e2a37577612b0cdf86b76d865cc051
//https://etherscan.io/getRawTx?tx=0x59b345c4657447c7e6eb9290e2f4be2144e2a37577612b0cdf86b76d865cc051
const rawTxHex =
  "0x02f901d30181d184ee6b28008512a05f2000830a61a39426ac1dba97c1f3f33eea9ad8b3e9d9dc588c023e80b901648ab936b800000000000000000000000000000000000000000000000000000000000000600000000000000000000000000000000000000000000000200d6ba6a458e1632800000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000007000000000000000000000000a71a526c962d08206a44b560a4dd67e97bb5fbc0000000000000000000000000f24ebddfe5d73423dec966f14c1ec714f59a6656000000000000000000000000d72320a3dc67d9815a0348199be7ff98d7df3158000000000000000000000000ae0f58c408514e60cc6d844cc80965aeab4bf6ff0000000000000000000000009e177bb9f107bffdc0f9b512f969f6c071d57d76000000000000000000000000e78e22ab9204e36948eff81facd92a7231f40210000000000000000000000000767f653905b82fd88369b8f24bf9ff71e6ba2a7cc001a0637a752c9e302b3d8c26096000fd01f3334b1494f06182149ec3167b91038a4ea02bd7dc40b2d31a594a8ef5a434fb6c1f68c54bcd24c823bf7c92bd0d3752f95e";
const testLabel = "Deposit DAI to vault"; // <= Name of the test
const testDirSuffix = "deposit_DAI_to_vault"; // <= directory to compare device snapshots to
const testNetwork = "ethereum";

const signedPlugin = false;

const devices = [
  {
    name: "nanos",
    label: "Nano S",
    steps: 7 // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanox",
    label: "Nano X",
    steps: 5 // <= Define the number of steps for this test case and this device
  }
];

devices.forEach((device) =>
  processTest(device, contractName, testLabel, testDirSuffix, rawTxHex, signedPlugin,"",testNetwork)
);
