#include "Color.h"


#include <cstdlib>

#include <QMap>
#include <QtGlobal>


Color::Color() : name_("unnamed") {
}


Color::Color(int r, int g, int b, QString name) : name_(name) {
    qcolor_ = QColor(r, g, b);
}


const QString& Color::readableName() const { return name_; }
const QColor& Color::qcolor() const { return qcolor_; }


#define INSERT_IN_MAP(r, g, b, n) colors.insert(n, Color(r, g, b, n));
const QMap<QString, Color>& Color::naubinoColors() {
    static QMap<QString, Color> colors;
    if (colors.isEmpty()) {
        INSERT_IN_MAP(229,  53,  23, "red");
        INSERT_IN_MAP(226,   0, 122, "pink");
        INSERT_IN_MAP(151, 190,  13, "green");
        INSERT_IN_MAP(  0, 139, 208, "blue");
        INSERT_IN_MAP(100,  31, 128, "purple");
        INSERT_IN_MAP(255, 204,   0, "yellow");
        INSERT_IN_MAP(  0,   0,   0, "black");
        INSERT_IN_MAP(160, 160, 160, "grey");
        INSERT_IN_MAP(255, 255, 255, "white");
    }
    return colors;
}
#undef INSERT_IN_MAP


#define APPEND_TO_LIST(n) colors.append(naubinoColors()[n]);
const QList<Color>& Color::possibleNaubColors() {
    static QList<Color> colors;
    if (colors.isEmpty()) {
        APPEND_TO_LIST("red");
        APPEND_TO_LIST("pink");
        APPEND_TO_LIST("green");
        APPEND_TO_LIST("blue");
        APPEND_TO_LIST("purple");
        APPEND_TO_LIST("yellow");
    }
    return colors;
}
#undef APPEND_TO_LIST


Color Color::randomNaub() {
    return possibleNaubColors().at(qrand() * 1.0f * possibleNaubColors().count() / RAND_MAX);
}

