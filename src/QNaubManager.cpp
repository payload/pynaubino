#include "QNaubManager.h"
#include <QNaub.h>
#include <Naub.h>
#include <Box2D/Dynamics/b2World.h>

void QNaubManager::add(Naub *naub) {
    QNaub *qnaub = new QNaub();
    qnaub->connect(naub, SIGNAL(changed(Naub*)), SLOT(update(Naub*)));
    qnaub->connect(naub, SIGNAL(removed(Naub*)), SLOT(remove(Naub*)));
    naub->connect(qnaub,
                  SIGNAL(selected(Pointer*)),
                  SLOT(select(Pointer*)));
    naub->connect(qnaub,
                  SIGNAL(deselected(Pointer*)),
                  SLOT(deselect(Pointer*)));
    qnaub->update(naub);
    emit added(qnaub);
}
