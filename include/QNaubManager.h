#ifndef QNAUBMANAGER_H
#define QNAUBMANAGER_H

#include <QObject>

class QNaub;
class Naub;

class QNaubManager : public QObject {
    Q_OBJECT
signals:
    void added(QNaub *qnaub);
public slots:
    void add(Naub *naub);
public:
    QNaubManager(QObject *parent = 0) : QObject(parent) {}
};

#endif // QNAUBMANAGER_H
