#include "spool_plugin.h"

void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    const spool_parameters_t *context = (spool_parameters_t *) msg->pluginContext;

    strlcpy(msg->name, "Spool", msg->nameLength);

    switch (context->selectorIndex) {
        case SPOOL_DEPOSIT:
            strlcpy(msg->version, "Deposit", msg->versionLength);
            break;
        case SPOOL_CLAIM:
        case SPOOL_CONTROLLER_REWARDS:
        case SPOOL_STAKING_REWARDS:
        case SPOOL_GET_REWARDS:
            strlcpy(msg->version, "Claim Rewards", msg->versionLength);
            break;
        case SPOOL_WITHDRAW_FAST:
            strlcpy(msg->version, "Fast withdraw", msg->versionLength);
            break;
        case SPOOL_WITHDRAW:
            strlcpy(msg->version, "Withdraw", msg->versionLength);
            break;
        case SPOOL_CREATE_VAULT:
            strlcpy(msg->version, "Creating spool", msg->versionLength);
            break;
        case SPOOL_STAKE:
            strlcpy(msg->version, "Staking", msg->versionLength);
            break;
        case SPOOL_UNSTAKE:
            strlcpy(msg->version, "Unstaking", msg->versionLength);
            break;
        case SPOOL_COMPOUND:
            strlcpy(msg->version, "Compounding", msg->versionLength);
            break;
        case SPOOL_CLAIM_VESTING:
            strlcpy(msg->version, "Claim vesting", msg->versionLength);
            break;
        case SPOOL_ADD_TOKEN:
            strlcpy(msg->version, "Add reward token", msg->versionLength);
            break;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
