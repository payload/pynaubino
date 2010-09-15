#include <QApplication>
#include <QTime>
#include <Naub.h>
#include <NaubJoint.h>
#include <NaubManager.h>
#include <JointManager.h>
#include <QNaubManager.h>
#include <QJointManager.h>
#include <QScene.h>
#include <QGraphicsView>
#include <Simulator.h>
#include <Qb2DebugDraw.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qsrand(QTime().currentTime().msec());

    Simulator *sim = new Simulator(&app);

    NaubManager *naubs = new NaubManager(&app);
    JointManager *joints = new JointManager(&app);
    QNaubManager *qnaubs = new QNaubManager(&app);
    QJointManager *qjoints = new QJointManager(&app);

    naubs->connect(sim, SIGNAL(timeout()), SLOT(update()));
    joints->connect(naubs,
                    SIGNAL(added(Joint*)),
                    SLOT(add(Joint*)));
    qnaubs->connect(naubs, SIGNAL(added(Naub*)), SLOT(add(Naub*)));
    qjoints->connect(joints,
                     SIGNAL(added(Joint*)),
                     SLOT(add(Joint*)));

    QScene *scene = new QScene(sim->world());
    scene->connect(qnaubs, SIGNAL(added(QNaub*)), SLOT(add(QNaub*)));
    scene->connect(qjoints, SIGNAL(added(QJoint*)), SLOT(add(QJoint*)));

    QGraphicsView *view = new QGraphicsView();
    view->setScene(scene);
    view->show();

    Naub *n0 = new Naub(sim->world());
    Naub *n1 = new Naub(sim->world());
    n0->setPos(Vec(-0.4, 0));
    n1->setPos(Vec( 0.4, 0));
    naubs->add(n0);
    naubs->add(n1);
    n0->contact(n1);

    sim->start(50);

    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    Qb2DebugDrawItem *dd = new Qb2DebugDrawItem(sim->world());
    scene->addItem(dd);

    int ret = app.exec();

    delete view;
    delete scene;

    return ret;
}

