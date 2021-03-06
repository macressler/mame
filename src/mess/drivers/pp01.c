// license:MAME
// copyright-holders:Miodrag Milanovic
/***************************************************************************

        PP-01 driver by Miodrag Milanovic

        08/09/2008 Preliminary driver.

****************************************************************************/


#include "includes/pp01.h"


/* Address maps */
static ADDRESS_MAP_START(pp01_mem, AS_PROGRAM, 8, pp01_state )
	AM_RANGE(0x0000, 0x0fff) AM_RAMBANK("bank1")
	AM_RANGE(0x1000, 0x1fff) AM_RAMBANK("bank2")
	AM_RANGE(0x2000, 0x2fff) AM_RAMBANK("bank3")
	AM_RANGE(0x3000, 0x3fff) AM_RAMBANK("bank4")
	AM_RANGE(0x4000, 0x4fff) AM_RAMBANK("bank5")
	AM_RANGE(0x5000, 0x5fff) AM_RAMBANK("bank6")
	AM_RANGE(0x6000, 0x6fff) AM_RAMBANK("bank7")
	AM_RANGE(0x7000, 0x7fff) AM_RAMBANK("bank8")
	AM_RANGE(0x8000, 0x8fff) AM_RAMBANK("bank9")
	AM_RANGE(0x9000, 0x9fff) AM_RAMBANK("bank10")
	AM_RANGE(0xa000, 0xafff) AM_RAMBANK("bank11")
	AM_RANGE(0xb000, 0xbfff) AM_RAMBANK("bank12")
	AM_RANGE(0xc000, 0xcfff) AM_RAMBANK("bank13")
	AM_RANGE(0xd000, 0xdfff) AM_RAMBANK("bank14")
	AM_RANGE(0xe000, 0xefff) AM_RAMBANK("bank15")
	AM_RANGE(0xf000, 0xffff) AM_RAMBANK("bank16")
ADDRESS_MAP_END

static ADDRESS_MAP_START( pp01_io, AS_IO, 8, pp01_state )
	AM_RANGE(0xc0, 0xc3) AM_DEVREADWRITE("ppi8255", i8255_device, read, write) // system
	//AM_RANGE(0xc4, 0xc7) AM_DEVREADWRITE("ppi8255", i8255_device, read, write) // user
	AM_RANGE(0xc8, 0xc8) AM_MIRROR(2) AM_DEVREADWRITE("uart", i8251_device, data_r, data_w)
	AM_RANGE(0xc9, 0xc9) AM_MIRROR(2) AM_DEVREADWRITE("uart", i8251_device, status_r, control_w)
	AM_RANGE(0xcc, 0xcf) AM_WRITE(pp01_video_write_mode_w)
	AM_RANGE(0xd0, 0xd3) AM_DEVREADWRITE("pit8253", pit8253_device, read, write)
	AM_RANGE(0xe0, 0xef) AM_MIRROR(0x10) AM_READWRITE(pp01_mem_block_r, pp01_mem_block_w)
ADDRESS_MAP_END

