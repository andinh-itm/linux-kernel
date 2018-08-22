/*

  Broadcom B43 wireless driver
  IEEE 802.11n HT-PHY data tables

  Copyright (c) 2011 Rafał Miłecki <zajec5@gmail.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; see the file COPYING.  If not, write to
  the Free Software Foundation, Inc., 51 Franklin Steet, Fifth Floor,
  Boston, MA 02110-1301, USA.

*/

#include "b43.h"
#include "tables_phy_ht.h"
#include "phy_common.h"
#include "phy_ht.h"

static const u16 b43_httab_0x12[] = {
	0x0000, 0x0008, 0x000a, 0x0010, 0x0012, 0x0019,
	0x001a, 0x001c, 0x0080, 0x0088, 0x008a, 0x0090,
	0x0092, 0x0099, 0x009a, 0x009c, 0x0100, 0x0108,
	0x010a, 0x0110, 0x0112, 0x0119, 0x011a, 0x011c,
	0x0180, 0x0188, 0x018a, 0x0190, 0x0192, 0x0199,
	0x019a, 0x019c, 0x0000, 0x0098, 0x00a0, 0x00a8,
	0x009a, 0x00a2, 0x00aa, 0x0120, 0x0128, 0x0128,
	0x0130, 0x0138, 0x0138, 0x0140, 0x0122, 0x012a,
	0x012a, 0x0132, 0x013a, 0x013a, 0x0142, 0x01a8,
	0x01b0, 0x01b8, 0x01b0, 0x01b8, 0x01c0, 0x01c8,
	0x01c0, 0x01c8, 0x01d0, 0x01d0, 0x01d8, 0x01aa,
	0x01b2, 0x01ba, 0x01b2, 0x01ba, 0x01c2, 0x01ca,
	0x01c2, 0x01ca, 0x01d2, 0x01d2, 0x01da, 0x0001,
	0x0002, 0x0004, 0x0009, 0x000c, 0x0011, 0x0014,
	0x0018, 0x0020, 0x0021, 0x0022, 0x0024, 0x0081,
	0x0082, 0x0084, 0x0089, 0x008c, 0x0091, 0x0094,
	0x0098, 0x00a0, 0x00a1, 0x00a2, 0x00a4, 0x0007,
	0x0007, 0x0007, 0x0007, 0x0007, 0x0007, 0x0007,
	0x0007, 0x0007, 0x0007, 0x0007, 0x0007, 0x0007,
	0x0007, 0x0007, 0x0007, 0x0007, 0x0007, 0x0007,
	0x0007, 0x0007, 0x0007, 0x0007, 0x0007, 0x0007,
	0x0007, 0x0007,
};

static const u16 b43_httab_0x27[] = {
	0x0009, 0x000e, 0x0011, 0x0014, 0x0017, 0x001a,
	0x001d, 0x0020, 0x0009, 0x000e, 0x0011, 0x0014,
	0x0017, 0x001a, 0x001d, 0x0020, 0x0009, 0x000e,
	0x0011, 0x0014, 0x0017, 0x001a, 0x001d, 0x0020,
	0x0009, 0x000e, 0x0011, 0x0014, 0x0017, 0x001a,
	0x001d, 0x0020,
};

static const u16 b43_httab_0x26[] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000,
};

