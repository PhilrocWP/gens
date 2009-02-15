/***************************************************************************
 * Gens: Main Loop.                                                        *
 *                                                                         *
 * Copyright (c) 1999-2002 by Stéphane Dallongeville                       *
 * Copyright (c) 2003-2004 by Stéphane Akhoun                              *
 * Copyright (c) 2008-2009 by David Korth                                  *
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU General Public License as published by the   *
 * Free Software Foundation; either version 2 of the License, or (at your  *
 * option) any later version.                                              *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License along *
 * with this program; if not, write to the Free Software Foundation, Inc., *
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// Debug messages.
#include "macros/debug_msg.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "g_main.hpp"
#include "gens.hpp"
#include "g_md.hpp"
#include "g_mcd.hpp"
#include "g_32x.hpp"
#include "gens_core/misc/misc.h"
#include "gens_core/misc/cpuflags.h"
#include "gens_core/vdp/vdp_rend.h"
#include "util/file/save.hpp"
#include "util/file/config_file.hpp"
#include "gens_core/vdp/vdp_io.h"
#include "util/sound/gym.hpp"
#include "gens_core/mem/mem_m68k.h"
#include "gens_core/sound/ym2612.h"
#include "parse.hpp"
#include "gens_core/cpu/sh2/cpu_sh2.h"
#include "gens_core/cpu/68k/cpu_68k.h"
#include "gens_core/cpu/z80/cpu_z80.h"
#include "gens_core/sound/psg.h"
#include "gens_core/sound/pwm.h"

// INI handling.
#include "port/ini.hpp"

#ifdef GENS_DEBUGGER
#include "debugger/debugger.hpp"
#endif /* GENS_DEBUGGER */

// CD-ROM drive access
#ifdef GENS_CDROM
#include "segacd/cd_aspi.hpp"
#endif /* GENS_CDROM */

// Gens UI
#include "gens_ui.hpp"

// Update Emulation functions
#include "g_update.hpp"

// Plugin Manager
#include "plugins/pluginmgr.hpp"

// File management functions.
#include "util/file/file.hpp"

// Video, Audio, and Input backends.
#include "video/vdraw.h"
#include "audio/audio.h"
#include "input/input.h"

// Video effects.
#include "video/v_effects.hpp"

// Language handler.
#include "language.h"

// Gens Settings struct
struct Gens_Settings_t Settings;
struct Gens_PathNames_t PathNames;
struct Gens_BIOS_Filenames_t BIOS_Filenames;
struct Gens_Misc_Filenames_t Misc_Filenames;
struct Gens_VideoSettings_t Video;

// bpp settings.
uint8_t bppMD;	// MD bpp
uint8_t bppOut;	// Output bpp.

// Renderers
#include <list>
using std::list;
list<MDP_Render_t*>::iterator rendMode_FS;
list<MDP_Render_t*>::iterator rendMode_W;

int fast_forward = 0;

POINT Window_Pos;

// Stupid temporary string needed for some stuff.
char Str_Tmp[1024];

char **language_name = NULL;
int Active = 1;
int Paused = 0;
int Net_Play = 0;
int Full_Screen = 0;
int Resolution = 1;
int Show_LED = 0;
int FS_Minimised = 0;
int Auto_Pause = 0;
int Auto_Fix_CS = 0;
int Country = -1;
int Country_Order[3];
int Intro_Style = 2;
int SegaCD_Accurate = 0;
int Kaillera_Client_Running = 0;
int Quick_Exit = 0;

static int Gens_Running = 0;


/**
 * Init_Settings(): Initialize the Settings struct.
 * @return 0 on success; non-zero on error.
 */
