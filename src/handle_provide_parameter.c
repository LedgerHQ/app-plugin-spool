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
             context->next_param = NONE;
             break;
        case NONE:
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
             context->next_param = NONE;
             break;
        case NONE:
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
            handle_transaction(msg, context);
            break;
        case SPOOL_GET_REWARDS:
        case SPOOL_CONTROLLER_REWARDS:
        case SPOOL_CLAIM:
            handle_get_rewards(msg, context);
            break;
        case SPOOL_ADD_TOKEN:
            handle_add_token(msg, context);
            break;
        default:
            PRINTF("Selector Index %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }

}
