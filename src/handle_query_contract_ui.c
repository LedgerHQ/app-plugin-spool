#include "spool_plugin.h"

// Set UI for the "Send" screen.
static void set_send_ui(ethQueryContractUI_t *msg, spool_parameters_t *context) {
    switch (context->selectorIndex) {
        case SPOOL_DEPOSIT:
            strlcpy(msg->title, "Deposit to vault", msg->titleLength);
            break;
        default:
            PRINTF("Unhandled selector Index: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    // Checks decimal places of token based on number length
    bool isBig = false;
    for (int i = 0; i < INT256_LENGTH; i++) {
        if (i < 24 && context->amount_sent[i] > 0) {
            isBig = true;
        }
    }

    if (isBig) {
        amountToString(context->amount_sent,
                       sizeof(context->amount_sent),
                       BIG_DECIMALS,
                       "DAI ",
                       msg->msg,
                       msg->msgLength);
    } else {
        amountToString(context->amount_sent,
                       sizeof(context->amount_sent),
                       SMALL_DECIMALS,
                       "USDT/C ",
                       msg->msg,
                       msg->msgLength);
    }
}

// Set UI for "Warning" screen.
static void set_deposit_ui(ethQueryContractUI_t *msg,
                           const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "DEPOSITING FUNDS", msg->titleLength);
    strlcpy(msg->msg, "", msg->msgLength);
}

static void set_create_spool_ui(ethQueryContractUI_t *msg,
                                const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "Spool", msg->titleLength);
    strlcpy(msg->msg, "Creating . . .", msg->msgLength);
}

static void set_claim_ui(ethQueryContractUI_t *msg,
                         const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "Spool", msg->titleLength);
    strlcpy(msg->msg, "Claiming . . .", msg->msgLength);
}

static void set_compound_ui(ethQueryContractUI_t *msg,
                            const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "Spool", msg->titleLength);
    strlcpy(msg->msg, "Compounding . . .", msg->msgLength);
}

static void set_fast_withdraw_ui(ethQueryContractUI_t *msg,
                                 const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "Fast withdraw", msg->titleLength);
    strlcpy(msg->msg, "Withdrawing . . .", msg->msgLength);
}

static void set_stake_ui(ethQueryContractUI_t *msg,
                         const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "Staking", msg->titleLength);

    amountToString(context->amount_sent,
                   sizeof(context->amount_sent),
                   BIG_DECIMALS,
                   "Amount ",
                   msg->msg,
                   msg->msgLength);
}

static void set_unstake_ui(ethQueryContractUI_t *msg,
                           const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "Unstaking", msg->titleLength);
    amountToString(context->amount_sent,
                   sizeof(context->amount_sent),
                   BIG_DECIMALS,
                   "Amount ",
                   msg->msg,
                   msg->msgLength);
}

static void set_add_token_ui(ethQueryContractUI_t *msg,
                             const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "Reward token:", msg->titleLength);

    if (context->token_found) {
        const char *ticker = context->ticker;
        strlcpy(msg->msg, ticker, msg->msgLength);
    } else {
        msg->msg[0] = '0';
        msg->msg[1] = 'x';
        // We need a random chainID for legacy reasons with `getEthAddressStringFromBinary`.
        // Setting it to `0` will make it work with every chainID :)
        uint64_t chainid = 0;

        // Get the string representation of the address stored in `context->beneficiary`. Put it in
        // `msg->msg`.
        getEthAddressStringFromBinary(
            (uint8_t *) context->token_address,
            msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
            chainid);
    }
}

static void set_added_token_amount_ui(ethQueryContractUI_t *msg,
                                      const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "Reward amount:", msg->titleLength);
    uint8_t decimals = context->decimals;
    const char *ticker = context->ticker;
    if (context->token_found) {
        amountToString(context->amount_sent,
                       sizeof(context->amount_sent),
                       decimals,
                       ticker,
                       msg->msg,
                       msg->msgLength);
    } else {
        amountToString(context->amount_sent,
                       sizeof(context->amount_sent),
                       BIG_DECIMALS,
                       "Amount: ",
                       msg->msg,
                       msg->msgLength);
    }
}

static void set_reward_end_time(ethQueryContractUI_t *msg,
                                const spool_parameters_t *context __attribute__((unused))) {
    PRINTF("set_reward_end_time\n");
    strlcpy(msg->title, "End time:", msg->titleLength);
    amountToString(context->end_timestamp,
                   sizeof(context->end_timestamp),
                   0,
                   "Timestamp: ",
                   msg->msg,
                   msg->msgLength);
}

