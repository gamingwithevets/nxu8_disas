#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "lib_nxu8.h"
#include "nxu8_instr.h"

struct nxu8_instr_mask instrs[] = {
	{0x8001, 0x0f00, 0x08, 0x00f0, 0x04, "ADD R%0d, R%1d",          NULL},
	{0x1000, 0x0f00, 0x08, 0x00ff, 0x00, "ADD R%0d, #%1sH",          NULL},
	{0xf006, 0x0e00, 0x08, 0x00e0, 0x04, "ADD ER%0d, ER%1d",        NULL},
	{0xe080, 0x0e00, 0x08, 0x007f, 0x00, "ADD ER%0d, #%1sH",         NULL},
	{0x8006, 0x0f00, 0x08, 0x00f0, 0x04, "ADDC R%0d, R%1d",         NULL},
	{0x6000, 0x0f00, 0x08, 0x00ff, 0x00, "ADDC R%0d, %1sH",         NULL},
	{0x8002, 0x0f00, 0x08, 0x00f0, 0x04, "AND R%0d, R%1d",          NULL},
	{0x2000, 0x0f00, 0x08, 0x00ff, 0x00, "AND R%0d, #%1hH",          NULL},
	{0x8007, 0x0f00, 0x08, 0x00f0, 0x04, "CMP R%0d, R%1d",          NULL},
	{0x7000, 0x0f00, 0x08, 0x00ff, 0x00, "CMP R%0d, #%1hH",          NULL},
	{0x8005, 0x0f00, 0x08, 0x00f0, 0x04, "CMPC R%0d, R%1d",         NULL},
	{0x5000, 0x0f00, 0x08, 0x00ff, 0x00, "CMPC R%0d, #%1hH",         NULL},
	{0xf005, 0x0e00, 0x08, 0x00e0, 0x04, "MOV ER%0d, ER%1d",        NULL},
	{0xe000, 0x0e00, 0x08, 0x00ff, 0x00, "MOV ER%0d, #%1sH",         NULL},
	{0x8000, 0x0f00, 0x08, 0x00f0, 0x04, "MOV R%0d, R%1d",          NULL},
	{0x0000, 0x0f00, 0x08, 0x00ff, 0x00, "MOV R%0d, #%1hH",          NULL},
	{0x8003, 0x0f00, 0x08, 0x00f0, 0x04, "OR R%0d, R%1d",           NULL},
	{0x3000, 0x0f00, 0x08, 0x00ff, 0x00, "OR R%0d, #%1hH",           NULL},
	{0x8004, 0x0f00, 0x08, 0x00f0, 0x04, "XOR R%0d, R%1d",          NULL},
	{0x4000, 0x0f00, 0x08, 0x00ff, 0x00, "XOR R%0d, #%1hH",          NULL},
	{0xf007, 0x0e00, 0x08, 0x00e0, 0x04, "CMP ER%0d, ER%1d",        NULL},
	{0x8008, 0x0f00, 0x08, 0x00f0, 0x04, "SUB R%0d, R%1d",          NULL},
	{0x8009, 0x0f00, 0x08, 0x00f0, 0x04, "SUBC R%0d, R%1d",         NULL},

	{0x800a, 0x0f00, 0x08, 0x00f0, 0x04, "SLL R%0d, R%1d",          NULL},
	{0x900a, 0x0f00, 0x08, 0x0070, 0x04, "SLL R%0d, %1d",           NULL},
	{0x800b, 0x0f00, 0x08, 0x00f0, 0x04, "SLLC R%0d, R%1d",         NULL},
	{0x900b, 0x0f00, 0x08, 0x0070, 0x04, "SLLC R%0d, %1d",          NULL},
	{0x800e, 0x0f00, 0x08, 0x00f0, 0x04, "SRA R%0d, R%1d",          NULL},
	{0x900e, 0x0f00, 0x08, 0x0070, 0x04, "SRA R%0d, %1d",           NULL},
	{0x800c, 0x0f00, 0x08, 0x00f0, 0x04, "SRL R%0d, R%1d",          NULL},
	{0x900c, 0x0f00, 0x08, 0x0070, 0x04, "SRL R%0d, %1d",           NULL},
	{0x800d, 0x0f00, 0x08, 0x00f0, 0x04, "SRLC R%0d, R%1d",         NULL},
	{0x900d, 0x0f00, 0x08, 0x0070, 0x04, "SRLC R%0d, %1d",          NULL},