int Init_Settings(void)
{
	// Initialize video settings.
	Video.borderColorEmulation = 1;
	Video.pauseTint = 1;
#ifdef GENS_OPENGL
	Video.Width_GL = 640;
	Video.Height_GL = 480;
	Video.glLinearFilter = 0;
#endif
	
	// Default bpp.
	bppMD = 32;
	bppOut = 32;
	
	// Old code from InitParameters().
	VDP_Num_Vis_Lines = 224;
	Net_Play = 0;
	Sprite_Over = 1;
	
	GYM_Dumping = 0;
	
	FS_Minimised = 0;
	Game = NULL;
	Genesis_Started = 0;
	SegaCD_Started = 0;
	_32X_Started = 0;
	CPU_Mode = 0;
	
	// This is needed even if the built-in debugger isn't compiled in.
	Debug = 0;
	
#ifdef GENS_OS_WIN32
	// Win32 needs the program's pathname.
	char exeFilename[1024];
	string tmpEXEPath;
	GetModuleFileName(NULL, exeFilename, sizeof(exeFilename));
	tmpEXEPath = File::GetDirFromPath(exeFilename);
	strncpy(PathNames.Gens_EXE_Path, tmpEXEPath.c_str(), sizeof(PathNames.Gens_EXE_Path));
	PathNames.Gens_EXE_Path[sizeof(PathNames.Gens_EXE_Path) - 1] = 0x00;
#endif
	
	Get_Save_Path(PathNames.Gens_Path, GENS_PATH_MAX);
	Create_Save_Directory(PathNames.Gens_Path);
	
	// Create default language filename.
	strncpy(PathNames.Language_Path, PathNames.Gens_Path, GENS_PATH_MAX);
	strcat(PathNames.Language_Path, "language.dat");
	
	// Create default configuration filename.
	strncpy(Str_Tmp, PathNames.Gens_Path, 1000);
	strcat(Str_Tmp, "gens.cfg");
	
	// Get the CPU flags.
	getCPUFlags();
	
	// Initialize the Plugin Manager.
	PluginMgr::init();
	
	// Set the default renderers.
	if (PluginMgr::lstRenderPlugins.empty())
	{
		// No render plugins found.
		DEBUG_MSG(gens, 0, "Fatal Error: No render plugins found.");
		fprintf(stderr, "%s(): FATAL ERROR: No render plugins found.\n", __func__);
		return 1;	// TODO: Replace with a better error code.
	}
	rendMode_FS = PluginMgr::lstRenderPlugins.begin();
	rendMode_W = PluginMgr::lstRenderPlugins.begin();
	
	// Build language strings and load the default configuration.
	Build_Language_String();
	Config::load(Str_Tmp, NULL);
	
	// Success.
	return 0;
}


/**
 * close_gens(): Close GENS.
 */
void close_gens(void)
{
	Gens_Running = 0;
}

/**
 * run_gens(): Run GENS.
 */
static inline void run_gens(void)
{
	Gens_Running = 1;
}

/**
 * is_gens_running(): Is GENS running?!
 * @return 1 if it's running.
 */
int is_gens_running(void)
{
	return Gens_Running;
}


/**
 * Init(): Initialize Gens.
 * @return 1 if successful; 0 on errors.
 */
int Init(void)
{
	MSH2_Init();
	SSH2_Init();
	M68K_Init();
	S68K_Init();
	Z80_Init();
	
	YM2612_Init(CLOCK_NTSC / 7, audio_get_sound_rate(), YM2612_Improv);
	PSG_Init(CLOCK_NTSC / 15, audio_get_sound_rate());
	PWM_Init();
	
	// Initialize the CD-ROM drive, if available.
#ifdef GENS_CDROM
	Init_CD_Driver();
#endif
	
	Init_Tab();
	
	run_gens();
	return 1;
}


/**
 * End_All(): Close all functions.
 */
void End_All(void)
{
	ROM::freeROM(Game);
	YM2612_End();
#ifdef GENS_CDROM
	End_CD_Driver();
#endif
	
	// Shut down the Plugin Manager.
	PluginMgr::end();
	
	// Shut down the input subsystem.
	input_end();
	
	// Shut down the audio subsystem.
	audio_end();
	
	// Shut down the video subsystem.
	vdraw_backend_end();
	if (vdraw_shutdown)
		vdraw_shutdown();
}


