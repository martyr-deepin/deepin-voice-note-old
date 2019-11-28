#ifndef NOTEWATCHERCONTROLLER_H
#define NOTEWATCHERCONTROLLER_H

#include <QObject>

class NoteWatcherController : public QObject
{
    Q_OBJECT
public:
    explicit NoteWatcherController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // NOTEWATCHERCONTROLLER_H