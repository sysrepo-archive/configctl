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

#ifdef GIT

#include <git2.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "internal.h"

#include "git.h"

git_signature *sign = NULL;
const char *sign_name = "Config Bot";
const char *sign_email = "bot@sysrepo.org";
const char *commit_message = "configctl inital commit";

// TODO: change to some other sane value
const char *repo_path = "/opt/git/configctl_test";
git_repository *repo = NULL;

static void check_error(int error_code, const char *action)
{
	const git_error *error = giterr_last();
	if (!error_code)
		return;

	__debug("Error %d %s - %s\n", error_code, action, (error && error->message) ? error->message : "???");
}

int configctl_git_open()
{
	int error;

	git_libgit2_init();
	error = git_repository_open(&repo, repo_path);
	check_error(error, "opening repository");

	return error;
}

void configctl_git_destroy()
{
	git_repository_free(repo);
	repo = NULL;
	git_libgit2_shutdown();
}

static struct git_commit *get_last_commit()
{
	int rc;
	git_commit * commit = NULL;
	git_oid oid_parent_commit;

	rc = git_reference_name_to_id( &oid_parent_commit, repo, "HEAD");
	if (0 == rc) {
		rc = git_commit_lookup( &commit, repo, &oid_parent_commit);
		if (0 == rc) {
			return commit;
		}
	}

	return NULL;
}

static char *get_file(char *path)
{
	char *file = NULL;
	char *pch = NULL;
	int len = 0;

	pch = strchr(path, '/');
	while (pch != NULL) {
		len = pch - path + 1;
		pch = strchr(pch + 1, '/');
	}
	file = (path + len);

	return file;
}

static int git_add(char *path)
{
	git_index *index;
	char *file;

	file = get_file(path);

	char *paths[] = {file};
	git_strarray array = {paths, 1};
	git_repository_index(&index, repo);

	git_index_add_all(index, &array, 0, NULL, NULL);
	git_index_write(index);
	git_index_free(index);

	return 0;
}

int configctl_git_commit(char *path)
{
	int rc;
	int git_status = -1;
	git_oid oid_blob;
	git_oid oid_tree;
	git_oid oid_commit;
	git_blob *blob;
	git_tree *tree_cmt;
	git_treebuilder *tree_bld;
	char *file;

	file = get_file(path);

#if 0
	// TODO: check if file is changed
	__debug("%s", file);
	git_diff_stats *stats;
	git_diff *diff;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	opts.pathspec.strings = &file;
	opts.pathspec.count = 1;
	rc = git_diff_index_to_workdir(&diff, repo, NULL, &opts);
	if(rc)
		goto error;
	int diff_num = git_diff_num_deltas(diff);
	__debug("%d", diff_num);

	git_diff_get_stats(&stats, diff);
	int x = git_diff_stats_files_changed(stats);
	__debug("%d", x);

	git_diff_free(diff);
#endif

	rc = git_add(file);
	if (rc)
		goto error;

	rc = git_blob_create_fromworkdir(&oid_blob, repo, file);
	if (rc)
		goto error;

	rc = git_blob_lookup(&blob, repo, &oid_blob);
	if (rc)
		goto error;

	rc = git_treebuilder_new(&tree_bld, repo, NULL );
	if (0 == rc) {
		rc = git_treebuilder_insert(NULL, tree_bld, file, &oid_blob, GIT_FILEMODE_BLOB);
		if (!rc) {
			rc = git_treebuilder_write(&oid_tree, tree_bld);
			if (!rc) {
				rc = git_tree_lookup(&tree_cmt, repo, &oid_tree);
				if (0 == rc) {
					git_commit *commit;
					commit = get_last_commit();
					git_signature_now(&sign, sign_name, sign_email);
					rc = git_commit_create(&oid_commit, repo, "HEAD", sign, sign, NULL,
						commit_message, tree_cmt, 1, (const struct git_commit **) &commit);
					if (!rc) {
						git_status = 0;
						__debug("successful git commit");
					}
					git_tree_free( tree_cmt );
					git_commit_free(commit);
					git_signature_free(sign);
				}
			}
		}
		git_treebuilder_free(tree_bld);
	}
	git_blob_free( blob );

error:
	return git_status;
}

static int create_initial_commit(git_repository *repo)
{
	git_signature *sign;
	git_index *index;
	git_oid tree_id, commit_id;
	git_tree *tree;
	int rc;

	git_signature_now(&sign, sign_name, sign_email);

	rc = git_repository_index(&index, repo);
	if (rc)
		__debug("could not open repository index");

	rc = git_index_write_tree(&tree_id, index);
	if (rc)
		__debug("unable to write initial tree from index");

	git_index_free(index);

	rc = git_tree_lookup(&tree, repo, &tree_id);
	if (rc)
		__debug("could not look up initial tree");

	rc = git_commit_create_v(&commit_id, repo, "HEAD", sign, sign, NULL, "Initial commit", tree, 0);
	if (rc)
		__debug("could not create the initial commit");

	git_tree_free(tree);
	git_signature_free(sign);

	return rc;
}

int configctl_git_create_config_dir(char *path)
{
	int rc = 0;
	git_repository *repo = NULL;

	git_libgit2_init();

	git_repository_init(&repo, path, 0);
	rc = create_initial_commit(repo);

	git_repository_free(repo);
	git_libgit2_shutdown();

	return rc;
}

#endif
