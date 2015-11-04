/*
 * Copyright (C) 2015 Deutsche Telekom AG.
 *
 * Author: Mislav Novakovic <mislav.novakovic@sartura.hr>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/times.h>
#include <string.h>
#include <libgen.h>
#include <limits.h>
#include <inttypes.h>

#include <libyang/libyang.h>

#include "functions.h"
#include "internal.h"

int check(struct configctl *ctx)
{
	if (!ctx)
		return -1;
	if (!ctx->root)
		return -2;
	if (!ctx->libyang)
		return -3;

	return 0;
}

struct lyd_node *get_node(struct lyd_node *node, char *path)
{
	if (node->schema != NULL && ( node->schema->nodetype & (LYS_LEAF | LYS_LEAFLIST | LYS_CONTAINER))) {

		char *pch = NULL;
		struct lyd_node *tmp;
		char name[strlen(path)];
		pch = strchr(path, '/');

		if (!pch && strlen(path) > 0) {
			LY_TREE_FOR(node, tmp) {
				if (!strcmp(path, tmp->schema->name)) {
					return tmp;
				}
			}
			return NULL;
		}

		snprintf(name, (strlen(path) - strlen(pch) + 1), "%s", path);

		// TODO implement list handling for multiple keys
		LY_TREE_FOR(node, tmp) {
			if (tmp->schema->nodetype == LYS_LIST) {
				char *list = (pch + 1);
				char *pch_list = NULL;
				char name_list[strlen(list)];
				pch_list = strchr((list), '/');
				snprintf(name_list, (strlen(list) - strlen(pch_list) + 1), "%s", list);

				if (!strcmp(((struct lyd_node_leaf_list *) tmp->child)->value_str, name_list)) {
					return get_node(tmp->child, (pch_list + 1));
				} else {
					continue;
				}
			}
			if (!strcmp(name, tmp->schema->name))
				return get_node(tmp->child, (pch + 1));
		}
	}

	return NULL;
}

int configctl_validate(struct configctl *ctx, char *config)
{
	if (!config)
		return -1;

	if (!ctx->model)
		ctx->model = lys_parse(ctx->libyang, ctx->schema, ctx->yang_format);

	if (ctx->root)
		lyd_free(ctx->root);

	ctx->root = lyd_parse(ctx->libyang, config, ctx->in_format, LYD_OPT_STRICT);

	if (ctx->root == NULL) {
		__debug("Failed to parse data.");
		goto error;
	}

	return 0;

error:
	return -1;
}

int configctl_set_leaf(struct configctl *ctx, const char *location, LY_DATA_TYPE type, union lyd_value_u val)
{
	struct lyd_node_leaf_list *result = NULL;
	struct lyd_node *node = NULL;
	struct lyd_node *new = NULL;
	char *pch = NULL;
	char *name;
	char path[strlen(location)];
	int len = 0;

	if (check(ctx))
		return -1;

	// TODO preserve data order
	node = get_node(ctx->root, (char *) location);
	if (node)
		lyd_free(node);

	pch = strchr(location, '/');
	while (pch != NULL) {
		len = pch - location + 1;
		pch = strchr(pch + 1, '/');
	}

	if (!len)
		return -1;

	snprintf(path, len, "%s", location);
	name = (char *) (location + len);

	node = get_node(ctx->root, &path[0]);
	if (!node)
		return -1;

	if (type == LY_TYPE_STRING) {
		new = lyd_new_leaf(node, ctx->model, name, val.string);
	} else if (type == LY_TYPE_INT8) {
		int len = snprintf(NULL, 0, "%"PRId8, val.int8);
		char *value = malloc(sizeof(char) * (len + 1));
		snprintf(value, (len + 1), "%"PRId8, val.int8);
		new = lyd_new_leaf(node, ctx->model, name, value);
		free(value);
	} else if (type == LY_TYPE_INT16) {
		int len = snprintf(NULL, 0, "%"PRId16, val.int16);
		char *value = malloc(sizeof(char) * (len + 1));
		snprintf(value, (len + 1), "%"PRId16, val.int16);
		new = lyd_new_leaf(node, ctx->model, name, value);
		free(value);
	} else if (type == LY_TYPE_INT32) {
		int len = snprintf(NULL, 0, "%"PRId32, val.int32);
		char *value = malloc(sizeof(char) * (len + 1));
		snprintf(value, (len + 1), "%"PRId32, val.int32);
		new = lyd_new_leaf(node, ctx->model, name, value);
		free(value);
	} else if (type == LY_TYPE_INT64) {
		int len = snprintf(NULL, 0, "%"PRId64, val.int64);
		char *value = malloc(sizeof(char) * (len + 1));
		snprintf(value, (len + 1), "%"PRId64, val.int64);
		new = lyd_new_leaf(node, ctx->model, name, value);
		free(value);
	} else if (type == LY_TYPE_UINT8) {
		int len = snprintf(NULL, 0, "%"PRIu8, val.uint8);
		char *value = malloc(sizeof(char) * (len + 1));
		snprintf(value, (len + 1), "%"PRIu8, val.uint8);
		new = lyd_new_leaf(node, ctx->model, name, value);
		free(value);
	} else if (type == LY_TYPE_UINT16) {
		int len = snprintf(NULL, 0, "%"PRIu16, val.uint16);
		char *value = malloc(sizeof(char) * (len + 1));
		snprintf(value, (len + 1), "%"PRIu16, val.uint16);
		new = lyd_new_leaf(node, ctx->model, name, value);
		free(value);
	} else if (type == LY_TYPE_UINT32) {
		int len = snprintf(NULL, 0, "%"PRIu32, val.uint32);
		char *value = malloc(sizeof(char) * (len + 1));
		snprintf(value, (len + 1), "%"PRIu32, val.uint32);
		new = lyd_new_leaf(node, ctx->model, name, value);
		free(value);
	} else if (type == LY_TYPE_UINT64) {
		int len = snprintf(NULL, 0, "%"PRIu64, val.uint64);
		char *value = malloc(sizeof(char) * (len + 1));
		snprintf(value, (len + 1), "%"PRIu64, val.uint64);
		new = lyd_new_leaf(node, ctx->model, name, value);
		free(value);
	}

	if (!new)
		return -1;

	result = (struct lyd_node_leaf_list *) new;
	if (!result ||  ((struct lys_node_leaflist *) result->schema)->type.base != type) {
		lyd_free(new);
		return -1;
	}

	return 0;
}
