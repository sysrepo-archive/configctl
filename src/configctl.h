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

#ifndef __API_H__
#define __API_H__

#include <sys/stat.h>

#include <libyang/tree_data.h>
#include <libyang/tree_schema.h>
#include <libyang/libyang.h>

struct configctl {
	char *config_file;
	char *yang_file;
	char *yang_folder;
	LYS_INFORMAT yang_format;
	LYD_FORMAT in_format;
	LYD_FORMAT out_format;

	struct ly_ctx *libyang;
	struct lyd_node *root;
	struct lys_module *model;

	char *config;
	size_t len_config;
	char *schema;
	size_t len_schema;
};

struct configctl *configctl_create();
int configctl_init(struct configctl *ctx, char *config_file, char *yang_file, char *yang_folder);
int configctl_destroy(struct configctl *ctx);

int configctl_validate(struct configctl *ctx, char *config);

const char *configctl_get_string(struct configctl *ctx, char *path);
int8_t	    configctl_get_int8  (struct configctl *ctx, char *path);
int16_t     configctl_get_int16 (struct configctl *ctx, char *path);
int32_t     configctl_get_int32 (struct configctl *ctx, char *path);
int64_t     configctl_get_int64 (struct configctl *ctx, char *path);
uint8_t     configctl_get_uint8 (struct configctl *ctx, char *path);
uint16_t    configctl_get_uint16(struct configctl *ctx, char *path);
uint32_t    configctl_get_uint32(struct configctl *ctx, char *path);
uint64_t    configctl_get_uint64(struct configctl *ctx, char *path);

int configctl_set_string(struct configctl *ctx, const char *location, const char *value);
int configctl_set_int8  (struct configctl *ctx, const char *location, int8_t      value);
int configctl_set_int16 (struct configctl *ctx, const char *location, int16_t     value);
int configctl_set_int32 (struct configctl *ctx, const char *location, int32_t     value);
int configctl_set_int64 (struct configctl *ctx, const char *location, int64_t     value);
int configctl_set_uint8 (struct configctl *ctx, const char *location, uint8_t     value);
int configctl_set_uint16(struct configctl *ctx, const char *location, uint16_t    value);
int configctl_set_uint32(struct configctl *ctx, const char *location, uint32_t    value);
int configctl_set_uint64(struct configctl *ctx, const char *location, uint64_t    value);

int configctl_commit(struct configctl *ctx);
int configctl_delete_element(struct configctl *ctx, const char *path);

int configctl_init_dir(char *path);

#endif /* __API_H__ */