/* Input ports */
static INPUT_PORTS_START( pp01 )
	PORT_START("LINE0")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Space") PORT_CODE(KEYCODE_SPACE)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Home") PORT_CODE(KEYCODE_HOME)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num 0") PORT_CODE(KEYCODE_0_PAD)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("0") PORT_CODE(KEYCODE_0)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("P") PORT_CODE(KEYCODE_P)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINE1")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F1") PORT_CODE(KEYCODE_F1)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F2") PORT_CODE(KEYCODE_F2)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num 1") PORT_CODE(KEYCODE_1_PAD)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("1") PORT_CODE(KEYCODE_1)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("A") PORT_CODE(KEYCODE_A)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Q") PORT_CODE(KEYCODE_Q)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINE2")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F3") PORT_CODE(KEYCODE_F3)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F4") PORT_CODE(KEYCODE_F4)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num 2") PORT_CODE(KEYCODE_2_PAD)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("2") PORT_CODE(KEYCODE_2)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("B") PORT_CODE(KEYCODE_B)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("R") PORT_CODE(KEYCODE_R)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINE3")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F5") PORT_CODE(KEYCODE_F5)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F6") PORT_CODE(KEYCODE_F6)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num 3") PORT_CODE(KEYCODE_3_PAD)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("3") PORT_CODE(KEYCODE_3)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("C") PORT_CODE(KEYCODE_C)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("S") PORT_CODE(KEYCODE_S)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINE4")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F7") PORT_CODE(KEYCODE_F7)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F8") PORT_CODE(KEYCODE_F8)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num 4") PORT_CODE(KEYCODE_4_PAD)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("4") PORT_CODE(KEYCODE_4)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("D") PORT_CODE(KEYCODE_D)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("T") PORT_CODE(KEYCODE_T)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINE5")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F9") PORT_CODE(KEYCODE_F9)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F10") PORT_CODE(KEYCODE_F10)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num 5") PORT_CODE(KEYCODE_5_PAD)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("5") PORT_CODE(KEYCODE_5)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("E") PORT_CODE(KEYCODE_E)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("U") PORT_CODE(KEYCODE_U)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINE6")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F11") PORT_CODE(KEYCODE_F11)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F12") PORT_CODE(KEYCODE_F12)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num 6") PORT_CODE(KEYCODE_6_PAD)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("6") PORT_CODE(KEYCODE_6)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F") PORT_CODE(KEYCODE_F)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("V") PORT_CODE(KEYCODE_V)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINE7")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F13") PORT_CODE(KEYCODE_PGUP)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("F14") PORT_CODE(KEYCODE_PGDN)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num 7") PORT_CODE(KEYCODE_7_PAD)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("7") PORT_CODE(KEYCODE_7)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("G") PORT_CODE(KEYCODE_G)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("W") PORT_CODE(KEYCODE_W)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINE8")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Backspace") PORT_CODE(KEYCODE_BACKSPACE)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Delete line") PORT_CODE(KEYCODE_TILDE)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num 8") PORT_CODE(KEYCODE_8_PAD)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("8") PORT_CODE(KEYCODE_8)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("H") PORT_CODE(KEYCODE_H)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("X") PORT_CODE(KEYCODE_X)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINE9")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num +") PORT_CODE(KEYCODE_PLUS_PAD)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num 9") PORT_CODE(KEYCODE_9_PAD)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("9") PORT_CODE(KEYCODE_9)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("I") PORT_CODE(KEYCODE_I)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Y") PORT_CODE(KEYCODE_Y)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINEA")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME(":") PORT_CODE(KEYCODE_QUOTE)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("J") PORT_CODE(KEYCODE_J)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Z") PORT_CODE(KEYCODE_Z)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINEB")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME(";") PORT_CODE(KEYCODE_COLON)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("K") PORT_CODE(KEYCODE_K)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("[") PORT_CODE(KEYCODE_OPENBRACE)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINEC")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num *") PORT_CODE(KEYCODE_ASTERISK)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num -") PORT_CODE(KEYCODE_MINUS_PAD)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME(",") PORT_CODE(KEYCODE_COMMA)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("L") PORT_CODE(KEYCODE_L)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("\\") PORT_CODE(KEYCODE_BACKSLASH)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINED")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Enter") PORT_CODE(KEYCODE_ENTER)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("-") PORT_CODE(KEYCODE_MINUS)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("M") PORT_CODE(KEYCODE_M)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("]") PORT_CODE(KEYCODE_CLOSEBRACE)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINEE")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num /") PORT_CODE(KEYCODE_SLASH_PAD)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("Num .") PORT_CODE(KEYCODE_DEL_PAD)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME(".") PORT_CODE(KEYCODE_STOP)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("N") PORT_CODE(KEYCODE_N)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("^") PORT_CODE(KEYCODE_TILDE)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINEF")
		PORT_BIT(0x01, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x02, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x04, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x08, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("/") PORT_CODE(KEYCODE_SLASH)
		PORT_BIT(0x10, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("O") PORT_CODE(KEYCODE_O)
		PORT_BIT(0x20, IP_ACTIVE_LOW, IPT_KEYBOARD) PORT_NAME("_") PORT_CODE(KEYCODE_HOME)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED)
	PORT_START("LINEALL")
		PORT_BIT(0x3F, IP_ACTIVE_LOW, IPT_UNUSED)
		PORT_BIT(0x40, IP_ACTIVE_LOW, IPT_UNUSED) PORT_NAME("Ctrl") PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(KEYCODE_RCONTROL)
		PORT_BIT(0x80, IP_ACTIVE_LOW, IPT_UNUSED) PORT_NAME("Shift") PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT)
INPUT_PORTS_END

