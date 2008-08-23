/**
 * GENS: Main Window. (GTK+)
 */

#include "genswindow.h"
#include "genswindow_callbacks.h"

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

// GENS GTK+ miscellaneous functions
#include "gtk-misc.h"

GtkWidget *gens_window;
GtkWidget *MenuBar;

GtkAccelGroup *accel_group;
GtkTooltips *tooltips;

void create_genswindow_menubar(GtkWidget *container);
void create_genswindow_FileMenu(GtkWidget *container);
void create_genswindow_FileMenu_ChangeStateSubMenu(GtkWidget *container);
void create_genswindow_GraphicsMenu(GtkWidget *container);
void create_genswindow_GraphicsMenu_OpenGLResSubMenu(GtkWidget *container);
void create_genswindow_GraphicsMenu_bppSubMenu(GtkWidget *container);
void create_genswindow_GraphicsMenu_RenderSubMenu(GtkWidget *container);


// Set to 0 to temporarily disable callbacks.
int do_callbacks = 1;


// Macros from Glade used to store GtkWidget pointers.
#define GLADE_HOOKUP_OBJECT(component, widget, name)			\
{									\
	g_object_set_data_full(G_OBJECT(component), name,		\
			       gtk_widget_ref(widget),			\
			       (GDestroyNotify)gtk_widget_unref);	\
}


#define GLADE_HOOKUP_OBJECT_NO_REF(component, widget, name)		\
{									\
	g_object_set_data(G_OBJECT(component), name, widget);		\
};


// Macro to create a menu item easily.
#define NewMenuItem(MenuItemWidget, MenuItemCaption, MenuItemName, Container)			\
{												\
	MenuItemWidget = gtk_image_menu_item_new_with_mnemonic(MenuItemCaption);		\
	gtk_widget_set_name(MenuItemWidget, MenuItemName);					\
	gtk_widget_show(MenuItemWidget);							\
	gtk_container_add(GTK_CONTAINER(Container), MenuItemWidget);				\
	GLADE_HOOKUP_OBJECT(gens_window, MenuItemWidget, MenuItemName);				\
}


// Macro to create a menu item easily, with an icon.
#define NewMenuItem_Icon(MenuItemWidget, MenuItemCaption, MenuItemName, Container,		\
			 IconWidget, IconFilename)						\
{												\
	NewMenuItem(MenuItemWidget, MenuItemCaption, MenuItemName, Container);			\
	IconWidget = create_pixmap(gens_window, IconFilename);					\
	gtk_widget_set_name(IconWidget, MenuItemName "_Icon");					\
	gtk_widget_show(IconWidget);								\
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItemWidget), IconWidget);		\
	GLADE_HOOKUP_OBJECT(gens_window, IconWidget, MenuItemName "_Icon");			\
}


// Macro to create a menu item easily, with a stock GTK+ icon.
#define NewMenuItem_StockIcon(MenuItemWidget, MenuItemCaption, MenuItemName, Container,		\
			      IconWidget, IconName)						\
{												\
	NewMenuItem(MenuItemWidget, MenuItemCaption, MenuItemName, Container);			\
	IconWidget = gtk_image_new_from_stock(IconName, GTK_ICON_SIZE_MENU);			\
	gtk_widget_set_name(IconWidget, MenuItemName "_Icon");					\
	gtk_widget_show(IconWidget);								\
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(MenuItemWidget), IconWidget);		\
	GLADE_HOOKUP_OBJECT(gens_window, IconWidget, MenuItemName "_Icon");			\
}


// Macro to create a menu separator.
#define NewMenuSeparator(SeparatorWidget, SeparatorName, Container)				\
{												\
	SeparatorWidget = gtk_separator_menu_item_new();					\
	gtk_widget_set_name(SeparatorWidget, SeparatorName);					\
	gtk_widget_show(SeparatorWidget);							\
	gtk_container_add(GTK_CONTAINER(Container), SeparatorWidget);				\
	gtk_widget_set_sensitive(SeparatorWidget, FALSE);					\
	GLADE_HOOKUP_OBJECT(gens_window, SeparatorWidget, SeparatorName);			\
}


