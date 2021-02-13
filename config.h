/* See LICENSE file for copyright and license details. */


/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 22; /* snap pixel */
static const unsigned int systraypinning = 0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst = 1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const int showbar = 0; /* 0 means no bar */
static const int topbar = 1; /* 0 means bottom bar */
static const char* fonts[] = { "Symbols Nerd Font:style=2048-em:size=10",
    "Operator Mono Lig:style=medium:size=12",
    /* "Hurmit Nerd Font Mono:style=medium:size=8", */
    "Mukta:style=Regular:size=14" };
static const int swallowfloating = 0; /* 1 means swallow floating windows by default */
static const char dmenufont[] = "monospace:size=10";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#005577";
static const char* colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = { "#555555", "#262626", "#282C34" },
    [SchemeSel] = { "#dddddd", "#262626", "#c0c5ce" },
};

static const char* const autostart[] = {
    /* "killall","dwmblocks", NULL, */
    "dwmblocks", NULL,
    NULL /* terminate */
};

/* tagging */
const static char* tags[] = { "१", "२", "३", "४", "५", "६", "७", "८", "९" };

typedef struct {
    const char* name;
    const void* cmd;
} Sp;

const char* spcmd1[] = { "pavucontrol", NULL };
/* const char *spcmd2[] = {"st", "-n", "notes" ,"-e","nvim","-c source /home/dhruv/.local/nvim/sessions/wiki", NULL }; */
const char* spcmd2[] = { "alacritty", "--class", "notes", "-e", "nvim", "-c source /home/dhruv/.local/share/nvim/sessions/wiki", NULL };
const char* spcmd3[] = { "st", "-n", "mmusic", "-e", "/home/dhruv/.config/tmux/session_script/music", NULL };
const char* spcmd4[] = { "st", "-n", "ippython", "-e", "ipython", NULL };
/* const char* spcmd5[] = { "sxiv", "/home/dhruv/vault/wa_stickers", "-N", "stickers", "-t", NULL }; */
const char* spcmd5[] = { "/usr/bin/chromium", "--profile-directory=Default", "--app-id=hnpfjngllnobngcgfapefoaidbinmjnm",NULL };

