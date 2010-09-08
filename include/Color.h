#ifndef COLOR_H
#define COLOR_H


#include "Prereqs.h"

#include <QPair>

class QColor;


namespace Color {

    const QColor& nameToColor(const QString&);
    const QString& colorToName(const QColor& color);
    QPair<const QColor&, const QString&> randomNaub();

};


#endif // COLOR_H