// Macro to create a menu item with radio buttons.
#define NewMenuItem_Radio(MenuItemWidget, MenuItemCaption, MenuItemName, Container, State, RadioGroup)	\
{												\
	MenuItemWidget = gtk_radio_menu_item_new_with_mnemonic(RadioGroup, (MenuItemCaption));	\
	RadioGroup = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(MenuItemWidget));	\
	gtk_widget_set_name(MenuItemWidget, MenuItemName);					\
	gtk_widget_show(MenuItemWidget);							\
	gtk_container_add(GTK_CONTAINER(Container), MenuItemWidget);				\
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(MenuItemWidget), State);		\
	GLADE_HOOKUP_OBJECT(gens_window, MenuItemWidget, MenuItemName);				\
}


// Macro to create a menu item with a checkbox.
#define NewMenuItem_Check(MenuItemWidget, MenuItemCaption, MenuItemName, Container, State)	\
{												\
	MenuItemWidget = gtk_check_menu_item_new_with_mnemonic(MenuItemCaption);		\
	gtk_widget_set_name(MenuItemWidget, MenuItemName);					\
	gtk_widget_show(MenuItemWidget);							\
	gtk_container_add(GTK_CONTAINER(Container), MenuItemWidget);				\
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(MenuItemWidget), State);		\
	GLADE_HOOKUP_OBJECT(gens_window, MenuItemWidget, MenuItemName);				\
}


// Macro to add an accelerator to a menu item.
#define AddMenuAccelerator(MenuItemWidget, Key, Modifier)					\
{												\
	gtk_widget_add_accelerator(MenuItemWidget, "activate", accel_group,			\
				   (Key), (GdkModifierType)(Modifier),				\
				   GTK_ACCEL_VISIBLE);						\
}


// Macro to add a callback to a menu item.
#define AddMenuCallback(MenuItemWidget, CallbackFunction)					\
{												\
	g_signal_connect((gpointer)MenuItemWidget, "activate",					\
			 G_CALLBACK (CallbackFunction), NULL);					\
}