static const u32 b43_httab_0x25[] = {
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

static const u32 b43_httab_0x2f[] = {
	0x00035700, 0x0002cc9a, 0x00026666, 0x0001581f,
	0x0001581f, 0x0001581f, 0x0001581f, 0x0001581f,
	0x0001581f, 0x0001581f, 0x0001581f, 0x00035700,
	0x0002cc9a, 0x00026666, 0x0001581f, 0x0001581f,
	0x0001581f, 0x0001581f, 0x0001581f, 0x0001581f,
	0x0001581f, 0x0001581f,
};

static const u16 b43_httab_0x1a[] = {
	0x0055, 0x0054, 0x0054, 0x0053, 0x0052, 0x0052,
	0x0051, 0x0051, 0x0050, 0x004f, 0x004f, 0x004e,
	0x004e, 0x004d, 0x004c, 0x004c, 0x004b, 0x004a,
	0x0049, 0x0049, 0x0048, 0x0047, 0x0046, 0x0046,
	0x0045, 0x0044, 0x0043, 0x0042, 0x0041, 0x0040,
	0x0040, 0x003f, 0x003e, 0x003d, 0x003c, 0x003a,
	0x0039, 0x0038, 0x0037, 0x0036, 0x0035, 0x0033,
	0x0032, 0x0031, 0x002f, 0x002e, 0x002c, 0x002b,
	0x0029, 0x0027, 0x0025, 0x0023, 0x0021, 0x001f,
	0x001d, 0x001a, 0x0018, 0x0015, 0x0012, 0x000e,
	0x000b, 0x0007, 0x0002, 0x00fd,
};

static const u16 b43_httab_0x1b[] = {
	0x0055, 0x0054, 0x0054, 0x0053, 0x0052, 0x0052,
	0x0051, 0x0051, 0x0050, 0x004f, 0x004f, 0x004e,
	0x004e, 0x004d, 0x004c, 0x004c, 0x004b, 0x004a,
	0x0049, 0x0049, 0x0048, 0x0047, 0x0046, 0x0046,
	0x0045, 0x0044, 0x0043, 0x0042, 0x0041, 0x0040,
	0x0040, 0x003f, 0x003e, 0x003d, 0x003c, 0x003a,
	0x0039, 0x0038, 0x0037, 0x0036, 0x0035, 0x0033,
	0x0032, 0x0031, 0x002f, 0x002e, 0x002c, 0x002b,
	0x0029, 0x0027, 0x0025, 0x0023, 0x0021, 0x001f,
	0x001d, 0x001a, 0x0018, 0x0015, 0x0012, 0x000e,
	0x000b, 0x0007, 0x0002, 0x00fd,
};

static const u16 b43_httab_0x1c[] = {
	0x0055, 0x0054, 0x0054, 0x0053, 0x0052, 0x0052,
	0x0051, 0x0051, 0x0050, 0x004f, 0x004f, 0x004e,
	0x004e, 0x004d, 0x004c, 0x004c, 0x004b, 0x004a,
	0x0049, 0x0049, 0x0048, 0x0047, 0x0046, 0x0046,
	0x0045, 0x0044, 0x0043, 0x0042, 0x0041, 0x0040,
	0x0040, 0x003f, 0x003e, 0x003d, 0x003c, 0x003a,
	0x0039, 0x0038, 0x0037, 0x0036, 0x0035, 0x0033,
	0x0032, 0x0031, 0x002f, 0x002e, 0x002c, 0x002b,
	0x0029, 0x0027, 0x0025, 0x0023, 0x0021, 0x001f,
	0x001d, 0x001a, 0x0018, 0x0015, 0x0012, 0x000e,
	0x000b, 0x0007, 0x0002, 0x00fd,
};

static const u32 b43_httab_0x1a_0xc0[] = {
	0x5bf70044, 0x5bf70042, 0x5bf70040, 0x5bf7003e,
	0x5bf7003c, 0x5bf7003b, 0x5bf70039, 0x5bf70037,
	0x5bf70036, 0x5bf70034, 0x5bf70033, 0x5bf70031,
	0x5bf70030, 0x5ba70044, 0x5ba70042, 0x5ba70040,
	0x5ba7003e, 0x5ba7003c, 0x5ba7003b, 0x5ba70039,
	0x5ba70037, 0x5ba70036, 0x5ba70034, 0x5ba70033,
	0x5b770044, 0x5b770042, 0x5b770040, 0x5b77003e,
	0x5b77003c, 0x5b77003b, 0x5b770039, 0x5b770037,
	0x5b770036, 0x5b770034, 0x5b770033, 0x5b770031,
	0x5b770030, 0x5b77002f, 0x5b77002d, 0x5b77002c,
	0x5b470044, 0x5b470042, 0x5b470040, 0x5b47003e,
	0x5b47003c, 0x5b47003b, 0x5b470039, 0x5b470037,
	0x5b470036, 0x5b470034, 0x5b470033, 0x5b470031,
	0x5b470030, 0x5b47002f, 0x5b47002d, 0x5b47002c,
	0x5b47002b, 0x5b47002a, 0x5b270044, 0x5b270042,
	0x5b270040, 0x5b27003e, 0x5b27003c, 0x5b27003b,
	0x5b270039, 0x5b270037, 0x5b270036, 0x5b270034,
	0x5b270033, 0x5b270031, 0x5b270030, 0x5b27002f,
	0x5b170044, 0x5b170042, 0x5b170040, 0x5b17003e,
	0x5b17003c, 0x5b17003b, 0x5b170039, 0x5b170037,
	0x5b170036, 0x5b170034, 0x5b170033, 0x5b170031,
	0x5b170030, 0x5b17002f, 0x5b17002d, 0x5b17002c,
	0x5b17002b, 0x5b17002a, 0x5b170028, 0x5b170027,
	0x5b170026, 0x5b170025, 0x5b170024, 0x5b170023,
	0x5b070044, 0x5b070042, 0x5b070040, 0x5b07003e,
	0x5b07003c, 0x5b07003b, 0x5b070039, 0x5b070037,
	0x5b070036, 0x5b070034, 0x5b070033, 0x5b070031,
	0x5b070030, 0x5b07002f, 0x5b07002d, 0x5b07002c,
	0x5b07002b, 0x5b07002a, 0x5b070028, 0x5b070027,
	0x5b070026, 0x5b070025, 0x5b070024, 0x5b070023,
	0x5b070022, 0x5b070021, 0x5b070020, 0x5b07001f,
	0x5b07001e, 0x5b07001d, 0x5b07001d, 0x5b07001c,
};

static const u32 b43_httab_0x1a_0x140[] = {
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

static const u32 b43_httab_0x1b_0x140[] = {
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

static const u32 b43_httab_0x1c_0x140[] = {
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

static const u16 b43_httab_0x1a_0x1c0[] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000,
};

static const u16 b43_httab_0x1b_0x1c0[] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000,
};

static const u16 b43_httab_0x1c_0x1c0[] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000,
};

static const u16 b43_httab_0x1a_0x240[] = {
	0x0036, 0x0036, 0x0036, 0x0036, 0x0036, 0x0036,
	0x0036, 0x0036, 0x0036, 0x0036, 0x0036, 0x0036,
	0x0036, 0x002a, 0x002a, 0x002a, 0x002a, 0x002a,
	0x002a, 0x002a, 0x002a, 0x002a, 0x002a, 0x002a,
	0x001e, 0x001e, 0x001e, 0x001e, 0x001e, 0x001e,
	0x001e, 0x001e, 0x001e, 0x001e, 0x001e, 0x001e,
	0x001e, 0x001e, 0x001e, 0x001e, 0x000e, 0x000e,
	0x000e, 0x000e, 0x000e, 0x000e, 0x000e, 0x000e,
	0x000e, 0x000e, 0x000e, 0x000e, 0x000e, 0x000e,
	0x000e, 0x000e, 0x000e, 0x000e, 0x01fc, 0x01fc,
	0x01fc, 0x01fc, 0x01fc, 0x01fc, 0x01fc, 0x01fc,
	0x01fc, 0x01fc, 0x01fc, 0x01fc, 0x01fc, 0x01fc,
	0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee,
	0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee,
	0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee,
	0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6,
};

static const u16 b43_httab_0x1b_0x240[] = {
	0x0036, 0x0036, 0x0036, 0x0036, 0x0036, 0x0036,
	0x0036, 0x0036, 0x0036, 0x0036, 0x0036, 0x0036,
	0x0036, 0x002a, 0x002a, 0x002a, 0x002a, 0x002a,
	0x002a, 0x002a, 0x002a, 0x002a, 0x002a, 0x002a,
	0x001e, 0x001e, 0x001e, 0x001e, 0x001e, 0x001e,
	0x001e, 0x001e, 0x001e, 0x001e, 0x001e, 0x001e,
	0x001e, 0x001e, 0x001e, 0x001e, 0x000e, 0x000e,
	0x000e, 0x000e, 0x000e, 0x000e, 0x000e, 0x000e,
	0x000e, 0x000e, 0x000e, 0x000e, 0x000e, 0x000e,
	0x000e, 0x000e, 0x000e, 0x000e, 0x01fc, 0x01fc,
	0x01fc, 0x01fc, 0x01fc, 0x01fc, 0x01fc, 0x01fc,
	0x01fc, 0x01fc, 0x01fc, 0x01fc, 0x01fc, 0x01fc,
	0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee,
	0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee,
	0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee,
	0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6,
};

static const u16 b43_httab_0x1c_0x240[] = {
	0x0036, 0x0036, 0x0036, 0x0036, 0x0036, 0x0036,
	0x0036, 0x0036, 0x0036, 0x0036, 0x0036, 0x0036,
	0x0036, 0x002a, 0x002a, 0x002a, 0x002a, 0x002a,
	0x002a, 0x002a, 0x002a, 0x002a, 0x002a, 0x002a,
	0x001e, 0x001e, 0x001e, 0x001e, 0x001e, 0x001e,
	0x001e, 0x001e, 0x001e, 0x001e, 0x001e, 0x001e,
	0x001e, 0x001e, 0x001e, 0x001e, 0x000e, 0x000e,
	0x000e, 0x000e, 0x000e, 0x000e, 0x000e, 0x000e,
	0x000e, 0x000e, 0x000e, 0x000e, 0x000e, 0x000e,
	0x000e, 0x000e, 0x000e, 0x000e, 0x01fc, 0x01fc,
	0x01fc, 0x01fc, 0x01fc, 0x01fc, 0x01fc, 0x01fc,
	0x01fc, 0x01fc, 0x01fc, 0x01fc, 0x01fc, 0x01fc,
	0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee,
	0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee,
	0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee,
	0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee, 0x01ee,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6, 0x01d6,
	0x01d6, 0x01d6,
};

static const u32 b43_httab_0x1f[] = {
	0x00000000, 0x00000000, 0x00016023, 0x00006028,
	0x00034036, 0x0003402e, 0x0007203c, 0x0006e037,
	0x00070030, 0x0009401f, 0x0009a00f, 0x000b600d,
	0x000c8007, 0x000ce007, 0x00101fff, 0x00121ff9,
	0x0012e004, 0x0014dffc, 0x0016dff6, 0x0018dfe9,
	0x001b3fe5, 0x001c5fd0, 0x001ddfc2, 0x001f1fb6,
	0x00207fa4, 0x00219f8f, 0x0022ff7d, 0x00247f6c,
	0x0024df5b, 0x00267f4b, 0x0027df3b, 0x0029bf3b,
	0x002b5f2f, 0x002d3f2e, 0x002f5f2a, 0x002fff15,
	0x00315f0b, 0x0032defa, 0x0033beeb, 0x0034fed9,
	0x00353ec5, 0x00361eb0, 0x00363e9b, 0x0036be87,
	0x0036be70, 0x0038fe67, 0x0044beb2, 0x00513ef3,
	0x00595f11, 0x00669f3d, 0x0078dfdf, 0x00a143aa,
	0x01642fff, 0x0162afff, 0x01620fff, 0x0160cfff,
	0x015f0fff, 0x015dafff, 0x015bcfff, 0x015bcfff,
	0x015b4fff, 0x015acfff, 0x01590fff, 0x0156cfff,
};

static const u32 b43_httab_0x21[] = {
	0x00000000, 0x00000000, 0x00016023, 0x00006028,
	0x00034036, 0x0003402e, 0x0007203c, 0x0006e037,
	0x00070030, 0x0009401f, 0x0009a00f, 0x000b600d,
	0x000c8007, 0x000ce007, 0x00101fff, 0x00121ff9,
	0x0012e004, 0x0014dffc, 0x0016dff6, 0x0018dfe9,
	0x001b3fe5, 0x001c5fd0, 0x001ddfc2, 0x001f1fb6,
	0x00207fa4, 0x00219f8f, 0x0022ff7d, 0x00247f6c,
	0x0024df5b, 0x00267f4b, 0x0027df3b, 0x0029bf3b,
	0x002b5f2f, 0x002d3f2e, 0x002f5f2a, 0x002fff15,
	0x00315f0b, 0x0032defa, 0x0033beeb, 0x0034fed9,
	0x00353ec5, 0x00361eb0, 0x00363e9b, 0x0036be87,
	0x0036be70, 0x0038fe67, 0x0044beb2, 0x00513ef3,
	0x00595f11, 0x00669f3d, 0x0078dfdf, 0x00a143aa,
	0x01642fff, 0x0162afff, 0x01620fff, 0x0160cfff,
	0x015f0fff, 0x015dafff, 0x015bcfff, 0x015bcfff,
	0x015b4fff, 0x015acfff, 0x01590fff, 0x0156cfff,
};

static const u32 b43_httab_0x23[] = {
	0x00000000, 0x00000000, 0x00016023, 0x00006028,
	0x00034036, 0x0003402e, 0x0007203c, 0x0006e037,
	0x00070030, 0x0009401f, 0x0009a00f, 0x000b600d,
	0x000c8007, 0x000ce007, 0x00101fff, 0x00121ff9,
	0x0012e004, 0x0014dffc, 0x0016dff6, 0x0018dfe9,
	0x001b3fe5, 0x001c5fd0, 0x001ddfc2, 0x001f1fb6,
	0x00207fa4, 0x00219f8f, 0x0022ff7d, 0x00247f6c,
	0x0024df5b, 0x00267f4b, 0x0027df3b, 0x0029bf3b,
	0x002b5f2f, 0x002d3f2e, 0x002f5f2a, 0x002fff15,
	0x00315f0b, 0x0032defa, 0x0033beeb, 0x0034fed9,
	0x00353ec5, 0x00361eb0, 0x00363e9b, 0x0036be87,
	0x0036be70, 0x0038fe67, 0x0044beb2, 0x00513ef3,
	0x00595f11, 0x00669f3d, 0x0078dfdf, 0x00a143aa,
	0x01642fff, 0x0162afff, 0x01620fff, 0x0160cfff,
	0x015f0fff, 0x015dafff, 0x015bcfff, 0x015bcfff,
	0x015b4fff, 0x015acfff, 0x01590fff, 0x0156cfff,
};

static const u32 b43_httab_0x20[] = {
	0x0b5e002d, 0x0ae2002f, 0x0a3b0032, 0x09a70035,
	0x09220038, 0x08ab003b, 0x081f003f, 0x07a20043,
	0x07340047, 0x06d2004b, 0x067a004f, 0x06170054,
	0x05bf0059, 0x0571005e, 0x051e0064, 0x04d3006a,
	0x04910070, 0x044c0077, 0x040f007e, 0x03d90085,
	0x03a1008d, 0x036f0095, 0x033d009e, 0x030b00a8,
	0x02e000b2, 0x02b900bc, 0x029200c7, 0x026d00d3,
	0x024900e0, 0x022900ed, 0x020a00fb, 0x01ec010a,
	0x01d20119, 0x01b7012a, 0x019e013c, 0x0188014e,
	0x01720162, 0x015d0177, 0x0149018e, 0x013701a5,
	0x012601be, 0x011501d8, 0x010601f4, 0x00f70212,
	0x00e90231, 0x00dc0253, 0x00d00276, 0x00c4029b,
	0x00b902c3, 0x00af02ed, 0x00a50319, 0x009c0348,
	0x0093037a, 0x008b03af, 0x008303e6, 0x007c0422,
	0x00750460, 0x006e04a3, 0x006804e9, 0x00620533,
	0x005d0582, 0x005805d6, 0x0053062e, 0x004e068c,
};

static const u32 b43_httab_0x22[] = {
	0x0b5e002d, 0x0ae2002f, 0x0a3b0032, 0x09a70035,
	0x09220038, 0x08ab003b, 0x081f003f, 0x07a20043,
	0x07340047, 0x06d2004b, 0x067a004f, 0x06170054,
	0x05bf0059, 0x0571005e, 0x051e0064, 0x04d3006a,
	0x04910070, 0x044c0077, 0x040f007e, 0x03d90085,
	0x03a1008d, 0x036f0095, 0x033d009e, 0x030b00a8,
	0x02e000b2, 0x02b900bc, 0x029200c7, 0x026d00d3,
	0x024900e0, 0x022900ed, 0x020a00fb, 0x01ec010a,
	0x01d20119, 0x01b7012a, 0x019e013c, 0x0188014e,
	0x01720162, 0x015d0177, 0x0149018e, 0x013701a5,
	0x012601be, 0x011501d8, 0x010601f4, 0x00f70212,
	0x00e90231, 0x00dc0253, 0x00d00276, 0x00c4029b,
	0x00b902c3, 0x00af02ed, 0x00a50319, 0x009c0348,
	0x0093037a, 0x008b03af, 0x008303e6, 0x007c0422,
	0x00750460, 0x006e04a3, 0x006804e9, 0x00620533,
	0x005d0582, 0x005805d6, 0x0053062e, 0x004e068c,
};

static const u32 b43_httab_0x24[] = {
	0x0b5e002d, 0x0ae2002f, 0x0a3b0032, 0x09a70035,
	0x09220038, 0x08ab003b, 0x081f003f, 0x07a20043,
	0x07340047, 0x06d2004b, 0x067a004f, 0x06170054,
	0x05bf0059, 0x0571005e, 0x051e0064, 0x04d3006a,
	0x04910070, 0x044c0077, 0x040f007e, 0x03d90085,
	0x03a1008d, 0x036f0095, 0x033d009e, 0x030b00a8,
	0x02e000b2, 0x02b900bc, 0x029200c7, 0x026d00d3,
	0x024900e0, 0x022900ed, 0x020a00fb, 0x01ec010a,
	0x01d20119, 0x01b7012a, 0x019e013c, 0x0188014e,
	0x01720162, 0x015d0177, 0x0149018e, 0x013701a5,
	0x012601be, 0x011501d8, 0x010601f4, 0x00f70212,
	0x00e90231, 0x00dc0253, 0x00d00276, 0x00c4029b,
	0x00b902c3, 0x00af02ed, 0x00a50319, 0x009c0348,
	0x0093037a, 0x008b03af, 0x008303e6, 0x007c0422,
	0x00750460, 0x006e04a3, 0x006804e9, 0x00620533,
	0x005d0582, 0x005805d6, 0x0053062e, 0x004e068c,
};

/* Some late-init table */
const u32 b43_httab_0x1a_0xc0_late[] = {
	0x10f90040, 0x10e10040, 0x10e1003c, 0x10c9003d,
	0x10b9003c, 0x10a9003d, 0x10a1003c, 0x1099003b,
	0x1091003b, 0x1089003a, 0x1081003a, 0x10790039,
	0x10710039, 0x1069003a, 0x1061003b, 0x1059003d,
	0x1051003f, 0x10490042, 0x1049003e, 0x1049003b,
	0x1041003e, 0x1041003b, 0x1039003e, 0x1039003b,
	0x10390038, 0x10390035, 0x1031003a, 0x10310036,
	0x10310033, 0x1029003a, 0x10290037, 0x10290034,
	0x10290031, 0x10210039, 0x10210036, 0x10210033,
	0x10210030, 0x1019003c, 0x10190039, 0x10190036,
	0x10190033, 0x10190030, 0x1019002d, 0x1019002b,
	0x10190028, 0x1011003a, 0x10110036, 0x10110033,
	0x10110030, 0x1011002e, 0x1011002b, 0x10110029,
	0x10110027, 0x10110024, 0x10110022, 0x10110020,
	0x1011001f, 0x1011001d, 0x1009003a, 0x10090037,
	0x10090034, 0x10090031, 0x1009002e, 0x1009002c,
	0x10090029, 0x10090027, 0x10090025, 0x10090023,
	0x10090021, 0x1009001f, 0x1009001d, 0x1009001b,
	0x1009001a, 0x10090018, 0x10090017, 0x10090016,
	0x10090015, 0x10090013, 0x10090012, 0x10090011,
	0x10090010, 0x1009000f, 0x1009000f, 0x1009000e,
	0x1009000d, 0x1009000c, 0x1009000c, 0x1009000b,
	0x1009000a, 0x1009000a, 0x10090009, 0x10090009,
	0x10090008, 0x10090008, 0x10090007, 0x10090007,
	0x10090007, 0x10090006, 0x10090006, 0x10090005,
	0x10090005, 0x10090005, 0x10090005, 0x10090004,
	0x10090004, 0x10090004, 0x10090004, 0x10090003,
	0x10090003, 0x10090003, 0x10090003, 0x10090003,
	0x10090003, 0x10090002, 0x10090002, 0x10090002,
	0x10090002, 0x10090002, 0x10090002, 0x10090002,
	0x10090002, 0x10090002, 0x10090001, 0x10090001,
	0x10090001, 0x10090001, 0x10090001, 0x10090001,
};

/**************************************************
 * R/W ops.
 **************************************************/

u32 b43_httab_read(struct b43_wldev *dev, u32 offset)
{
	u32 type, value;

	type = offset & B43_HTTAB_TYPEMASK;
	offset &= ~B43_HTTAB_TYPEMASK;
	B43_WARN_ON(offset > 0xFFFF);

	switch (type) {
	case B43_HTTAB_8BIT:
		b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, offset);
		value = b43_phy_read(dev, B43_PHY_HT_TABLE_DATALO) & 0xFF;
		break;
	case B43_HTTAB_16BIT:
		b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, offset);
		value = b43_phy_read(dev, B43_PHY_HT_TABLE_DATALO);
		break;
	case B43_HTTAB_32BIT:
		b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, offset);
		value = b43_phy_read(dev, B43_PHY_HT_TABLE_DATAHI);
		value <<= 16;
		value |= b43_phy_read(dev, B43_PHY_HT_TABLE_DATALO);
		break;
	default:
		B43_WARN_ON(1);
		value = 0;
	}

	return value;
}