	{0x9032, 0x0e00, 0x08, 0x0000, 0x00, "L ER%0d, %D[EA]",        NULL},
	{0x9052, 0x0e00, 0x08, 0x0000, 0x00, "L ER%0d, %D[EA+]",       NULL},
	{0x9002, 0x0e00, 0x08, 0x00e0, 0x04, "L ER%0d, %D[ER%1d]",     NULL},
	{0xa008, 0x0e00, 0x08, 0x00e0, 0x04, "L ER%0d, %D%2hH[ER%1d]", NULL},
	{0xb000, 0x0e00, 0x08, 0x003f, 0x00, "L ER%0d, %D%1sH[BP]",    NULL},
	{0xb040, 0x0e00, 0x08, 0x003f, 0x00, "L ER%0d, %D%1sH[FP]",    NULL},
	{0x9012, 0x0e00, 0x08, 0x0000, 0x00, "L ER%0d, %D%2hH",        NULL},
	{0x9030, 0x0f00, 0x08, 0x0000, 0x00, "L R%0d, %D[EA]",         NULL},
	{0x9050, 0x0f00, 0x08, 0x0000, 0x00, "L R%0d, %D[EA+]",        NULL},
	{0x9000, 0x0f00, 0x08, 0x00e0, 0x04, "L R%0d, %D[ER%1d]",      NULL},
	{0x9008, 0x0f00, 0x08, 0x00e0, 0x04, "L R%0d, %D%2hH[ER%1d]",  NULL},
	{0xd000, 0x0f00, 0x08, 0x003f, 0x00, "L R%0d, %D%1sH[BP]",     NULL},
	{0xd040, 0x0f00, 0x08, 0x003f, 0x00, "L R%0d, %D%1sH[FP]",     NULL},
	{0x9010, 0x0f00, 0x08, 0x0000, 0x00, "L R%0d, %D%2hH",         NULL},
	{0x9034, 0x0c00, 0x08, 0x0000, 0x00, "L XR%0d, %D[EA]",        NULL},
	{0x9054, 0x0c00, 0x08, 0x0000, 0x00, "L XR%0d, %D[EA+]",       NULL},
	{0x9036, 0x0800, 0x08, 0x0000, 0x00, "L QR%0d, %D[EA]",        NULL},
	{0x9056, 0x0800, 0x08, 0x0000, 0x00, "L QR%0d, %D[EA+]",       NULL},