GtkWidget* create_gens_window(void)
{
	GdkPixbuf *gens_window_icon_pixbuf;
	GtkWidget *vbox1;
	GtkWidget *handlebox1;
	
	tooltips = gtk_tooltips_new();
	accel_group = gtk_accel_group_new();
	
	// Create the GENS window.
	gens_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(gens_window, "gens_window");
	gtk_container_set_border_width(GTK_CONTAINER(gens_window), 5);
	gtk_window_set_title(GTK_WINDOW(gens_window), "Gens");
	gtk_window_set_position(GTK_WINDOW(gens_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(gens_window), 640, 480);
	GLADE_HOOKUP_OBJECT_NO_REF(gens_window, gens_window, "gens_window");
	
	// Load the window icon.
	gens_window_icon_pixbuf = create_pixbuf("Gens2.ico");
	if (gens_window_icon_pixbuf)
	{
		gtk_window_set_icon(GTK_WINDOW (gens_window), gens_window_icon_pixbuf);
		gdk_pixbuf_unref(gens_window_icon_pixbuf);
	}
	
	// Layout objects.
	vbox1 = gtk_vbox_new(FALSE, 0);
	gtk_widget_set_name(vbox1, "vbox1");
	gtk_widget_show(vbox1);
	gtk_container_add(GTK_CONTAINER(gens_window), vbox1);
	GLADE_HOOKUP_OBJECT(gens_window, vbox1, "vbox1");
	
	handlebox1 = gtk_handle_box_new();
	gtk_widget_set_name(handlebox1, "handlebox1");
	gtk_widget_show(handlebox1);
	gtk_box_pack_start(GTK_BOX(vbox1), handlebox1, FALSE, FALSE, 0);
	gtk_handle_box_set_shadow_type(GTK_HANDLE_BOX(handlebox1), GTK_SHADOW_NONE);
	gtk_handle_box_set_snap_edge(GTK_HANDLE_BOX(handlebox1), GTK_POS_LEFT);
	GLADE_HOOKUP_OBJECT(gens_window, vbox1, "handlebox1");
	
	// Create the menu bar.
	create_genswindow_menubar(handlebox1);
	
	// Add the accel group.
	gtk_window_add_accel_group(GTK_WINDOW(gens_window), accel_group);
	
	// Callbacks for if the window is closed.
	g_signal_connect ((gpointer)gens_window, "delete_event",
			  G_CALLBACK(on_gens_window_close), NULL);
	g_signal_connect ((gpointer)gens_window, "destroy_event",
			  G_CALLBACK(on_gens_window_close), NULL);
	
	return gens_window;
}


/**
 * create_genswindow_menubar(): Create the menu bar.
 * @param container Container for the menu bar.
 */
void create_genswindow_menubar(GtkWidget *container)
{
	MenuBar = gtk_menu_bar_new();
	gtk_widget_set_name(MenuBar, "MenuBar");
	gtk_widget_show(MenuBar);
	gtk_container_add(GTK_CONTAINER(container), MenuBar);
	
	// File menu.
	create_genswindow_FileMenu(MenuBar);
	
	// Graphic menu.
	create_genswindow_GraphicsMenu(MenuBar);
}


/**
 * create_genswindow_FileMenu(): Create the file menu.
 * @param container Container for this menu.
 */
void create_genswindow_FileMenu(GtkWidget *container)
{
	GtkWidget *File;			GtkWidget *File_Icon;
	GtkWidget *FileMenu;
	GtkWidget *FileMenu_OpenROM;		GtkWidget *FileMenu_OpenROM_Icon;
	GtkWidget *FileMenu_BootCD;		GtkWidget *FileMenu_BootCD_Icon;
	GtkWidget *FileMenu_Netplay;		GtkWidget *FileMenu_Netplay_Icon;
	GtkWidget *FileMenu_ROMHistory;		GtkWidget *FileMenu_ROMHistory_Icon;
	GtkWidget *FileMenu_CloseROM;		GtkWidget *FileMenu_CloseROM_Icon;
	GtkWidget *FileMenu_Separator1;
	GtkWidget *FileMenu_GameGenie;		GtkWidget *FileMenu_GameGenie_Icon;
	GtkWidget *FileMenu_Separator2;
	GtkWidget *FileMenu_LoadState;		GtkWidget *FileMenu_LoadState_Icon;
	GtkWidget *FileMenu_SaveState;		GtkWidget *FileMenu_SaveState_Icon;
	GtkWidget *FileMenu_QuickLoad;		GtkWidget *FileMenu_QuickLoad_Icon;
	GtkWidget *FileMenu_QuickSave;		GtkWidget *FileMenu_QuickSave_Icon;
	GtkWidget *FileMenu_ChangeState;	GtkWidget *FileMenu_ChangeState_Icon;
	GtkWidget *FileMenu_Quit;		GtkWidget *FileMenu_Quit_Icon;
	
	// File
	NewMenuItem_Icon(File, "_File", "File", container, File_Icon, "resource.png");
	
	// Menu object for the FileMenu
	FileMenu = gtk_menu_new();
	gtk_widget_set_name(FileMenu, "FileMenu");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(File), FileMenu);
	
	// Open ROM...
	NewMenuItem_Icon(FileMenu_OpenROM, "_Open ROM...", "FileMenu_OpenROM", FileMenu,
			 FileMenu_OpenROM_Icon, "folder_slin_open.png");
	AddMenuAccelerator(FileMenu_OpenROM, GDK_O, GDK_CONTROL_MASK);
	AddMenuCallback(FileMenu_OpenROM, on_FileMenu_OpenROM_activate);
	
	// Boot CD
	NewMenuItem_Icon(FileMenu_BootCD, "_Boot CD", "FileMenu_BootCD", FileMenu,
			 FileMenu_BootCD_Icon, "cdrom2_unmount.png");
	AddMenuAccelerator(FileMenu_BootCD, GDK_B, GDK_CONTROL_MASK);
	AddMenuCallback(FileMenu_BootCD, on_FileMenu_BootCD_activate);
	
	// Netplay (currently disabled)
	NewMenuItem_Icon(FileMenu_Netplay, "_Netplay", "FileMenu_Netplay", FileMenu,
			 FileMenu_Netplay_Icon, "Modem.png");
	gtk_widget_set_sensitive(FileMenu_Netplay, FALSE);
	
	// ROM History
	NewMenuItem_Icon(FileMenu_ROMHistory, "ROM _History", "FileMenu_ROMHistory", FileMenu,
			 FileMenu_ROMHistory_Icon, "history.png");
	// TODO: ROM History submenu
	
	// Close ROM
	NewMenuItem_Icon(FileMenu_CloseROM, "_Close ROM", "FileMenu_CloseROM", FileMenu,
			 FileMenu_CloseROM_Icon, "filleclose.png");
	gtk_widget_add_accelerator(FileMenu_CloseROM, "activate", accel_group,
				   GDK_W, (GdkModifierType)GDK_CONTROL_MASK,
				   GTK_ACCEL_VISIBLE);
	AddMenuCallback(FileMenu_CloseROM, on_FileMenu_CloseROM_activate);
	
	// Separator
	NewMenuSeparator(FileMenu_Separator1, "FileMenu_Separator1", FileMenu);
	
	// Game Genie
	NewMenuItem_Icon(FileMenu_GameGenie, "_Game Genie", "FileMenu_GameGenie", FileMenu,
			 FileMenu_GameGenie_Icon, "password.png");
	AddMenuCallback(FileMenu_GameGenie, on_FileMenu_GameGenie_activate);
	
	// Separator
	NewMenuSeparator(FileMenu_Separator2, "FileMenu_Separator2", FileMenu);
	
	// Load State...
	NewMenuItem_Icon(FileMenu_LoadState, "_Load State...", "FileMenu_LoadState", FileMenu,
			 FileMenu_LoadState_Icon, "folder_slin_open.png");
	AddMenuAccelerator(FileMenu_LoadState, GDK_F8, GDK_SHIFT_MASK);
	AddMenuCallback(FileMenu_LoadState, on_FileMenu_LoadState_activate);
	
	// Save State As...
	NewMenuItem_StockIcon(FileMenu_SaveState, "_Save State As...", "FileMenu_SaveState", FileMenu,
			      FileMenu_SaveState_Icon, "gtk-save-as");
	AddMenuAccelerator(FileMenu_SaveState, GDK_F5, GDK_SHIFT_MASK);
	AddMenuCallback(FileMenu_SaveState, on_FileMenu_SaveState_activate);
	
	// Quick Load
	NewMenuItem_Icon(FileMenu_QuickLoad, "Quick Load", "FileMenu_QuickLoad", FileMenu,
			 FileMenu_QuickLoad_Icon, "reload.png");
	AddMenuAccelerator(FileMenu_QuickLoad, GDK_F8, 0);
	AddMenuCallback(FileMenu_QuickLoad, on_FileMenu_QuickLoad_activate);
	
	// Quick Save
	NewMenuItem_StockIcon(FileMenu_QuickSave, "Quick Save", "FileMenu_QuickSave", FileMenu,
			      FileMenu_QuickSave_Icon, "gtk-save");
	AddMenuAccelerator(FileMenu_QuickSave, GDK_F5, 0);
	AddMenuCallback(FileMenu_QuickSave, on_FileMenu_QuickSave_activate);
	
	// Change State
	NewMenuItem_StockIcon(FileMenu_ChangeState, "Change State", "FileMenu_ChangeState", FileMenu,
			      FileMenu_ChangeState_Icon, "gtk-revert-to-saved");
	// Change State submenu
	create_genswindow_FileMenu_ChangeStateSubMenu(FileMenu_ChangeState);
	
	// Quit
	NewMenuItem_StockIcon(FileMenu_Quit, "_Quit", "FileMenu_Quit", FileMenu,
			      FileMenu_Quit_Icon, "gtk-quit");
	AddMenuAccelerator(FileMenu_Quit, GDK_Q, GDK_CONTROL_MASK);
	AddMenuCallback(FileMenu_Quit, on_FileMenu_Quit_activate);
}