void b43_httab_read_bulk(struct b43_wldev *dev, u32 offset,
			 unsigned int nr_elements, void *_data)
{
	u32 type;
	u8 *data = _data;
	unsigned int i;

	type = offset & B43_HTTAB_TYPEMASK;
	offset &= ~B43_HTTAB_TYPEMASK;
	B43_WARN_ON(offset > 0xFFFF);

	b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, offset);

	for (i = 0; i < nr_elements; i++) {
		switch (type) {
		case B43_HTTAB_8BIT:
			*data = b43_phy_read(dev, B43_PHY_HT_TABLE_DATALO) & 0xFF;
			data++;
			break;
		case B43_HTTAB_16BIT:
			*((u16 *)data) = b43_phy_read(dev, B43_PHY_HT_TABLE_DATALO);
			data += 2;
			break;
		case B43_HTTAB_32BIT:
			*((u32 *)data) = b43_phy_read(dev, B43_PHY_HT_TABLE_DATAHI);
			*((u32 *)data) <<= 16;
			*((u32 *)data) |= b43_phy_read(dev, B43_PHY_HT_TABLE_DATALO);
			data += 4;
			break;
		default:
			B43_WARN_ON(1);
		}
	}
}

void b43_httab_write(struct b43_wldev *dev, u32 offset, u32 value)
{
	u32 type;

	type = offset & B43_HTTAB_TYPEMASK;
	offset &= 0xFFFF;

	switch (type) {
	case B43_HTTAB_8BIT:
		B43_WARN_ON(value & ~0xFF);
		b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, offset);
		b43_phy_write(dev, B43_PHY_HT_TABLE_DATALO, value);
		break;
	case B43_HTTAB_16BIT:
		B43_WARN_ON(value & ~0xFFFF);
		b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, offset);
		b43_phy_write(dev, B43_PHY_HT_TABLE_DATALO, value);
		break;
	case B43_HTTAB_32BIT:
		b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, offset);
		b43_phy_write(dev, B43_PHY_HT_TABLE_DATAHI, value >> 16);
		b43_phy_write(dev, B43_PHY_HT_TABLE_DATALO, value & 0xFFFF);
		break;
	default:
		B43_WARN_ON(1);
	}

	return;
}

