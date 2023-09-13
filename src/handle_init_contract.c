#include "spool_plugin.h"

static int find_selector(uint32_t selector, const uint32_t *selectors, size_t n, selector_t *out) {
    for (selector_t i = 0; i < n; i++) {
        if (selector == selectors[i]) {
            *out = i;
            return 0;
        }
    }
    return -1;
}


// Called once to init.
void handle_init_contract(void *parameters) {
    // Cast the msg to the type of structure we expect (here, ethPluginInitContract_t).
    ethPluginInitContract_t *msg = (ethPluginInitContract_t *) parameters;

    // Make sure we are running a compatible version.
    if (msg->interfaceVersion != ETH_PLUGIN_INTERFACE_VERSION_LATEST) {
        PRINTF("Wrong interface version: expected %d got %d\n",
               ETH_PLUGIN_INTERFACE_VERSION_LATEST,
               msg->interfaceVersion);
        // If not the case, return the `UNAVAILABLE` status.
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    // Double check that the `context_t` struct is not bigger than the maximum size (defined by
    // `msg->pluginContextLength`).
    if (msg->pluginContextLength < sizeof(spool_parameters_t)) {
        PRINTF("Spool context size too big: expected %d got %d\n",
               sizeof(spool_parameters_t),
               msg->pluginContextLength);
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    spool_parameters_t *context = (spool_parameters_t *) msg->pluginContext;
    // Initialize the context (to 0).
    memset(context, 0, sizeof(*context));

    uint32_t selector = U4BE(msg->selector, 0);
    if (find_selector(selector, SPOOL_SELECTORS, NUM_SPOOL_SELECTORS, &context->selectorIndex)) {
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
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