/**
 * genswindow_FileMenu_ChangeStateSubMenu(): Create the Change State submenu.
 * @param container Container for this menu.
 */
#define CREATE_SAVE_SLOT(widget, ObjName, text, defState, callbackFunc)			\
{											\
	NewMenuItem_Radio(widget, text, ObjName, SubMenu, defState, SlotGroup);		\
	g_signal_connect((gpointer)widget, "activate", G_CALLBACK(callbackFunc), NULL);	\
}
void create_genswindow_FileMenu_ChangeStateSubMenu(GtkWidget *container)
{
	GtkWidget *SubMenu;
	GtkWidget *FileMenu_ChangeState_SubMenu_0;
	GtkWidget *FileMenu_ChangeState_SubMenu_1;
	GtkWidget *FileMenu_ChangeState_SubMenu_2;
	GtkWidget *FileMenu_ChangeState_SubMenu_3;
	GtkWidget *FileMenu_ChangeState_SubMenu_4;
	GtkWidget *FileMenu_ChangeState_SubMenu_5;
	GtkWidget *FileMenu_ChangeState_SubMenu_6;
	GtkWidget *FileMenu_ChangeState_SubMenu_7;
	GtkWidget *FileMenu_ChangeState_SubMenu_8;
	GtkWidget *FileMenu_ChangeState_SubMenu_9;
	GSList *SlotGroup = NULL;
	
	// Create the submenu.
	SubMenu = gtk_menu_new();
	gtk_widget_set_name(SubMenu, "FileMenu_ChangeState_SubMenu");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(container), SubMenu);
	
	// Create the save slot entries.
	CREATE_SAVE_SLOT(FileMenu_ChangeState_SubMenu_0, "FileMenu_ChangeState_SubMenu_0",
			 "0", TRUE, on_FileMenu_ChangeState_SubMenu_0_activate);
	CREATE_SAVE_SLOT(FileMenu_ChangeState_SubMenu_1, "FileMenu_ChangeState_SubMenu_1",
			 "1", FALSE, on_FileMenu_ChangeState_SubMenu_1_activate);
	CREATE_SAVE_SLOT(FileMenu_ChangeState_SubMenu_2, "FileMenu_ChangeState_SubMenu_2",
			 "2", FALSE, on_FileMenu_ChangeState_SubMenu_2_activate);
	CREATE_SAVE_SLOT(FileMenu_ChangeState_SubMenu_3, "FileMenu_ChangeState_SubMenu_3",
			 "3", FALSE, on_FileMenu_ChangeState_SubMenu_3_activate);
	CREATE_SAVE_SLOT(FileMenu_ChangeState_SubMenu_4, "FileMenu_ChangeState_SubMenu_4",
			 "4", FALSE, on_FileMenu_ChangeState_SubMenu_4_activate);
	CREATE_SAVE_SLOT(FileMenu_ChangeState_SubMenu_5, "FileMenu_ChangeState_SubMenu_5",
			 "5", FALSE, on_FileMenu_ChangeState_SubMenu_5_activate);
	CREATE_SAVE_SLOT(FileMenu_ChangeState_SubMenu_6, "FileMenu_ChangeState_SubMenu_6",
			 "6", FALSE, on_FileMenu_ChangeState_SubMenu_6_activate);
	CREATE_SAVE_SLOT(FileMenu_ChangeState_SubMenu_7, "FileMenu_ChangeState_SubMenu_7",
			 "7", FALSE, on_FileMenu_ChangeState_SubMenu_7_activate);
	CREATE_SAVE_SLOT(FileMenu_ChangeState_SubMenu_8, "FileMenu_ChangeState_SubMenu_8",
			 "8", FALSE, on_FileMenu_ChangeState_SubMenu_8_activate);
	CREATE_SAVE_SLOT(FileMenu_ChangeState_SubMenu_9, "FileMenu_ChangeState_SubMenu_9",
			 "9", FALSE, on_FileMenu_ChangeState_SubMenu_9_activate);
}


