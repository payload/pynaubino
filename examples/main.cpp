#include <QtGui/QApplication>
#include <Naubino.h>
#include <Scene.h>
#include <View.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Naubino naubino;
    Scene scene(naubino);
    View view(scene);
    view.show();

    naubino.joinNaubs(naubino.addNaub(Vec(-0.30, 0)),
                      naubino.addNaub(Vec( 0.30, 0)));
    QTimer *timer = new QTimer();
    timer->connect(timer, SIGNAL(timeout()), &naubino, SLOT(update()));
    timer->start(50);

    return a.exec();
}