	{0x9033, 0x0e00, 0x08, 0x0000, 0x00, "ST ER%0d, %D[EA]",        NULL},
	{0x9053, 0x0e00, 0x08, 0x0000, 0x00, "ST ER%0d, %D[EA+]",       NULL},
	{0x9003, 0x0e00, 0x08, 0x00e0, 0x04, "ST ER%0d, %D[ER%d]",      NULL},
	{0xa009, 0x0e00, 0x08, 0x00e0, 0x04, "ST ER%0d, %D%2hH[ER%1d]", NULL},
	{0xb080, 0x0e00, 0x08, 0x003f, 0x00, "ST ER%0d, %D%1sH[BP]",    NULL},
	{0xb0c0, 0x0e00, 0x08, 0x003f, 0x00, "ST ER%0d, %D%1sH[FP]",    NULL},
	{0x9013, 0x0e00, 0x08, 0x0000, 0x00, "ST ER%0d, %D%2hH",        NULL},
	{0x9031, 0x0f00, 0x08, 0x0000, 0x00, "ST R%0d, %D[EA]",         NULL},
	{0x9051, 0x0f00, 0x08, 0x0000, 0x00, "ST R%0d, %D[EA+]",        NULL},
	{0x9001, 0x0f00, 0x08, 0x00e0, 0x04, "ST R%0d, %D[ER%1d]",      NULL},
	{0x9009, 0x0f00, 0x08, 0x00e0, 0x04, "ST R%0d, %D%2hH[ER%1d]",  NULL},
	{0xd080, 0x0f00, 0x08, 0x003f, 0x00, "ST R%0d, %D%1sH[BP]",     NULL},
	{0xd0c0, 0x0f00, 0x08, 0x003f, 0x00, "ST R%0d, %D%1sH[FP]",     NULL},
	{0x9011, 0x0f00, 0x08, 0x0000, 0x00, "ST R%0d, %D%2hH",         NULL},
	{0x9035, 0x0c00, 0x08, 0x0000, 0x00, "ST XR%0d, %D[EA]",        NULL},
	{0x9055, 0x0c00, 0x08, 0x0000, 0x00, "ST XR%0d, %D[EA+]",       NULL},
	{0x9037, 0x0800, 0x08, 0x0000, 0x00, "ST QR%0d, %D[EA]",        NULL},
	{0x9057, 0x0800, 0x08, 0x0000, 0x00, "ST QR%0d, %D[EA+]",       NULL},

	{0xe100, 0x00ff, 0x00, 0x0000, 0x00, "ADD SP, #%0sH",           NULL},
	{0xa00f, 0x00f0, 0x04, 0x0000, 0x00, "MOV ECSR, R%0d",          NULL},
	{0xa00d, 0x0e00, 0x08, 0x0000, 0x00, "MOV ELR, ER%0d",          NULL},
	{0xa00c, 0x00f0, 0x04, 0x0000, 0x00, "MOV EPSW, R%0d",          NULL},
	{0xa005, 0x0e00, 0x08, 0x0000, 0x00, "MOV ER%0d, ELR",          NULL},
	{0xa01a, 0x0e00, 0x08, 0x0000, 0x00, "MOV ER%0d, SP",           NULL},
	{0xa00b, 0x00f0, 0x04, 0x0000, 0x00, "MOV PSW, R%0d",           NULL},
	{0xe900, 0x00ff, 0x00, 0x0000, 0x00, "MOV PSW, #%0hH",          NULL},
	{0xa007, 0x0f00, 0x08, 0x0000, 0x00, "MOV R%0d, ECSR",          NULL},
	{0xa004, 0x0f00, 0x08, 0x0000, 0x00, "MOV R%0d, EPSW",          NULL},
	{0xa003, 0x0f00, 0x08, 0x0000, 0x00, "MOV R%0d, PSW",           NULL},
	{0xa10a, 0x00f0, 0x04, 0x0000, 0x00, "MOV SP, ER%0d",           NULL},

	{0xf05e, 0x0e00, 0x08, 0x0000, 0x00, "PUSH ER%0d",              NULL},
	{0xf07e, 0x0800, 0x08, 0x0000, 0x00, "PUSH QR%0d",              NULL},
	{0xf04e, 0x0f00, 0x08, 0x0000, 0x00, "PUSH R%0d",               NULL},
	{0xf06e, 0x0c00, 0x08, 0x0000, 0x00, "PUSH XR%0d",              NULL},
	{0xf0ce, 0x0f00, 0x08, 0x0000, 0x00, "PUSH %0r"},
	{0xf01e, 0x0e00, 0x08, 0x0000, 0x00, "POP ER%0d",               NULL},
	{0xf03e, 0x0800, 0x08, 0x0000, 0x00, "POP QR%0d",               NULL},
	{0xf00e, 0x0f00, 0x08, 0x0000, 0x00, "POP R%0d",                NULL},
	{0xf02e, 0x0c00, 0x08, 0x0000, 0x00, "POP XR%0d",               NULL},
	{0xf08e, 0x0f00, 0x08, 0x0000, 0x00, "POP %0r"},

