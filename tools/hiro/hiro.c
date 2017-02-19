#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>
#include <mruby/array.h>

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

char* relative_path(const char* dir, const char* filename) {
  size_t len, dir_len, filename_len;
  char* fullpath;

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

int main(int argc, char** argv) {
  char* root = dirname(argv[0]);

  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    return 1;
  }

  mrb_state* mrb = mrb_open();

  define_argument_const(mrb, argc, argv);

  execute(mrb, root, argv[1]);

  if(mrb->exc) {
    mrb_print_error(mrb);
    mrb_close(mrb);
    SDL_Quit();
    return 1;
  }

  free(root);
  mrb_close(mrb);
  SDL_Quit();

  return 0;
}
