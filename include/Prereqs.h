#ifndef PREREQS_H
#define PREREQS_H

#include <stdlib.h>
#include <QObject>

static inline double drand() { return (((double)qrand())/RAND_MAX); }

#endif // PREREQS_H
