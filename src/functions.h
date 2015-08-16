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

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <libyang/libyang.h>

#include "configctl.h"

int check(struct configctl *ctx);
char *ctl_get_parents_path(struct lyd_node *node);
struct lyd_node *get_node(struct lyd_node *node,char *path);
struct lyd_node_leaf_list *ctl_edit_number(struct configctl *ctx, char *path, int64_t value);
int configctl_set_leaf(struct configctl *ctx, const char *location, LY_DATA_TYPE type, union lyd_value_u val);
char *get_folder(char *path);

#endif /* __FUNCTIONS_H__ */
