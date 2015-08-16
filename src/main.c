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
#include <getopt.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/times.h>
#include <string.h>
#include <libgen.h>

#include <libyang/libyang.h>

#include "configctl.h"
#include "edit.h"
#include "functions.h"
#include "git.h"
#include "internal.h"

struct ly_ctx *libyang = NULL;

static void usage(const char *name)
{
	printf("Usage: %s [-h] [-c file] [-y file] [-e location] [-p dir]\n\n", name);
	printf(" -c, --config   Set config file (required)\n");
	printf(" -y, --model    Set yang model (required)\n");
	printf(" -e, --editor   Set editor (required)\n");
	printf(" -p, --path     Set yang model search path\n");
	printf(" -h, --help     Show this text\n");
}

int main(int argc, char **argv)
{
	char *config_file = NULL, *yang_file = NULL, *yang_folder = NULL, *editor = NULL;
	struct configctl *ctx = NULL;
	int c;

	int opt_i;
	struct option opt[] = {
		{ "help", no_argument, 0, 'h' },
		{ "config", required_argument, 0, 'c' },
		{ "yang", required_argument, 0, 'y' },
		{ "path", required_argument, 0, 'p' },
		{ "editor", required_argument, 0, 'e' },
		{ 0, 0, 0, 0 }
	};

	while ((c = getopt_long(argc, argv, "c:y:p:e:h", opt, &opt_i)) != -1) {
		switch (c) {
		case 'c':
			config_file = optarg;
			break;
		case 'y':
			yang_file = optarg;
			break;
		case 'p':
			yang_folder = optarg;
			break;
		case 'e':
			editor = optarg;
			break;
		case 'h':
		default:
			usage(argv[0]);
			return -1;
		}
	}

	if (!config_file || !yang_file || !editor) {
		usage(argv[0]);
		return -1;
	}

	ctx = calloc(1, sizeof(struct configctl));
	if (!ctx)
		return -1;

	if (configctl_init(ctx, config_file, yang_file, yang_folder))
		goto error;

	if (configctl_validate(ctx, ctx->config))
		goto error;

	#ifdef GIT
	int rc = configctl_git_open();
	if (rc)
		goto error;
	#endif

	open_config_file(ctx, editor, ctx->config);

	#ifdef GIT
	configctl_git_destroy();
	#endif

	configctl_destroy(ctx);

	return 0;

error:
	usage(argv[0]);

	configctl_destroy(ctx);

	return -1;
}
