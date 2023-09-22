#include "spool_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    spool_parameters_t *context = (spool_parameters_t *) msg->pluginContext;
    msg->tokenLookup1 = NULL;
    msg->tokenLookup2 = NULL;

    switch (context->selectorIndex) {
        case SPOOL_CREATE_VAULT:
        case SPOOL_V2_DEPLOY_VAULT:
        case SPOOL_STAKE:
        case SPOOL_UNSTAKE:
            msg->numScreens = 1;
            break;
        case SPOOL_DEPOSIT:
        case SPOOL_ADD_TOKEN:
            msg->numScreens = 2;
            break;
        case SPOOL_CLAIM:
        case SPOOL_CONTROLLER_REWARDS:
        case SPOOL_GET_REWARDS:
        case SPOOL_STAKING_REWARDS:
        case SPOOL_WITHDRAW:
        case SPOOL_WITHDRAW_FAST:
        case SPOOL_CLAIM_VESTING:
        case SPOOL_COMPOUND:
            msg->numScreens = 0;
            break;
//             v2
        case SPOOL_V2_REDEEM_FAST:
        case SPOOL_V2_REDEEM:
        case SPOOL_V2_DEPOSIT:
        case SPOOL_V2_CLAIM_WITHDRAWAL:
        case SPOOL_V2_SWAP_AND_DEPOSIT:
            msg->numScreens = 2;
            break;
        case SPOOL_V2_ADD_TOKEN:
        case SPOOL_V2_EXTEND_REWARD:
            msg->numScreens = 4;
            msg->tokenLookup1 = context->token_address;
            break;
    }
    msg->uiType = ETH_UI_TYPE_GENERIC;
    msg->result = ETH_PLUGIN_RESULT_OK;
}
