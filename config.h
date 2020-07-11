/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 3;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 30;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int statuspad	    = 15;
static const char *fonts[]          = { "JetBrainsMono Nerd Font Mono:style=Regular:pixelsize=14:antialias=true:autohint=true","JoyPixels:pixelsize=18:style=Regular:antialias=true:autohint=true"};
static const char dmenufont[]       = { "JetBrainsMono Nerd Font:pixelsize=16:antialias=true:autohint=true" };
static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int vertpad            = 5;       /* vertical padding of bar */
static const int sidepad            = 5;       /* horizontal padding of bar */
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1,  col_gray3  },
	[SchemeStatus]  = { col_gray4, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray4, col_gray1,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_gray4, col_gray1,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray4, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};
static const char *const autostart[] = {
	NULL /* terminate */
};

/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static char *tags[] = { "1:", "2:", "3:" , "4:", "5:" , "6:" , "7:  " , "8:ﯙ" , "9:漣" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class	     						instance  title        		tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",								NULL,     NULL,				0,         1,          0,           0,        -1 },
	{ "firefox",							NULL,     "Firefox",			1 << 1,    0,          0,          -1,        -1 },
	{ "Chromium",							NULL,     NULL,				1 << 1,    0,          0,          -1,        -1 },
	{ "TelegramDesktop",					NULL,     NULL,				1 << 6,    0,          0,          -1,        -1 },
	{ "St",									NULL,     NULL,				0,         0,          1,           0,        -1 },
	{ NULL,									NULL,     "Event Tester", 	0,         1,          0,           1,        -1 }, /* xev */
	{ "Thunar",								NULL,     NULL,           	1 << 5 ,   0,          0,          -1,        -1 },
	{ "code-oss",							NULL,     NULL,          	1 << 2,    0,          0,          -1,        -1 },
	{ "VSCodium",							NULL,     NULL,         	1 << 2,    0,          0,          -1,        -1 },
	{ "jetbrains-studio",					NULL,     NULL,				1 << 4,	   0,		   0,		   -1,        -1 },
	{ "Microsoft Teams - Preview",			NULL,     NULL,				0,         1,          0,          -1,        -1 },
	{ "Genymotion Player",					NULL,     NULL,				0,         1,          0,          -1,        -1 },
};

#include "layouts/fibonacci.c"
#include "layouts/bstack.c"
#include "layouts/deck.c"
#include "layouts/columns.c"
#include "layouts/gapplessgrid.c"
#include "layouts/centeredfloatingmaster.c"
#include "layouts/centeredmaster.c"
#include "layouts/grid.c"
#include "layouts/horizgrid.c"

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " [] ",      tile },    /* first entry is default */
	{ " <> ",      NULL },    /* no layout function means floating behavior */
	{ " [M] ",      monocle },
	{ " [\] ",     dwindle }, // fibonacci dwindle
	{ " (@) ",      spiral }, // fibonacci spiral
	{ "TTT",      bstack},
	{"|M|",      centeredmaster}, 
	{ "[D]",      deck},
	{ ":::",      gaplessgrid},
	{ ">M>",      centeredfloatingmaster },
	{ "HHH",      grid },
	{ "---",      horizgrid },
	{ "|||",      col },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "j4-dmenu-desktop --dmenu 'dmenu_run -l 10 -x 680 -y 390 -w 500'"};
//, "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static Key keys[] = {
	/* modifier                     key        function        argument */
//	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	//{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Down,     focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Up,   focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ Mod1Mask,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	//{ MODKEY|ShiftMask,             XK_comma,  focusmon,       {.i = -1 } },
	//{ MODKEY|ShiftMask,             XK_period, focusmon,       {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_l,      incrgaps,       {.i = -1 } },
//	{ MODKEY|Mod1Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
//	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
//	{ MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
//	{ MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
//	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
//	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
//	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
//	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
//	{ MODKEY|Mod1Mask,              XK_y,      incrohgaps,     {.i = +1 } },
//	{ MODKEY|Mod1Mask,              XK_o,      incrohgaps,     {.i = -1 } },
//	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
//	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY,             		XK_Tab,      cycleview,     {.i=1} },
	{ MODKEY|ShiftMask,           XK_Tab,      cycleview,     {.i=0} },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

