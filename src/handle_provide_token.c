#include "spool_plugin.h"

void handle_provide_token(ethPluginProvideInfo_t *msg) {
    spool_parameters_t *context = (spool_parameters_t *) msg->pluginContext;
    PRINTF("IN PROVIDE TOKEN: %d\n", msg->item1);
    if (msg->item1) {
        // The Ethereum App found the information for the requested token!
        // Store its decimals.
        context->decimals = msg->item1->token.decimals;
        // Store its ticker.
        strlcpy(context->ticker, (char *) msg->item1->token.ticker, sizeof(context->ticker));
        // Keep track that we found the token.
        context->token_found = true;
    } else {
        // The Ethereum App did not manage to find the info for the requested token.
        context->token_found = false;
        // Default to ETH decimals (for wei).
        context->decimals = 18;
        // Default to "???" when information was not found.
        strlcpy(context->ticker, "???", sizeof(context->ticker));
        // If we wanted to add a screen, say a warning screen for example, we could instruct the
        // ethereum app to add an additional screen by setting `msg->additionalScreens` here, just
        // like so:
        // msg->additionalScreens = 1;
    }

    PRINTF("PROVIDE TOKEN RESULT: %d\n", context->token_found);

    msg->result = ETH_PLUGIN_RESULT_OK;
}
