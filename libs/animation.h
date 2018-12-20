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

// creates a new Animation instance
Animation Animation_new(double duration, int interpolation, double value);
// sets the target value for an Animation instance
void Animation_set(Animation* anim, double value);
// turns the animation back around to its original value
void Animation_abort(Animation* anim);
// updates the animation
void Animation_tick(Animation* anim);
// returns the processed value for an animation
double Animation_get(Animation* anim);

struct AnimationSet {
  Animation** animations;
  size_t length;
};

typedef struct AnimationSet AnimationSet;

// creates a new, empty, animation
AnimationSet AnimationSet_new();
// pushes an Animation instance to an AnimationSet instance
size_t AnimationSet_push(AnimationSet* as, Animation* anim);
// updates all the animations stored inside of an animation set
void AnimationSet_tick(AnimationSet* as);
// sets the target value for the n-th animation of an animation set
void AnimationSet_set(AnimationSet* as, size_t index, double value);
// gets the processed value for the n-th animation of an animation set
double AnimationSet_get(AnimationSet* as, size_t index);
// aborts the n-th animation
void AnimationSet_abort(AnimationSet* as, size_t index);

#endif
