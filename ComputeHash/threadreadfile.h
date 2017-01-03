#ifndef THREADREADFILE_H
#define THREADREADFILE_H

#include <QObject>
#include "util/util.h"

#ifdef _DEBUG
#include <QDebug>
#endif

class ThreadReadFile : public QObject
{
    Q_OBJECT
public:
    explicit ThreadReadFile(QObject *parent = 0);
    void doWork(util::factoryCreateResult computeStruct, QString filePath);

signals:
    void resultReady(util::computeResult result);

private:
    inline void emitResult(util::ResultMessageType resultType ,util::ComputeType computeType ,
                    QString filePath ,qint64 fileSize ,qint64 fileProgress ,
                    QString result = QString());
    inline qint64 automaticDivision(qint64 fileSize);

};

#endif // THREADREADFILE_H
