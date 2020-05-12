#include"scan.h"

int monscanf(char * c){
  int running = 1;
  while(running){
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_KEYDOWN :
        switch(event.key.keysym.sym){
          case SDLK_a : *c = 'a'; running = 0; break;
          case SDLK_b : *c = 'b'; running = 0; break;
          case SDLK_c : *c = 'c'; running = 0; break;
          case SDLK_d : *c = 'd'; running = 0; break;
          case SDLK_e : *c = 'e'; running = 0; break;
          case SDLK_f : *c = 'f'; running = 0; break;
          case SDLK_g : *c = 'g'; running = 0; break;
          case SDLK_h : *c = 'h'; running = 0; break;
          case SDLK_i : *c = 'i'; running = 0; break;
          case SDLK_j : *c = 'j'; running = 0; break;
          case SDLK_k : *c = 'k'; running = 0; break;
          case SDLK_l : *c = 'l'; running = 0; break;
          case SDLK_m : *c = 'm'; running = 0; break;
          case SDLK_n : *c = 'n'; running = 0; break;
          case SDLK_o : *c = 'o'; running = 0; break;
          case SDLK_p : *c = 'p'; running = 0; break;
          case SDLK_q : *c = 'q'; running = 0; break;
          case SDLK_r : *c = 'r'; running = 0; break;
          case SDLK_s : *c = 's'; running = 0; break;
          case SDLK_t : *c = 't'; running = 0; break;
          case SDLK_u : *c = 'u'; running = 0; break;
          case SDLK_v : *c = 'v'; running = 0; break;
          case SDLK_w : *c = 'w'; running = 0; break;
          case SDLK_x : *c = 'x'; running = 0; break;
          case SDLK_y : *c = 'y'; running = 0; break;
          case SDLK_z : *c = 'z'; running = 0; break;
        }
        break;
      }
    }
  }
}

int testscanf(){
  char c;
  monscanf(&c);
  printf("%c\n",c);
  return 0;
}
