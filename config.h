#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "SauceCodePro Nerd Font Mono:size=16", "Source Han Sans CN:size=16" };
static const char dmenufont[]       = "SauceCodePro Nerd Font Mono:size=16";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#37474F";
static const char col_border[]        = "#42A5F5";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	//[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeNorm] = { col_gray3, "#000000", "#222222" },
	[SchemeSel]  = { "#000000", "#669999", "#000000"  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_border  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
//static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };
//static const char *tags[] = { "\u4e00", "\u4e8c", "\u4e09", "\u56db", "\u4e94", "\u516d", "\u4e03", "\u516b", "\u4e5d" };
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Android Emulator", NULL,       NULL,       0,            1,           -1 },
	{ "Emulator", NULL,       NULL,       0,            1,           -1 },
	{ "quemu-system-i386", NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "Tile",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browsercmd[]  = { "google-chrome-stable", NULL };
static const char *slockcmd[]  = { "slock", NULL };

static const char *upvol[]   = { "/home/lhy/scripts/vol-up.sh",  NULL };
static const char *downvol[] = { "/home/lhy/scripts/vol-down.sh",  NULL };
static const char *mutevol[] = { "/home/lhy/scripts/vol-toggle.sh",  NULL };

static const char *wpcmd[]  = { "/home/lhy/scripts/wp-change.sh", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "80x24", NULL };

//static const char *setcolemakcmd[]  = { "/home/lhy/scripts/setxmodmap-colemak.sh", NULL };
static const char *suspendcmd[]  = { "systemctl", "suspend", NULL };
static const char *hibernatecmd[]  = { "systemctl", "hibernate", NULL };

static const char *TouchpadEnabledCmd[]  = { "/home/lhy/scripts/touchpad-enabled.sh", NULL };
static const char *TouchpadDisabledCmd[]  = { "/home/lhy/scripts/touchpad-disabled.sh", NULL };
static const char *TouchpadToggleCmd[]  = { "/home/lhy/scripts/touchpad-toggle.sh", NULL };
static const char *CmusPlayOrPause[]  = { "/home/lhy/scripts/cmus-functions/cmus-play-pause.sh", NULL };
static const char *CmusVolUp[]  = { "/home/lhy/scripts/cmus-functions/cmus-vol-up.sh", NULL };
static const char *CmusVolDown[]  = { "/home/lhy/scripts/cmus-functions/cmus-vol-down.sh", NULL };
static const char *CmusPreSong[]  = { "/home/lhy/scripts/cmus-functions/cmus-pre-song.sh", NULL };
static const char *CmusNextSong[]  = { "/home/lhy/scripts/cmus-functions/cmus-next-song.sh", NULL };
static const char *CmusShuffleToggle[]  = { "/home/lhy/scripts/cmus-functions/cmus-Shuffle-toggle.sh", NULL };
static const char *CmusRepeatToggle[]  = { "/home/lhy/scripts/cmus-functions/cmus-Repeat-toggle.sh", NULL };
static const char *CmusLyrics[]  = { "/home/lhy/scripts/cmus-functions/cmus-osdlyrics.sh", NULL };
static const char *screenshotcmd[] = { "flameshot", "gui", NULL };
static const char *FilesNavigationCmd[] = { "thunar", NULL };
static const char *FilesSearchCmd[] = { "fsearch", NULL };

static Key keys[] = {
	/* modifier            key                      function        argument */
	{ MODKEY,              XK_d,                    spawn,          {.v = dmenucmd } },
	{ MODKEY,              XK_e,                    spawn,          {.v = FilesNavigationCmd } },
	{ MODKEY,              XK_s,                    spawn,          {.v = FilesSearchCmd } },
	{ MODKEY,              XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,  XK_l,                    spawn,          {.v = slockcmd } },
	{ MODKEY,              XK_c,                    spawn,          {.v = browsercmd } },
//	{ MODKEY|ShiftMask,    XK_m,                    spawn,          {.v = setcolemakcmd } },
	{ MODKEY|ControlMask,  XK_r,                    spawn,          {.v = suspendcmd } },
	{ MODKEY|ControlMask,  XK_h,                    spawn,          {.v = hibernatecmd } },
	{ MODKEY|ControlMask,  XK_q,                    quit,           {0} },
	{ 0,                   XF86XK_AudioLowerVolume, spawn,          {.v = downvol } },
	{ 0,                   XF86XK_AudioMute,        spawn,          {.v = mutevol } },
	{ 0,                   XF86XK_AudioRaiseVolume, spawn,          {.v = upvol   } },
	{ MODKEY,              XK_bracketleft,          spawn,          {.v = downvol } },
	{ MODKEY,              XK_backslash,            spawn,          {.v = mutevol } },
	{ MODKEY,              XK_bracketright,         spawn,          {.v = upvol   } },
	{ MODKEY,              XK_b,                    spawn,          {.v = wpcmd } },
	{ 0,                   XK_Print,                spawn,          {.v = screenshotcmd } },
    { MODKEY,              XK_apostrophe,           togglescratch,  {.v = scratchpadcmd } }, // open a new window in the screen center
//	{ MODKEY,              XK_t,                    spawn,          {.v = TouchpadDisabledCmd } },
//	{ MODKEY|ShiftMask,    XK_t,                    spawn,          {.v = TouchpadEnabledCmd } },
	{ MODKEY,              XK_t,                    spawn,          {.v = TouchpadToggleCmd } },
	{ ControlMask|ShiftMask,    XK_p,                    spawn,          {.v = CmusPlayOrPause } },
	{ ControlMask|ShiftMask,    XK_s,                    spawn,          {.v = CmusShuffleToggle } },
	{ ControlMask|ShiftMask,    XK_r,                    spawn,          {.v = CmusRepeatToggle } },
	{ ControlMask|ShiftMask,    XK_l,                    spawn,          {.v = CmusLyrics } },
	{ ControlMask|ShiftMask,    XK_Up,                   spawn,          {.v = CmusVolUp } },
	{ ControlMask|ShiftMask,    XK_Down,                 spawn,          {.v = CmusVolDown } },
	{ ControlMask|ShiftMask,    XK_Left,                 spawn,          {.v = CmusPreSong } },
	{ ControlMask|ShiftMask,    XK_Right,                  spawn,          {.v = CmusNextSong } },
	{ MODKEY|ShiftMask,    XK_j,                    rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_k,                    rotatestack,    {.i = -1 } },
	{ MODKEY,              XK_j,                    focusstack,     {.i = +1 } },
	{ MODKEY,              XK_k,                    focusstack,     {.i = -1 } },
    { MODKEY,              XK_h,                    viewtoleft,     {0} },
	{ MODKEY,              XK_l,                    viewtoright,    {0} },
	{ MODKEY|ShiftMask,    XK_h,                    tagtoleft,      {0} },
	{ MODKEY|ShiftMask,    XK_l,                    tagtoright,     {0} },
	{ MODKEY|ShiftMask,    XK_u,                    incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_i,                    incnmaster,     {.i = -1 } },
	{ MODKEY,              XK_u,                    setmfact,       {.f = -0.05} },
	{ MODKEY,              XK_i,                    setmfact,       {.f = +0.05} },
	{ MODKEY,              XK_comma,                focusmon,       {.i = -1 } },
	{ MODKEY,              XK_period,               focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_comma,                tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,    XK_period,               tagmon,         {.i = +1 } },
	{ MODKEY,              XK_n,                    hidewin,        {0} },
	{ MODKEY|ShiftMask,    XK_n,                    restorewin,     {0} },
	{ MODKEY,              XK_p,                    hideotherwins,  {0}},
	{ MODKEY|ShiftMask,    XK_p,                    restoreotherwins, {0}},
	{ MODKEY|ShiftMask,    XK_Return,               zoom,           {0} },
	{ MODKEY,              XK_Tab,                  view,           {0} },
	{ MODKEY,              XK_q,                    killclient,     {0} },
	{ MODKEY,              XK_f,                    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,              XK_m,                    setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,    XK_e,                    fullscreen,     {0} },
	{ MODKEY,              XK_space,                setlayout,      {0} },
	{ MODKEY|ShiftMask,    XK_space,                togglefloating, {0} },
	TAGKEYS(               XK_1,                      0)
	TAGKEYS(               XK_2,                      1)
	TAGKEYS(               XK_3,                      2)
	TAGKEYS(               XK_4,                      3)
	TAGKEYS(               XK_5,                      4)
	TAGKEYS(               XK_6,                      5)
	TAGKEYS(               XK_7,                      6)
	TAGKEYS(               XK_8,                      7)
	TAGKEYS(               XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
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

