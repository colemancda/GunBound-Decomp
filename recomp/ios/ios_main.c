/* iOS entry: SDL's UIKit code owns main() and calls SDL_main (this function,
 * renamed by SDL_main.h) once the application has started. There is no command
 * line, so the arguments of the runtime's own main (compiled as rt_main) are
 * built here from the app's Documents folder:
 *
 *   Documents/                the game's files, imported by the user through
 *                             Finder or the Files app: GunBound.gme,
 *                             graphics.xfs, sound.xfs, avatar.xfs, the .dat files,
 *                             and Launcher.cs or launcher.key for the login token
 *   Documents/save/           what the game writes, the registry file
 *   Documents/gunbound.conf   optional, one setting per line:
 *                               broker HOST[:PORT]
 *                               user NAME
 *                               password PW
 *                               token HEX96        (instead of user/password)
 *                               option --any-runtime-option [value]
 *                             '#' starts a comment.
 *
 * Output goes to Documents/log.txt, so that it can be read from Finder. */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <SDL.h>
#include <SDL_main.h>

int rt_main(int argc, char **argv);

#define MAX_ARGS 64
static char *args[MAX_ARGS];
static int nargs;

static void add(const char *s) {
    if (nargs < MAX_ARGS - 1) args[nargs++] = strdup(s);
}

static char *trim(char *s) {
    while (*s == ' ' || *s == '\t') s++;
    char *e = s + strlen(s);
    while (e > s && (e[-1] == '\n' || e[-1] == '\r' || e[-1] == ' ' || e[-1] == '\t')) *--e = 0;
    return s;
}

int main(int argc, char **argv) {
    (void)argc;
    const char *home = getenv("HOME");
    char docs[1024], save[1100], path[1200];
    snprintf(docs, sizeof docs, "%s/Documents", home ? home : ".");
    snprintf(save, sizeof save, "%s/save", docs);
    mkdir(docs, 0755);
    mkdir(save, 0755);

    snprintf(path, sizeof path, "%s/log.txt", docs);
    if (freopen(path, "w", stderr)) setvbuf(stderr, NULL, _IOLBF, 0);
    freopen(path, "a", stdout);

    char broker[256] = "", user[64] = "", password[64] = "", token[128] = "";
    add(argv && argv[0] ? argv[0] : "gunbound");
    snprintf(path, sizeof path, "%s/gunbound.conf", docs);
    FILE *f = fopen(path, "r");
    char line[512];
    char *extra[MAX_ARGS / 2];
    int nextra = 0;
    while (f && fgets(line, sizeof line, f)) {
        char *s = trim(line);
        if (!*s || *s == '#') continue;
        char *v = s + strcspn(s, " \t");
        if (*v) *v++ = 0;
        v = trim(v);
        if (!strcmp(s, "broker")) snprintf(broker, sizeof broker, "%s", v);
        else if (!strcmp(s, "user")) snprintf(user, sizeof user, "%s", v);
        else if (!strcmp(s, "password")) snprintf(password, sizeof password, "%s", v);
        else if (!strcmp(s, "token")) snprintf(token, sizeof token, "%s", v);
        else if (!strcmp(s, "option") && nextra < MAX_ARGS / 2 - 1) {
            /* "--name value": the first word, then the rest as one argument */
            char *val = v + strcspn(v, " \t");
            if (*val) *val++ = 0;
            extra[nextra++] = strdup(v);
            val = trim(val);
            if (*val && nextra < MAX_ARGS / 2 - 1) extra[nextra++] = strdup(val);
        } else
            fprintf(stderr, "gunbound.conf: unknown setting \"%s\"\n", s);
    }
    if (f) fclose(f);
    else fprintf(stderr, "no %s; using the defaults (account admin/1234, broker from the registry file)\n", path);

    snprintf(path, sizeof path, "%s/GunBound.gme", docs);
    add("--exe"), add(path);
    add("--gamedir"), add(docs);
    add("--savedir"), add(save);
    add("--fullscreen");
    if (broker[0]) add("--broker"), add(broker);
    if (token[0]) {
        add("--cmdline"), add(token);
    } else {
        add("--login"), add(user[0] ? user : "admin"), add(password[0] ? password : "1234");
    }
    for (int i = 0; i < nextra; i++) add(extra[i]);
    args[nargs] = NULL;

    for (int i = 0; i < nargs; i++) {
        int secret = (i >= 2 && !strcmp(args[i - 2], "--login")) || (i >= 1 && !strcmp(args[i - 1], "--cmdline"));
        fprintf(stderr, "%s%s", i ? " " : "args: ", secret ? "***" : args[i]);
    }
    fprintf(stderr, "\n");
    return rt_main(nargs, args);
}
