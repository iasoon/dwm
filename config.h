/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
	"monospace:size=10"
};
static const char base03[]	= "#002b36";
static const char base02[]	= "#073642";
static const char base01[]	= "#586e75";
static const char base00[]	= "#657b83";
static const char base0[]	= "#839496";
static const char base1[]	= "#93a1a1";
static const char base2[]	= "#eee8d5";
static const char base3[]	= "#fdf6e3";
static const char yellow[]	= "#b58900";
static const char orange[]	= "#cb4b16";
static const char red[]		= "#dc322f";
static const char magenta[] = "#d33682";
static const char violet[]	= "#6c71c4";
static const char blue[]	= "#268bd2";
static const char cyan[]	= "#2aa198";
static const char green[]	= "#859900";

enum {
	SolarizedDark,
	SolarizedLight,
	PaletteCount,
};

static const char *colors[PaletteCount][ColCount] = {
	[SolarizedDark] = {
		/* Bar */
		[ColBar]	   = base03,
		[ColText]	   = base1,
		/* Tags */
		[ColTag]	   = base3,
		[ColSelected]  = yellow,
		[ColHighlight] = blue,
		[ColVacant]	   = base0,
		/* Borders */
		[ColBorder]	   = base03,
	},
	[SolarizedLight] = {
		/* Bar */
		[ColBar]	   = base3,
		[ColText]	   = base01,
		/* Tags */
		[ColTag]	   = base03,
		[ColSelected]  = yellow,
		[ColHighlight] = blue,
		[ColVacant]	   = base00,
		/* Borders */
		[ColBorder]	   = base03,
	},
};

static const unsigned int emptypalette   = SolarizedLight;
static const unsigned int defaultpalette = SolarizedDark;
static const ClientPalette clientpalettes[] = {
	/* title	palette */
	{"st",		SolarizedLight},
	{"emacs",	SolarizedLight},
};

static const char dmenufont[]       = "monospace:size=10";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* tagging */
static const char *tags[] = { "b", "m", "w", "v", "z" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
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

#define CLIENTKEYS(KEY, N) \
	{ MODKEY,                       KEY,      focusnth,       {.i = N        } }, \
	{ MODKEY|ShiftMask,             KEY,      zoomnth,        {.i = N        } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont,
								  "-nb", base02, "-nf", base3,
								  "-sb", base3 , "-sf", base02,
								  NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_x,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_0,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_p,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_y,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_l,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_b,                      0)
	TAGKEYS(                        XK_m,                      1)
	TAGKEYS(                        XK_w,                      2)
	TAGKEYS(                        XK_v,                      3)
	TAGKEYS(                        XK_z,                      4)
	CLIENTKEYS(                     XK_h,                      0)
	CLIENTKEYS(                     XK_t,                      1)
	CLIENTKEYS(                     XK_n,                      2)
	CLIENTKEYS(                     XK_s,                      3)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

