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
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#include <libyang/libyang.h>

#include "configctl.h"
#include "edit.h"
#include "functions.h"
#include "git.h"
#include "internal.h"

int configctl_get_int8(struct configctl *ctx, char *path, int8_t *value)
{
	struct lyd_node_leaf_list *result = NULL;

	if (check(ctx))
		return -1;

	result = (struct lyd_node_leaf_list *) get_node(ctx->root, path);
	if (!result)
		return -1;

	if (result->value_type == LY_TYPE_INT8) {
		*value = result->value.int8;
		return 0;
	}

	return -1;
}

int configctl_get_int16(struct configctl *ctx, char *path, int16_t *value)
{
	struct lyd_node_leaf_list *result = NULL;

	if (check(ctx))
		return -1;

	result = (struct lyd_node_leaf_list *) get_node(ctx->root, path);
	if (!result)
		return -1;

	if (result->value_type == LY_TYPE_INT16) {
		*value = result->value.int16;
		return 0;
	}

	return -1;
}

int configctl_get_int32(struct configctl *ctx, char *path, int32_t *value)
{
	struct lyd_node_leaf_list *result = NULL;

	if (check(ctx))
		return -1;

	result = (struct lyd_node_leaf_list *) get_node(ctx->root, path);
	if (!result)
		return -1;

	if (result->value_type == LY_TYPE_INT32) {
		*value = result->value.int32;
		return 0;
	}

	return -1;
}

int configctl_get_int64(struct configctl *ctx, char *path, int64_t *value)
{
	struct lyd_node_leaf_list *result = NULL;

	if (check(ctx))
		return -1;

	result = (struct lyd_node_leaf_list *) get_node(ctx->root, path);
	if (!result)
		return -1;

	if (result->value_type == LY_TYPE_INT64) {
		*value = result->value.int64;
		return 0;
	}

	return -1;
}

int configctl_get_uint8(struct configctl *ctx, char *path, uint8_t *value)
{
	struct lyd_node_leaf_list *result = NULL;

	if (check(ctx))
		return -1;

	result = (struct lyd_node_leaf_list *) get_node(ctx->root, path);
	if (!result)
		return -1;

	if (result->value_type == LY_TYPE_UINT8) {
		*value = result->value.uint8;
		return 0;
	}

	return -1;
}

int configctl_get_uint16(struct configctl *ctx, char *path, uint16_t *value)
{
	struct lyd_node_leaf_list *result = NULL;

	if (check(ctx))
		return -1;

	result = (struct lyd_node_leaf_list *) get_node(ctx->root, path);
	if (!result)
		return -1;

	if (result->value_type == LY_TYPE_UINT16) {
		*value = result->value.uint16;
		return 0;
	}

	return -1;
}

int configctl_get_uint32(struct configctl *ctx, char *path, uint32_t *value)
{
	struct lyd_node_leaf_list *result = NULL;

	if (check(ctx))
		return -1;

	result = (struct lyd_node_leaf_list *) get_node(ctx->root, path);
	if (!result)
		return -1;

	if (result->value_type == LY_TYPE_UINT32) {
		*value = result->value.uint32;
		return 0;
	}

	return -1;
}

int configctl_get_uint64(struct configctl *ctx, char *path, uint64_t *value)
{
	struct lyd_node_leaf_list *result = NULL;

	if (check(ctx))
		return -1;

	result = (struct lyd_node_leaf_list *) get_node(ctx->root, path);
	if (!result)
		return -1;

	if (result->value_type == LY_TYPE_UINT64) {
		*value = result->value.uint64;
		return 0;
	}

	return -1;
}

int configctl_set_int8(struct configctl *ctx, const char *location, int8_t value)
{
	union lyd_value_u val;

	val.int8 = value;
	int rc = configctl_set_leaf(ctx, location, LY_TYPE_INT8, val);
	if (rc)
		return -1;

	return 0;
}

int configctl_set_int16(struct configctl *ctx, const char *location, int16_t value)
{
	union lyd_value_u val;

	val.int16 = value;
	int rc = configctl_set_leaf(ctx, location, LY_TYPE_INT16, val);
	if (rc)
		return -1;

	return 0;
}

int configctl_set_int32(struct configctl *ctx, const char *location, int32_t value)
{
	union lyd_value_u val;

	val.int32 = value;
	int rc = configctl_set_leaf(ctx, location, LY_TYPE_INT32, val);
	if (rc)
		return -1;

	return 0;
}

int configctl_set_int64(struct configctl *ctx, const char *location, int64_t value)
{
	union lyd_value_u val;

	val.int64 = value;
	int rc = configctl_set_leaf(ctx, location, LY_TYPE_INT64, val);
	if (rc)
		return -1;

	return 0;
}

