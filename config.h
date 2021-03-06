/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int floatindicator =
    0; /* draw a rectanglular indicator for floating windows */
static const unsigned int drawunderline = 1; /* draw only underline under bar */
static const unsigned int barborder =
    0; /* draw border around bar , overrider drawunderline*/
static const unsigned int barborderpx = 2; /* size of underline under bar*/
static const unsigned int notitle = 1;     /* display window name*/
static unsigned int borderpx = 1;          /* border pixel of windows */
static const unsigned int snap = 3;        /* snap pixel */
static const int swallowfloating =
    0;                         /* 1 means swallow floating windows by default */
static const int showbar = 1;  /* 0 means no bar */
static const int topbar = 1;   /* 0 means bottom bar */
static const int user_bh = 29; /* 0 means that dwm will calculate bar height, >=
                                  1 means dwm will user_bh as bar height */
static const char *fonts[] = {"Symbols Nerd Font:style=2048-em:size=12",
                              "Hurmit Nerd Font Mono:style=medium:size=9"};
static const char dmenufont[] = {
    "JetBrains Mono:pixelsize=18:antialias=true:autohint=true"};
static unsigned int gappih = 10; /* horiz inner gap between windows */
static unsigned int gappiv = 10; /* vert inner gap between windows */
static unsigned int gappoh =
    10; /* horiz outer gap between windows and screen edge */
static unsigned int gappov =
    10; /* vert outer gap between windows and screen edge */
static int smartgaps =
    0;                  /* 1 means no outer gap when there is only one window */
static int vertpad = 1; /* vertical padding of bar */
static int sidepad = 1; /* horizontal padding of bar */
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
#define OPAQUE 0xff
static const unsigned int baralpha = 0xff;
static const unsigned int borderalpha = OPAQUE;
static int usealtbar = 1;                   /* 1 means use non-dwm status bar */
static int altbar_bh = 20;                  /* altbar height */
static const char *altbarclass = "Polybar"; /* Alternate bar class name */
static const char *alttrayname = "tray";    /* Polybar tray instance name */
static const char *altbarcmd =
    "/home/dhruv/.config/polybar/launch.sh &"; /* Alternate bar launch command
                                                */
#define BROWSER "firefox"
#define TERMINAL "alacritty"
#define EDITOR "nvim"

static const char *colors[][3] = {
    /*                         fg             bg        border   */
    [SchemeNorm] = {col_gray3, "#1f2430", "#5E6470"},
    [SchemeSel] = {col_gray4, "#1f2430", "#dab997"},
    [SchemeStatus] = {"#ffffff", "#1f2430",
                      "#000000"}, // Statusbar right {text,background,not used
                                  // // but cannot be empty}
    [SchemeTagsSel] = {"#1f2430", "#dab997",
                       "#000000"}, // Tagbar left selected {text,background,not
                                   // // used but cannot be empty}
    [SchemeTagsNorm] =
        {"#ffffff", "#1f2430",
         "#000000"}, // Tagbar left unselected {text,background,not used but //
                     // cannot be empty}
    [SchemeTagsUrgent] =
        {"#1f2430", "#ff6666",
         "#000000"}, // Tagbar left unselected {text,background,not used but //
                     // cannot be empty}
    [SchemeInfoSel] =
        {col_gray4, "#1f2430",
         "#000000"}, // infobar middle  selected {text,background,not used but
                     // // cannot be empty}
    [SchemeInfoNorm] =
        {col_gray4, "#1f2430",
         "#000000"}, // infobar middle  unselected {text,background,not used //
                     // but cannot be empty}
    [SchemeBarBorder] = {"#a6e1ff", "#a6e1ff", "#a6e1ff"}, // border around bar
};

static const unsigned int alphas[][3] = {
    /*                      fg      bg        border     */
    [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeSel] = {OPAQUE, baralpha, borderalpha},
    [SchemeStatus] = {OPAQUE, baralpha, borderalpha},
    [SchemeTagsSel] = {OPAQUE, OPAQUE, borderalpha},
    [SchemeTagsNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeTagsUrgent] = {OPAQUE, OPAQUE, borderalpha},
    [SchemeInfoSel] = {OPAQUE, baralpha, borderalpha},
    [SchemeInfoNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeBarBorder] = {OPAQUE, baralpha, borderalpha},
};
static const char *const autostart[] = {
    NULL, NULL /* terminate */
};

