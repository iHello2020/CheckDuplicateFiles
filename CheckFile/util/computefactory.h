#ifndef COMPUTEFACTORY_H
#define COMPUTEFACTORY_H

#include <QObject>
#include <QList>
#include "util/util.h"
#include "compute.h"

class CHECKFILESHARED_EXPORT Factory :public QObject
{
public:
    explicit Factory(QObject *parent = 0);
    virtual ~Factory();
    virtual QList<util::factoryCreateResult> createCompute(const util::CheckType type);

};

#endif // COMPUTEFACTORY_H
