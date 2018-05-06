#ifndef EYE_H
#define EYE_H

#include <QObject>
#include "dialog.h"

class eye : public QObject
{
    Q_OBJECT
public:
    explicit eye(QObject *parent = nullptr, Dialog *dia = nullptr);

signals:

public slots:

private:
    Dialog *ui;
};

#endif // EYE_H
