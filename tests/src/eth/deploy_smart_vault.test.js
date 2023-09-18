// import { processTest } from "../test.fixture";
//
// const contractName = "SmartVaultFactory";
// // https://etherscan.io/tx/0x135154565300be4c409ba51eb15f4b3738ecf2003342f2f8c7b4e28892e0fca2
// // https://etherscan.io/getRawTx?tx=0x135154565300be4c409ba51eb15f4b3738ecf2003342f2f8c7b4e28892e0fca2
// const rawTxHex =
//     "0x02f90452010b8405f5e1008502ff1bb89e830ff954948049fc710d4a1deea6a6bcef772c166ced7a82f580b903e46fc3f5d500000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000220000000000000000000000000000000000000000000000000000000000000026000000000000000000000000000000000000000000000000000000000000002a0000000000000000000000000000000000000000000000000000000000000000400000000000000000000000000000000000000000000000000000000000002c00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000a000000000000000000000000c216ad6280f4fa92a5159ef383a1206d432481c80000000000000000000000007dbadf3cc5c9c7177b6f976910ef84ad90e018a800000000000000000000000000000000000000000000000000000000000003400000000000000000000000000000000000000000000000000000000000000360000000000000000000000000000000000000000000000000000000000000038000000000000000000000000000000000000000000000000000000000000003a00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000002260000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000f446169204f70706f7274756e6973740000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000f446169204f70706f7274756e69737400000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000300000000000000000000000027f38719608422af8a31509cbbb5facd582f6e1f000000000000000000000000fe6d982a773f4251da4ba04fc8fe7f2717413599000000000000000000000000fbc81d6e3e85462b56ebdaef71fe26af77cdffa90000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000c001a0cb64b4517fba378788c047de9cd8d507e4034adb20eebc321a4f732b249643daa07be53d5938ae62390f763091f48ac52cec85a3270fa6b8069b498ad8a1c3465b";
// const testLabel = "V2 Deploy Vault"; // <= Name of the test
// const testDirSuffix = "v2_deploy_vault"; // <= directory to compare device snapshots to
// const testNetwork = "ethereum";
//
// const signedPlugin = false;
//
// const devices = [
//     {
//         name: "nanos",
//         label: "Nano S",
//         steps: 6 // <= Define the number of steps for this test case and this device
//     },
//     {
//         name: "nanox",
//         label: "Nano X",
//         steps: 4 // <= Define the number of steps for this test case and this device
//     }
// ];
//
// devices.forEach((device) =>
//   processTest(device, contractName, testLabel, testDirSuffix, rawTxHex, signedPlugin,"",testNetwork)
// );
