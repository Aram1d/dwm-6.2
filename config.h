/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";

static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;

static const char *colors[][3]      = {
	/*					fg         bg          border   */
        [SchemeNorm] =	 { "#FFFFFF", "#2E3440" , "#2E3440", },  // normal ( unselected win border | unselected text (tag) | unsel bg )
        [SchemeSel]  =	 { "#FFFFFF", "#6A9BBB", "#3E4450",  },  // selected (selected win border | selected text (tag) | sel bg 0088ED)
        [SchemeWarn] =	 { "#000000", "#ffff00", "#ff0000",  },  // urgent/warning  (black on yellow)
        [SchemeUrgent]=	 { "#5EE88B", "#2E3440", "#2E4340",  }, // green text on normal bg
        { "#ff61a2", "#2E3440", "#2E3440", }, //magenta
        { "#8abeb7", "#2E3440", "#2E3440", }, //cyan
        { "#81a2be", "#2E3440", "#2E3440", }, //blue
        { "#8abeb7", "#2E3440", "#2E3440", }, //yellow
        { "#8abeb7", "#2E3440", "#2E3440", }, //orange
};

static const unsigned int alphas[][3]      = {
        	/*               fg      bg        border     */
        	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
        	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "\uf223 Rem", "\uf0ac Net", "\uf87c Media", "\uf121 Devel", "\uf0b1 Work", "\uf120 Term", "\uf108 Vi En", "\uf11b Games", "\uf592 Misc" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                 instance    title       tags mask     isfloating   monitor  ignoretransient */

  { "TelegramDesktop",     NULL,       NULL,       1 << 0,       0,           -1,          0},
  { "Skype",               NULL,       NULL,       1 << 0,       0,           -1,          0},

	{ "firefox",           NULL,       NULL,       1 << 1,       0,           -1,          0},
  { "Chromium",            NULL,       NULL,       1 << 1,       0,           -1,          0},

  { "Gimp",                NULL,       NULL,       1 << 2,       0,           -1,          0},
  { "Rawtherapee",         NULL,       NULL,       1 << 2,       0,           -1,          0},
  { "Inkscape",            NULL,       NULL,       1 << 2,       0,           -1,          0},
  { "Vuescan",             NULL,       NULL,       1 << 2,       0,           -1,          0},

  { "Atom",                NULL,       NULL,      1 <<  3,       0,           -1,          0},
  { "jetbrains-webstorm",  NULL ,      NULL,      1 <<  3,       0,           -1,          1},

  { "kile",                NULL,       NULL,      1 <<  4,       0,           -1,          0},
  { "Texmaker",            NULL,       NULL,      1 <<  4,       0,           -1,          0},
  { "robo3t",              NULL,       NULL,      1 <<  4,       0,           -1,          0},
  { "libreoffice-writer",  NULL,       NULL,      1 <<  4,       0,           -1,          0},
  { "libreoffice-calc",    NULL,       NULL,      1 <<  4,       0,           -1,          0},

  { "Arandr",              NULL ,      NULL,      1 <<  8,       0,           -1,          0},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
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

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
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
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  TAGKEYS(                        0x26,                      0)
  TAGKEYS(                        0xe9,                      1)
  TAGKEYS(                        0x22,                      2)
  TAGKEYS(                        0x27,                      3)
  TAGKEYS(                        0x28,                      4)
  TAGKEYS(                        0x2d,                      5)
	TAGKEYS(                        0xe8,                      6)
  TAGKEYS(                        0x5f,                      7)
  TAGKEYS(                        0xe7,                      8)
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
