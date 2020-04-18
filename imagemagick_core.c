/*
  Copyright (C) 2020 by Shohei YOSHIDA

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdint.h>
#include <emacs-module.h>

#include "imagemagick_wrapper.h"

int plugin_is_GPL_compatible;

static char *retrieve_string(emacs_env *env, emacs_value str, ptrdiff_t *size) {
    *size = 0;

    env->copy_string_contents(env, str, NULL, size);
    char *p = malloc(*size);
    if (p == NULL) {
        *size = 0;
        return NULL;
    }
    env->copy_string_contents(env, str, p, size);

    return p;
}

static emacs_value Fimagemagick_init(emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data) {
    el_magick_initialize();
    return env->intern(env, "t");
}

static emacs_value Fimagemagick_scale(emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data) {
    ptrdiff_t size;
    char *src_path = retrieve_string(env, args[0], &size);
    char *dest_path = retrieve_string(env, args[1], &size);
    char *geo = retrieve_string(env, args[2], &size);

    el_magick_scale(src_path, dest_path, geo);

    free(src_path);
    free(dest_path);
    free(geo);
    return env->intern(env, "t");
}

static emacs_value Fimagemagick_blur(emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data) {
    ptrdiff_t size;
    char *src_path = retrieve_string(env, args[0], &size);
    char *dest_path = retrieve_string(env, args[1], &size);
    double radius = env->extract_float(env, args[2]);
    double sigma = env->extract_float(env, args[3]);

    el_magick_blur(src_path, dest_path, radius, sigma);

    free(src_path);
    free(dest_path);
    return env->intern(env, "t");
}

static emacs_value Fimagemagick_size(emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data) {
    ptrdiff_t size;
    char *src_path = retrieve_string(env, args[0], &size);

    size_t width = 0, height = 0;
    el_magick_size(src_path, &width, &height);
    free(src_path);

    emacs_value ret[2];
    ret[0] = env->make_integer(env, (intmax_t)width);
    ret[1] = env->make_integer(env, (intmax_t)height);

    return env->funcall(env, env->intern(env, "cons"), 2, ret);
}

static void bind_function(emacs_env *env, const char *name, emacs_value Sfun) {
    emacs_value Qfset = env->intern(env, "fset");
    emacs_value Qsym = env->intern(env, name);
    emacs_value args[] = {Qsym, Sfun};

    env->funcall(env, Qfset, 2, args);
}

static void provide(emacs_env *env, const char *feature) {
    emacs_value Qfeat = env->intern(env, feature);
    emacs_value Qprovide = env->intern(env, "provide");
    emacs_value args[] = {Qfeat};

    env->funcall(env, Qprovide, 1, args);
}

int emacs_module_init(struct emacs_runtime *ert) {
    emacs_env *env = ert->get_environment(ert);

#define DEFUN(lsym, csym, amin, amax, doc, data) bind_function(env, lsym, env->make_function(env, amin, amax, csym, doc, data))

    DEFUN("imagemagick-core-init", Fimagemagick_init, 0, 0, NULL, NULL);
    DEFUN("imagemagick-core-scale", Fimagemagick_scale, 3, 3, NULL, NULL);
    DEFUN("imagemagick-core-blur", Fimagemagick_blur, 4, 4, NULL, NULL);
    DEFUN("imagemagick-core-size", Fimagemagick_size, 1, 1, NULL, NULL);
#undef DEFUN

    provide(env, "imagemagick-core");
    return 0;
}