/* Machine driver */
static MACHINE_CONFIG_START( pp01, pp01_state )
	/* basic machine hardware */
	MCFG_CPU_ADD("maincpu", I8080, 2000000)
	MCFG_CPU_PROGRAM_MAP(pp01_mem)
	MCFG_CPU_IO_MAP(pp01_io)

	/* video hardware */
	MCFG_SCREEN_ADD("screen", RASTER)
	MCFG_SCREEN_REFRESH_RATE(50)
	MCFG_SCREEN_VBLANK_TIME(ATTOSECONDS_IN_USEC(2500)) /* not accurate */
	MCFG_SCREEN_SIZE(256, 256)
	MCFG_SCREEN_VISIBLE_AREA(0, 256-1, 0, 256-1)
	MCFG_SCREEN_UPDATE_DRIVER(pp01_state, screen_update_pp01)
	MCFG_SCREEN_PALETTE("palette")

	MCFG_PALETTE_ADD("palette", 8)
	MCFG_PALETTE_INIT_OWNER(pp01_state, pp01)

	/* sound hardware */
	MCFG_SPEAKER_STANDARD_MONO("mono")
	MCFG_SOUND_ADD("speaker", SPEAKER_SOUND, 0)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.50)
	//MCFG_SOUND_WAVE_ADD(WAVE_TAG, "cassette")
	//MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.25)

	/* Devices */
	MCFG_DEVICE_ADD("uart", I8251, 0)
	// when rts and dtr are both high, the uart is being used for cassette operations

	MCFG_DEVICE_ADD("pit8253", PIT8253, 0)
	MCFG_PIT8253_CLK0(0)
	MCFG_PIT8253_OUT0_HANDLER(WRITELINE(pp01_state,pp01_pit_out0))
	MCFG_PIT8253_CLK1(2000000)
	MCFG_PIT8253_OUT1_HANDLER(WRITELINE(pp01_state,pp01_pit_out1))
	MCFG_PIT8253_CLK2(2000000)
	MCFG_PIT8253_OUT2_HANDLER(DEVWRITELINE("pit8253", pit8253_device, write_clk0))

	MCFG_DEVICE_ADD("ppi8255", I8255A, 0)
	MCFG_I8255_IN_PORTA_CB(READ8(pp01_state, pp01_8255_porta_r))
	MCFG_I8255_OUT_PORTA_CB(WRITE8(pp01_state, pp01_8255_porta_w))
	MCFG_I8255_IN_PORTB_CB(READ8(pp01_state, pp01_8255_portb_r))
	MCFG_I8255_OUT_PORTB_CB(WRITE8(pp01_state, pp01_8255_portb_w))
	MCFG_I8255_IN_PORTC_CB(READ8(pp01_state, pp01_8255_portc_r))
	MCFG_I8255_OUT_PORTC_CB(WRITE8(pp01_state, pp01_8255_portc_w))

	/* internal ram */
	MCFG_RAM_ADD(RAM_TAG)
	MCFG_RAM_DEFAULT_SIZE("64K")
	MCFG_RAM_DEFAULT_VALUE(0x00)
MACHINE_CONFIG_END

/* ROM definition */

ROM_START( pp01 )
	ROM_REGION( 0x18000, "maincpu", ROMREGION_ERASEFF )

	ROM_LOAD( "ep01.rom", 0x14000, 0x0400, CRC(e48e440f) SHA1(aaae41f0bf163f254e28f6e4d9f6010b349e0c45))
	ROM_LOAD( "ep02.rom", 0x14400, 0x0400, CRC(b9314867) SHA1(220e2a686c6624574e8ea7f6012030c8378a8be6))
	ROM_LOAD( "ep03.rom", 0x14800, 0x0400, CRC(47b91d49) SHA1(51445e24d1c375e798c5ed7b48cb1c7b5e01603a))
	ROM_LOAD( "ep04.rom", 0x14c00, 0x0400, CRC(cc890123) SHA1(7110f301453d925da0d3f29c2ba4eacd5ff8583d))
	ROM_LOAD( "ep05.rom", 0x15000, 0x0400, CRC(b36e2071) SHA1(7c7b2c410f4039980627196575109426bb7bab35))
	ROM_LOAD( "ep06.rom", 0x15400, 0x0400, CRC(3f74efb3) SHA1(77d055eb53ba9b4b14eb2bb8d71f93095b846bb5))
	ROM_LOAD( "ep07.rom", 0x15800, 0x0400, CRC(1dd0bc29) SHA1(109bc3f24a76884d2581f75edc532917cb7ea155))
	ROM_LOAD( "ep08.rom", 0x15c00, 0x0400, CRC(607b710a) SHA1(c5ac7da31204c54d6892d6b708d0291d71963581))
	ROM_LOAD( "ep09.rom", 0x16000, 0x0400, CRC(07f773d1) SHA1(a6cf454318ef0a564a86e669b751e414b12c12d1))
	ROM_LOAD( "ep10.rom", 0x16400, 0x0400, CRC(7793d84b) SHA1(d16ad3db36c8cec68713082ee60324219d3d5032))
	ROM_LOAD( "ep11.rom", 0x16800, 0x0400, CRC(d1b98b5e) SHA1(5526af6317667d707ae413916242cd1bac821373))
	ROM_LOAD( "ep12.rom", 0x16c00, 0x0400, CRC(03c45326) SHA1(f9157ab86cdf1d111bcf19c24e4d7250705be965))
	ROM_LOAD( "ep13.rom", 0x17000, 0x0400, CRC(51769d6c) SHA1(76d6e91cf32b1eb94b9c0ded02e5057ed7ff7d72))
	ROM_LOAD( "ep14.rom", 0x17400, 0x0400, CRC(5d48cefb) SHA1(9b8599dabaf7297ec800fa9a122ad7e3b7b30e8b))
	ROM_LOAD( "ep15.rom", 0x17800, 0x0400, CRC(f44bfe36) SHA1(0ab3c4f061dff6f779685409b07343d0a839fdae))
	ROM_LOAD( "ep16.rom", 0x17c00, 0x0400, CRC(f39c230d) SHA1(9789cedef5655bcb82561f387cc1a6cf48287d78))
ROM_END


/* Driver */

/*    YEAR  NAME    PARENT  COMPAT  MACHINE     INPUT   CLASS           INIT     COMPANY   FULLNAME   FLAGS */
COMP( 198?, pp01,   0,      0,      pp01,       pp01,   driver_device,   0,       "ZVT",   "PP-01", GAME_NOT_WORKING )