/**
 * create_genswindow_FileMenu(): Create the file menu.
 * @param container Container for this menu.
 */
void create_genswindow_GraphicsMenu(GtkWidget *container)
{
	GtkWidget *Graphic;			GtkWidget *Graphic_Icon;
	GtkWidget *GraphicsMenu;
	GtkWidget *GraphicsMenu_FullScreen;	GtkWidget *GraphicsMenu_FullScreen_Icon;
	GtkWidget *GraphicsMenu_VSync;
	GtkWidget *GraphicsMenu_Stretch;
	GtkWidget *GraphicsMenu_Separator1;
	GtkWidget *GraphicsMenu_OpenGL;
	GtkWidget *GraphicsMenu_OpenGLRes;
	GtkWidget *GraphicsMenu_bpp;
	GtkWidget *GraphicsMenu_Separator2;
	GtkWidget *GraphicsMenu_ColorAdjust;	GtkWidget *GraphicsMenu_ColorAdjust_Icon;
	GtkWidget *GraphicsMenu_Render;		GtkWidget *GraphicsMenu_Render_Icon;
	GtkWidget *GraphicsMenu_Separator3;
	GtkWidget *GraphicsMenu_SpriteLimit;
	GtkWidget *GraphicsMenu_Separator4;
	GtkWidget *GraphicsMenu_FrameSkip;	GtkWidget *GraphicsMenu_FrameSkip_Icon;
	GtkWidget *GraphicsMenu_Separator5;
	GtkWidget *GraphicsMenu_ScreenShot;	GtkWidget *GraphicsMenu_ScreenShot_Icon;
	
	// Graphic
	NewMenuItem_Icon(Graphic, "_Graphics", "Graphics", container, Graphic_Icon, "xpaint.png");
	
	// Menu object for the GraphicsMenu
	GraphicsMenu = gtk_menu_new();
	gtk_widget_set_name(GraphicsMenu, "GraphicsMenu");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(Graphic), GraphicsMenu);
	
	// Full Screen
	NewMenuItem_Icon(GraphicsMenu_FullScreen, "_Full Screen", "GraphicsMenu_FullScreen", GraphicsMenu,
			 GraphicsMenu_FullScreen_Icon, "viewmag1.png");
	AddMenuAccelerator(GraphicsMenu_FullScreen, GDK_Return, GDK_MOD1_MASK);
	AddMenuCallback(GraphicsMenu_FullScreen, on_GraphicsMenu_FullScreen_activate);
	
	// VSync
	NewMenuItem_Check(GraphicsMenu_VSync, "_VSync", "GraphicsMenu_VSync", GraphicsMenu, FALSE);
	AddMenuAccelerator(GraphicsMenu_VSync, GDK_F3, GDK_SHIFT_MASK);
	AddMenuCallback(GraphicsMenu_VSync, on_GraphicsMenu_VSync_activate);
	
	// Stretch
	NewMenuItem_Check(GraphicsMenu_Stretch, "_Stretch", "GraphicsMenu_Stretch", GraphicsMenu, FALSE);
	AddMenuAccelerator(GraphicsMenu_Stretch, GDK_F2, GDK_SHIFT_MASK);
	AddMenuCallback(GraphicsMenu_Stretch, on_GraphicsMenu_Stretch_activate);
	
	// Separator
	NewMenuSeparator(GraphicsMenu_Separator1, "GraphicsMenu_Separator1", GraphicsMenu);
	
	// OpenGL
	NewMenuItem_Check(GraphicsMenu_OpenGL, "Open_GL", "GraphicsMenu_OpenGL", GraphicsMenu, FALSE);
	AddMenuAccelerator(GraphicsMenu_OpenGL, GDK_r, GDK_SHIFT_MASK);
	AddMenuCallback(GraphicsMenu_OpenGL, on_GraphicsMenu_OpenGL_activate);
	
	// OpenGL Resolution
	NewMenuItem(GraphicsMenu_OpenGLRes, "OpenGL Resolution", "GraphicsMenu_OpenGLRes", GraphicsMenu);
	// OpenGL Resolution submenu
	create_genswindow_GraphicsMenu_OpenGLResSubMenu(GraphicsMenu_OpenGLRes);
	
	// Bits per pixel (OpenGL mode) [TODO: Where is this value actually used?]
	NewMenuItem(GraphicsMenu_bpp, "Bits per pixel", "GraphicsMenu_bpp", GraphicsMenu);
	// Bits per pixel submenu
	create_genswindow_GraphicsMenu_bppSubMenu(GraphicsMenu_bpp);
	
	// Separator
	NewMenuSeparator(GraphicsMenu_Separator2, "GraphicsMenu_Separator2", GraphicsMenu);
	
	// Color Adjust
	NewMenuItem_StockIcon(GraphicsMenu_ColorAdjust, "Color Adjust...", "GraphicsMenu_ColorAdjust", GraphicsMenu,
			      GraphicsMenu_ColorAdjust_Icon, "gtk-select-color");
	AddMenuCallback(GraphicsMenu_ColorAdjust, on_GraphicsMenu_ColorAdjust_activate);
	
	// Render
	NewMenuItem_Icon(GraphicsMenu_Render, "_Render", "GraphicsMenu_Render", GraphicsMenu,
			 GraphicsMenu_Render_Icon, "viewmag.png");
	// Render submenu
	create_genswindow_GraphicsMenu_RenderSubMenu(GraphicsMenu_Render);
	
	// Separator
	NewMenuSeparator(GraphicsMenu_Separator3, "GraphicsMenu_Separator3", GraphicsMenu);
	
	// Sprite Limit
	NewMenuItem_Check(GraphicsMenu_SpriteLimit, "Sprite Limit", "GraphicsMenu_SpriteLimit", GraphicsMenu, TRUE);
	AddMenuCallback(GraphicsMenu_SpriteLimit, on_GraphicsMenu_SpriteLimit_activate);
	
	// Separator
	NewMenuSeparator(GraphicsMenu_Separator4, "GraphicsMenu_Separator4", GraphicsMenu);
	
	// Frame Skip
	NewMenuItem_Icon(GraphicsMenu_FrameSkip, "Frame Skip", "GraphicsMenu_FrameSkip", GraphicsMenu,
			 GraphicsMenu_FrameSkip_Icon, "2rightarrow.png");
	// TODO: Frame Skip submenu
	
	// Separator
	NewMenuSeparator(GraphicsMenu_Separator5, "GraphicsMenu_Separator5", GraphicsMenu);
	
	// Screen Shot
	NewMenuItem_Icon(GraphicsMenu_ScreenShot, "Screen Shot", "GraphicsMenu_ScreenShot", GraphicsMenu,
			 GraphicsMenu_ScreenShot_Icon, "editcopy.png");
	AddMenuAccelerator(GraphicsMenu_ScreenShot, GDK_BackSpace, GDK_SHIFT_MASK);
	AddMenuCallback(GraphicsMenu_ScreenShot, on_GraphicsMenu_ScreenShot_activate);
}