	{0xa00e, 0x0f00, 0x08, 0x00f0, 0x04, "MOV CR%0d, R%1d",         NULL},
	{0xf02d, 0x0e00, 0x08, 0x0000, 0x00, "MOV CER%0d, %D[EA]",     NULL},
	{0xf03d, 0x0e00, 0x08, 0x0000, 0x00, "MOV CER%0d, %D[EA+]",    NULL},
	{0xf00d, 0x0f00, 0x08, 0x0000, 0x00, "MOV CR%0d, %D[EA]",      NULL},
	{0xf01d, 0x0f00, 0x08, 0x0000, 0x00, "MOV CR%0d, %D[EA+]",     NULL},
	{0xf04d, 0x0c00, 0x08, 0x0000, 0x00, "MOV CXR%0d, %D[EA]",     NULL},
	{0xf05d, 0x0c00, 0x08, 0x0000, 0x00, "MOV CXR%0d, %D[EA+]",    NULL},
	{0xf06d, 0x0800, 0x08, 0x0000, 0x00, "MOV CQR%0d, %D[EA]",     NULL},
	{0xf07d, 0x0800, 0x08, 0x0000, 0x00, "MOV CQR%0d, %D[EA+]",    NULL},
	{0xa006, 0x0f00, 0x08, 0x00f0, 0x04, "MOV R%0d, CR%0d",         NULL},
	{0xf0ad, 0x0e00, 0x08, 0x0000, 0x00, "MOV %D[EA], CER%0d",     NULL},
	{0xf0bd, 0x0e00, 0x08, 0x0000, 0x00, "MOV %D[EA+], CER%0d",    NULL},
	{0xf08d, 0x0f00, 0x08, 0x0000, 0x00, "MOV %D[EA], CR%0d",      NULL},
	{0xf09d, 0x0f00, 0x08, 0x0000, 0x00, "MOV %D[EA+], CR%0d",     NULL},
	{0xf0cd, 0x0c00, 0x08, 0x0000, 0x00, "MOV %D[EA], CXR%0d",     NULL},
	{0xf0dd, 0x0c00, 0x08, 0x0000, 0x00, "MOV %D[EA+], CXR%0d",    NULL},
	{0xf0ed, 0x0800, 0x08, 0x0000, 0x00, "MOV %D[EA], CQR%0d",     NULL},
	{0xf0fd, 0x0800, 0x08, 0x0000, 0x00, "MOV %D[EA+], CQR%0d",    NULL},

	{0xf00a, 0x00e0, 0x04, 0x0000, 0x00, "LEA [ER%0d]",             NULL},
	{0xf00b, 0x00e0, 0x04, 0x0000, 0x00, "LEA %2hH[ER%0d]",         NULL},
	{0xf00c, 0x0000, 0x00, 0x0000, 0x00, "LEA %2hH",                NULL},

	{0x801f, 0x0f00, 0x08, 0x0000, 0x00, "DAA R%0d",                NULL},
	{0x803f, 0x0f00, 0x08, 0x0000, 0x00, "DAS R%0d",                NULL},
	{0x805f, 0x0f00, 0x08, 0x0000, 0x00, "NEG R%0d",                NULL},

	{0xa000, 0x0f00, 0x08, 0x0070, 0x04, "SB R%0d.%1d",             NULL},
	{0xa080, 0x0070, 0x04, 0x0000, 0x00, "SB %D%2hH.%0d",           NULL},
	{0xa002, 0x0f00, 0x08, 0x0070, 0x04, "RB R%0d.%1d",             NULL},
	{0xa082, 0x0070, 0x04, 0x0000, 0x00, "RB %D%2hH.%0d",           NULL},
	{0xa001, 0x0f00, 0x08, 0x0070, 0x04, "TB R%0d.%1d",             NULL},
	{0xa081, 0x0070, 0x04, 0x0000, 0x00, "TB %D%2hH.%0d",           NULL},

