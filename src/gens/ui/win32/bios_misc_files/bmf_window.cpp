/***************************************************************************
 * Gens: (Win32) BIOS/Misc Files Window.                                   *
 *                                                                         *
 * Copyright (c) 1999-2002 by Stéphane Dallongeville                       *
 * Copyright (c) 2003-2004 by Stéphane Akhoun                              *
 * Copyright (c) 2008-2010 by David Korth                                  *
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

#include "bmf_window.hpp"
#include "ui/common/bmf_window_common.h"
#include "emulator/g_main.hpp"
#include "gens/gens_window.h"

#include "gens_ui.hpp"

// C includes.
#include <stdio.h>
#include <string.h>

// C++ includes.
#include <string>
using std::string;

// Win32 includes.
#include "libgsft/w32u/w32u_windows.h"
#include "libgsft/w32u/w32u_windowsx.h"
#include "libgsft/w32u/w32u_commctrl.h"
#include "ui/win32/resource.h"

// libgsft includes.
#include "libgsft/gsft_win32.h"
#include "libgsft/gsft_win32_gdi.h"
#include "libgsft/gsft_szprintf.h"

// Window.
HWND bmf_window = NULL;

// Window class.
static WNDCLASS bmf_wndclass;

// Window size. (NOTE: THESE ARE IN DIALOG UNITS, and must be converted to pixels using DLU_X() / DLU_Y().)
#define BMF_WINDOW_WIDTH  245
#define BMF_WINDOW_HEIGHT 225

#define BMF_FRAME_WIDTH (BMF_WINDOW_WIDTH-10)

// Widgets.
static HWND	txtFile[12];
static HWND	btnOK, btnCancel, btnApply;
#define IDC_BMF_TXTFILE 0x8000

// Window procedure.
static LRESULT CALLBACK bmf_window_wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Widget creation functions.
static void WINAPI bmf_window_create_child_windows(HWND hWnd);

// Configuration load/save functions.
static void WINAPI bmf_window_init(void);
static void WINAPI bmf_window_save(void);

// Callbacks.
static void WINAPI bmf_window_callback_btnChange_clicked(int file);


/**
 * bmf_window_show(): Show the BIOS/Misc Files window.
 */
void bmf_window_show(void)
{
	if (bmf_window)
	{
		// BIOS/Misc Files window is already visible. Set focus.
		// TODO: Figure out how to do this.
		ShowWindow(bmf_window, SW_SHOW);
		return;
	}
	
	if (bmf_wndclass.lpfnWndProc != bmf_window_wndproc)
	{
		// Create the window class.
		bmf_wndclass.style = 0;
		bmf_wndclass.lpfnWndProc = bmf_window_wndproc;
		bmf_wndclass.cbClsExtra = 0;
		bmf_wndclass.cbWndExtra = 0;
		bmf_wndclass.hInstance = ghInstance;
		bmf_wndclass.hIcon = LoadIconA(ghInstance, MAKEINTRESOURCE(IDI_GENS_APP));
		bmf_wndclass.hCursor = LoadCursorA(NULL, IDC_ARROW);
		bmf_wndclass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
		bmf_wndclass.lpszMenuName = NULL;
		bmf_wndclass.lpszClassName = "bmf_window";
		
		pRegisterClassU(&bmf_wndclass);
	}
	
	// Create the window.
	bmf_window = pCreateWindowU("bmf_window", "BIOS/Misc Files",
					WS_DLGFRAME | WS_POPUP | WS_SYSMENU | WS_CAPTION,
					CW_USEDEFAULT, CW_USEDEFAULT,
					DLU_X(BMF_WINDOW_WIDTH), DLU_Y(BMF_WINDOW_HEIGHT),
					gens_window, NULL, ghInstance, NULL);
	
	// Set the actual window size.
	gsft_win32_set_actual_window_size(bmf_window, DLU_X(BMF_WINDOW_WIDTH), DLU_Y(BMF_WINDOW_HEIGHT));
	
	// Center the window on the parent window.
	gsft_win32_center_on_window(bmf_window, gens_window);
	
	UpdateWindow(bmf_window);
	ShowWindow(bmf_window, SW_SHOW);
}


/**
 * bmf_window_create_child_windows(): Create child windows.
 * @param hWnd HWND of the parent window.
 */
