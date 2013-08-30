#include "expansion.h"

#include <glib.h>
#include <stdlib.h>
#include <string.h>

#ifdef RANGE
#include "range_expansion.h"

gint wsh_exp_range(gchar*** hosts, gsize* num_hosts, const gchar* range_query, GError** err) { 
	if (err) g_assert_no_error(*err);
	g_assert(hosts);
	g_assert(num_hosts);
	g_assert(range_query);

	if (wsh_exp_range_init(err))
		return EXIT_FAILURE;

	if (wsh_exp_range_expand(hosts, range_query, err)) {
		return EXIT_FAILURE;
	}

	wsh_exp_range_cleanup();

	*num_hosts = g_strv_length(*hosts);

	return EXIT_SUCCESS;
}
#endif

gint wsh_exp_filename(gchar*** hosts, gsize* num_hosts, const gchar* filename, GError** err) {
	if (err) g_assert_no_error(*err);

	if (g_file_test(filename, G_FILE_TEST_IS_EXECUTABLE))
		return wsh_exp_exec_filename(hosts, num_hosts, filename, err);
	return wsh_exp_flat_filename(hosts, num_hosts, filename, err);
}

gint wsh_exp_flat_filename(gchar*** hosts, gsize* num_hosts, const gchar* filename, GError** err) {
	gchar* file_contents;

	if (! g_file_get_contents(filename, &file_contents, NULL, err))
		return EXIT_FAILURE;

	*hosts = g_strsplit(file_contents, "\n", 0);
	*num_hosts = g_strv_length(*hosts) - 1;
	g_free(file_contents);

	return EXIT_SUCCESS;
}

gint wsh_exp_exec_filename(gchar*** hosts, gsize* num_hosts, const gchar* filename, GError** err) {
	gchar* output = NULL;
	gchar* new_filename = NULL;
	gint ret = EXIT_SUCCESS;

	if (! g_path_is_absolute(filename))
		new_filename = g_strdup_printf("./%s", filename);
	else
		new_filename = g_strdup(filename);

	if (!g_spawn_command_line_sync(new_filename, &output, NULL, NULL, err)) {
		ret = EXIT_FAILURE;
		goto wsh_exp_exec_filename_fail;
	}

	*hosts = g_strsplit(output, "\n", 0);
	*num_hosts = g_strv_length(*hosts) - 1;

wsh_exp_exec_filename_fail:
	g_free(new_filename);
	return ret;
}
