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

#ifndef __INTERNAL_H__
#define __INTERNAL_H__

#define PROJECT_NAME "configctl"

#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

#ifdef DEBUG
# define __debug(fmt, ...) do { \
		fprintf(stderr, "%s: %s: %s (%d): " fmt "\n", PROJECT_NAME, __FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__); \
	} while (0)
#else
# define __debug(fmt, ...) do { } while (0)
#endif

#endif /* __INTERNAL_H__ */