/**
 * create_genswindow_GraphicsMenu_OpenGLResSubMenu(): Create the OpenGL Resolution submenu.
 * @param container Container for this menu.
 */
void create_genswindow_GraphicsMenu_OpenGLResSubMenu(GtkWidget *container)
{
	GtkWidget *SubMenu;
	GtkWidget *ResItem;
	GSList *ResGroup = NULL;
	
	// TODO: Move this array somewhere else.
	int resolutions[5][2] =
	{
		{320, 240},
		{640, 480},
		{800, 600},
		{1024, 768},
		{-1, -1}, // Custom
	};
	
	int i;
	char ObjName[64];
	char ResName[16];
	
	// Create the submenu.
	SubMenu = gtk_menu_new();
	gtk_widget_set_name(SubMenu, "GraphicsMenu_OpenGLRes_SubMenu");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(container), SubMenu);
	
	// Create the resolution entries.
	for (i = 0; i < 5; i++)
	{
		if (resolutions[i][0] > 0)
			sprintf(ResName, "%dx%d", resolutions[i][0], resolutions[i][1]);
		else
			strcpy(ResName, "Custom");
		
		sprintf(ObjName, "GraphicsMenu_OpenGLRes_SubMenu_%s", ResName);
		NewMenuItem_Radio(ResItem, ResName, ObjName, SubMenu, (i == 0 ? TRUE : FALSE), ResGroup);
		// TODO: Somehow pass the resolution ID using the parameter.
		//g_signal_connect((gpointer)ResItem, G_CALLBACK(on_ResItem_activate), NULL);
	}
}


