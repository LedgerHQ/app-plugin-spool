#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

#define PARAMETER_LENGTH 32
#define SELECTOR_SIZE    4

#define RUN_APPLICATION 1

// Number of selectors defined in this plugin. Should match the enum `selector_t`.
#define NUM_SPOOL_SELECTORS 13

// Name of the plugin.
#define PLUGIN_NAME "Spool"

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
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
} spoolSelector_t;

// Enumeration used to parse the smart contract data.
typedef enum {
    PATHS_OFFSET,
    AMOUNT_SENT,
    ADDRESS,
    NONE,
} parameter;

extern const uint8_t *const SPOOL_SELECTORS[NUM_SPOOL_SELECTORS];

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct spool_parameters_t {
    // transaction parsing
    uint8_t amount_sent[INT256_LENGTH];
    uint8_t token_address[ADDRESS_LENGTH];

    // token querying
    uint8_t token_found;
    uint8_t decimals;
    char ticker[MAX_TICKER_LEN];

    // For parsing data.
    uint8_t next_param;  // Set to be the next param we expect to parse.
    uint16_t offset;     // Offset at which the array or struct starts.
    bool go_to_offset;   // If set, will force the parsing to iterate through parameters until
                         // `offset` is reached.

    // For both parsing and display.
    selector_t selectorIndex;
} spool_parameters_t;

// Piece of code that will check that the above structure is not bigger than 5 * 32. Do not remove
// this check.
_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");

void handle_init_contract(void *parameters);
void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);