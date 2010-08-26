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
    naubino.update();

    return a.exec();
}
