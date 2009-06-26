/*
Copyright (c) 2008-2009, Purple Scout AB <opensource@purplescout.se>

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#include "Python.h"
#include <sys/prctl.h>

#define KILL_TITLE_MAX_LEN 15

/* Pointer to the programs environment. From unistd.h */
extern char **environ;

/* Not declared in any header file, but lukily some python extension
apparently needed it at some point in time. So we use it too :-) */
extern void Py_GetArgcArgv(int *argc, char ***argv);

static int g_maxlen = 0;
static char *g_title = NULL;

static char* strend(char* str)
{
    return str + strlen(str);
}

static char* moveenv(char** env)
{
    char *end = env[0] - 1;
    char* str = NULL;
    int i = -1;
    while (env[++i]) {
        if (end + 1 != env[i]) {
            break;
        }
        str = strdup(env[i]);
        if (!str) {
            break;
        }
        end = strend(env[i]);
        env[i] = str;
    }
    return end;
}

static int setupspace(int argc, char **argv, char **env)
{
    if ((argc > 0) && argv && env) {
        char* end = strend(argv[argc-1]);
        if (end + 1 == env[0]) {
            end = moveenv(env);
        }
        return (int)(end - argv[0]);
    }
    return 0;
}

static void init(void)
{
    int argc = 0;
    char **argv = NULL; 
    Py_GetArgcArgv(&argc, &argv);
    g_maxlen = setupspace(argc, argv, environ);
    g_title = argv[0];
}

static PyObject *
processtitle_gettitlemaxlen(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    return Py_BuildValue("i", g_maxlen);
}

static PyObject *
processtitle_gettitle(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    return Py_BuildValue("s", g_title);
}

static PyObject *
processtitle_settitle(PyObject *self, PyObject *args)
{
    const char *new_title;

    if (!PyArg_ParseTuple(args, "s", &new_title))
        return NULL;

    strncpy(g_title, new_title, g_maxlen);
    g_title[g_maxlen] = '\0';

    Py_RETURN_NONE;
}

static PyObject *
processtitle_getkilltitlemaxlen(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    return Py_BuildValue("i", KILL_TITLE_MAX_LEN);
}

static PyObject *
processtitle_getkilltitle(PyObject *self, PyObject *args)
{
    char title[KILL_TITLE_MAX_LEN + 1];

    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    prctl(PR_GET_NAME, title, 0, 0, 0);
    title[KILL_TITLE_MAX_LEN] = '\0';

    return Py_BuildValue("s", title);
}

static PyObject *
processtitle_setkilltitle(PyObject *self, PyObject *args)
{
    const char *title = NULL;

    if (!PyArg_ParseTuple(args, "s", &title))
        return NULL;

    prctl(PR_SET_NAME, title, 0, 0, 0);

    Py_RETURN_NONE;
}

static PyMethodDef ProcessTitleMethods[] = {
    {"gettitlemaxlen",  processtitle_gettitlemaxlen, METH_VARARGS, "Returns the maximum length for the process title."},
    {"gettitle",  processtitle_gettitle, METH_VARARGS, "Get the process title."},
    {"settitle",  processtitle_settitle, METH_VARARGS, "Set the process title."},
    {"getkilltitlemaxlen",  processtitle_getkilltitlemaxlen, METH_VARARGS, "Returns the maximum length for the process kill title."},
    {"getkilltitle",  processtitle_getkilltitle, METH_VARARGS, "Get the process kill title."},
    {"setkilltitle",  processtitle_setkilltitle, METH_VARARGS, "Set the process kill title."},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

PyMODINIT_FUNC
initprocesstitle(void)
{
    init();
    (void)Py_InitModule("processtitle", ProcessTitleMethods);
}

