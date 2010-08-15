#ifndef COLOR_H
#define COLOR_H

#include <QtCore>
#include <QColor>

class Color
{
public:
    Color() : _name("unnamed") {
        _qcolor = QColor();
    }

    Color(int r, int g, int b, QString name)
        : _name(name) {
        _qcolor = QColor(r, g, b);
    }

    QString readableName() { return _name; }
    QColor qcolor() { return _qcolor; }

    static QMap<QString, Color>* naubino();
    static QList<Color>* naub();

    static Color randomNaub();

protected:
    QString _name;
    QColor _qcolor;
private:
    static void M0(int r, int g, int b, QString n);
    static void M1(QString n);
};

#endif // COLOR_H
