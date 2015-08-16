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

static void test_invalid_container_name()
{
	int rc = configctl_set_string(ctx, "hello_wrong/toto", "text");
	if (!rc)
		fail();
}

static void test_invalid_leaf_name()
{
	int rc = configctl_set_uint64(ctx, "hello/wrong_number" , 12);
	if (!rc)
		fail();
}


static void test_invalid_number_32()
{
	int rc = configctl_set_int32(ctx, "hello/number8" , 1234);
	if (!rc)
		fail();
}

static void test_invalid_number_64()
{
	int rc = configctl_set_uint64(ctx, "hello/number8" , 12);
	if (!rc)
		fail();
}

static void test_invalid_string()
{
	int rc = configctl_set_string(ctx, "hello/wrong_number" , "12");
	if (!rc)
		fail();
}

/* TODO fix memory leak when creating string node in number node
static void test_invalid_string_todo()
{
	int rc = configctl_set_string(ctx, "hello/number8" , "12");
	if (!rc)
		fail();
}
*/

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test_setup_teardown(test_invalid_container_name, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_invalid_leaf_name, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_invalid_number_32, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_invalid_number_64, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_invalid_string, setup_f, teardown_f),
		//cmocka_unit_test_setup_teardown(test_invalid_string_todo, setup_f, teardown_f),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