/**
 * create_genswindow_GraphicsMenu_bppSubMenu(): Create the bits per pixel submenu.
 * @param container Container for this menu.
 */
void create_genswindow_GraphicsMenu_bppSubMenu(GtkWidget *container)
{
	GtkWidget *SubMenu;
	GtkWidget *GraphicsMenu_bpp_SubMenu_16;
	GtkWidget *GraphicsMenu_bpp_SubMenu_24;
	GtkWidget *GraphicsMenu_bpp_SubMenu_32;
	GSList *bppGroup = NULL;
	
	// Create the submenu.
	SubMenu = gtk_menu_new();
	gtk_widget_set_name(SubMenu, "GraphicsMenu_bpp_SubMenu");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(container), SubMenu);
	
	// Create the resolution entries.
	/*
	NewMenuItem_Radio(GraphicsMenu_bpp_SubMenu_16, "16",
			  "GraphicsMenu_bpp_SubMenu_16", SubMenu, FALSE, bppGroup);
	g_signal_connect((gpointer)GraphicsMenu_bpp_SubMenu_16, "activate",
			 G_CALLBACK(on_GraphicsMenu_bpp_SubMenu_16_activate), NULL);
	
	NewMenuItem_Radio(GraphicsMenu_bpp_SubMenu_24, "24",
			  "GraphicsMenu_bpp_SubMenu_24", SubMenu, FALSE, bppGroup);
	g_signal_connect((gpointer)GraphicsMenu_bpp_SubMenu_24, "activate",
			 G_CALLBACK(on_GraphicsMenu_bpp_SubMenu_24_activate), NULL);

	NewMenuItem_Radio(GraphicsMenu_bpp_SubMenu_32, "32",
			  "GraphicsMenu_bpp_SubMenu_32", SubMenu, FALSE, bppGroup);
	g_signal_connect((gpointer)GraphicsMenu_bpp_SubMenu_32, "activate",
			 G_CALLBACK(on_GraphicsMenu_bpp_SubMenu_32_activate), NULL);
	*/
}


