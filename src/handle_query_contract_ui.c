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
    for (int i = 0 ; i < INT256_LENGTH; i++) {
        if (i < 24 && context->amount_sent[i] > 0) {
            isBig = true;
        }
    }

    if (isBig) {
        amountToString(context->amount_sent,
                       sizeof(context->amount_sent),
                       18,
                       "DAI ",
                       msg->msg,
                       msg->msgLength);
    } else {
        amountToString(context->amount_sent,
                       sizeof(context->amount_sent),
                       6,
                       "USDT/C ",
                       msg->msg,
                       msg->msgLength);
        }
}

// Set UI for "Warning" screen.
static void set_warning_ui(ethQueryContractUI_t *msg,
                           const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "SENDING STABLE", msg->titleLength);
    strlcpy(msg->msg, "USDT / DAI / USDC", msg->msgLength);
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

    amountToString(context->amount_sent,
                   sizeof(context->amount_sent),
                   18,
                   "Shares ",
                   msg->msg,
                   msg->msgLength);
}

static void set_stake_ui(ethQueryContractUI_t *msg,
                           const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "Staking", msg->titleLength);

    amountToString(context->amount_sent,
                   sizeof(context->amount_sent),
                   18,
                   "Amount ",
                   msg->msg,
                   msg->msgLength);
}

static void set_unstake_ui(ethQueryContractUI_t *msg,
                           const spool_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "Unstaking", msg->titleLength);
    amountToString(context->amount_sent,
                   sizeof(context->amount_sent),
                   18,
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
            context->token_address,
            msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
            msg->pluginSharedRW->sha3,
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
                       18,
                       "Amount: ",
                       msg->msg,
                       msg->msgLength);
    }
}



void handle_query_contract_ui(void *parameters) {
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
    spool_parameters_t *context = (spool_parameters_t *) msg->pluginContext;

    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);
    msg->result = ETH_PLUGIN_RESULT_OK;
    uint8_t index = msg->screenIndex;

    switch (index) {
            case 0:
                switch(context -> selectorIndex) {
                    case SPOOL_DEPOSIT:
                        set_warning_ui(msg, context);
                        break;
                    case SPOOL_CLAIM:
                    case SPOOL_CONTROLLER_REWARDS:
                    case SPOOL_GET_REWARDS:
                    case SPOOL_CLAIM_VESTING:
                    case SPOOL_STAKING_REWARDS:
                        set_claim_ui(msg, context);
                        break;
                    case SPOOL_WITHDRAW:
                    case SPOOL_WITHDRAW_FAST:
                        set_fast_withdraw_ui(msg, context);
                        break;
                    case SPOOL_CREATE_VAULT:
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
                        set_add_token_ui(msg, context);
                        break;
                }
                break;
            case 1:
                switch(context -> selectorIndex) {
                    case SPOOL_DEPOSIT:
                        set_send_ui(msg, context);
                        break;
                    case SPOOL_ADD_TOKEN:
                        set_added_token_amount_ui(msg, context);
                        break;
                }

                break;
            default:
               PRINTF("Received an invalid screenIndex\n");
               msg->result = ETH_PLUGIN_RESULT_ERROR;
               return;
        }
}