	{0xed08, 0x0000, 0x00, 0x0000, 0x00, "EI",                      NULL},
	{0xebf7, 0x0000, 0x00, 0x0000, 0x00, "DI",                      NULL},
	{0xed80, 0x0000, 0x00, 0x0000, 0x00, "SC",                      NULL},
	{0xeb7f, 0x0000, 0x00, 0x0000, 0x00, "RC",                      NULL},
	{0xfecf, 0x0000, 0x00, 0x0000, 0x00, "CPLC",                    NULL},

	// TODO: Fix this
	{0xc000, 0x00ff, 0x00, 0x0000, 0x00, "BGE %0OH",                },
	{0xc100, 0x00ff, 0x00, 0x0000, 0x00, "BLT %0OH",                },
	{0xc200, 0x00ff, 0x00, 0x0000, 0x00, "BGT %0OH",                },
	{0xc300, 0x00ff, 0x00, 0x0000, 0x00, "BLE %0OH",                },
	{0xc400, 0x00ff, 0x00, 0x0000, 0x00, "BGES %0OH",               },
	{0xc500, 0x00ff, 0x00, 0x0000, 0x00, "BLTS %0OH",               },
	{0xc600, 0x00ff, 0x00, 0x0000, 0x00, "BGTS %0OH",               },
	{0xc700, 0x00ff, 0x00, 0x0000, 0x00, "BLES %0OH",               },
	{0xc800, 0x00ff, 0x00, 0x0000, 0x00, "BNE %0OH",                },
	{0xc900, 0x00ff, 0x00, 0x0000, 0x00, "BEQ %0OH",                },
	{0xca00, 0x00ff, 0x00, 0x0000, 0x00, "BNV %0OH",                },
	{0xcb00, 0x00ff, 0x00, 0x0000, 0x00, "BOV %0OH",                },
	{0xcc00, 0x00ff, 0x00, 0x0000, 0x00, "BPS %0OH",                },
	{0xcd00, 0x00ff, 0x00, 0x0000, 0x00, "BNS %0OH",                },
	{0xce00, 0x00ff, 0x00, 0x0000, 0x00, "BAL %0OH",                },

	{0x810f, 0x0e00, 0x08, 0x00e0, 0x04, "EXTBW ER%0d",             NULL},

	{0xe500, 0x003f, 0x00, 0x0000, 0x00, "SWI %1hH",                NULL},
	{0xffff, 0x0000, 0x00, 0x0000, 0x00, "BRK",                      NULL},

	// TODO: Fix this
	{0xf000, 0x0f00, 0x08, 0x0000, 0x00, "B %0h:%2hH",              },
	{0xf002, 0x00f0, 0x04, 0x0000, 0x00, "B ER%d",                  NULL},
	{0xf001, 0x0f00, 0x08, 0x0000, 0x00, "BL %0h:%2hH",             },
	{0xf003, 0x00f0, 0x04, 0x0000, 0x00, "BL ER%d",                 NULL},

	{0xf004, 0x0e00, 0x08, 0x00f0, 0x04, "MUL ER%0d, R%1d",       NULL},
	{0xf009, 0x0e00, 0x08, 0x00f0, 0x04, "DIV ER%0d, R%1d",       NULL},

	{0xfe2f, 0x0000, 0x00, 0x0000, 0x00, "INC [EA]",               NULL},
	{0xfe3f, 0x0000, 0x00, 0x0000, 0x00, "DEC [EA]",               NULL},
	{0xfe1f, 0x0000, 0x00, 0x0000, 0x00, "RT",                      NULL},
	{0xfe0f, 0x0000, 0x00, 0x0000, 0x00, "RTI",                     NULL},
	{0xfe8f, 0x0000, 0x00, 0x0000, 0x00, "NOP",                     NULL},
};

int bit_length(int x) {
    return floor(log2(x)) + 1;
}

struct nxu8_instr *nxu8_decode_instr(struct nxu8_decoder *decoder, uint32_t addr) {
	// Get the instruction word
	uint16_t instr_fw = nxu8_read16(decoder, addr);

	uint8_t dsr_len = 0;

