#include "animation.h"

Animation Animation_new(double duration, int interpolation, double value) {
  Animation a;
  a.duration = duration;
  a.interpolation = interpolation;
  a.value = value;
  a.from = value;
  a.to = value;
  a.lastTick = getMillis();
  a.direction = 0;
  return a;
}

void Animation_set(Animation* anim, double value) {
  if (value == anim->from && value != anim->to) {
    Animation_abort(anim);
  }
  else if (value != anim->to) {
    anim->from = anim->value;
    anim->to = value;
    anim->direction = anim->to > anim->from;
  }
}

void Animation_abort(Animation* anim) {
  double tmp = anim->from;
  anim->from = anim->to;
  anim->to = tmp;
}

void Animation_tick(Animation* anim) {
  double dt = getMillis() - anim->lastTick;
  // printf("%.2lf (%.2lf, %.2lf)\n", anim->value, anim->to, anim->from);
  if (anim->value < anim->to && anim->to > anim->from || anim->value > anim->to && anim->to < anim->from) {
    anim->value += dt * (anim->to - anim->from) / anim->duration;
  }
  else {
    // printf("Howdy!\n");
    anim->value = anim->to;
    anim->from = anim->value;
    anim->direction = 0;
  }
  anim->lastTick += dt;
}

double Animation_get(Animation* anim) {
  // return (double)anim->direction * .5 + .5;
  // printf("%d %s\n", anim->direction, anim->interpolation == QUADRATIC_INTERPOLATION ? "true" : "false");
  if (anim->direction == 0) {
    return anim->value;
  }
  else {
    double ratio = (anim->value - anim->from) / (anim->to - anim->from) * anim->direction;
    double multiplier = (anim->to - anim->from) * anim->direction;
    double offset = anim->from;
    switch (anim->interpolation) {
      case LINEAR_INTERPOLATION:
        return offset + ratio * multiplier;
      case QUADRATIC_INTERPOLATION:
        return offset + ratio * ratio * multiplier;
      case CUBIC_INTERPOLATION:
        return offset + ratio * ratio * ratio * multiplier;
      case SINE_INTERPOLATION:
        return offset + sin(ratio * M_PI / 2) * multiplier;
      default:
        return anim->value;
    }
  }
}

AnimationSet AnimationSet_new() {
  AnimationSet as;
  as.length = 0;
  as.animations = (Animation**)malloc(0);
  return as;
}

size_t AnimationSet_push(AnimationSet* as, Animation* anim) {
  Animation** animations = (Animation**)malloc(sizeof(Animation*) * (as->length + 1));
  size_t n;
  for (n = 0; n < as->length; n++) {
    animations[n] = as->animations[n];
  }
  animations[as->length] = anim;
  free(as->animations);
  as->animations = animations;
  return as->length++;
}

void AnimationSet_tick(AnimationSet* as) {
  size_t n;
  for (n = 0; n < as->length; n++) {
    Animation_tick(as->animations[n]);
  }
}

void AnimationSet_set(AnimationSet* as, size_t index, double value) {
  if (index > as->length) {
    printf("Invalid index for AnimationSet_set: index is %d, length is %d\n", index, as->length);
    return;
  }
  Animation_set(as->animations[index], value);
}

double AnimationSet_get(AnimationSet* as, size_t index) {
  if (index > as->length) {
    printf("Invalid index for AnimationSet_get: index is %d, length is %d\n", index, as->length);
    return 0;
  }
  return Animation_get(as->animations[index]);
}

void AnimationSet_abort(AnimationSet* as, size_t index) {
  if (index > as->length) {
    printf("Invalid index for AnimationSet_abort: index is %d, length is %d\n", index, as->length);
    return;
  }
  Animation_abort(as->animations[index]);
}
