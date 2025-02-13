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
#include "list.h"
#include "plugin/data/system/authentication/authorized_key.h"

#include <string.h>
#include <stdlib.h>
#include <utlist.h>

void system_authorized_key_list_init(system_authorized_key_element_t **head)
{
	*head = NULL;
}

int system_authorized_key_list_add(system_authorized_key_element_t **head, system_authorized_key_t key)
{
	system_authorized_key_element_t *new_el = (system_authorized_key_element_t *) malloc(sizeof(system_authorized_key_element_t));

	if (!new_el) {
		return -1;
	}

	// copy value
	system_authorized_key_init(&new_el->key);
	system_authorized_key_set_name(&new_el->key, key.name);
	system_authorized_key_set_algorithm(&new_el->key, key.algorithm);
	system_authorized_key_set_data(&new_el->key, key.data);

	// add to list
	LL_APPEND(*head, new_el);

	return 0;
}

system_authorized_key_element_t *system_authorized_key_list_find(system_authorized_key_element_t *head, const char *name)
{
	system_authorized_key_element_t *found = NULL;
	system_authorized_key_element_t el = {
		.key = {
			.name = (char *) name,
		},
	};

	LL_SEARCH(head, found, &el, system_authorized_key_element_cmp_fn);

	return found;
}

int system_authorized_key_list_remove(system_authorized_key_element_t **head, const char *name)
{
	system_authorized_key_element_t *found = system_authorized_key_list_find(*head, name);

	if (!found) {
		return -1;
	}

	// remove and free found element
	LL_DELETE(*head, found);
	system_authorized_key_free(&found->key);
	free(found);

	return 0;
}

int system_authorized_key_element_cmp_fn(void *e1, void *e2)
{
	system_authorized_key_element_t *s1 = (system_authorized_key_element_t *) e1;
	system_authorized_key_element_t *s2 = (system_authorized_key_element_t *) e2;

	return strcmp(s1->key.name, s2->key.name);
}

void system_authorized_key_list_free(system_authorized_key_element_t **head)
{
	system_authorized_key_element_t *iter_el = NULL, *tmp_el = NULL;

	LL_FOREACH_SAFE(*head, iter_el, tmp_el)
	{
		LL_DELETE(*head, iter_el);
		system_authorized_key_free(&iter_el->key);
		free(iter_el);
	}

	system_authorized_key_list_init(head);
}
