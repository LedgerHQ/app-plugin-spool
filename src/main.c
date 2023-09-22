/*******************************************************************************
 *   Ethereum 2 Deposit Application
 *   (c) 2020 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "os.h"
#include "cx.h"

#include "glyphs.h"

#include "spool_plugin.h"

// VAULT METHODS

// Function: deposit(address[] vaultStrategies,uint128 amount,bool transferFromVault)
// MethodID: 0x8ab936b8
// static const uint8_t SPOOL_DEPOSIT_SELECTOR[SELECTOR_SIZE] = {0x8a, 0xb9, 0x36, 0xb8};

// Function: claim(bool doRedeemVault,address[] vaultStrategies,bool doRedeemUser)
// MethodID: 0x084fd9b4
// static const uint8_t SPOOL_CLAIM_SELECTOR[SELECTOR_SIZE] = {0x08, 0x4f, 0xd9, 0xb4};

// Function: getRewards(address[] tokens)
// MethodID: 0x510ccb43
// static const uint8_t SPOOL_GET_REWARDS_SELECTOR[SELECTOR_SIZE] = {0x51, 0x0c, 0xcb, 0x43};

// Function: withdrawFast(address[] vaultStrategies,uint128 sharesToWithdraw,bool withdrawAll,tuple
// fastWithdrawParams) MethodID: 0xd7b9d423
// static const uint8_t SPOOL_WITHDRAW_FAST_SELECTOR[SELECTOR_SIZE] = {0xd7, 0xb9, 0xd4, 0x23};

// Function: withdraw(address[] vaultStrategies,uint128 sharesToWithdraw,bool withdrawAll)
// MethodID: 0xfd3c11a8
// static const uint8_t SPOOL_WITHDRAW_SELECTOR[SELECTOR_SIZE] = {0xfd, 0x3c, 0x11, 0xa8};

// Function: addToken(address token,uint32 rewardsDuration,uint256 reward)
// MethodID: 0x73c2ad9c
// static const uint8_t SPOOL_ADD_TOKEN_SELECTOR[SELECTOR_SIZE] = {0x73, 0xc2, 0xad, 0x9c};

// CONTROLLER METHODS

// Function: createVault(tuple details)
// MethodID: 0xc48ef844
// static const uint8_t SPOOL_CREATE_VAULT_SELECTOR[SELECTOR_SIZE] = {0xc4, 0x8e, 0xf8, 0x44};

// Function: getRewards(address[] vaults)
// MethodID: 0x510ccb43
// static const uint8_t SPOOL_CONTROLLER_REWARDS_SELECTOR[SELECTOR_SIZE] = {0x51, 0x0c, 0xcb, 0x43};

// STAKING METHODS

// Function: stake(uint256 amount)
// MethodID: 0xa694fc3a
// static const uint8_t SPOOL_STAKE_SELECTOR[SELECTOR_SIZE] = {0xa6, 0x94, 0xfc, 0x3a};

// Function: unstake(uint256 amount)
// MethodID: 0x2e17de78
// static const uint8_t SPOOL_UNSTAKE_SELECTOR[SELECTOR_SIZE] = {0x2e, 0x17, 0xde, 0x78};

// Function: getRewards(address[] tokens, bool doClaimVoSpoolRewards)
// MethodID: 0xf4de10ac
// static const uint8_t SPOOL_STAKING_REWARDS_SELECTOR[SELECTOR_SIZE] = {0xf4, 0xde, 0x10, 0xac};

// Function: compound(bool doCompoundVoSpoolRewards)
// MethodID: 0xd1e6044a
// static const uint8_t SPOOL_COMPOUND_SELECTOR[SELECTOR_SIZE] = {0xd1, 0xe6, 0x04, 0x4a};

// VESTING

// Function: claim()
// MethodID: 0x4e71d92d
// static const uint8_t SPOOL_CLAIM_VESTING_SELECTOR[SELECTOR_SIZE] = {0x4e, 0x71, 0xd9, 0x2d};

// V2

// Function: deploySmartVault(tuple specification)
// MethodID: 0x6fc3f5d5
// static const uint8_t SPOOL_V2_DEPLOY_VAULT_SELECTOR[SELECTOR_SIZE] = {0x6f, 0xc3, 0xf5, 0xd5};


static const uint32_t SPOOL_DEPOSIT_SELECTOR = 0x8ab936b8;
static const uint32_t SPOOL_CLAIM_SELECTOR = 0x084fd9b4;
static const uint32_t SPOOL_GET_REWARDS_SELECTOR = 0x510ccb43;
static const uint32_t SPOOL_WITHDRAW_FAST_SELECTOR = 0xd7b9d423;
static const uint32_t SPOOL_WITHDRAW_SELECTOR = 0xfd3c11a8;
static const uint32_t SPOOL_ADD_TOKEN_SELECTOR = 0x73c2ad9c;
static const uint32_t SPOOL_CREATE_VAULT_SELECTOR = 0xc48ef844;
static const uint32_t SPOOL_CONTROLLER_REWARDS_SELECTOR = 0x510ccb43;
static const uint32_t SPOOL_STAKE_SELECTOR = 0xa694fc3a;
static const uint32_t SPOOL_UNSTAKE_SELECTOR = 0x2e17de78;
static const uint32_t SPOOL_STAKING_REWARDS_SELECTOR = 0xf4de10ac;
static const uint32_t SPOOL_COMPOUND_SELECTOR = 0xd1e6044a;
static const uint32_t SPOOL_CLAIM_VESTING_SELECTOR = 0x4e71d92d;

static const uint32_t SPOOL_V2_DEPLOY_VAULT_SELECTOR = 0x6fc3f5d5;
static const uint32_t SPOOL_V2_ADD_TOKEN_SELECTOR = 0x2aba2aeb;
static const uint32_t SPOOL_V2_CLAIM_WITHDRAWAL_SELECTOR = 0xf8a70486;
static const uint32_t SPOOL_V2_SWAP_AND_DEPOSIT_SELECTOR = 0xd99d32e3;
static const uint32_t SPOOL_V2_REDEEM_FAST_SELECTOR = 0xe1c2eea6;
static const uint32_t SPOOL_V2_REDEEM_SELECTOR = 0x388bbfd3;
static const uint32_t SPOOL_V2_DEPOSIT_SELECTOR = 0xfa15b91b;
static const uint32_t SPOOL_V2_CLAIM_REWARD_SELECTOR = 0xfb7e92ea;
static const uint32_t SPOOL_V2_EXTEND_REWARD_SELECTOR = 0xb02029e0;

// Array of all the different spool selectors.
const uint8_t *const SPOOL_SELECTORS[NUM_SPOOL_SELECTORS] = {SPOOL_DEPOSIT_SELECTOR,
                                                             SPOOL_CLAIM_SELECTOR,
                                                             SPOOL_GET_REWARDS_SELECTOR,
                                                             SPOOL_WITHDRAW_FAST_SELECTOR,
                                                             SPOOL_WITHDRAW_SELECTOR,
                                                             SPOOL_CREATE_VAULT_SELECTOR,
                                                             SPOOL_CONTROLLER_REWARDS_SELECTOR,
                                                             SPOOL_STAKE_SELECTOR,
                                                             SPOOL_UNSTAKE_SELECTOR,
                                                             SPOOL_STAKING_REWARDS_SELECTOR,
                                                             SPOOL_COMPOUND_SELECTOR,
                                                             SPOOL_CLAIM_VESTING_SELECTOR,
                                                             SPOOL_ADD_TOKEN_SELECTOR,
                                                             SPOOL_V2_DEPLOY_VAULT_SELECTOR,
                                                             SPOOL_V2_ADD_TOKEN_SELECTOR,
                                                             SPOOL_V2_CLAIM_WITHDRAWAL_SELECTOR,
                                                             SPOOL_V2_SWAP_AND_DEPOSIT_SELECTOR,
                                                             SPOOL_V2_REDEEM_FAST_SELECTOR,
                                                             SPOOL_V2_REDEEM_SELECTOR,
                                                             SPOOL_V2_DEPOSIT_SELECTOR,
                                                             SPOOL_V2_CLAIM_REWARD_SELECTOR,
                                                             SPOOL_V2_EXTEND_REWARD_SELECTOR};

void spool_plugin_call(int message, void *parameters) {
    switch (message) {
        case ETH_PLUGIN_INIT_CONTRACT:
            handle_init_contract(parameters);
            break;
        case ETH_PLUGIN_PROVIDE_PARAMETER:
            handle_provide_parameter(parameters);
            break;
        case ETH_PLUGIN_FINALIZE:
            handle_finalize(parameters);
            break;
        case ETH_PLUGIN_PROVIDE_INFO:
            handle_provide_token(parameters);
            break;
        case ETH_PLUGIN_QUERY_CONTRACT_ID:
            handle_query_contract_id(parameters);
            break;
        case ETH_PLUGIN_QUERY_CONTRACT_UI:
            handle_query_contract_ui(parameters);
            break;
        default:
            PRINTF("Unhandled message %d\n", message);
            break;
    }
}

void handle_query_ui_exception(unsigned int *args) {
    switch (args[0]) {
        case ETH_PLUGIN_QUERY_CONTRACT_UI:
            ((ethQueryContractUI_t *) args[1])->result = ETH_PLUGIN_RESULT_ERROR;
            break;
        default:
            break;
    }
}

// Calls the ethereum app.
void call_app_ethereum() {
    unsigned int libcall_params[5];
    libcall_params[0] = (unsigned int) "Ethereum";
    libcall_params[1] = 0x100;
    libcall_params[2] = RUN_APPLICATION;
    libcall_params[3] = (unsigned int) NULL;
#ifdef HAVE_NBGL
    caller_app_t capp;
    const char name[] = APPNAME;
    nbgl_icon_details_t icon_details;
    uint8_t bitmap[sizeof(ICONBITMAP)];

    memcpy(&icon_details, &ICONGLYPH, sizeof(ICONGLYPH));
    memcpy(&bitmap, &ICONBITMAP, sizeof(bitmap));
    icon_details.bitmap = (const uint8_t *) bitmap;
    capp.name = (const char *) name;
    capp.icon = &icon_details;
    libcall_params[4] = (unsigned int) &capp;
#else
    libcall_params[4] = (unsigned int) NULL;
#endif
    os_lib_call((unsigned int *) &libcall_params);
}

__attribute__((section(".boot"))) int main(int arg0) {
    // exit critical section
    __asm volatile("cpsie i");

    // ensure exception will work as planned
    os_boot();

    // Try catch block. Please read the docs for more information on how to use those!
    BEGIN_TRY {
        TRY {
            // Low-level black magic.
            check_api_level(CX_COMPAT_APILEVEL);
            // Check if we are called from the dashboard.
            if (!arg0) {
                // called from dashboard, launch Ethereum app
                call_app_ethereum();
                return 0;
            } else {
                // Not called from dashboard: called from the ethereum app!
                const unsigned int *args = (unsigned int *) arg0;

                // If `ETH_PLUGIN_CHECK_PRESENCE` is set, this means the caller is just trying to
                // know whether this app exists or not. We can skip `spool_plugin_call`.
                if (args[0] != ETH_PLUGIN_CHECK_PRESENCE) {
                    spool_plugin_call(args[0], (void *) args[1]);
                }
            }
        }
        CATCH_OTHER(e) {
            switch (e) {
                // These exceptions are only generated on handle_query_contract_ui()
                case 0x6502:
                case EXCEPTION_OVERFLOW:
                    handle_query_ui_exception((unsigned int *) arg0);
                    break;
                default:
                    break;
            }
            PRINTF("Exception 0x%x caught\n", e);
        }
        FINALLY {
            os_lib_end();
        }
    }
    END_TRY;

    return 0;
}
