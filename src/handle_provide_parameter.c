#include "spool_plugin.h"

// Copy amount sent parameter to amount_sent
static void handle_amount_sent(const ethPluginProvideParameter_t *msg,
                               spool_parameters_t *context) {
    copy_parameter(context->amount_sent, msg->parameter, sizeof(context->amount_sent));
}

static void handle_transaction(ethPluginProvideParameter_t *msg, spool_parameters_t *context) {
    switch (context->next_param) {
        case PATHS_OFFSET:
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - sizeof(context->offset));
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:
            handle_amount_sent(msg, context);
            context->next_param = END;
            break;
        case END:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_get_rewards(ethPluginProvideParameter_t *msg, spool_parameters_t *context) {
    switch (context->next_param) {
        case PATHS_OFFSET:  // vault strategies
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - sizeof(context->offset));
            context->next_param = END;
            break;
        case END:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_add_token(ethPluginProvideParameter_t *msg, spool_parameters_t *context) {
    switch (context->next_param) {
        case ADDRESS:
            copy_address(context->token_address, msg->parameter, sizeof(context->token_address));
            context->next_param = NONE;
            break;
        case AMOUNT_SENT:
            handle_amount_sent(msg, context);
            context->next_param = NONE;
            break;
        case NONE:
            context->next_param = AMOUNT_SENT;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

// v2
static void handle_redeem(ethPluginProvideParameter_t *msg, spool_parameters_t *context) {
    switch (context->next_param) {
        case SKIP:
             if (context->skip_counter > 0) {
                 context->skip_counter--;
                 break; // exit early since we're skipping
             }
             context->next_param = BENEFICIARY;
             break;
        case ADDRESS:
            copy_address(context->vault_address, msg->parameter, sizeof(context->vault_address));
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:
            handle_amount_sent(msg, context);
            context->next_param = END;
            break;
        case PATHS_OFFSET:
            context->next_param = ADDRESS;
            break;
        case BENEFICIARY:
            copy_address(context->beneficiary, msg->parameter, sizeof(context->beneficiary));
            context->next_param = PATHS_OFFSET;
            break;
        case END:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_redeem_fast(ethPluginProvideParameter_t *msg, spool_parameters_t *context) {
    switch (context->next_param) {
        case SKIP:
             if (context->skip_counter > 0) {
                 context->skip_counter--;
                 break; // exit early since we're skipping
             }
             context->next_param = ADDRESS;
             break;
        case ADDRESS:
            copy_address(context->vault_address, msg->parameter, sizeof(context->vault_address));
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:
            handle_amount_sent(msg, context);
            context->next_param = END;
            break;
        case NFT_IDS:
            context->next_param = PATHS_OFFSET;
            break;
        case PATHS_OFFSET:
            context->next_param = BENEFICIARY;
            break;
        case BENEFICIARY:
            copy_address(context->beneficiary, msg->parameter, sizeof(context->beneficiary));
            context->next_param = END;
            break;
        case END:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_deposit(ethPluginProvideParameter_t *msg, spool_parameters_t *context) {
    switch (context->next_param) {
            case SKIP:
                 if (context->skip_counter > 0) {
                     context->skip_counter--;
                     break; // exit early since we're skipping
                 }
                 context->next_param = ADDRESS;
                 break;
            case ADDRESS:
                copy_address(context->vault_address, msg->parameter, sizeof(context->vault_address));
                context->next_param = PATHS_OFFSET;
                break;
            case PATHS_OFFSET:
                context->next_param = BENEFICIARY;
                break;
            case BENEFICIARY:
                copy_address(context->beneficiary, msg->parameter, sizeof(context->beneficiary));
                context->next_param = END;
                break;
            case END:
                break;
            default:
                PRINTF("Param not supported: %d\n", context->next_param);
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                break;
        }
}

static void handle_claim_withdraw(ethPluginProvideParameter_t *msg, spool_parameters_t *context) {
    switch (context->next_param) {
        case VAULT_ADDRESS:
            copy_address(context->vault_address, msg->parameter, sizeof(context->vault_address));
            context->next_param = PATHS_OFFSET;
            break;
        case PATHS_OFFSET:
            context->next_param = NONE;
            break;
        case NONE:
            context->next_param = BENEFICIARY;
            break;
        case BENEFICIARY:
            copy_address(context->beneficiary, msg->parameter, sizeof(context->beneficiary));
            context->next_param = END;
            break;
        case END:
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_add_reward_token(ethPluginProvideParameter_t *msg, spool_parameters_t *context) {
    switch (context->next_param) {
        case ADDRESS:
            copy_address(context->token_address, msg->parameter, sizeof(context->token_address));
            switch (context->selectorIndex) {
                case SPOOL_V2_ADD_TOKEN:
                    context->next_param = END_TIMESTAMP;
                    break;
                case SPOOL_V2_EXTEND_REWARD:
                    context->next_param = AMOUNT_SENT;
                    break;
            }
            break;
        case VAULT_ADDRESS:
            copy_address(context->vault_address, msg->parameter, sizeof(context->vault_address));
            context->next_param = ADDRESS;
            break;
        case END_TIMESTAMP:
            copy_parameter(context->end_timestamp, msg->parameter, sizeof(context->end_timestamp));
            switch (context->selectorIndex) {
                case SPOOL_V2_ADD_TOKEN:
                    context->next_param = AMOUNT_SENT;
                    break;
                case SPOOL_V2_EXTEND_REWARD:
                    context->next_param = NONE;
                    break;
            }
            break;
        case AMOUNT_SENT:
            handle_amount_sent(msg, context);
            switch (context->selectorIndex) {
                case SPOOL_V2_ADD_TOKEN:
                    context->next_param = NONE;
                    break;
                case SPOOL_V2_EXTEND_REWARD:
                    context->next_param = END_TIMESTAMP;
                    break;
            }
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported in add reward: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_swap_and_deposit(ethPluginProvideParameter_t *msg, spool_parameters_t *context) {
    switch (context->next_param) {
            case SKIP:
                if (context->skip_counter > 0) {
                    context->skip_counter--;
                    break; // exit early since we're skipping
                }
                context->next_param = VAULT_ADDRESS;
                break;
            case VAULT_ADDRESS:
                copy_address(context->vault_address, msg->parameter, sizeof(context->vault_address));
                context->next_param = BENEFICIARY;
                break;
            case BENEFICIARY:
                copy_address(context->beneficiary, msg->parameter, sizeof(context->beneficiary));
                context->next_param = END;
                break;
            case END:
                break;
            default:
                PRINTF("Param not supported: %d\n", context->next_param);
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                break;
        }
}

static void handle_claim_reward(ethPluginProvideParameter_t *msg, spool_parameters_t *context) {

}

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;
    spool_parameters_t *context = (spool_parameters_t *) msg->pluginContext;

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case SPOOL_CREATE_VAULT:
        case SPOOL_WITHDRAW_FAST:
        case SPOOL_WITHDRAW:
        case SPOOL_STAKE:
        case SPOOL_UNSTAKE:
        case SPOOL_STAKING_REWARDS:
        case SPOOL_COMPOUND:
        case SPOOL_CLAIM_VESTING:
        case SPOOL_DEPOSIT:
        case SPOOL_V2_DEPLOY_VAULT:         // V2
            handle_transaction(msg, context);
            break;
        case SPOOL_GET_REWARDS:
        case SPOOL_CONTROLLER_REWARDS:
        case SPOOL_CLAIM:
        case SPOOL_V2_CLAIM_REWARD:
            handle_get_rewards(msg, context);
            break;
        case SPOOL_ADD_TOKEN:
            handle_add_token(msg, context);
            break;
        case SPOOL_V2_REDEEM_FAST:
            handle_redeem_fast(msg, context);
            break;
        case SPOOL_V2_REDEEM:
            handle_redeem(msg, context);
            break;
        case SPOOL_V2_DEPOSIT:
            handle_deposit(msg, context);
            break;
        case SPOOL_V2_CLAIM_WITHDRAWAL:
            handle_claim_withdraw(msg, context);
            break;
        case SPOOL_V2_ADD_TOKEN:
        case SPOOL_V2_EXTEND_REWARD:
            handle_add_reward_token(msg, context);
            break;
        case SPOOL_V2_SWAP_AND_DEPOSIT:
            handle_swap_and_deposit(msg, context);
            break;
        default:
            PRINTF("Selector Index %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
