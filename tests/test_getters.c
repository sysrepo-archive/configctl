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

static void test_get_leaf_foo_string()
{
	const char *result = configctl_get_string(ctx, "hello/foo");
	if (!result)
		fail();

	assert_string_equal("text", result);
}

static void test_get_leaf_bar_string()
{
	const char *result = configctl_get_string(ctx, "hello/bar");
	if (!result)
		fail();

	assert_string_equal("1234", result);
}

static void test_get_leaf_bar_int()
{
	int rc;
	int32_t result;
	rc = configctl_get_int32(ctx, "hello/bar", &result);
	if (rc)
		fail();

	assert_int_equal(1234, result);
}

static void test_get_int_8()
{
	int rc;
	int8_t result;
	rc = configctl_get_int8(ctx, "hello/numbers/number_8", &result);
	if (rc)
		fail();

	assert_int_equal(1,  (int) result);
}

static void test_get_int_16()
{
	int rc;
	int16_t result;
	rc = configctl_get_int16(ctx, "hello/numbers/number_16", &result);
	if (rc)
		fail();

	assert_int_equal(1, result);
}

static void test_get_int_32()
{
	int rc;
	int32_t result;
	rc = configctl_get_int32(ctx, "hello/numbers/number_32", &result);
	if (rc)
		fail();

	assert_int_equal(1, result);
}

static void test_get_int_64()
{
	int rc;
	int64_t result;
	rc = configctl_get_int64(ctx, "hello/numbers/number_64", &result);
	if (rc)
		fail();

	assert_int_equal(1, result);
}

static void test_get_uint_8()
{
	int rc;
	uint8_t result;
	rc = configctl_get_uint8(ctx, "hello/numbers/number_u8", &result);
	if (rc)
		fail();

	assert_int_equal(1,  (int) result);
}

static void test_get_uint_16()
{
	int rc;
	uint16_t result;
	rc = configctl_get_uint16(ctx, "hello/numbers/number_u16", &result);
	if (rc)
		fail();

	assert_int_equal(1, result);
}

static void test_get_uint_32()
{
	int rc;
	uint32_t result;
	rc = configctl_get_uint32(ctx, "hello/numbers/number_u32", &result);
	if (rc)
		fail();

	assert_int_equal(1, result);
}

static void test_get_uint_64()
{
	int rc;
	uint64_t result;
	rc = configctl_get_uint64(ctx, "hello/numbers/number_u64", &result);
	if (rc)
		fail();

	assert_int_equal(1, result);
}

static void test_failed_get_int_8()
{
	int rc;
	int8_t result;
	rc = configctl_get_int8(ctx, "hello/numbers/new_number_8", &result);
	if (!rc)
		fail();
}

static void test_failed_get_int_16()
{
	int rc;
	int16_t result;
	rc = configctl_get_int16(ctx, "hello/numbers/new_number_16", &result);
	if (!rc)
		fail();
}

static void test_failed_get_int_32()
{
	int rc;
	int32_t result;
	rc = configctl_get_int32(ctx, "hello/numbers/new_number_32", &result);
	if (!rc)
		fail();
}

static void test_failed_get_int_64()
{
	int rc;
	int64_t result;
	rc = configctl_get_int64(ctx, "hello/numbers/new_number_64", &result);
	if (!rc)
		fail();
}

static void test_failed_get_uint_8()
{
	int rc;
	uint8_t result;
	rc = configctl_get_uint8(ctx, "hello/numbers/new_number_u8", &result);
	if (!rc)
		fail();
}

static void test_failed_get_uint_16()
{
	int rc;
	uint16_t result;
	rc = configctl_get_uint16(ctx, "hello/numbers/new_number_u16", &result);
	if (!rc)
		fail();
}

static void test_failed_get_uint_32()
{
	int rc;
	uint32_t result;
	rc = configctl_get_uint32(ctx, "hello/numbers/new_number_u32", &result);
	if (!rc)
		fail();
}

static void test_failed_get_uint_64()
{
	int rc;
	uint64_t result;
	rc = configctl_get_uint64(ctx, "hello/numbers/new_number_u64", &result);
	if (!rc)
		fail();
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test_setup_teardown(test_get_leaf_foo_string, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_get_leaf_bar_string, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_get_leaf_bar_int, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_get_int_8, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_get_int_16, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_get_int_32, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_get_int_64, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_get_uint_8, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_get_uint_16, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_get_uint_32, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_get_uint_64, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_failed_get_int_8, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_failed_get_int_16, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_failed_get_int_32, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_failed_get_int_64, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_failed_get_uint_8, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_failed_get_uint_16, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_failed_get_uint_32, setup_f, teardown_f),
		cmocka_unit_test_setup_teardown(test_failed_get_uint_64, setup_f, teardown_f),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
