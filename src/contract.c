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
const uint32_t SPOOL_SELECTORS[NUM_SPOOL_SELECTORS] = {SPOOL_DEPOSIT_SELECTOR,
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
