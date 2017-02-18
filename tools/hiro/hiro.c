#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>
#include <mruby/array.h>

int prepare_game() {
  if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    return 1;
  }
  return 0;
}

FILE* open(const char* name) {
  if(name == NULL) {
    name = "hiro.rb";
  }

  return fopen(name, "r");
}

void execute(mrb_state* mrb, const char* name) {
  FILE* fp = open(name);

  if(fp == NULL) {
    printf("Cannot open program file. (%s)\n", name);
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
  if(prepare_game()) {
    printf("SDL initialize failed!\n");
    return 1;
  }

  mrb_state* mrb = mrb_open();

  define_argument_const(mrb, argc, argv);

  execute(mrb, argv[1]);

  if(mrb->exc) {
    mrb_print_error(mrb);
    mrb_close(mrb);
    return 1;
  }

  mrb_close(mrb);
  return 0;
}
