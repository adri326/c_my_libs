#ifndef MY_LIBS_ANIMATION_H
#define MY_LIBS_ANIMATION_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "time.h"

enum {
  LINEAR_INTERPOLATION,
  QUADRATIC_INTERPOLATION,
  CUBIC_INTERPOLATION,
  SINE_INTERPOLATION
} Animation_interpolation;

struct Animation {
  double duration;
  unsigned int interpolation;
  double from;
  double to;
  double value;
  long int lastTick;
  char direction;
};

typedef struct Animation Animation;

Animation Animation_new(double duration, int interpolation, double value);
void Animation_set(Animation* anim, double value);
void Animation_abort(Animation* anim);
void Animation_tick(Animation* anim);
double Animation_get(Animation* anim);

struct AnimationSet {
  Animation** animations;
  size_t length;
};

typedef struct AnimationSet AnimationSet;

AnimationSet AnimationSet_new();
size_t AnimationSet_push(AnimationSet* as, Animation* anim);
void AnimationSet_tick(AnimationSet* as);
void AnimationSet_set(AnimationSet* as, size_t index, double value);
double AnimationSet_get(AnimationSet* as, size_t index);
void AnimationSet_abort(AnimationSet* as, size_t index);

#endif
