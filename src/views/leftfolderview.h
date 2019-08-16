#ifndef LEFTFOLDERVIEW_H
#define LEFTFOLDERVIEW_H

#include <QListWidget>
#include "folerwidgetitem.h"
#include "src/app/consts.h"



class LeftFolderView : public QListWidget
{
    Q_OBJECT
public:
    LeftFolderView();
    void addWidgetItem(FOLDER folder);
public slots:
    void handleCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
private:
    void initUI();
    void initConnection();

};

#endif // LEFTFOLDERVIEW_H
