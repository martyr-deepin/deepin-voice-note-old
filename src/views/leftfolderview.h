#ifndef LEFTFOLDERVIEW_H
#define LEFTFOLDERVIEW_H

#include <QListWidget>
#include "folerwidgetitem.h"



class LeftFolderView : public QListWidget
{
    Q_OBJECT
public:
    LeftFolderView();
public slots:
    void handleCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
private:
    void initUI();
    void initConnection();
    void addWidgetItem(FOLDER folder);
};

#endif // LEFTFOLDERVIEW_H
