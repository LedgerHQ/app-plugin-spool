#include "spool_plugin.h"

void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    const spool_parameters_t *context = (spool_parameters_t *) msg->pluginContext;

    strlcpy(msg->name, "Spool", msg->nameLength);

    switch (context->selectorIndex) {
        case SPOOL_DEPOSIT:
        case SPOOL_V2_DEPOSIT:
            strlcpy(msg->version, "Deposit", msg->versionLength);
            break;
        case SPOOL_CLAIM:
        case SPOOL_CONTROLLER_REWARDS:
        case SPOOL_STAKING_REWARDS:
        case SPOOL_GET_REWARDS:
        case SPOOL_V2_CLAIM_REWARD:
            strlcpy(msg->version, "Claim Rewards", msg->versionLength);
            break;
        case SPOOL_WITHDRAW_FAST:
            strlcpy(msg->version, "Fast withdraw", msg->versionLength);
            break;
        case SPOOL_WITHDRAW:
            strlcpy(msg->version, "Withdraw", msg->versionLength);
            break;
        case SPOOL_CREATE_VAULT:
        case SPOOL_V2_DEPLOY_VAULT:
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
        case SPOOL_V2_REDEEM_FAST:
            strlcpy(msg->version, "Fast redeem", msg->versionLength);
            break;
        case SPOOL_V2_REDEEM:
            strlcpy(msg->version, "Redeem", msg->versionLength);
            break;
        case SPOOL_V2_CLAIM_WITHDRAWAL:
            strlcpy(msg->version, "Claim withdrawal", msg->versionLength);
            break;
        case SPOOL_V2_ADD_TOKEN:
            strlcpy(msg->version, "Add incentive", msg->versionLength);
            break;
        case SPOOL_V2_EXTEND_REWARD:
            strlcpy(msg->version, "Extend reward", msg->versionLength);
            break;
        case SPOOL_V2_SWAP_AND_DEPOSIT:
            strlcpy(msg->version, "Swap and deposit", msg->versionLength);
            break;
        default:
            PRINTF("Unhandled selectorIndex %d\n", context->selectorIndex);
            strlcpy(msg->version, "Error, no selector", msg->versionLength);
            break;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