static void WINAPI bmf_window_create_child_windows(HWND hWnd)
{
	// Create all frames.
	HWND grpBox;
	
	// Positioning.
	int grpBox_Top = 0, grpBox_Height = 0, grpBox_Entry = 0;
	int entryTop;
	
	for (int file = 0; bmf_entries[file].title != NULL; file++)
	{
		if (!bmf_entries[file].entry)
		{
			// No entry buffer. This is a new frame.
			grpBox_Top += grpBox_Height + DLU_Y(5);
			grpBox_Height = DLU_Y(15);
			grpBox_Entry = 0;
			
			grpBox = pCreateWindowU(WC_BUTTON, bmf_entries[file].title,
						WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
						DLU_X(5), grpBox_Top,
						DLU_X(BMF_FRAME_WIDTH), grpBox_Height,
						hWnd, NULL, ghInstance, NULL);
			SetWindowFontU(grpBox, w32_fntMessage, true);
		}
		else
		{
			// File entry.
			grpBox_Height += DLU_Y(15);
			entryTop = DLU_Y(12) + (grpBox_Entry * DLU_Y(15));
			SetWindowPos(grpBox, NULL, 0, 0,
					DLU_X(BMF_FRAME_WIDTH), grpBox_Height,
					SWP_NOMOVE | SWP_NOZORDER);
			
			// Create the label for the file.
			HWND lblFile = pCreateWindowU(WC_STATIC, bmf_entries[file].title,
							WS_CHILD | WS_VISIBLE | SS_LEFT,
							DLU_X(5+5), grpBox_Top + entryTop + DLU_Y(1),
							DLU_X(45), DLU_Y(10),
							hWnd, NULL, ghInstance, NULL);
			SetWindowFontU(lblFile, w32_fntMessage, true);
			
			// Create the textbox for the file.
			txtFile[file] = pCreateWindowExU(WS_EX_CLIENTEDGE, WC_EDIT, NULL,
								WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_LEFT | ES_AUTOHSCROLL,
								DLU_X(5+5+45+5), grpBox_Top+entryTop,
								DLU_X(BMF_FRAME_WIDTH-(5+45+5+45+5+5)), DLU_Y(12),
								hWnd, (HMENU)(IDC_BMF_TXTFILE + file), ghInstance, NULL);
			SetWindowFontU(txtFile[file], w32_fntMessage, true);
			Edit_LimitTextU(txtFile[file], GENS_PATH_MAX-1);
			
			// Create the "Change..." button for the file.
			HWND btnChange = pCreateWindowU(WC_BUTTON, "Change...",
							WS_CHILD | WS_VISIBLE | WS_TABSTOP,
							DLU_X(5+BMF_FRAME_WIDTH-(5+45)), grpBox_Top + entryTop,
							DLU_X(45), DLU_Y(12),
							hWnd, (HMENU)(IDC_BTN_CHANGE + file), ghInstance, NULL);
			SetWindowFontU(btnChange, w32_fntMessage, true);
			
			// Next entry.
			grpBox_Entry++;
		}
	}
	
	// Create the dialog buttons.
	
	const int btnTop = DLU_Y(BMF_WINDOW_HEIGHT-5-14);
	int btnLeft = DLU_X(BMF_WINDOW_WIDTH-5-50-5-50-5-50);
	const int btnInc = DLU_X(5+50);
	
	// OK button.
	btnOK = pCreateWindowU(WC_BUTTON, "&OK",
				WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
				btnLeft, btnTop,
				DLU_X(50), DLU_Y(14),
				hWnd, (HMENU)IDOK, ghInstance, NULL);
	SetWindowFontU(btnOK, w32_fntMessage, true);
	
	// Cancel button.
	btnLeft += btnInc;
	btnCancel = pCreateWindowU(WC_BUTTON, "&Cancel",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP,
					btnLeft, btnTop,
					DLU_X(50), DLU_Y(14),
					hWnd, (HMENU)IDCANCEL, ghInstance, NULL);
	SetWindowFontU(btnCancel, w32_fntMessage, true);
	
	// Apply button.
	btnLeft += btnInc;
	btnApply = pCreateWindowU(WC_BUTTON, "&Apply",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP,
					btnLeft, btnTop,
					DLU_X(50), DLU_Y(14),
					hWnd, (HMENU)IDAPPLY, ghInstance, NULL);
	SetWindowFontU(btnApply, w32_fntMessage, true);
	
	// Disable the "Apply" button initially.
	Button_Enable(btnApply, false);
	
	// Initialize the file textboxes.
	bmf_window_init();
	
	// Set focus to the first textbox.
	// (Index 0 is the frame; Index 1 is the textbox.)
	SetFocus(txtFile[1]);
}


