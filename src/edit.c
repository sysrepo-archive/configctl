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
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#include <libyang/libyang.h>

#include "edit.h"
#include "functions.h"
#include "git.h"
#include "internal.h"

static char *prompt_and_read(const char * prompt)
{
	char *response;
	char *bufsize;

	printf("%s", prompt);
	asprintf(&bufsize, "%%%us", BUFSIZ);

	if ((response = malloc(BUFSIZ + 1)) == NULL) {
		__debug("out of memory\n");
		exit(1);
	 }

	scanf(bufsize, response);
	free(bufsize);

	return response;
}

static int save_file(char *config_file, char *config)
{

	if (!config)
		return -1;

	if (!config_file)
		return -1;

	int status;

	status = remove(config_file);

	if (status)
		return 1;

	FILE *f = fopen(config_file, "w");
	if (f == NULL) {
		__debug("Error opening file %s!\n", config_file);
		return 1;
	}

	fprintf(f, "%s", config);

	fclose(f);
#ifdef GIT
	configctl_git_commit(config_file);
#endif

	return 0;
}

int open_config_file(struct configctl *ctx, char *editor, char *config)
{
	int len = strlen(config);
	char file_name[22];
	char buffer[len];
	char *input = NULL;
	int fd;

	memset(file_name, 0, sizeof(file_name));
	memset(buffer, 0, sizeof(buffer));

	strncpy(file_name, "/tmp/configctl-XXXXXX", 21);
	strncpy(buffer, config, (len + 1));

	errno = 0;
	fd = mkstemp(file_name);

	if (fd < 1) {
		__debug("creation of temp file failed with error [%s]\n", strerror(errno));
		return 1;
	} else {
		__debug("temporary file [%s] created\n", file_name);
	}

	errno = 0;
	if (-1 == write(fd, buffer, sizeof(buffer))) {
		__debug("write failed with error [%s]\n", strerror(errno));
		return 1;
	}

	while (1) {
		pid_t pid=fork();
		if (0 == pid) {
			execv(editor, (char *[]) { editor, file_name, NULL });
			exit(127);
		} else {
			waitpid(pid, 0, 0);
		}

		memset(buffer, 0, sizeof(buffer));

		errno = 0;
		len = lseek(fd, 0, SEEK_END);
		if (-1 == len) {
			__debug("lseek failed with error [%s]\n", strerror(errno));
			return 1;
		}

		if (-1 == lseek(fd, 0, SEEK_SET)) {
			__debug("lseek failed with error [%s]\n", strerror(errno));
			return 1;
		}

		if ((read(fd, buffer, len)) < 0 ) {
			__debug("read failed with error\n");
			break;
		}

		if (!configctl_validate(ctx, buffer))
			break;

		while (1) {
			input = prompt_and_read("\nInvalid data! Do you want to discard changes? y/n\n");

			if (!strncasecmp(input, "y", 1)) {
				free(input);
				unlink(file_name);
				return open_config_file(ctx, editor, config);
			} else {
				free(input);
				break;
			}
		}
	}

	while (1) {
		input = prompt_and_read("Do you wish to quit and save your new configuration? y/n\n");

		if (!strncasecmp(input, "y", 1)) {
			free(input);
			unlink(file_name);
			save_file(ctx->config_file, buffer);
			break;
		} else {
			free(input);
			return open_config_file(ctx, editor, buffer);
		}
	}

	return 0;
}
