#include "Color.h"

Color::Color() : _name("unnamed") {
    _qcolor = QColor();
}

Color::Color(int r, int g, int b, QString name)
    : _name(name) {
    _qcolor = QColor(r, g, b);
}

QString Color::readableName() { return _name; }
QColor Color::qcolor() { return _qcolor; }

#define M0(r, g, b, n) colors->insert(n, Color(r, g, b, n));
QMap<QString, Color>* Color::naubino() {
    static QMap<QString, Color> *colors = new QMap<QString, Color>();
    if (colors->isEmpty()) {
        M0(229,  53,  23, "red");
        M0(226,   0, 122, "pink");
        M0(151, 190,  13, "green");
        M0(  0, 139, 208, "blue");
        M0(100,  31, 128, "purple");
        M0(255, 204,   0, "yellow");
        M0(  0,   0,   0, "black");
        M0(160, 160, 160, "grey");
        M0(255, 255, 255, "white");
    }
    return colors;
}
#undef M0

#define M1(n) colors->append(naubino()->value(n));
QList<Color>* Color::naub() {
    static QList<Color> *colors = new QList<Color>();
    if (colors->isEmpty()) {
        M1("red"); M1("pink"); M1("green"); M1("blue"); M1("purple");
        M1("yellow");
    }
    return colors;
}
#undef M1

Color Color::randomNaub() {
    return naub()->at(qrand() * 1.0f * naub()->count() / RAND_MAX);
}