/* tagging */
/* static char *tags[]    = { "???", "???", "???", "???", "???", "???", "???", "???", "???"}; */
static char *tags[] = {"???", "???", "???", "???", "???", "???", "???", "???", "???"};
static char *tagsalt[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
/* static char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"}; */

static const Rule rules[] = {
    /*  class i                     instance title           tagsmask isfloating
       isterminal  noswallow isfakefullscreen  width  height   x     y
       floatborderpx  monitor */
    {"Gimp", NULL, NULL, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0 - 1},
    {"Pavucontrol", NULL, NULL, 0, 1, 0, 0, 0, 400, 650, 0, 0, 0 - 1},
    {"finder", NULL, NULL, 0, 1, 0, 0, 0, 530, 250, 679, 439, 0 - 1},
    {"firefox", NULL, NULL, 0, 0, 0, -1, 1, 0, 0, -1, -1, 0 - 1},
    {"firefox", NULL, "Picture-in-Picture", 0, 1, 0, -1, 0, 710, 400, 0, 0,
     0 - 1},
    {"TelegramDesktop", NULL, NULL, 1 << 7, 0, 0, -1, 0, 0, 0, -1, -1, 0 - 1},
    {"St", NULL, NULL, 0, 0, 1, 0, 0, 0, 0, -1, -1, 0 - 1},
    {"Alacritty", NULL, NULL, 0, 0, 1, 0, 0, 0, 0, -1, -1, 0 - 1},
    {NULL, NULL, "Event Tester", 0, 1, 0, 1, 0, 0, 0, -1, -1, 0 - 1}, /* xev */
    {"lemonbar", NULL, NULL, 0, 1, 0, -1, 0, 0, 0, -1, -1, 0 - 1},
    {"bar", NULL, NULL, 0, 1, 0, -1, 0, 0, 0, -1, -1, 0 - 1},
    {"code-oss", NULL, NULL, 1 << 2, 0, 0, -1, 0, 0, 0, -1, -1, 0 - 1},
    {"VSCodium", NULL, NULL, 1 << 2, 0, 0, -1, 0, 0, 0, -1, -1, 0 - 1},
    {"jetbrains-studio", NULL, NULL, 1 << 4, 0, 0, -1, 0, 0, 0, -1, -1, 0 - 1},
    {"Genymotion Player", NULL, NULL, 1 << 4, 1, 0, -1, 0, 0, 0, -1, -1, 0 - 1},
    {"Genymotion", NULL, NULL, 1 << 4, 1, 0, -1, 0, 0, 0, -1, -1, 0 - 1},
    {"Microsoft Teams - Preview", NULL, NULL, 1 << 7, 1, 0, -1, 0, 0, 0, -1, -1,
     0 - 1},
    {"Thunderbird", NULL, NULL, 1 << 7, 0, 0, -1, 0, 0, 0, -1, -1, 0 - 1},
    {"discord", NULL, NULL, 1 << 6, 0, 0, -1, 0, 0, 0, -1, -1, 0 - 1},
};

#include "layouts/bstack.c"
#include "layouts/centeredfloatingmaster.c"
#include "layouts/centeredmaster.c"
#include "layouts/columns.c"
#include "layouts/fibonacci.c"
#include "layouts/gapplessgrid.c"
#include "layouts/grid.c"
#include "layouts/horizgrid.c"

/* layout(s) */
static float mfact = 0.65;    /* factor of master area size [0.05..0.95] */
static const int nmaster = 1; /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol   arrange function */
    {"[]", tile},
    {"\\", spiral},
    {"<>", NULL},
    {"M", monocle},
    {"/ ", dwindle},
    {"TTT", bstack},
    {"|M|", centeredmaster},
    {":::", gaplessgrid},
    {">M>", centeredfloatingmaster},
    {"HHH", grid},
    {"---", horizgrid},
    {"|||", col},
    {NULL, NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
    {MODKEY, KEY, view, {.ui = 1 << TAG}},                                     \
        {Mod1Mask, KEY, toggleview, {.ui = 1 << TAG}},                         \
        {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                      \
        {Mod1Mask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
    {                                                                          \
        .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                   \
    }

/* commands spawned when clicking statusbar, the mouse button pressed is
 * exported as BUTTON */

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "/home/dhruv/.config/scripts/dmenu_run/dmenu_run", NULL};
static const char *termcmd[] = {TERMINAL, NULL};
static const char *browsercmd[] = {BROWSER, NULL};
static const char *editorcmd[] = {"st", "-c", EDITOR, "-e", EDITOR, NULL};
/* static const char *chromecommand[]= {"chromium", NULL};
static const char *mailcommand[]  = {"thunderbird", NULL};
static const char *filecommand[]  = {"thunar", NULL}; */

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    // { "normbgcolor",        STRING,  &normbgcolor },
    // { "normbordercolor",    STRING,  &normbordercolor },
    // { "normfgcolor",        STRING,  &normfgcolor },
    // { "selbgcolor",         STRING,  &selbgcolor },
    // { "selbordercolor",     STRING,  &selbordercolor },
    // { "selfgcolor",         STRING,  &selfgcolor },
    {"borderpx", INTEGER, &borderpx},
    {"usealtbar", INTEGER, &usealtbar},
    {"altbar_bh", INTEGER, &altbar_bh},
    {"gappoh", INTEGER, &gappoh},
    {"gappov", INTEGER, &gappov},
    {"gappih", INTEGER, &gappih},
    {"gappiv", INTEGER, &gappiv},
    {"smartgaps", INTEGER, &smartgaps},
    {"vertpad", INTEGER, &vertpad},
    {"sidepad", INTEGER, &sidepad},
    {"mfact", FLOAT, &mfact},
    // { "snap",              INTEGER, &snap },
    // { "showbar",           INTEGER, &showbar },
    // { "topbar",            INTEGER, &topbar },
    // { "nmaster",           INTEGER, &nmaster },
    // { "resizehints",         INTEGER, &resizehints },
    {NULL, INTEGER, NULL},
};

/* Keybindings */
static Key keys[] = {

    {MODKEY, XK_e, spawn, {.v = editorcmd}},
    {MODKEY, XK_space, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_w, spawn, {.v = browsercmd}},
    /* {MODKEY  ,                         XK_c,             spawn,          {.v
       = chromecommand} }, */
    {MODKEY | ShiftMask, XK_c, spawn,
     SHCMD(
         "/home/dhruv/.local/share/go/bin/rofi-code -r 'rofi -dmenu -p code'")},
    /* {MODKEY  ,                         XK_m,             spawn,          {.v
    = mailcommand} }, {MODKEY  ,                         XK_n, spawn, {.v =
    filecommand} }, */
    {MODKEY | Mod1Mask | ShiftMask, XK_0, defaultgaps, {0}},
    {MODKEY | ShiftMask, XK_w, switchurgent, {.ui = 0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {Mod1Mask, XK_Return, zoom, {0}},
    {MODKEY | ShiftMask, XK_equal, setcfact, {.f = +0.10}},
    {MODKEY | ShiftMask, XK_f, togglefullscr, {0}},
    {MODKEY | ShiftMask, XK_minus, setcfact, {.f = -0.10}},
    {MODKEY | ShiftMask, XK_o, setcfact, {.f = 0.00}},
    /* {MODKEY | ShiftMask,               XK_period,        tagmon,         {.i
       = +1}}, */
    {MODKEY | ShiftMask, XK_q, quit, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    /* {MODKEY,                           XK_comma,         focusmon,       {.i
       = -1 } }, */
    {MODKEY | ShiftMask, XK_n, togglealttag, {0}},

    /* Resize  gaps */
    {MODKEY | Mod1Mask, XK_h, incrgaps, {.i = +1}},
    {MODKEY | Mod1Mask, XK_l, incrgaps, {.i = -1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_h, incrogaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_l, incrogaps, {.i = -1}},
    {MODKEY | Mod1Mask | ControlMask, XK_h, incrigaps, {.i = +1}},
    {MODKEY | Mod1Mask | ControlMask, XK_l, incrigaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_0, togglegaps, {0}},
    {MODKEY | Mod1Mask | ShiftMask, XK_0, defaultgaps, {0}},
    {MODKEY, XK_y, incrihgaps, {.i = +1}},
    {MODKEY, XK_o, incrihgaps, {.i = -1}},
    {MODKEY | ControlMask, XK_y, incrivgaps, {.i = +1}},
    {MODKEY | ControlMask, XK_o, incrivgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_y, incrohgaps, {.i = +1}},
    {MODKEY | Mod1Mask, XK_o, incrohgaps, {.i = -1}},
    {MODKEY | ShiftMask, XK_y, incrovgaps, {.i = +1}},
    {MODKEY | ShiftMask, XK_o, incrovgaps, {.i = -1}},

    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_q, killclient, {0}},
    {Mod1Mask, XK_Tab, view, {0}},

    /* move resize patch */
    {MODKEY | ControlMask | ShiftMask, XK_Down, moveresizeedge, {.v = "B"}},
    {MODKEY | ControlMask | ShiftMask, XK_Left, moveresizeedge, {.v = "L"}},
    {MODKEY | ControlMask | ShiftMask, XK_Right, moveresizeedge, {.v = "R"}},
    {MODKEY | ControlMask | ShiftMask, XK_Up, moveresizeedge, {.v = "T"}},
    {MODKEY | ControlMask, XK_Down, moveresizeedge, {.v = "b"}},
    {MODKEY | ControlMask, XK_Left, moveresizeedge, {.v = "l"}},
    {MODKEY | ControlMask, XK_Right, moveresizeedge, {.v = "r"}},
    {MODKEY | ControlMask, XK_Up, moveresizeedge, {.v = "t"}},
    {MODKEY | ShiftMask, XK_Down, moveresize, {.v = "0x 0y 0w 10h"}},
    {MODKEY | ShiftMask, XK_Left, moveresize, {.v = "0x 0y -10w 0h"}},
    {MODKEY | ShiftMask, XK_Right, moveresize, {.v = "0x 0y 10w 0h"}},
    {MODKEY | ShiftMask, XK_Up, moveresize, {.v = "0x 0y 0w -10h"}},
    {MODKEY, XK_Down, moveresize, {.v = "0x 10y 0w 0h"}},
    {MODKEY, XK_Left, moveresize, {.v = "-10x 0y 0w 0h"}},
    {MODKEY, XK_Right, moveresize, {.v = "10x 0y 0w 0h"}},
    {MODKEY, XK_Up, moveresize, {.v = "0x -10y 0w 0h"}},
    {MODKEY | ShiftMask, XK_j, aspectresize, {.i = +24}},
    {MODKEY | ShiftMask, XK_k, aspectresize, {.i = -24}},

    {MODKEY, XK_Tab, shiftview, {.i = +1}},
    {MODKEY | ShiftMask, XK_Tab, shiftview, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagtoright, {0}},
    {MODKEY | ShiftMask, XK_comma, tagtoleft, {0}},
    {MODKEY, XK_period, viewtoright, {0}},
    {MODKEY, XK_comma, viewtoleft, {0}},
    {MODKEY, XK_g, goyo, {.v = &layouts[1]}},

    {MODKEY | ControlMask, XK_comma, cyclelayout, {.i = -1}},
    {MODKEY | ControlMask, XK_period, cyclelayout, {.i = +1}},

    {MODKEY, XK_m, hidewin, {0}},
    {MODKEY | ShiftMask, XK_m, restorewin, {0}},
    {MODKEY, XK_n, hideotherwins, {0}},
    {MODKEY | ShiftMask, XK_n, restoreotherwins, {0}},

    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)};

static Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkLtSymbol, 0, Button1, cyclelayout, {.i = +1}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
    IPCCOMMAND(view, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(toggleview, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(tag, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(toggletag, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(tagmon, 1, {ARG_TYPE_UINT}),
    IPCCOMMAND(focusmon, 1, {ARG_TYPE_SINT}),
    IPCCOMMAND(focusstack, 1, {ARG_TYPE_SINT}),
    IPCCOMMAND(zoom, 1, {ARG_TYPE_NONE}),
    IPCCOMMAND(spawn, 1, {ARG_TYPE_PTR}),
    IPCCOMMAND(incnmaster, 1, {ARG_TYPE_SINT}),
    IPCCOMMAND(killclient, 1, {ARG_TYPE_SINT}),
    IPCCOMMAND(togglefloating, 1, {ARG_TYPE_NONE}),
    IPCCOMMAND(setmfact, 1, {ARG_TYPE_FLOAT}),
    IPCCOMMAND(setlayoutsafe, 1, {ARG_TYPE_PTR}),
    IPCCOMMAND(quit, 1, {ARG_TYPE_NONE})};
