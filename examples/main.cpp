#include <QApplication>
#include <QTime>
#include <Naub.h>
#include <NaubManager.h>
#include <JointManager.h>
#include <QNaubManager.h>
#include <QJointManager.h>
#include <QScene.h>
#include <QGraphicsView>
#include <Simulator.h>

/*
#include <Naubino.h>
#include <NaubPairSpammer.h>
#include <Scene.h>
#include <View.h>



#include <NaubPairSpammer.h>
#include <ContactListener.h>
#include <SimpleContactHandler.h>
#include <Cycler.h>
#include <Popper.h>
#include <Menu.h>
*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qsrand(QTime().currentTime().msec());

    Simulator *sim = new Simulator();

    NaubManager *naubs = new NaubManager();
    JointManager *joints = new JointManager();
    QNaubManager *qnaubs = new QNaubManager();
    QJointManager *qjoints = new QJointManager();

    naubs->connect(sim, SIGNAL(timeout()), SLOT(update()));
    qnaubs->connect(naubs, SIGNAL(added(Naub*)), SLOT(add(Naub*)));
    qjoints->connect(joints, SIGNAL(added(Joint*)), SLOT(add(Joint*)));

    QScene *scene = new QScene();
    scene->connect(qnaubs, SIGNAL(added(QNaub*)), SLOT(add(QNaub*)));

    QGraphicsView *view = new QGraphicsView();
    view->setScene(scene);
    view->show();

    Naub *n0 = new Naub(sim->world());
    Naub *n1 = new Naub(sim->world());
    n0->setPos(Vec(-1, 0));
    n1->setPos(Vec( 1, 0));
    naubs->add(n0);
    naubs->add(n1);
    naubs->join(n0, n1);

    sim->start(50);

    /*
    Naubino naubino;

    NaubPairSpammer spam(&naubino);
    spam.start(2000);

    ContactListener conlistener;
    naubino.world().SetContactListener(&conlistener);

    SimpleContactHandler conhandler;
    conhandler.connect(&conlistener,
                       SIGNAL(naubOnNaub(Naub*,Naub*)),
                       SLOT(naubOnNaub(Naub*,Naub*)));
    conhandler.connect(&naubino,
                       SIGNAL(preUpdate()),
                       SLOT(handle()));

    Cycler cycler;
    cycler.connect(&naubino,
                   SIGNAL(mergedNaub(Naub*)),
                   SLOT(testForCycle(Naub*)));

    Popper popper(&naubino);
    popper.connect(&cycler,
                   SIGNAL(cycleFound(QList<Naub*>*)),
                   SLOT(popNaubs(QList<Naub*>*)));

    Scene scene(&naubino);
    scene.connect(&naubino,
            SIGNAL(newNaub(Naub*)),
            SLOT(newNaub(Naub*)));
    scene.connect(&naubino,
            SIGNAL(newNaubJoint(NaubJoint*)),
            SLOT(newNaubJoint(NaubJoint*)));

    Menu menu(&scene);
    menu.start();

    View view(&scene);
    view.show();

    QTimer timer;
    timer.connect(&timer, SIGNAL(timeout()), &naubino, SLOT(update()));
    timer.start(50);
*/

    return app.exec();
}

