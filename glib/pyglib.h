/* -*- Mode: C; c-basic-offset: 4 -*-
 * pyglib - Python bindings for GLib toolkit.
 * Copyright (C) 1998-2003  James Henstridge
 *               2004-2008  Johan Dahlin
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#ifndef __PYGLIB_H__
#define __PYGLIB_H__

#include <Python.h>

#include <glib.h>

G_BEGIN_DECLS

typedef void (*PyGLibThreadBlockFunc) (void);

void pyglib_init(void);
void pyglib_init_internal(PyObject *api);
PyGILState_STATE pyglib_gil_state_ensure(void);
void pyglib_gil_state_release(PyGILState_STATE state);
gboolean pyglib_enable_threads(void);
gboolean pyglib_error_check(GError **error);
gboolean pyglib_gerror_exception_check(GError **error);
gboolean pyglib_threads_enabled(void);
PyObject *pyglib_main_context_new(GMainContext *context);
void pyglib_set_thread_block_funcs(PyGLibThreadBlockFunc block_threads_func,
				   PyGLibThreadBlockFunc unblock_threads_func);
void pyglib_block_threads(void);
void pyglib_unblock_threads(void);

#define pyglib_begin_allow_threads		\
    G_STMT_START {                              \
        PyThreadState *_save = NULL;            \
        if (pyglib_threads_enabled())		\
            _save = PyEval_SaveThread();

#define pyglib_end_allow_threads                \
        if (pyglib_threads_enabled())           \
            PyEval_RestoreThread(_save);        \
    } G_STMT_END

G_END_DECLS

#endif /* __PYGLIB_H__ */
