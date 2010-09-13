#ifndef QNAUB_H
#define QNAUB_H

#include <QObject>

class Naub;

class QNaub : public QObject {
    Q_OBJECT
signals:
    void selected();
    void deselected();
public slots:
    void update(Naub *naub);
};

#endif // QNAUB_H
