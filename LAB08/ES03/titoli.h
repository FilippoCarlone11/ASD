#ifndef ASD_TITOLI_H
#define ASD_TITOLI_H
#include "titolo.h"

typedef struct titoli *Titoli;

Titoli titoliLOADwp();
void Titolistore(Titoli t);
void TITOLIfree(Titoli t);
void operations(Titoli t);
#endif //ASD_TITOLI_H