	// DSR Instructions
	char dsr[5];
	if ((instr_fw & 0xff00) == 0xe300) {
		sprintf(dsr, "%d", instr_fw & 0x00ff);
		instr_fw = nxu8_read16(decoder, addr + 2);
		dsr_len += 2;
	} else if ((instr_fw & 0xff0f) == 0x900f) {
		sprintf(dsr, "R%d", (instr_fw >> 4) & 0xf);
		instr_fw = nxu8_read16(decoder, addr + 2);
		dsr_len += 2;
	} else if (instr_fw == 0xfe9f) {
		sprintf(dsr, "DSR");
		instr_fw = nxu8_read16(decoder, addr + 2);
		dsr_len += 2;
	}

	// Find the matching instruction
	for (int x = 0; x < sizeof(instrs) / sizeof(struct nxu8_instr_mask); x++) {
		uint16_t mask = (instrs[x].arg0_mask | instrs[x].arg1_mask) ^ 0xFFFF;

		if ((instr_fw & mask) == instrs[x].instr_mask) {
			// Initialise the instruction
			struct nxu8_instr *instr = malloc(sizeof(struct nxu8_instr));

			instr->addr = addr;
			instr->len = dsr_len + 2;
			instr->nxrefs_from = 0;
			instr->xrefs_from = NULL;
			instr->nxrefs_to = 0;
			instr->xrefs_to = NULL;

			char mnemonic[50];
			char *head = mnemonic;
			char *fmt = instrs[x].format_string;

			while (*fmt != '\0') {
				switch (*fmt) {
					case '%': {
						uint16_t src;
						uint8_t src_bits;
						fmt++;
						switch (*fmt) {
							case '0': {
								src_bits = bit_length(instrs[x].arg0_mask) - instrs[x].arg0_shift;
								src = (instr_fw & instrs[x].arg0_mask) >> instrs[x].arg0_shift;
								break;
							}
							case '1': {
								src_bits = bit_length(instrs[x].arg1_mask) - instrs[x].arg1_shift;
								src = (instr_fw & instrs[x].arg1_mask) >> instrs[x].arg1_shift;
								break;
							}
							case '2': {
								src_bits = 16;
								src = nxu8_read16(decoder, addr + instr->len);
								instr->len += 2;
								break;
							}
							default: fmt--;
						}
						fmt++;
						switch (*fmt) {
							case 'd': {
								head += sprintf(head, "%d", src);
								break;
							}
							case 'R':
							case 'r': {
								int count = 0;
								if (src & 8) { head += sprintf(head, "LR"); count++; }
								if (src & 4) { head += sprintf(head, "%sEPSW", count != 0 ? ", " : ""); count++; }
								if (src & 2) { head += sprintf(head, "%s%s", count != 0 ? ", " : "", *fmt == 'r' ? "ELR" : "PC"); count++; }
								if (src & 1) { head += sprintf(head, "%sEA", count != 0 ? ", " : ""); count++; }
								break;
							}
							case 'h': {
								if (src > 0x9f) head += sprintf(head, "0");
								head += sprintf(head, "%X", src);
								break;
							}
							case 's': {
								// Sign extend src
								src |= (src >> (src_bits - 1)) ? (0xFFF << src_bits) : 0;
								head += sprintf(head, "%s%02X", src & 0x8000 ? "-" : "", src & 0x8000 ? (src ^ 0xFFFF) + 1 : src);
								break;
							}
							case 'O': {
								src |= (src >> src_bits) ? (0xFFF << src_bits) : 0;
								signed char srcs = src;
								srcs *= 2;
								head += sprintf(head, "%X:%04X", addr >> 16, (addr+srcs+2) & 0xffff);
								break;
							}
							case 'D': {
								if (dsr_len > 0) head += sprintf(head, "%s:", dsr);
								break;
							}
						}
						break;
					}

					default: {
						*(head++) = *fmt;
						break;
					}
				}
				fmt++;
			}
			*head = '\0';

			// Copy the mnemonic
			size_t length = strlen(mnemonic) + 1;
			instr->assembly = malloc(length);
			strcpy(instr->assembly, mnemonic);

			return instr;
		}
	}

	return NULL;
}
