#pragma once
#include <fcntl.h>
#include <include/mySimpleComputer.h>
#include <termios.h>
#include <unistd.h>

enum keys
{
  SEQ_A = 65,
  SEQ_B,
  SEQ_C,
  SEQ_D,
  SEQ_E,
  SEQ_F,
  SEQ_G,
  SEQ_H,
  SEQ_I,
  SEQ_J,
  SEQ_K,
  SEQ_L,
  SEQ_M,
  SEQ_N,
  SEQ_O,
  SEQ_P,
  SEQ_Q,
  SEQ_R,
  SEQ_S,
  SEQ_T,
  SEQ_U,
  SEQ_V,
  SEQ_W,
  SEQ_X,
  SEQ_Y,
  SEQ_Z,

  SEQ_a = 97,
  SEQ_b,
  SEQ_c,
  SEQ_d,
  SEQ_e,
  SEQ_f,
  SEQ_g,
  SEQ_h,
  SEQ_i,
  SEQ_j,
  SEQ_k,
  SEQ_l,
  SEQ_m,
  SEQ_n,
  SEQ_o,
  SEQ_p,
  SEQ_q,
  SEQ_r,
  SEQ_s,
  SEQ_t,
  SEQ_u,
  SEQ_v,
  SEQ_w,
  SEQ_x,
  SEQ_y,
  SEQ_z,

  SEQ_0 = 48,
  SEQ_1,
  SEQ_2,
  SEQ_3,
  SEQ_4,
  SEQ_5,
  SEQ_6,
  SEQ_7,
  SEQ_8,
  SEQ_9,
  SEQ_PLUS = 43,
  SEQ_MINUS = 45,

  SEQ_UP = 200,
  SEQ_DOWN,
  SEQ_RIGHT,
  SEQ_LEFT,

  SEQ_F5 = 250,
  SEQ_F6 = 260,

  SEQ_ESC = 27,
  SEQ_ENTER = 10,
  SEQ_ACKSPACE = 127
};

extern struct termios TERM;

int rk_readkey (enum keys *key);
int rk_mytermsave (void);
int rk_mytermrestore (void);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
int rk_readvalue (int *value, int timeout);