void b43_httab_write_few(struct b43_wldev *dev, u32 offset, size_t num, ...)
{
	va_list args;
	u32 type, value;
	unsigned int i;

	type = offset & B43_HTTAB_TYPEMASK;
	offset &= 0xFFFF;

	va_start(args, num);
	switch (type) {
	case B43_HTTAB_8BIT:
		b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, offset);
		for (i = 0; i < num; i++) {
			value = va_arg(args, int);
			B43_WARN_ON(value & ~0xFF);
			b43_phy_write(dev, B43_PHY_HT_TABLE_DATALO, value);
		}
		break;
	case B43_HTTAB_16BIT:
		b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, offset);
		for (i = 0; i < num; i++) {
			value = va_arg(args, int);
			B43_WARN_ON(value & ~0xFFFF);
			b43_phy_write(dev, B43_PHY_HT_TABLE_DATALO, value);
		}
		break;
	case B43_HTTAB_32BIT:
		b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, offset);
		for (i = 0; i < num; i++) {
			value = va_arg(args, int);
			b43_phy_write(dev, B43_PHY_HT_TABLE_DATAHI,
				      value >> 16);
			b43_phy_write(dev, B43_PHY_HT_TABLE_DATALO,
				      value & 0xFFFF);
		}
		break;
	default:
		B43_WARN_ON(1);
	}
	va_end(args);

	return;
}

