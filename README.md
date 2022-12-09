# Ledger Spool Plugin

This is a plugin for the Ethereum application which helps parsing and displaying relevant information when signing Spool transactions.

## Prerequisite

Be sure to have your environment correctly set up (see [Getting Started](https://ledger.readthedocs.io/en/latest/userspace/getting_started.html)) and [ledgerblue](https://pypi.org/project/ledgerblue/) and installed.

If you want to benefit from [vscode](https://code.visualstudio.com/) integration, it's recommended to move the toolchain in `/opt` and set `BOLOS_ENV` environment variable as follows

```
BOLOS_ENV=/opt/bolos-devenv
```

and do the same with `BOLOS_SDK` environment variable

```
BOLOS_SDK=/opt/nanos-secure-sdk
```

## Documentation

Need more information about the interface, the architecture, or general stuff about ethereum plugins? You can find more about them in the [ethereum-app documentation](https://github.com/LedgerHQ/app-ethereum/blob/master/doc/ethapp_plugins.asc).

## Smart Contracts

Smart contracts covered by this plugin are:

| Contract Name           |Smart Contract |
|-------------------------| --- |
| Vault (various proxies) | `0xa308828904977BbcEb91A9B0cb3dB07636734Fb7` |
| Controller              | `0xdd4051c3571c143b989c3227e8eb50983974835c`|
| Staking                 | `0xc3160c5cc63b6116dd182faa8393d3ad9313e213`|
| Vesting                 | `0x08772c1872c997Fec8dA3c7f36C1FC28EBE72E97`|


## Compilation

```
make DEBUG=1  # compile optionally with PRINTF
make load     # load the app on the Nano using ledgerblue
```

This plugin uses the [ethereum-plugin-sdk](https://github.com/LedgerHQ/ethereum-plugin-sdk/). If there's an error while building, try running `git pull --recurse-submodules` in order to update the sdk. If this fixes your bug, please file an issue or create a PR to add the new sdk version :)

If you need to update the sdk, you will need to do it locally and create a PR on the [ethereum-plugin-sdk repo](https://github.com/LedgerHQ/ethereum-plugin-sdk/).

## Tests & Continuous Integration

The flow processed in [GitHub Actions](https://github.com/features/actions) is the following:

- Code formatting with [clang-format](http://clang.llvm.org/docs/ClangFormat.html)
- Compilation of the application for Ledger Nano S in [ledger-app-builder](https://github.com/LedgerHQ/ledger-app-builder)


## RDP tests execution

You can test the plugin using a remote development host, if you deal with an unsupported CPU architecture (Ex.: Apple M1). Your server must have a GUI Desktop installed.

1. Install first xrdp on remote linux VM (Ex: Ubuntu 20.04.1)
```
sudo apt install xrdp
````

2. Set access control to none :
```
xhost +
```
> ```access control disabled, clients can connect from any host```


3. Connect to the VM using Remote Desktop Client using port forwarding through ssh connection on port 3389. This will keep the security at maximum and avoid exposing the VM to the web on RDP port.

```
ssh -i PRIVATEKEY USERNAME@PUBLICIP -L 3389:localhost:3389
```

4. Identify the Display index:
```
echo $DISPLAY
```
>```:10.0```

5. In the terminal where are executed the tests set Display to the RDP previous value, here ``:10.0``:

```
export DISPLAY=:10.0
```

6. After this setup you could run ``yarn test`` and see the emulator in the RDP display going through the test sequence.


