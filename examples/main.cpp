#include <QApplication>
#include <QTime>
#include <Naubino.h>
#include <QNaubino.h>
#include <TestGame.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qsrand(QTime().currentTime().msec());

    Naubino naubino;
    QNaubino qnaubino(naubino);
    qnaubino.init();

    foo(naubino);

    return app.exec();
}

