/*See LICENSE file for copyright and license details. */
// THIS IS A CHANGE
/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 15;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int splitstatus        = 1;        /* 1 for split status items */
static const char *splitdelim        = ";";       /* Character used for separating status */
static const char *fonts[]          = { "Hack:size=10", "Symbols Nerd Font:size=10" };
static const char dmenufont[]       = "size=10";
static const char col_gray3[]       = "#f1be9b"; 
static const char col_gray1[]       = "#020914";
static const char col_gray2[]       = "#a8856c";
static const char col_gray4[]       = "#f1be9b"; 
static const char col_cyan[]        = "#63576E";

static const unsigned int baralpha = 242;
static const unsigned int borderalpha = 140;

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray4 },
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};


/* tagging */
//static const char *tags[] = { "Deus", "Vertias", "Pax", "Amor", "Libertas", "Sapientia", };
//static const char *tags[] = { "", "", "", "", "", "", };
static const char *tags[] = {"󱇪","󱇫", "󰯊",};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 2,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
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
static const char *prtscrcmd[] = { "flameshot", "gui", NULL};
static const char *volumeDown[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL};
static const char *volumeUp[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL};
static const char *volumeMute[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL};
//static const char *micMute[] = { "pactl", "set-source-mute", "@DEFAULT_SOURCE@", "toggle", NULL};



#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       33,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             36, spawn,          {.v = termcmd } },
	{ MODKEY,                       56,      togglebar,      {0} },
	{ MODKEY,                       44,      focusstack,     {.i = +1 } },
	{ MODKEY,                       45,      focusstack,     {.i = -1 } },
	{ MODKEY,                       31,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       40,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       43,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       46,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             44,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             45,      movestack,      {.i = -1 } },
	{ MODKEY,                       33, zoom,           {0} },
	{ MODKEY,                       23,    view,           {0} },
	{ MODKEY|ShiftMask,             54,      killclient,     {0} },
	{ MODKEY,                       28,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       41,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       47,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       65,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             65,  togglefloating, {0} },
	{ MODKEY,                       19,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             19,      tag,            {.ui = ~0 } },
	{ MODKEY,                       58,  focusmon,       {.i = -1 } },
	{ MODKEY,                       59, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             58,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             59, tagmon,         {.i = +1 } },
	TAGKEYS(                        10,                      0)
	TAGKEYS(                        11,                      1)
	TAGKEYS(                        12,                      2)
	//TAGKEYS(                        XK_4,                      3)
	//TAGKEYS(                        XK_5,                      4)
	//TAGKEYS(                        XK_6,                      5)
	//TAGKEYS(                        XK_7,                      6)
	//TAGKEYS(                        XK_8,                      7)
	//TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             38,      quit,           {0} },
        { 0,			        107,  spawn,	   {.v = prtscrcmd } },
	{ MODKEY|ShiftMask, 		20, spawn,	{.v = volumeMute} },
	{ MODKEY,			20, spawn,	{.v = volumeDown} },
	{ MODKEY,			21, spawn,	{.v = volumeUp} },


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

