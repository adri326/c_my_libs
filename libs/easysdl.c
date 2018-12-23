#include "easysdl.h"

void Point_draw(const Point p, Color c) {
  if (p->dimension != 2) {
    printf("Point_draw: point dimension should be equal to 2, p is %d\n", p->dimension);
    return;
  }
  strokePoint(p->coordinates[0], p->coordinates[1], c);
}

void Poly_stroke(const Poly p, Color c) {
  if (p->dimension != 2) {
    printf("Poly_stroke: poly dimension should be equal to 2, p is %d\n", p->dimension);
    return;
  }
  if (p->n_points == 0) {
    printf("Poly_stroke: poly has no point\n");
    return;
  }
  size_t n;
  double x = p->points[0]->coordinates[0];
  double y = p->points[0]->coordinates[1];
  for (n = 1; n < p->n_points; n++) {
    strokeLine(x, y, p->points[n]->coordinates[0], p->points[n]->coordinates[1], c);
    x = p->points[n]->coordinates[0];
    y = p->points[n]->coordinates[1];
  }
  if (p->n_points > 2) {
    strokeLine(x, y, p->points[0]->coordinates[0], p->points[0]->coordinates[1], c);
  }
}

void setEZSDLScale(double newScale) {
  easysdlScale = newScale;
}

void setEZSDLOffset(double x, double y) {
  easysdlOffsetX = x;
  easysdlOffsetY = y;
}

void centerEZSDLOffset(double width, double height) {
  easysdlOffsetX = width / easysdlScale / 2;
  easysdlOffsetY = height / easysdlScale / 2;
}

double getEZMouseX() {
  return (double)EZ_souris_x() / easysdlScale - easysdlOffsetX;
}

double getEZMouseY() {
  return -((double)EZ_souris_y() / easysdlScale - easysdlOffsetY);
}

bool easysdlHasExited() {
  return easysdlExited;
}

bool fetchEvents(void (*handler)(int)) {
  int evt = 0;
  bool res = false;
  #if EASYSDL_VERSION_MAJOR == 0 && EASYSDL_VERSION_MINOR == 1 && EASYSDL_VERSION_PATCH == 0
  while (EZ_recupere_evenement_continu(&evt)) {
    res = true;
    if (evt == EZ_EXIT) {
      easysdlExited = true;
    }
    (*handler)(evt);
  }
  #elif EASYSDL_VERSION_MAJOR == 0 && EASYSDL_VERSION_MINOR == 1 && EASYSDL_VERSION_PATCH == 1
  while (evt = EZ_recupere_evenement_continu()) {
    res = true;
    if (evt == EZ_EXIT) {
      easysdlExited = true;
    }
    (*handler)(evt);
  }
  #endif
  return res;
}

void waitExit() {
  bool loop = true;
  while (loop) {
    EZ_attendre(20);
    int evt;
    while (EZ_recupere_evenement_continu(&evt)) {
      if (evt == EZ_EXIT) loop = false;
    }
  }
}

Keymap Keymap_new() {
  Keymap km = (Keymap)malloc(sizeof(struct Keymap));
  km->n_keys = 0;
  km->n_binds = (size_t*)malloc(0);
  km->raw = (int**)malloc(0);
  km->pressed = (bool**)malloc(0);
  return km;
}

void Keymap_destroy(Keymap km) {
  if (km->n_keys > 0) {
    free(km->raw);
    free(km->pressed);
  }
  free(km);
}

int Keymap_addKey(Keymap km) {
  int** newRaws = (int**)malloc(sizeof(int*) * (km->n_keys + 1));
  bool** newPressed = (bool**)malloc(sizeof(bool*) * (km->n_keys + 1));
  size_t* newNBinds = (size_t*)malloc(sizeof(size_t) * (km->n_keys + 1));
  size_t n;
  for (n = 0; n < km->n_keys; n++) {
    newRaws[n] = km->raw[n];
    newPressed[n] = km->pressed[n];
    newNBinds[n] = km->n_binds[n];
  }
  newRaws[km->n_keys] = (int*)malloc(0);
  newPressed[km->n_keys] = (bool*)malloc(0);
  newNBinds[km->n_keys] = 0;
  free(km->pressed);
  free(km->raw);
  free(km->n_binds);
  km->raw = newRaws;
  km->pressed = newPressed;
  km->n_binds = newNBinds;

  return km->n_keys++;
}

void Keymap_bindKey(Keymap km, const int index, const int raw) {
  if (index >= km->n_keys) {
    printf("Invalid index for Keymap_bindKey: index is %d, length is %d\n", index, km->n_keys);
    return;
  }
  if (!Keymap_hasBoundKey(km, index, raw)) {
    int* newRaw = (int*)malloc(sizeof(int) * (km->n_binds[index] + 1));
    bool* newPressed = (bool*)malloc(sizeof(bool) * (km->n_binds[index] + 1));
    size_t n;
    for (n = 0; n < km->n_binds[index]; n++) {
      newRaw[n] = km->raw[index][n];
      newPressed[n] = km->pressed[index][n];
    }
    newRaw[km->n_binds[index]] = raw;
    newPressed[km->n_binds[index]] = false;
    free(km->raw[index]);
    free(km->pressed[index]);
    km->raw[index] = newRaw;
    km->pressed[index] = newPressed;
    km->n_binds[index]++;
  }
}

void Keymap_unbindKey(Keymap km, const int index, const int raw) {
  if (index >= km->n_keys) {
    printf("Invalid index for Keymap_bindKey: index is %d, length is %d\n", index, km->n_keys);
    return;
  }
  if (!Keymap_hasBoundKey(km, index, raw)) {
    int* newRaw = (int*)malloc(sizeof(int) * (km->n_binds[index] - 1));
    bool* newPressed = (bool*)malloc(sizeof(bool) * (km->n_binds[index] - 1));
    size_t n, o;
    for (n = 0, o = 0; n < km->n_binds[index]; n++, o++) {
      if (km->raw[index][n] == raw) {
        o--;
        continue;
      }
      newRaw[o] = km->raw[index][n];
      newPressed[o] = km->pressed[index][n];
    }
    free(km->raw[index]);
    free(km->pressed[index]);
    km->raw[index] = newRaw;
    km->pressed[index] = newPressed;
    km->n_binds[index]++;
  }
}

bool Keymap_hasBoundKey(Keymap km, const int index, const int raw) {
  if (index >= km->n_keys) {
    printf("Invalid index for Keymap_hasBoundKey: index is %d, length is %d\n", index, km->n_keys);
    return false;
  }
  size_t n;
  for (n = 0; n < km->n_binds[index]; n++) {
    if (km->raw[index][n] == raw) return true;
  }
  return false;
}

void Keymap_update(Keymap km, const int key, const bool down) {
  size_t n, o;
  for (n = 0; n < km->n_keys; n++) {
    for (o = 0; o < km->n_binds[n]; o++) {
      if (key == km->raw[n][o]) {
        km->pressed[n][o] = down;
      }
    }
  }
}

bool Keymap_pressed(Keymap km, const int index) {
  if (index >= km->n_keys) {
    printf("Invalid index for Keymap_pressed: index is %d, length is %d\n", index, km->n_keys);
    return false;
  }
  size_t n;
  for (n = 0; n < km->n_binds[index]; n++) {
    if (km->pressed[index][n]) return true;
  }
  return false;
}