int configctl_set_uint8(struct configctl *ctx, const char *location, uint8_t value)
{
	union lyd_value_u val;

	val.uint8 = value;
	int rc = configctl_set_leaf(ctx, location, LY_TYPE_UINT8, val);
	if (rc)
		return -1;

	return 0;
}

int configctl_set_uint16(struct configctl *ctx, const char *location, uint16_t value)
{
	union lyd_value_u val;

	val.uint16 = value;
	int rc = configctl_set_leaf(ctx, location, LY_TYPE_UINT16, val);
	if (rc)
		return -1;

	return 0;
}

int configctl_set_uint32(struct configctl *ctx, const char *location, uint32_t value)
{
	union lyd_value_u val;

	val.uint32 = value;
	int rc = configctl_set_leaf(ctx, location, LY_TYPE_UINT32, val);
	if (rc)
		return -1;

	return 0;
}

int configctl_set_uint64(struct configctl *ctx, const char *location, uint64_t value)
{
	union lyd_value_u val;

	val.uint64 = value;
	int rc = configctl_set_leaf(ctx, location, LY_TYPE_UINT64, val);
	if (rc)
		return -1;

	return 0;
}

int configctl_set_string(struct configctl *ctx, const char *location, const char *value)
{
	union lyd_value_u val;

	val.string = value;
	int rc = configctl_set_leaf(ctx, location, LY_TYPE_STRING, val);
	if (rc)
		return -1;

	return 0;
}

int configctl_delete_element(struct configctl *ctx, const char *path)
{
	struct lyd_node *node = NULL;

	if (check(ctx))
		return -1;

	node = get_node(ctx->root, (char *) path);
	if (!node)
		return -1;

	// TODO delete list if key node is deleted
	lyd_free(node);

	return 0;
}

struct configctl *configctl_create()
{
	struct configctl *ctx = NULL;

	ctx = calloc(1, sizeof(struct configctl));
	return ctx;
}

int configctl_init(struct configctl *ctx, char *config_file, char *yang_file, char *yang_folder)
{
	char *schema = NULL, *config = NULL;
	struct stat sb;
	int fd = 0;

	ctx->yang_format = LYS_IN_YIN;
	ctx->in_format = LYD_XML;
	ctx->out_format = LYD_XML;

	if (!config_file || !yang_file)
		goto error;

	ctx->libyang = ly_ctx_new(yang_folder);

	if (!ctx->libyang)
		goto error;

	fd = open(yang_file, O_RDONLY);
	if (fd == -1) {
		__debug("fd is %d, the input file could not be opened (%s).\n", fd, strerror(errno));
		goto error;
	}

	if (fstat(fd, &sb) == -1) {
		__debug("unable to get input file information (%s).\n", strerror(errno));
		goto error;
	}

	if (!S_ISREG(sb.st_mode)) {
		__debug("input file not a file.\n");
		goto error;
	}

	schema = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	ctx->len_schema = sb.st_size;
	close(fd);


	fd = open(config_file, O_RDONLY);
	if (fd == -1) {
		__debug("fd is %d, the input file could not be opened (%s).\n", fd, strerror(errno));
		goto error;
	}

	if (fstat(fd, &sb) == -1) {
		__debug("unable to get input file information (%s).\n", strerror(errno));
		goto error;
	}

	if (!S_ISREG(sb.st_mode)) {
		__debug("input file not a file.\n");
		goto error;
	}

	config = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	ctx->len_config = sb.st_size;
	close(fd);

	ctx->config = config;
	ctx->schema = schema;

	if (configctl_validate(ctx, ctx->config))
		goto error;

	ctx->config_file = config_file;
	ctx->yang_file = yang_file;
	ctx->yang_folder = yang_folder;

	return 0;

error:

	if (schema)
		munmap(schema, sb.st_size);
	if (config)
		munmap(config, sb.st_size);

	if (fd != -1)
		close(fd);

	return -1;
}

int configctl_destroy(struct configctl *ctx)
{
	if (ctx->root)
		lyd_free(ctx->root);

	if (ctx->libyang)
		ly_ctx_destroy(ctx->libyang);

	if (ctx)
		free(ctx);

	return 0;
}

int configctl_commit(struct configctl *ctx)
{
	FILE *fp;

	if (check(ctx))
		return -1;

	fp = fopen(ctx->config_file, "w");

	if (fp == NULL) {
		__debug("can't open output file %s!\n", ctx->config_file);
	}

	lyd_print(fp, ctx->root, LYD_XML);

	fclose(fp);

	return 0;
}

const char *configctl_get_string(struct configctl *ctx, char *path)
{
	struct lyd_node_leaf_list *result = NULL;

	if (check(ctx))
		return NULL;

	result = (struct lyd_node_leaf_list *) get_node(ctx->root, path);

	if (!result)
		return NULL;

	return result->value_str;
}

int configctl_init_dir(char *path)
{
#ifdef GIT
	return configctl_git_create_config_dir(path);
#else
	// TODO make directory
	return 0;
#endif
}
