#include <QApplication>
#include <QTime>
#include <Naubino.h>
#include <QNaubino.h>
#include <TestGame.h>
#include <Spammer.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qsrand(QTime().currentTime().msec());

    Naubino naubino;
    QNaubino qnaubino(naubino);
    qnaubino.init();
    Spammer spammer(naubino);
    spammer.start(1000);

    return app.exec();
}

