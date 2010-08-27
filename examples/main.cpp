#include <QtGui/QApplication>
#include <Naubino.h>
#include <Scene.h>
#include <View.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Naubino naubino;
    Scene scene(naubino);
    View view(scene);
    view.show();

    Naub &a = naubino.addNaub(Vec(-0.30, 0));
    Naub &b = naubino.addNaub(Vec( 0.30, 0));
    naubino.joinNaubs(a, b);
    naubino.joinWithCenter(a);
    naubino.joinWithCenter(b);

    QTimer *timer = new QTimer();
    timer->connect(timer, SIGNAL(timeout()), &naubino, SLOT(update()));
    timer->start(50);

    int ret = app.exec();

    timer->stop();
    timer->disconnect();
    delete timer;
    timer = 0;

    return ret;
}
