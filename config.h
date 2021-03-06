/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace-bold:size=8" };
static const char dmenufont[]       = "monospace:size=8";
static const char colour0[]         = "#000000";  /* background */
static const char colour1[]         = "#444444";  /* border */
static const char colour2[]         = "#bbbbbb";  /* unselected font */
static const char colour3[]         = "#00bb00";  /* selected font */
static const char colour4[]         = "#202020";  /* background of window-title */
static const char colour5[]         = "#0000ff";
static const char colour6[]         = "#00ff00";
static const char colour7[]         = "#ff0000";
static const char *colours[][3]      = {
	/*                fg        bg        border  */
	[SchemeNorm] = {  colour2,  colour0,  colour1 },
	[SchemeSel]  = {  colour3,  colour4,  colour4 },
	[SchemeTest] = {  colour5,  colour6,  colour7 },
};

/* tagging */
static const char *tags[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance    title         tags mask     isfloating   monitor */
	{ "Gimp",         NULL,       NULL,         0,            1,           -1 },
	{ "Firefox",      NULL,       NULL,         1 << 0,       0,           -1 },
	{ "Thunderbird",  NULL,       NULL,         1 << 0,       0,           -1 },
	{ NULL,           NULL,       "ranger",     1 << 1,       0,           -1 },
	{ NULL,           NULL,       "weechat",    1 << 3,       0,           -1 },
	{ NULL,           NULL,       "terminal0",  1 << 0,       0,           -1 },
	{ NULL,           NULL,       "terminal1",  1 << 1,       0,           -1 },
	{ NULL,           NULL,       "terminal2",  1 << 2,       0,           -1 },
	{ NULL,           NULL,       "terminal3",  1 << 3,       0,           -1 },
	{ NULL,           NULL,       "terminal4",  1 << 4,       0,           -1 },
	{ NULL,           NULL,       "terminal5",  1 << 5,       0,           -1 },
	{ NULL,           NULL,       "terminal6",  1 << 6,       0,           -1 },
	{ NULL,           NULL,       "terminal7",  1 << 7,       0,           -1 },
	{ NULL,           NULL,       "terminal8",  1 << 8,       0,           -1 },
	{ NULL,           NULL,       "terminal9",  1 << 9,       0,           -1 },
	{ NULL,           NULL,       "terminalA",  1 << 10,      0,           -1 },
	{ NULL,           NULL,       "terminalB",  1 << 11,      0,           -1 },
	{ NULL,           NULL,       "terminalC",  1 << 12,      0,           -1 },
	{ NULL,           NULL,       "terminalD",  1 << 13,      0,           -1 },
	{ NULL,           NULL,       "terminalE",  1 << 14,      0,           -1 },
	{ NULL,           NULL,       "terminalF",  1 << 15,      0,           -1 },
	{ "onboard",      NULL,       NULL,         -1,           1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", colour0, "-nf", colour2, "-sb", colour4, "-sf", colour3, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *screenshot[]  = { "scrot", "-z", NULL };

static Key keys[] = {
	/* modifier                     key           function          argument */
	{ MODKEY,                       XK_t,         spawn,            { .v = termcmd }},                /* [mod] [t]          -> spawn terminal */
	{ MODKEY,                       XK_s,         spawn,            { .v = screenshot }},             /* [mod] [s]          -> take screenshot */
	{ MODKEY,                       XK_Escape,    spawn,            { .v = dmenucmd }},               /* [mod] [esc]        -> spawn dmenu */
	{ MODKEY,                       XK_Page_Up,   focusstack,       { .i = -1 }},                     /* [mod] [PageUp]     -> window-stack down */
	{ MODKEY,                       XK_Page_Down, focusstack,       { .i = +1 }},                     /* [mod] [PageDown]   -> window-stack up */
	{ MODKEY,                       XK_1,         playsound,        { .ui = 0 }},                     /* [mod] [1]          -> play sound 0 */
	TAGKEYS(                        XK_F1,                          0)                                /* [mod] [F1]         -> handle tag 0 */
	TAGKEYS(                        XK_F2,                          1)                                /* [mod] [F2]         -> handle tag 1 */
	TAGKEYS(                        XK_F3,                          2)                                /* [mod] [F3]         -> handle tag 2 */
	TAGKEYS(                        XK_F4,                          3)                                /* [mod] [F4]         -> handle tag 3 */
	TAGKEYS(                        XK_F5,                          4)                                /* [mod] [F5]         -> handle tag 4 */
	TAGKEYS(                        XK_F6,                          5)                                /* [mod] [F6]         -> handle tag 5 */
	TAGKEYS(                        XK_F7,                          6)                                /* [mod] [F7]         -> handle tag 6 */
	TAGKEYS(                        XK_F8,                          7)                                /* [mod] [F8]         -> handle tag 7 */
	TAGKEYS(                        XK_F9,                          8)                                /* [mod] [F9]         -> handle tag 8 */
	TAGKEYS(                        XK_F10,                         9)                                /* [mod] [F10]        -> handle tag 9 */
	TAGKEYS(                        XK_F11,                         10)                               /* [mod] [F11]        -> handle tag a */
	TAGKEYS(                        XK_F12,                         11)                               /* [mod] [F12]        -> handle tag b */
	{ MODKEY,                       XK_Left,      incnmaster,       { .i = +1 }},                     /* [mod] [←]          -> stack->master */
	{ MODKEY,                       XK_Right,     incnmaster,       { .i = -1 }},                     /* [mod] [→]          -> master->stack */
	{ MODKEY|ShiftMask,             XK_Left,      view_adjacent,    { .i = -1 }},                     /* [mod] [Shift] [←]  -> prev tag */
	{ MODKEY|ShiftMask,             XK_Right,     view_adjacent,    { .i = +1 }},                     /* [mod] [Shift] [→]  -> next tag */
	{ MODKEY|ShiftMask,             XK_x,         killclient,       { 0 }},                           /* [mod] [Shift] [x]  -> kill window */
	{ MODKEY|ShiftMask,             XK_t,         setlayout,        { .v = &layouts[ 0 ] }},          /* [mod] [Shift] [t]  -> layout = tiled */
	{ MODKEY|ShiftMask,             XK_f,         setlayout,        { .v = &layouts[ 1 ] }},          /* [mod] [Shift] [f]  -> layout = floating */
	{ MODKEY|ShiftMask,             XK_m,         setlayout,        { .v = &layouts[ 2 ] }},          /* [mod] [Shift] [m]  -> layout = monocle */
	{ MODKEY|ShiftMask,             XK_q,         quit,             { 0 }},                           /* [mod] [Shift] [q]  -> quit dwm */
	{ MODKEY,                       XK_minus,     setmfact,         { .f = -0.01 }},                  /* [mod] [Shift] [-]  -> decrease main-size */
  { MODKEY,                       XK_plus,      setmfact,         { .f = +0.01 }},                  /* [mod] [Shift] [+]  -> increase main-size */
	{ MODKEY,                       XK_Return,    zoom,             { 0 }},                           /* [mod] [Return]     -> set selected window to main-window */
	{ MODKEY,                       XK_Tab,       view,             { 0 }},                           /* [mod] [Tab]        -> go to previous tag */
	{ MODKEY,                       0x1008FF26,   changekbrlayout,  { .i = -1 }},                     /* [mod] [<=]           -> go to previous xkb-layout */
	{ MODKEY,                       0x1008FF27,   changekbrlayout,  { .i = +1 }},                     /* [mod] [<=]           -> go to next xkb-layout */
	{ MODKEY|ShiftMask,             XK_Escape,    togglebar,        { 0 }},                           /* [mod] [Shift] [Esc]  -> toogle panel  */
};
	/* modifier                     key        function        argument
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
};
	*/

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function          argument */
	{ ClkKbrSymbol,         0,              Button1,        changekbrlayout,  {0} },
	{ ClkLtSymbol,          0,              Button1,        setlayout,        {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,        {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,             {0} },
	{ ClkStatusText,        0,              Button1,        togglecalendar,   {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,        {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating,   {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,      {0} },
	{ ClkTagBar,            0,              Button1,        view,             {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,       {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,              {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,        {0} },
};

#define ADDSCRIPT(...) {(const char * const []) { __VA_ARGS__, (const char *) NULL }},

/* startup-scripts */
static const Script startup[] = {
  ADDSCRIPT("st", "-t", "ranger", "-e", "ranger")
  ADDSCRIPT("st", "-t", "terminal2")
  ADDSCRIPT("st", "-t", "terminal3")
  ADDSCRIPT("st", "-t", "terminal4")
  ADDSCRIPT("st", "-t", "terminal5")
  ADDSCRIPT("st", "-t", "terminal6")
  ADDSCRIPT("st", "-t", "terminal7")
  ADDSCRIPT("st", "-t", "terminal8")
  ADDSCRIPT("st", "-t", "terminal9")
  ADDSCRIPT("st", "-t", "terminalA")
  ADDSCRIPT("st", "-t", "terminalB")
  ADDSCRIPT("firefox")
  ADDSCRIPT("thunderbird")
  ADDSCRIPT("xss-lock", "slock")
};

#define ADDKBR(name,...) {name, (const char * const []) { "setxkbmap", __VA_ARGS__, (const char *) NULL }},
static const KBRcfg kbrConfig[] = {
  ADDKBR("de", "de")
  ADDKBR("il", "il", "phonetic")
  ADDKBR("bg", "bg", "phonetic")
  ADDKBR("gr", "gr")
};
static char *SoundCommand[] = { "ffplay", "-autoexit", NULL, NULL };
static const char *Sounds[] = {
  "~/sba/res/sounds/BaDumTss.mp3",
};
const int SoundsCount = 1;
#define DEFAULT_LAYOUT 2