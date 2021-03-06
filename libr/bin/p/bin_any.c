/* radare - LGPL - Copyright 2009-2015 - pancake, nibble */

#include <r_types.h>
#include <r_util.h>
#include <r_lib.h>
#include <r_bin.h>
#include <r_magic.h>

static char *get_filetype (RBinFile *arch) {
	ut8 buf[4096] = {0};
	char *res = NULL;
	RMagic * ck;
	if (!arch) return NULL;
	ck = r_magic_new (0);
	if (ck && arch && arch->buf) {
		const char *tmp = NULL;
		r_magic_load (ck, R_MAGIC_PATH);
		r_buf_read_at (arch->buf, 0, buf, sizeof (buf));
		tmp = r_magic_buffer (ck, buf, sizeof (buf));
		if (tmp) res = strdup (tmp);
	}
	r_magic_free (ck);
	return res;
}

static RBinInfo* info(RBinFile *arch) {
	RBinInfo *ret = R_NEW0 (RBinInfo);
	if (!ret) return NULL;
	ret->lang = "";
	ret->file = arch->file? strdup (arch->file): NULL;
	ret->type = get_filetype (arch);
	ret->has_pi = 0;
	ret->has_canary = 0;
	ret->bits = 32;
	ret->big_endian = 0;
	ret->has_va = 0;
	ret->has_nx = 0;
	ret->dbg_info = 0;
	ret->dbg_info = 0;
	ret->dbg_info = 0;
	return ret;
}

static int load(RBinFile *arch) {
	return R_TRUE;
}

static int destroy(RBinFile *arch) {
	return R_TRUE;
}

static ut64 baddr(RBinFile *arch) {
	return 0LL;
}

struct r_bin_plugin_t r_bin_plugin_any = {
	.name = "any",
	.desc = "Dummy format r_bin plugin",
	.license = "LGPL3",
	.init = NULL,
	.fini = NULL,
	.get_sdb = NULL,
	.load = &load,
	.load_bytes = NULL,
	.destroy = &destroy,
	.check = NULL,
	.baddr = &baddr,
	.boffset = NULL,
	.binsym = NULL,
	.entries = NULL,
	.sections = NULL,
	.symbols = NULL,
	.imports = NULL,
	.strings = NULL,
	.info = info,
	.fields = NULL,
	.libs = NULL,
	.relocs = NULL,
	.dbginfo = NULL,
	.create = NULL,
	.write = NULL,
	.minstrlen = 0,
};

#ifndef CORELIB
struct r_lib_struct_t radare_plugin = {
	.type = R_LIB_TYPE_BIN,
	.data = &r_bin_plugin_any,
	.version = R2_VERSION
};
#endif