// /usr/bin/chromium --profile-directory=Default --app-id=hnpfjngllnobngcgfapefoaidbinmjnm
// crx_hnpfjngllnobngcgfapefoaidbinmjnm
static Sp scratchpads[] = {
    /* name              cmd  */
    { "pavucontrol", spcmd1 },
    { "notes", spcmd2 },
    { "mmusic", spcmd3 },
    { "ippython", spcmd4 },
    { "whatsapp", spcmd5 },
};
static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */

    /*   class          , instance                               , title          , tagsmask , isfloating , ispermanent , isterminal , noswallow , isfakefullscreen , monitor , */
    { "Gimp"            , NULL                                   , NULL           , 0        , 1          , 0           , 0          , 1         , 0                , -1 }    ,
    { "Pavucontrol"     , NULL                                   , NULL           , 0        , 1          , 0           , 0          , 1         , 0                , -1 }    ,
    { "firefox"         , NULL                                   , NULL           , 0        , 0          , 0           , 0          , 1         , 0                , -1 }    ,
    { "qt4-ssh-askpass" , NULL                                   , NULL           , 0        , 0          , 0           , 0          , 1         , 0                , -1 }    ,
    { "openssh-askpass" , NULL                                   , NULL           , 0        , 0          , 0           , 0          , 1         , 0                , -1 }    ,
    { "LibreWolf"       , NULL                                   , NULL           , 0        , 0          , 0           , 0          , 1         , 1                , -1 }    ,
    { "Chromium"       , NULL                                   , NULL           , 0        , 0          , 0           , 0          , 1         , 1                , -1 }    ,

    { "Thunar"          , NULL                                   , NULL           , 0        , 0          , 0           , 0          , 1         , 0                , -1 }    ,
    { "St"              , NULL                                   , NULL           , 0        , 0          , 0           , 1          , 0         , 0                , -1 }    ,
    { "Alacritty"       , NULL                                   , NULL           , 0        , 0          , 0           , 1          , 0         , 0                , -1 }    ,
    { "Toolkit"         , NULL                                   , NULL           , 0        , 1          , 0           , 0          , 1         , 0                , -1 }    ,
    { NULL              , NULL                                   , "Event Tester" , 0        , 1          , 0           , 0          , 1         , 0                , -1 }    ,
    { NULL              , "pavucontrol"                          , NULL           , SPTAG(0) , 1          , 0           , 0          , 1         , 0                , -1 }    ,
    { NULL              , "notes"                                , NULL           , SPTAG(1) , 0          , 0           , 0          , 1         , 0                , -1 }    ,
    { NULL              , "mmusic"                               , NULL           , SPTAG(2) , 1          , 0           , 0          , 1         , 0                , -1 }    ,
    { NULL              , "ippython"                             , NULL           , SPTAG(3) , 1          , 0           , 0          , 1         , 0                , -1 }    ,
    { NULL              , "crx_hnpfjngllnobngcgfapefoaidbinmjnm" , NULL           , SPTAG(4) , 1          , 0           , 0          , 0         , 1                , -1 }    ,
    /* { NULL           , "stickers"                             , NULL           , SPTAG(4) , 1          , 0           , 0          , 1         , -1 }             , */
};
/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1; /* number of clients in master area */
static const int resizehints = 1; /* 1 means respect decoration hints */
static const int attachdirection = 0; /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */
static const int decorhints = 1; /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=", tile }, /* first entry is default */
    { "><>", NULL }, /* no layout function means floating behavior */
    { "[M]", monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                     \
    { MODKEY, KEY, view, { .ui = 1 << TAG } },                \
        { Mod1Mask, KEY, toggleview, { .ui = 1 << TAG } },    \
        { MODKEY | ShiftMask, KEY, tag, { .ui = 1 << TAG } }, \
        { Mod1Mask | ShiftMask, KEY, toggletag, { .ui = 1 << TAG } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                          \
    {                                                       \
        .v = (const char*[]) { "/bin/sh", "-c", cmd, NULL } \
    }
/* #define BROWSER "librewolf" */
#define TERMINAL "st"
/* #define TERMINAL "alacritty" */
/* #define EDITOR "nvim" */

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char* dmenucmd[] = {
    "/home/dhruv/.config/scripts/dmenu_run/dmenu_run", NULL
};

static const char* termcmd[] = { TERMINAL, NULL };
/* static const char* browsercmd[] = { "/home/dhruv/.config/scripts/lof",BROWSER, NULL }; */
/* static const char* editorcmd[] = { "alacritty", "-e", EDITOR, NULL }; */

static Key keys[] = {
    /* modifier                     key        function        argument */
    { Mod1Mask, 55, togglescratch, { .ui = 0 } }, // v
    { Mod1Mask, 57, togglescratch, { .ui = 1 } }, // n
    { Mod1Mask, 58, togglescratch, { .ui = 2 } }, // m
    { Mod1Mask, 33, togglescratch, { .ui = 3 } }, // m
    { Mod1Mask, 61, togglescratch, { .ui = 4 } }, //
    /* { MODKEY                           , 65       , spawn          , { .v = dmenucmd } }        , // space */
    /* { MODKEY                           , 36       , spawn          , { .v = termcmd } }         , // return */
    /* { MODKEY                           , 26       , spawn          , { .v = editorcmd } }       , // e */
    /* { MODKEY                           , 25       , spawn          , { .v = browsercmd } }      , // w */
    { MODKEY, 56, togglebar, { 0 } }, // b
    { MODKEY, 44, focusstack, { .i = +1 } }, // j
    { MODKEY, 45, focusstack, { .i = -1 } }, // k
    { MODKEY, 31, incnmaster, { .i = +1 } }, // i
    { MODKEY, 40, incnmaster, { .i = -1 } }, // d
    { MODKEY | ShiftMask, 43, setmfact, { .f = -0.05 } }, // h
    { MODKEY | ShiftMask, 46, setmfact, { .f = +0.05 } }, // l
    { MODKEY | ShiftMask, 44, setcfact, { .f = +0.25 } }, // j
    { MODKEY | ShiftMask, 45, setcfact, { .f = -0.25 } }, // k
    { MODKEY | ShiftMask, 32, setcfact, { .f = 0.00 } }, // o

    { MODKEY | ShiftMask, 35, movestack, { .i = +1 } }, // ]
    { MODKEY | ShiftMask, 34, movestack, { .i = -1 } }, // [
    { MODKEY, 39, togglestickey, { 0 } }, // s

    { MODKEY, 116, moveresize, { .v = "0x 25y 0w 0h" } }, // down
    { MODKEY, 111, moveresize, { .v = "0x -25y 0w 0h" } }, // up
    { MODKEY, 114, moveresize, { .v = "25x 0y 0w 0h" } }, // right
    { MODKEY, 113, moveresize, { .v = "-25x 0y 0w 0h" } }, // left
    { MODKEY | ShiftMask, 116, moveresize, { .v = "0x 0y 0w 25h" } }, // down
    { MODKEY | ShiftMask, 111, moveresize, { .v = "0x 0y 0w -25h" } }, // up
    { MODKEY | ShiftMask, 114, moveresize, { .v = "0x 0y 25w 0h" } }, // right
    { MODKEY | ShiftMask, 113, moveresize, { .v = "0x 0y -25w 0h" } }, // left
    { MODKEY | ControlMask, 111, moveresizeedge, { .v = "t" } }, // up
    { MODKEY | ControlMask, 116, moveresizeedge, { .v = "b" } }, // down
    { MODKEY | ControlMask, 113, moveresizeedge, { .v = "l" } }, // left
    { MODKEY | ControlMask, 114, moveresizeedge, { .v = "r" } }, // right
    { MODKEY | ControlMask | ShiftMask, 111, moveresizeedge, { .v = "T" } }, // up
    { MODKEY | ControlMask | ShiftMask, 116, moveresizeedge, { .v = "B" } }, // down
    { MODKEY | ControlMask | ShiftMask, 113, moveresizeedge, { .v = "L" } }, // left
    { MODKEY | ControlMask | ShiftMask,
        114,
        moveresizeedge,
        { .v = "R" } }, // right

    { MODKEY | ShiftMask, 41, togglefullscr, { 0 } }, // f
    { Mod1Mask, 36, zoom, { 0 } }, // return
    { MODKEY, 253, view, { 0 } }, // backslash
    { MODKEY, 28, setlayout, { .v = &layouts[0] } }, // t
    { MODKEY, 41, setlayout, { .v = &layouts[2] } }, // f
    /* {MODKEY                         , XK_space , setlayout      , {0}}                       , */
    { MODKEY | ShiftMask, 65, togglefloating, { 0 } }, // space
    { MODKEY, 19, view, { .ui = ~0 } }, // 0
    { MODKEY | ShiftMask, 19, tag, { .ui = ~0 } }, // 0
    { MODKEY, 59, focusmon, { .i = -1 } }, // comma
    { MODKEY, 60, focusmon, { .i = +1 } }, // period
    { MODKEY | ShiftMask, 59, tagmon, { .i = -1 } }, // comma
    { MODKEY | ShiftMask, 60, tagmon, { .i = +1 } }, // period
    { MODKEY | ControlMask, 25, killclient, { 0 } }, // w
    { MODKEY | ShiftMask, 26, quit, { 0 } }, // e
    { MODKEY, 35, shiftview, { .i = +1 } }, // ]
    { MODKEY, 34, shiftview, { .i = -1 } }, // [
    { MODKEY, 60, viewtoright, { 0 } }, // period
    { MODKEY, 59, viewtoleft, { 0 } }, // comma
    { MODKEY, 42, goyo, { .v = &layouts[1] } }, // g
    { MODKEY, 58, hidewin, { 0 } }, // m
    { MODKEY | ShiftMask, 58, restorewin, { 0 } }, // m
    /* {MODKEY, 46, hideotherwins, {0}},                // l */
    /* {MODKEY | ShiftMask, 46, restoreotherwins, {0}}, // l */
    { Mod1Mask | ControlMask, 19, tagtoocc, { 0 } }, // 0
    TAGKEYS(10, 0) // 1
    TAGKEYS(11, 1) // 2
    TAGKEYS(12, 2) // 3
    TAGKEYS(13, 3) // 4
    TAGKEYS(14, 4) // 5
    TAGKEYS(15, 5) // 6
    TAGKEYS(16, 6) // 7
    TAGKEYS(17, 7) // 8
    TAGKEYS(18, 8) // 9
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument
     */
    { ClkLtSymbol, 0, Button1, setlayout, { 0 } },
    { ClkLtSymbol, 0, Button3, setlayout, { .v = &layouts[2] } },
    /* {ClkWinTitle , 0      , Button2 , zoom           , {0}}                   , */
    { ClkStatusText, 0, Button2, spawn, { .v = termcmd } },
    { ClkClientWin, MODKEY, Button1, movemouse, { 0 } },
    { ClkClientWin, MODKEY, Button2, togglefloating, { 0 } },
    { ClkClientWin, MODKEY, Button3, resizemouse, { 0 } },
    { ClkTagBar, 0, Button1, view, { 0 } },
    { ClkTagBar, 0, Button3, toggleview, { 0 } },
    { ClkTagBar, MODKEY, Button1, tag, { 0 } },
    { ClkTagBar, MODKEY, Button3, toggletag, { 0 } },
};