/**
 * IsAsyncAllowed(): Determines if asynchronous stuff is allowed.
 * @return 0 if not allowed; non-zero otherwise.
 */
int IsAsyncAllowed(void)
{
	// In GENS Re-Recording, async is disabled if:
	// - Async is explicitly disabled due to testing for desyncs.
	// - A movie is being played or recorded.
	// Since none of the above applies here, async is allowed.
	return 1;

	// TODO
#if 0
	if(MainMovie.Status == MOVIE_RECORDING)
		return false;
	if(MainMovie.Status == MOVIE_PLAYING)
		return false;
#endif
}


// The following is stuff imported from g_sdldraw.c.
// TODO: Figure out where to put it.
int (*Update_Frame)(void);
int (*Update_Frame_Fast)(void);

// TODO: Only used for DirectDraw.
int Flag_Clr_Scr = 0;

// VSync flags
int FS_VSync;
int W_VSync;


/**
 * Clear_Screen_MD(): Clears the MD screen.
 */
int ice = 0;
void Clear_Screen_MD(void)
{
	memset(MD_Screen, 0x00, sizeof(MD_Screen));
	memset(MD_Screen32, 0x00, sizeof(MD_Screen32));
}


/**
 * get_mdp_render_t(): Get the current MDP_Render_t*. (C wrapper)
 * @return Current MDP_Render_t*.
 */
MDP_Render_t* get_mdp_render_t(void)
{
	const list<MDP_Render_t*>::iterator& rendMode = (vdraw_get_fullscreen() ? rendMode_FS : rendMode_W);
	return (*rendMode);
}


/**
 * GensMainLoop(): The main program loop.
 */
void GensMainLoop(void)
{
	while (is_gens_running())
	{
		// Update the UI.
		GensUI::update();
		
		// Update physical controller inputs.
		input_update();
		
#ifdef GENS_DEBUGGER
		if (Debug)
		{
			// DEBUG
			Update_Debug_Screen();
			vdraw_flip();
			GensUI::sleep(100);
		}
		else
#endif /* GENS_DEBUGGER */
		if (Genesis_Started || _32X_Started || SegaCD_Started)
		{
			if ((Active) && (!Paused))
			{
				// EMULATION ACTIVE
				if (fast_forward)
					Update_Emulation_One();
				else
					Update_Emulation();
				
				#ifdef GENS_OS_UNIX
				// Prevent 100% CPU usage.
				// The CPU scheduler will take away CPU time from Gens/GS if
				// it notices that the process is eating up too much CPU time.
				GensUI::sleep(1, true);
				#endif
			}
			else
			{
				// EMULATION PAUSED
				if (_32X_Started)
					Do_32X_VDP_Only();
				else
					Do_VDP_Only();
				
				if (Video.pauseTint)
				{
					// Emulation is paused.
					Pause_Screen();
				}
				
				vdraw_flip();
				GensUI::sleep(100);
			}
		}
		else
		{
			// No game is currently running.
			
			// Update the screen.
			vdraw_flip();
			
			// Determine how much sleep time to add, based on intro style.
			// TODO: Move this to v_draw.cpp?
			if (audio_get_gym_playing())
			{
				// PLAY GYM
				Play_GYM();
			}
			else if (Intro_Style == 1)
			{
				// Gens logo effect. (TODO: This is broken!)
				GensUI::sleep(5);
			}
			else if (Intro_Style == 2)
			{
				// "Strange" effect. (TODO: This is broken!)
				GensUI::sleep(10);
			}
			else if (Intro_Style == 3)
			{
				// Genesis BIOS. (TODO: This is broken!)
				GensUI::sleep(20);
			}
			else
			{
				// Blank screen. (MAX IDLE)
				GensUI::sleep(200);
			}
		}
	}
}
