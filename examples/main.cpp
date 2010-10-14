#include <QApplication>
#include <QTime>
#include <QTimer>
#include <Naubino.h>
#include <QNaubino.h>
#include <TestGame.h>
#include <Spammer.h>
#include <Cycler.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qsrand(QTime().currentTime().msec());

    Naubino naubino;
    QNaubino qnaubino(naubino);
    qnaubino.init();

    Cycler cycler;
    cycler.connect(&naubino,
                   SIGNAL(merged(Naub*)),
                   SLOT(testForCycle(Naub*)));
    naubino.connect(&cycler,
                    SIGNAL(cycleFound(QList<Naub*>&)),
                    SLOT(remove(QList<Naub*>&)));

    Spammer spammer(naubino);
    spammer.setInterval(2000);
    spammer.connect(&naubino,
                    SIGNAL(started()),
                    SLOT(start()));
    spammer.connect(&naubino,
                    SIGNAL(paused()),
                    SLOT(stop()));

    TestGame foo(naubino);
    QTimer timer;
    timer.singleShot(50, &foo, SLOT(foo()));

    naubino.start();

    return app.exec();
}

