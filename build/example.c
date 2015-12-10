// gcc -I ../src -L . -lconfigctl example.c -o example
// export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
// ./example

#include <stdio.h>
#include <stdlib.h>

#include <configctl.h>

int main(int argc, char **argv)
{
	struct configctl *ctx = NULL;
	const char *result_string;
	int32_t result_int32;
	int rc;

	ctx = calloc(1, sizeof(struct configctl));
	if (!ctx)
		return -1;

	rc = configctl_init(ctx, "../tests/config/hello.xml", "../tests/config/hello@2015-06-08.yin", "../tests/config/");
	if (rc) {
		printf("error in configctl_init()\n");
		return -1;
	}

	result_string = configctl_get_string(ctx, "hello/foo");
	if (!result_string) {
		printf("error in configctl_get_string()\n");
		return -1;
	}

	printf("hello/foo: '%s'\n", result_string);

	rc = configctl_get_int32(ctx, "hello/bar", &result_int32);
	if (!rc)
		printf("hello/bar: '%d'\n", result_int32);

	rc = configctl_set_int32(ctx, "hello/bar", 50);
	if (rc) {
		printf("error in configctl_set_int32()\n");
		return -1;
	}

	rc = configctl_get_int32(ctx, "hello/bar", &result_int32);
	if (!rc) {
		if (result_int32 != 50) {
			printf("error in configctl_get_int32()\n");
		}
	}

	printf("hello/bar: '%d'\n", result_int32);

	configctl_destroy(ctx);

	return 0;
}
