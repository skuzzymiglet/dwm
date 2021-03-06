#include "colors.h"

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 0; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int gappih = 30;
static const unsigned int gappiv = 30;
static const unsigned int gappoh = 30;
static const unsigned int gappov = 30;
static const int smartgaps =
    1; /* 1 means no outer gap when there is only one window */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1;  /* 0 means bottom bar */
static const char *fonts[] = {
    "IBM Plex Mono:size=20",
    "NotoColorEmoji:pixelsize=20:antialias=true:autohint=true"};
static const char dmenufont[] = "IBM Plex Mono:size=28";
static const char *colors[][3] = {
    /*               fg         bg         border   */ [SchemeNorm] = {light1,
                                                                       dark0,
                                                                       dark1},
    [SchemeSel] = {dark0, light1, bright_orange},
};

/* tagging */
static const char *tags[] = {"1", "2", "3"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {NULL, NULL, NULL, 0, False, -1},
};

#define FORCE_VSPLIT 1
#include "vanitygaps.c"

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */

static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"🔳", centeredmaster},
    {"◻", monocle},
    {"🪟", tile}, /* first entry is default */
    {"🖱", NULL}, /* no layout function means floating behavior */
    {"◾", centeredfloatingmaster},
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"rofi",        "-modi",       "drun",
                                 "-show-icons", "-icon-theme", "Papirus",
                                 "-show",       "drun",        NULL};
/* static const char *termcmd[]  = { "st", "scroll", NULL }; */
static const char *termcmd[] = {"st", NULL};
static const char *topcmd[] = {"st", "ytop", NULL};
static const char *filecmd[] = {"st", "lf", NULL};
static const char *chatcmd[] = {"st", "abduco", "-A",     "weechat", "weechat",
                                "-r", "/mouse", "enable", NULL};
static const char *emojicmd[] = {"rofi",  "-modi", "emoji",
                                 "-show", "emoji", NULL};
static const char *calccmd[] = {"rofi", "-modi", "calc", "-show", "calc", NULL};
static const char *mailcmd[] = {"st", "abduco", "-A", "aerc", "aerc", NULL};
static const char *browsercmd[] = {"qutebrowser", NULL};
static const char *passcmd[] = {"rofi-pass", NULL};
static const char *feedcmd[] = {"st", "newsboat", NULL};
static const char *mixercmd[] = {"st", "pulsemixer", NULL};
static const char *lockcmd[] = {"slock", NULL};
static const char *openselcmd[] = {"~/bin/open", NULL};
static const char *musiccmd[] = {"st", "abduco", "-A", "music", "cmus", NULL};

#include "selfrestart.c"
#include <X11/XF86keysym.h>

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_p, spawn, {.v = passcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY | ShiftMask, XK_Return, spawn,
     SHCMD("st abduco -A $(abduco | awk '/^ /{print $4}' | rofi -dmenu)")},
    {MODKEY | ShiftMask, XK_k, spawn,
     SHCMD("ps -o comm --no-headers x | uniq | rofi -dmenu | xargs killall")},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_l, spawn, {.v = musiccmd}},
    {MODKEY, XK_c, spawn, {.v = calccmd}},
    {MODKEY, XK_f, spawn, {.v = filecmd}},
    {MODKEY, XK_y, spawn, {.v = topcmd}},
    {MODKEY, XK_x, spawn, {.v = chatcmd}},
    {MODKEY, XK_e, spawn, {.v = emojicmd}},
    {MODKEY, XK_a, spawn, {.v = mixercmd}},
    {MODKEY, XK_w, spawn, {.v = browsercmd}},
    {MODKEY, XK_v, spawn, SHCMD("st nvim")},
    {MODKEY | ShiftMask, XK_w, spawn, SHCMD("rofi -modi window -show window")},
    {MODKEY | ShiftMask, XK_m, spawn, {.v = mailcmd}},
    {MODKEY | ShiftMask, XK_o, spawn, {.v = openselcmd}},
    /* {MODKEY,              XK_n,      spawn,           {.v = feedcmd}}, */
    {MODKEY, XK_s, spawn, {.v = lockcmd}},
    {MODKEY | ShiftMask, XK_s, spawn,
     SHCMD("rofi -dmenu <  ~/servers | xargs st mosh")},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[2]}},
    {MODKEY | ShiftMask, XK_f, setlayout, {.v = &layouts[3]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_u, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_o, setlayout, {.v = &layouts[4]}},
    {MODKEY, XK_g, togglegaps, {0}},
    {MODKEY, XK_space, zoom, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_grave, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_grave, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    /* {MODKEY,             XK_F1, spawn,         SHCMD("st sudo "), */
    {0, XF86XK_MonBrightnessUp, spawn, SHCMD("xbacklight -inc 10")},
    {0, XF86XK_MonBrightnessDown, spawn, SHCMD("xbacklight -dec 10")},
    {0, XF86XK_AudioRaiseVolume, spawn,
     SHCMD("pamixer -i 5 && killall -36 goblocks")},
    {0, XF86XK_AudioLowerVolume, spawn,
     SHCMD("pamixer -d 5 && killall -36 goblocks")},
    {0, XF86XK_AudioMute, spawn, SHCMD("pamixer -t && killall -36 goblocks")},
    {0, XF86XK_AudioRewind, spawn, SHCMD(" cmus-remote -C \"seek -5\"")},
    {0, XF86XK_AudioForward, spawn, SHCMD("cmus-remote -C \"seek +5\"")},
    {0, XF86XK_AudioPrev, spawn, SHCMD("cmus-remote -C \"player-prev\"")},
    {0, XF86XK_AudioNext, spawn, SHCMD("cmus-remote -C \"player-next\"")},
    {0, XF86XK_AudioPlay, spawn, SHCMD("cmus-remote -C \"player-pause\"")},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_r, self_restart, {0}},
    {MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[0]}},
    {ClkWinTitle, 0, Button1, spawn, SHCMD("rofi -modi window -show window")},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