static void set_vault_ui(ethQueryContractUI_t *msg,
                         const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "Vault:", msg->titleLength);
    msg->msg[0] = '0';
    msg->msg[1] = 'x';
    // We need a random chainID for legacy reasons with `getEthAddressStringFromBinary`.
    // Setting it to `0` will make it work with every chainID :)
    uint64_t chainid = 0;
    getEthAddressStringFromBinary(
        (uint8_t *) context->vault_address,
        msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
        chainid);
}

static void set_beneficiary_ui(ethQueryContractUI_t *msg,
                               const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "Receiver:", msg->titleLength);
    msg->msg[0] = '0';
    msg->msg[1] = 'x';
    // We need a random chainID for legacy reasons with `getEthAddressStringFromBinary`.
    // Setting it to `0` will make it work with every chainID :)
    uint64_t chainid = 0;
    getEthAddressStringFromBinary(
        (uint8_t *) context->beneficiary,
        msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
        chainid);
}

static void set_shares_ui(ethQueryContractUI_t *msg,
                          const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "Shares:", msg->titleLength);
    amountToString(context->amount_sent,
                   sizeof(context->amount_sent),
                   BIG_DECIMALS,
                   "Amount: ",
                   msg->msg,
                   msg->msgLength);
}

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    spool_parameters_t *context = (spool_parameters_t *) msg->pluginContext;

    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);
    msg->result = ETH_PLUGIN_RESULT_OK;
    uint8_t index = msg->screenIndex;

    switch (index) {
        case 0:
            switch (context->selectorIndex) {
                case SPOOL_DEPOSIT:
                    set_deposit_ui(msg, context);
                    break;
                case SPOOL_CLAIM:
                case SPOOL_CONTROLLER_REWARDS:
                case SPOOL_GET_REWARDS:
                case SPOOL_V2_CLAIM_REWARD:
                case SPOOL_CLAIM_VESTING:
                case SPOOL_STAKING_REWARDS:
                    set_claim_ui(msg, context);
                    break;
                case SPOOL_WITHDRAW:
                case SPOOL_WITHDRAW_FAST:
                    set_fast_withdraw_ui(msg, context);
                    break;
                case SPOOL_CREATE_VAULT:
                case SPOOL_V2_DEPLOY_VAULT:
                    set_create_spool_ui(msg, context);
                    break;
                case SPOOL_STAKE:
                    set_stake_ui(msg, context);
                    break;
                case SPOOL_UNSTAKE:
                    set_unstake_ui(msg, context);
                    break;
                case SPOOL_COMPOUND:
                    set_compound_ui(msg, context);
                    break;
                case SPOOL_ADD_TOKEN:
                case SPOOL_V2_ADD_TOKEN:
                case SPOOL_V2_EXTEND_REWARD:
                    set_add_token_ui(msg, context);
                    break;
                case SPOOL_V2_REDEEM_FAST:
                case SPOOL_V2_REDEEM:
                case SPOOL_V2_DEPOSIT:
                case SPOOL_V2_CLAIM_WITHDRAWAL:
                case SPOOL_V2_SWAP_AND_DEPOSIT:
                    set_vault_ui(msg, context);
                    break;
                default:
                    PRINTF("Unhandled selector index: %d\n", context->selectorIndex);
                    break;
            }
            break;
        case 1:
            switch (context->selectorIndex) {
                case SPOOL_DEPOSIT:
                    set_send_ui(msg, context);
                    break;
                case SPOOL_ADD_TOKEN:
                case SPOOL_V2_ADD_TOKEN:
                case SPOOL_V2_EXTEND_REWARD:
                    set_added_token_amount_ui(msg, context);
                    break;
                case SPOOL_V2_REDEEM_FAST:
                case SPOOL_V2_REDEEM:
                    set_shares_ui(msg, context);
                    break;
                case SPOOL_V2_CLAIM_WITHDRAWAL:
                case SPOOL_V2_SWAP_AND_DEPOSIT:
                case SPOOL_V2_DEPOSIT:
                    set_beneficiary_ui(msg, context);
                    break;
                default:
                    PRINTF("Unhandled selector index: %d\n", context->selectorIndex);
                    break;
            }
            break;
        case 2:
            switch (context->selectorIndex) {
                case SPOOL_V2_ADD_TOKEN:
                case SPOOL_V2_EXTEND_REWARD:
                    set_vault_ui(msg, context);
                    break;
                default:
                    PRINTF("Unhandled selector index: %d\n", context->selectorIndex);
                    break;
            }
            break;
        case 3:
            switch (context->selectorIndex) {
                case SPOOL_V2_ADD_TOKEN:
                case SPOOL_V2_EXTEND_REWARD:
                    set_reward_end_time(msg, context);
                    break;
                default:
                    PRINTF("Unhandled selector index: %d\n", context->selectorIndex);
                    break;
            }
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
}
