#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

#define PARAMETER_LENGTH 32
#define SELECTOR_SIZE    4

#define RUN_APPLICATION 1

#define NUM_SPOOL_SELECTORS 14

#define PLUGIN_NAME "Spool"

#define TOKEN_SENT_FOUND     1
#define TOKEN_RECEIVED_FOUND 1 << 1

typedef enum {
    SPOOL_DEPOSIT,
    SPOOL_CLAIM,
    SPOOL_GET_REWARDS,
    SPOOL_WITHDRAW_FAST,
    SPOOL_WITHDRAW,
    SPOOL_CREATE_VAULT,
    SPOOL_CONTROLLER_REWARDS,
    SPOOL_STAKE,
    SPOOL_UNSTAKE,
    SPOOL_STAKING_REWARDS,
    SPOOL_COMPOUND,
    SPOOL_CLAIM_VESTING,
    SPOOL_ADD_TOKEN,
    SPOOL_APPROVE
} spoolSelector_t;

extern const uint8_t *const SPOOL_SELECTORS[NUM_SPOOL_SELECTORS];

typedef enum {
    PATHS_OFFSET,
    PATHS_LEN,
    AMOUNT_SENT,
    TOKEN_SENT,
    ADDRESS,
    ALLOWANCE,
    NONE,
} parameter;

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct spool_parameters_t {
    // transaction parsing
    uint8_t amount_sent[INT256_LENGTH];
    uint8_t token_address[ADDRESS_LENGTH];

    // token querying
    uint8_t token_found;
    uint8_t decimals;
    char ticker[MAX_TICKER_LEN];

    // parameter positioning
    uint8_t offset;
    uint8_t next_param;
    uint8_t selectorIndex;

} spool_parameters_t;

void handle_init_contract(void *parameters);
void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);