void b43_httab_write_bulk(struct b43_wldev *dev, u32 offset,
			  unsigned int nr_elements, const void *_data)
{
	u32 type, value;
	const u8 *data = _data;
	unsigned int i;

	type = offset & B43_HTTAB_TYPEMASK;
	offset &= ~B43_HTTAB_TYPEMASK;
	B43_WARN_ON(offset > 0xFFFF);

	b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, offset);

	for (i = 0; i < nr_elements; i++) {
		switch (type) {
		case B43_HTTAB_8BIT:
			value = *data;
			data++;
			B43_WARN_ON(value & ~0xFF);
			b43_phy_write(dev, B43_PHY_HT_TABLE_DATALO, value);
			break;
		case B43_HTTAB_16BIT:
			value = *((u16 *)data);
			data += 2;
			B43_WARN_ON(value & ~0xFFFF);
			b43_phy_write(dev, B43_PHY_HT_TABLE_DATALO, value);
			break;
		case B43_HTTAB_32BIT:
			value = *((u32 *)data);
			data += 4;
			b43_phy_write(dev, B43_PHY_HT_TABLE_DATAHI, value >> 16);
			b43_phy_write(dev, B43_PHY_HT_TABLE_DATALO,
					value & 0xFFFF);
			break;
		default:
			B43_WARN_ON(1);
		}
	}
}