/**
 * bmf_window_close(): Close the About window.
 */
void bmf_window_close(void)
{
	if (!bmf_window)
		return;
	
	// Destroy the window.
	DestroyWindow(bmf_window);
	bmf_window = NULL;
}


/**
 * bmf_window_init(): Initialize the file text boxes.
 */
static void WINAPI bmf_window_init(void)
{
	for (int file = 0; bmf_entries[file].title != NULL; file++)
	{
		if (!bmf_entries[file].entry)
			continue;
		
		// Set the entry text.
		Edit_SetTextU(txtFile[file], bmf_entries[file].entry);
	}
	
	// Disable the "Apply" button initially.
	Button_Enable(btnApply, false);
}


/**
 * bmf_window_save(): Save the BIOS/Misc Files.
 */
static void WINAPI bmf_window_save(void)
{
	int file;
	for (file = 0; bmf_entries[file].title != NULL; file++)
	{
		if (!bmf_entries[file].entry)
			continue;
		
		// Save the entry text.
		Edit_GetTextU(txtFile[file], bmf_entries[file].entry, GENS_PATH_MAX-1);
		bmf_entries[file].entry[GENS_PATH_MAX-1] = 0x00;
	}
	
	// Disable the "Apply" button.
	Button_Enable(btnApply, false);
}


/**
 * bmf_window_wndproc(): Window procedure.
 * @param hWnd hWnd of the window.
 * @param message Window message.
 * @param wParam
 * @param lParam
 * @return
 */
static LRESULT CALLBACK bmf_window_wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE:
			bmf_window_create_child_windows(hWnd);
			break;
		
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDOK:
					bmf_window_save();
					DestroyWindow(hWnd);
					break;
				case IDCANCEL:
					DestroyWindow(hWnd);
					break;
				case IDAPPLY:
					bmf_window_save();
					break;
				default:
					switch (LOWORD(wParam) & 0xFF00)
					{
						case IDC_BTN_CHANGE:
							bmf_window_callback_btnChange_clicked(LOWORD(wParam) & 0xFF);
							break;
						case IDC_BMF_TXTFILE:
							if (HIWORD(wParam) == EN_CHANGE)
							{
								// File textbox was changed.
								// Enable the "Apply" button.
								Button_Enable(btnApply, true);
							}
							break;
						default:
							// Unknown command identifier.
							break;
					}
					break;
			}
			break;
		
		case WM_DESTROY:
			if (hWnd != bmf_window)
				break;
			
			bmf_window = NULL;
			break;
		
		default:
			break;
	}
	
	return pDefWindowProcU(hWnd, message, wParam, lParam);
}


/**
 * bmf_window_callback_btnChange_clicked(): A "Change..." button was clicked.
 * @param file File ID number.
 */
static void WINAPI bmf_window_callback_btnChange_clicked(int file)
{
	// Check that this is a valid file entry.
	if (!bmf_entries[file].entry)
		return;
	
	char tmp[64];
	szprintf(tmp, sizeof(tmp), "Select %s File", bmf_entries[file].title);
	
	// Get the currently entered filename.
	char cur_file[GENS_PATH_MAX];
	Edit_GetTextU(txtFile[file], cur_file, sizeof(cur_file));
	cur_file[sizeof(cur_file)-1] = 0x00;
	
	// Request a new file.
	string new_file = GensUI::openFile(tmp, cur_file, bmf_entries[file].filter, bmf_window);
	
	// If "Cancel" was selected, don't do anything.
	if (new_file.empty())
		return;
	
	// Set the new file.
	Edit_SetTextU(txtFile[file], new_file.c_str());
	
	// Enable the "Apply" button.
	Button_Enable(btnApply, true);
}