/**
 * create_genswindow_GraphicsMenu_RenderSubMenu(): Create the Render submenu.
 * @param container Container for this menu.
 */
void create_genswindow_GraphicsMenu_RenderSubMenu(GtkWidget *container)
{
	GtkWidget *SubMenu;
	GtkWidget *RenderItem;
	GSList *RenderGroup = NULL;
	
	// TODO: Move this array somewhere else.
	const char* Render[12] =
	{
		"Normal",
		"Double",
		"Interpolated",
		"Scanline",
		"50% Scanline",
		"25% Scanline",
		"Interpolated Scanline",
		"Interpolated 50% Scanline",
		"Interpolated 25% Scanline",
		"2xSAI (Kreed)",
		"Scale2x",
		"Hq2x",
	};
	const char* RenderTag[12] =
	{
		"normal",
		"double",
		"int",
		"scan",
		"50scan",
		"25scan",
		"intscan",
		"int50scan",
		"int25scan",
		"_2xsai",
		"scale2x",
		"hq2x",
	};
	
	int i;
	char ObjName[64];
	
	// Create the submenu.
	SubMenu = gtk_menu_new();
	gtk_widget_set_name(SubMenu, "GraphicsMenu_Render_SubMenu");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(container), SubMenu);
	
	// Create the render entries.
	for (i = 0; i < 12; i++)
	{
		sprintf(ObjName, "GraphicsMenu_OpenGLRes_SubMenu_%s", RenderTag[i]);
		NewMenuItem_Radio(RenderItem, Render[i], ObjName, SubMenu, (i == 0 ? TRUE : FALSE), RenderGroup);
		// TODO: Somehow pass the render ID using the parameter.
		//g_signal_connect((gpointer)RenderItem, G_CALLBACK(on_RenderItem_activate), NULL);
	}
}
