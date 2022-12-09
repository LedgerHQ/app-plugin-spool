#include "spool_plugin.h"

// Called once to init.
void handle_init_contract(void *parameters) {
    ethPluginInitContract_t *msg = (ethPluginInitContract_t *) parameters;

    if (msg->interfaceVersion != ETH_PLUGIN_INTERFACE_VERSION_LATEST) {
        PRINTF("Wrong interface version: expected %d got %d\n",
               ETH_PLUGIN_INTERFACE_VERSION_LATEST,
               msg->interfaceVersion);
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    if (msg->pluginContextLength < sizeof(spool_parameters_t)) {
        PRINTF("Spool context size too big: expected %d got %d\n",
               sizeof(spool_parameters_t),
               msg->pluginContextLength);
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    spool_parameters_t *context = (spool_parameters_t *) msg->pluginContext;
    memset(context, 0, sizeof(*context));

    for (uint8_t i = 0; i < NUM_SPOOL_SELECTORS; i++) {
        if (memcmp((uint8_t *) PIC(SPOOL_SELECTORS[i]), msg->selector, SELECTOR_SIZE) == 0) {
            context->selectorIndex = i;
            break;
        }
    }

    // Set `next_param` to be the first field we expect to parse.
    switch (context->selectorIndex) {
        case SPOOL_CREATE_VAULT:
        case SPOOL_CLAIM:
        case SPOOL_STAKING_REWARDS:
        case SPOOL_CLAIM_VESTING:
        case SPOOL_COMPOUND:
            context->next_param = NONE;
            break;
        case SPOOL_WITHDRAW:
        case SPOOL_WITHDRAW_FAST:
        case SPOOL_CONTROLLER_REWARDS:
        case SPOOL_GET_REWARDS:
        case SPOOL_DEPOSIT:
            context->next_param = PATHS_OFFSET;
            break;
        case SPOOL_STAKE:
        case SPOOL_UNSTAKE:
            context->next_param = AMOUNT_SENT;
            break;
        case SPOOL_ADD_TOKEN:
            context->next_param = ADDRESS;
            break;
        default:
            PRINTF("Missing selectorIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}
