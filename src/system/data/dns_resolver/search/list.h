/*
 * telekom / sysrepo-plugin-system
 *
 * This program is made available under the terms of the
 * BSD 3-Clause license which is available at
 * https://opensource.org/licenses/BSD-3-Clause
 *
 * SPDX-FileCopyrightText: 2022 Deutsche Telekom AG
 * SPDX-FileContributor: Sartura Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef SYSTEM_PLUGIN_DATA_DNS_RESOLVER_SEARCH_LIST_H
#define SYSTEM_PLUGIN_DATA_DNS_RESOLVER_SEARCH_LIST_H

#include "types.h"

void system_dns_search_list_init(system_dns_search_element_t **head);
int system_dns_search_list_add(system_dns_search_element_t **head, system_dns_search_t search);
system_dns_search_element_t *system_dns_search_list_find(system_dns_search_element_t *head, const char *domain);
int system_dns_search_list_remove(system_dns_search_element_t **head, const char *domain);
int system_dns_search_element_cmp_fn(void *e1, void *e2);
void system_dns_search_list_free(system_dns_search_element_t **head);

#endif // SYSTEM_PLUGIN_DATA_DNS_RESOLVER_SEARCH_LIST_H