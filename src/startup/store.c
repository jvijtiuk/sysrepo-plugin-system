#include "store.h"
#include "common.h"
#include "ly_tree.h"

// API for getting system data
#include "api/dns_resolver/search.h"
#include "api/dns_resolver/server.h"
#include "api/ntp/server.h"

// data manipulation
#include "data/ip_address.h"
#include "data/dns_resolver/search/list.h"
#include "data/dns_resolver/server/list.h"
#include "srpc/ly_tree.h"
#include "srpc/types.h"

#include <sysrepo.h>
#include <unistd.h>
#include <errno.h>

#include <sysrepo.h>

#include <srpc.h>

#include <utlist.h>

static int system_startup_store_hostname(void *priv, const struct lyd_node *system_container_node);
static int system_startup_store_contact(void *priv, const struct lyd_node *system_container_node);
static int system_startup_store_location(void *priv, const struct lyd_node *system_container_node);

int system_startup_store_data(system_ctx_t *ctx, sr_session_ctx_t *session)
{
	int error = 0;
	sr_data_t *subtree = NULL;

	error = sr_get_subtree(session, SYSTEM_SYSTEM_CONTAINER_YANG_PATH, 0, &subtree);
	if (error) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "sr_get_subtree() error (%d): %s", error, sr_strerror(error));
		goto error_out;
	}

	srpc_startup_store_t store_values[] = {
		{
			"hostname",
			system_startup_store_hostname,
		},
		{
			"contact",
			system_startup_store_contact,
		},
		{
			"location",
			system_startup_store_location,
		},
	};

	for (size_t i = 0; i < ARRAY_SIZE(store_values); i++) {
		const srpc_startup_store_t *store = &store_values[i];

		error = store->cb(ctx, subtree->tree);
		if (error) {
			SRPLG_LOG_ERR(PLUGIN_NAME, "Startup store callback failed for value %s", store->name);
			goto error_out;
		}
	}

	goto out;

error_out:
	error = -1;

out:
	if (subtree) {
		sr_release_data(subtree);
	}

	return error;
}

static int system_startup_store_hostname(void *priv, const struct lyd_node *system_container_node)
{
	int error = 0;

	return error;
}

static int system_startup_store_contact(void *priv, const struct lyd_node *system_container_node)
{
	int error = 0;

	return error;
}

static int system_startup_store_location(void *priv, const struct lyd_node *system_container_node)
{
	int error = 0;

	return error;
}