#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>
#include <mruby/array.h>
#include <mruby/variable.h>
#include <mruby/class.h>

char* dirname(const char *path) {
  size_t len;
  char *p, *dir;

  if(path == NULL) {
    return NULL;
  }

  p = strrchr(path, '/');
  len = p != NULL ? (size_t)(p - path) : strlen(path);

  dir = (char *)malloc(len + 1);
  strncpy(dir, path, len);
  dir[len] = '\0';

  return dir;
}

char* clear_path_dots(const char* filename) {
  size_t len, cut_size;
  char* new_name;

  cut_size = 1;
  len = strlen(filename);
  while(*filename == '.') {
    cut_size++;
    filename++;
  }

  new_name = (char *)malloc(len - cut_size);
  strncpy(new_name, filename + 1, len - cut_size + 1);
  return new_name;
}

char* relative_path(const char* dir, const char* filename) {
  size_t len, dir_len, filename_len;
  char* fullpath;

  int relative_to_up = (filename[0] == '.' && filename[1] == '.');
  int relative_current = (filename[0] == '.' && filename[1] == '/');

  if(relative_to_up || relative_current) {
    return relative_path(dirname(dir), clear_path_dots(filename));
  }

  dir_len = strlen(dir);
  filename_len = strlen(filename);
  len = dir_len + filename_len + 1; // With '/'
  fullpath = (char*)malloc(len + 1);

  strncpy(fullpath, dir, strlen(dir));
  fullpath[dir_len] = '/';

  strncpy(fullpath + dir_len + 1, filename, filename_len);
  fullpath[len] = '\0';

  return fullpath;
}

void execute(mrb_state* mrb, const char* dir, const char* name) {
  const char* path;
  FILE* fp;

  if(name == NULL) {
    name = "hiro.rb";
  }

  path = relative_path(dir, name);
  fp = fopen(path, "r");

  if(fp == NULL) {
    printf("Cannot open program file. (%s)\n", path);
    return;
  }

  struct mrbc_context* cxt = mrbc_context_new(mrb);
  mrbc_filename(mrb, cxt, name);
  mrb_load_file_cxt(mrb, fp, cxt);

  fclose(fp);
  mrbc_context_free(mrb, cxt);
}

void define_argument_const(mrb_state* mrb, int argc, char** argv) {
  int i;
  mrb_value ary;

  ary = mrb_ary_new(mrb);
  for(i = 1; i < argc; i++) {
    mrb_ary_push(mrb, ary, mrb_str_new(mrb, argv[i], strlen(argv[i])));
  }

  mrb_define_global_const(mrb, "ARGV", ary);
}

int has_error(mrb_state* mrb) {
  if(mrb->exc) {
    mrb_print_error(mrb);
    mrb_close(mrb);
    SDL_Quit();
    return 1;
  }
  return 0;
}

mrb_value mrb_init_load_path(mrb_state* mrb, const char* root, const char* execute) {
  const char* path;
  path = dirname(relative_path(root, execute));
  mrb_value paths = mrb_ary_new(mrb);
  mrb_ary_push(mrb, paths, mrb_str_new_cstr(mrb, root));
  mrb_ary_push(mrb, paths, mrb_str_new_cstr(mrb, path));
  return paths;
}

int main(int argc, char** argv) {
  char* root = dirname(argv[0]);

  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    return 1;
  }

  mrb_state* mrb = mrb_open();

  define_argument_const(mrb, argc, argv);
  mrb_gv_set(mrb, mrb_intern_cstr(mrb, "$:"), mrb_init_load_path(mrb, root, argv[1]));

  execute(mrb, root, argv[1]);

  // TODO: Close game when ruby raise error
  if(has_error(mrb)) {
    free(root);
    mrb_close(mrb);
    SDL_Quit();
    return 1;
  }

  free(root);
  mrb_close(mrb);
  SDL_Quit();

  return 0;
}
