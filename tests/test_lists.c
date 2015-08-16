/*
 * Copyright (C) 2015 Deutsche Telekom AG.
 *
 * Author: Mislav Novakovic <mislav.novakovic@sartura.hr>
 * Author: Luka Perkov <luka.perkov@sartura.hr>
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

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmocka.h>

#include <libyang/libyang.h>

#include "../src/configctl.h"
#include "../src/internal.h"

struct configctl *ctx = NULL;

#define _STRINGIZE(s) #s
#define _STRINGIFY(s) _STRINGIZE(s)

#define CONFIG_FILE	_STRINGIFY(PROJECT_LOCATION) "/tests/config/hello.xml"
#define YIN_FILE	_STRINGIFY(PROJECT_LOCATION) "/tests/config/hello@2015-06-08.yin"
#define YIN_FOLDER	_STRINGIFY(PROJECT_LOCATION) "/tests/config/"

static int setup_f()
{
	int rc;

#ifndef PROJECT_LOCATION
	return -1;
#endif

	ctx = calloc(1, sizeof(struct configctl));
	if (!ctx)
		return -1;

	rc = configctl_init(ctx, CONFIG_FILE, YIN_FILE, YIN_FOLDER);
	if (rc)
		return -1;

	return 0;
}

static int teardown_f()
{
	configctl_destroy(ctx);
	return 0;
}

static void test_get_list_leaf_name()
{
	const char *result = configctl_get_string(ctx, "hello/person/foo/foo2/name");
	assert_string_equal("foo", result);
}

static void test_get_list_leaf_age()
{
	int32_t result = configctl_get_int32(ctx, "hello/person/foo/foo2/age");
	assert_int_equal(20, result);
}

static void test_del_list_leaf_element()
{
	int rc = configctl_delete_element(ctx, "hello/person/foo/foo2/name");
	if (rc)
		fail();

	const char *result = configctl_get_string(ctx, "hello/person/foo/foo2/name");
	if (result)
		fail();
}


int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test_setup_teardown(test_get_list_leaf_name, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_get_list_leaf_age, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_del_list_leaf_element, setup_f, teardown_f),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
