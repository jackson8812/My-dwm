/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_plum[]        = "#634985";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_plum,  col_plum  },
};

/* tagging */
static const char *tags[] = {"", " ", " ", "", "", " ", " ", "", "" }; 

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       0,            0,           -1 },
	{ "Turtl",    NULL,       NULL,       0,            1,           -1 },
	{ "Ferdi",   NULL,       NULL,        0,            1,            1 },
	{ "pavucontrol", NULL,   NULL,        0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_plum, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *slock[] = { "slock", NULL };
static const char *terminator[] = { "terminator", NULL };
static const char *gcal[] = { "gnome-calendar", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		          XK_l, 	   spawn,     	   {.v = slock } },
	{ MODKEY|ShiftMask,							XK_t,			 spawn,					 {.v = terminator } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ Mod4Mask,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ Mod4Mask,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ Mod4Mask,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ Mod4Mask,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ Mod4Mask|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ Mod4Mask|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ Mod4Mask|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ Mod4Mask|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ Mod4Mask|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ Mod4Mask|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ Mod4Mask|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ Mod4Mask|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	{ Mod4Mask|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ Mod4Mask|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ Mod4Mask|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ Mod4Mask|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
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
	{ MODKEY|ControlMask, 					XK_1,			 spawn,          {.v = gcal } },
  { Mod4Mask,					    XK_Down,	moveresize,		{.v = (int []){ 0, 25, 0, 0 }}},
  { Mod4Mask,					    XK_Up,		moveresize,		{.v = (int []){ 0, -25, 0, 0 }}},
  { Mod4Mask,					    XK_Right,	moveresize,		{.v = (int []){ 25, 0, 0, 0 }}},
  { Mod4Mask,					    XK_Left,	moveresize,		{.v = (int []){ -25, 0, 0, 0 }}},
  { Mod4Mask|ShiftMask,			    XK_Down,	moveresize,		{.v = (int []){ 0, 0, 0, 25 }}},
  { Mod4Mask|ShiftMask,			    XK_Up,		moveresize,		{.v = (int []){ 0, 0, 0, -25 }}},
  { Mod4Mask|ShiftMask,			    XK_Right,	moveresize,		{.v = (int []){ 0, 0, 25, 0 }}},
  { Mod4Mask|ShiftMask,			    XK_Left,	moveresize,		{.v = (int []){ 0, 0, -25, 0 }}},
  { Mod4Mask|ControlMask,             XK_Up,     moveresizeedge, {.v = "t"} },
  { Mod4Mask|ControlMask,             XK_Down,   moveresizeedge, {.v = "b"} },
  { Mod4Mask|ControlMask,             XK_Left,   moveresizeedge, {.v = "l"} },
  { Mod4Mask|ControlMask,             XK_Right,  moveresizeedge, {.v = "r"} },
  { Mod4Mask|ControlMask|ShiftMask,   XK_Up,     moveresizeedge, {.v = "T"} },
  { Mod4Mask|ControlMask|ShiftMask,   XK_Down,   moveresizeedge, {.v = "B"} },
  { Mod4Mask|ControlMask|ShiftMask,   XK_Left,   moveresizeedge, {.v = "L"} },
  { Mod4Mask|ControlMask|ShiftMask,   XK_Right,  moveresizeedge, {.v = "R"} },
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
