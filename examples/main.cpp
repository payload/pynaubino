#include <QtGui/QApplication>
#include <Naubino.h>
#include <Scene.h>
#include <View.h>

#include <NaubPairSpammer.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Naubino naubino;
    Scene scene(naubino);
    View view(scene);
    view.show();

    QTimer timer;
    timer.connect(timer, SIGNAL(timeout()), &naubino, SLOT(update()));
    timer.start(50);

    NaubPairSpammer spam(&naubino);
    spam.start(2000);

    return app.exec();
}
