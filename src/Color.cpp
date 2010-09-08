#include "Color.h"


#include <cstdlib>

#include <QColor>
#include <QHash>

static bool g_initialized = false;

static QHash<QString, QColor> g_nameToColor;
static QHash<QRgb, QString> g_colorToName;
static QList<QColor> g_possibleNaubColors;


static void initialize() {

    Q_ASSERT(g_initialized == false);
    Q_ASSERT(g_nameToColor.empty() == true);
    Q_ASSERT(g_colorToName.empty() == true);
    Q_ASSERT(g_possibleNaubColors.empty() == true);


#define NEW_COLOR(r, g, b, name) \
        Q_ASSERT(r >= 0 && r <= 255); \
        Q_ASSERT(g >= 0 && g <= 255); \
        Q_ASSERT(b >= 0 && b <= 255); \
        g_nameToColor[name] = QColor(qRgb(r,g,b)); \
        g_colorToName[qRgb(r,g,b)] = name;

    NEW_COLOR(229,  53,  23, "red");
    NEW_COLOR(226,   0, 122, "pink");
    NEW_COLOR(151, 190,  13, "green");
    NEW_COLOR(  0, 139, 208, "blue");
    NEW_COLOR(100,  31, 128, "purple");
    NEW_COLOR(255, 204,   0, "yellow");
    NEW_COLOR(  0,   0,   0, "black");
    NEW_COLOR(160, 160, 160, "grey");
    NEW_COLOR(255, 255, 255, "white");

#undef NEW_COLOR


    g_initialized = true;


    g_possibleNaubColors.append(Color::nameToColor("red"));
    g_possibleNaubColors.append(Color::nameToColor("pink"));
    g_possibleNaubColors.append(Color::nameToColor("green"));
    g_possibleNaubColors.append(Color::nameToColor("blue"));
    g_possibleNaubColors.append(Color::nameToColor("purple"));
    g_possibleNaubColors.append(Color::nameToColor("yellow"));
}


namespace Color {


const QColor& nameToColor(const QString& name) {
    if (g_initialized == false) { initialize(); }
    return g_nameToColor[name];
}


const QString& colorToName(const QColor& color) {
    if (g_initialized == false) { initialize(); }
    Q_ASSERT(g_colorToName.contains(color.rgb()));
    return g_colorToName[color.rgb()];
}


QPair<const QColor&, const QString&> randomNaub() {
    if (g_initialized == false) { initialize(); }

    const QColor& color = g_possibleNaubColors.at(qrand() * 1.0f *
            g_possibleNaubColors.count() / RAND_MAX);
    const QString& name = colorToName(color.rgb());

    return QPair<const QColor&, const QString&>(color, name);
}


}

