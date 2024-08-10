#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "lib/lib_nxu8.h"

struct instr_line {
	struct label {
		char *name;
		bool global;
		uint32_t parent;
	};
	char *ins_str;
	uint32_t addr;
};

int main(int argc, char **argv) {
	// Display usage
	if (argc != 2) {
		printf("Usage: %s [Input File]\n", argv[0]);
		return -1;
	}

	struct nxu8_decoder *decoder = nxu8_init_decoder_file(argv[1]);

	uint32_t addr = 0;
	while (addr <= decoder->buf_sz) {
		struct nxu8_instr *instr = nxu8_decode_instr(decoder, addr);

		if (instr != NULL) {
			printf("%X:%04XH\t", instr->addr >> 16, instr->addr & 0xffff);
			for (int x = 0; x < instr->len; x += 2) printf("%04X", nxu8_read16(decoder, addr + x));
			if (instr->len < 4) printf("\t");
			printf("\t%s\n", instr->assembly);
			addr += instr->len;
		} else {
			uint16_t val = nxu8_read16(decoder, addr);
			printf("%X:%04XH\t%04X\t\tDW %04XH\n", addr >> 16, addr & 0xffff, val, val);
			addr += 2;
		}
	}

	return 0;
}