/**************************************************
 * Tables ops.
 **************************************************/

#define httab_upload(dev, offset, data) do { \
		b43_httab_write_bulk(dev, offset, ARRAY_SIZE(data), data); \
	} while (0)
void b43_phy_ht_tables_init(struct b43_wldev *dev)
{
	BUILD_BUG_ON(ARRAY_SIZE(b43_httab_0x1a_0xc0_late) !=
			B43_HTTAB_1A_C0_LATE_SIZE);

	httab_upload(dev, B43_HTTAB16(0x12, 0), b43_httab_0x12);
	httab_upload(dev, B43_HTTAB16(0x27, 0), b43_httab_0x27);
	httab_upload(dev, B43_HTTAB16(0x26, 0), b43_httab_0x26);
	httab_upload(dev, B43_HTTAB32(0x25, 0), b43_httab_0x25);
	httab_upload(dev, B43_HTTAB32(0x2f, 0), b43_httab_0x2f);
	httab_upload(dev, B43_HTTAB16(0x1a, 0), b43_httab_0x1a);
	httab_upload(dev, B43_HTTAB16(0x1b, 0), b43_httab_0x1b);
	httab_upload(dev, B43_HTTAB16(0x1c, 0), b43_httab_0x1c);
	httab_upload(dev, B43_HTTAB32(0x1a, 0x0c0), b43_httab_0x1a_0xc0);
	httab_upload(dev, B43_HTTAB32(0x1a, 0x140), b43_httab_0x1a_0x140);
	httab_upload(dev, B43_HTTAB32(0x1b, 0x140), b43_httab_0x1b_0x140);
	httab_upload(dev, B43_HTTAB32(0x1c, 0x140), b43_httab_0x1c_0x140);
	httab_upload(dev, B43_HTTAB16(0x1a, 0x1c0), b43_httab_0x1a_0x1c0);
	httab_upload(dev, B43_HTTAB16(0x1b, 0x1c0), b43_httab_0x1b_0x1c0);
	httab_upload(dev, B43_HTTAB16(0x1c, 0x1c0), b43_httab_0x1c_0x1c0);
	httab_upload(dev, B43_HTTAB16(0x1a, 0x240), b43_httab_0x1a_0x240);
	httab_upload(dev, B43_HTTAB16(0x1b, 0x240), b43_httab_0x1b_0x240);
	httab_upload(dev, B43_HTTAB16(0x1c, 0x240), b43_httab_0x1c_0x240);
	httab_upload(dev, B43_HTTAB32(0x1f, 0), b43_httab_0x1f);
	httab_upload(dev, B43_HTTAB32(0x21, 0), b43_httab_0x21);
	httab_upload(dev, B43_HTTAB32(0x23, 0), b43_httab_0x23);
	httab_upload(dev, B43_HTTAB32(0x20, 0), b43_httab_0x20);
	httab_upload(dev, B43_HTTAB32(0x22, 0), b43_httab_0x22);
	httab_upload(dev, B43_HTTAB32(0x24, 0), b43_httab_0x24);
}
newcodenewcodenewcodenewcodenewcodenewcodenewcode
