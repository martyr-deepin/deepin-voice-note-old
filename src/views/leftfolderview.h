#ifndef LEFTFOLDERVIEW_H
#define LEFTFOLDERVIEW_H

#include <QListWidget>
#include <QMenu>
#include "folerwidgetitem.h"
#include "src/app/consts.h"



class LeftFolderView : public QListWidget
{
    Q_OBJECT
public:
    LeftFolderView(FolderController *m_folderCtr);
    void addWidgetItem(FOLDER folder);
public slots:
    void handleCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void handleDelItem(bool checked);
    void handleRenameItem(bool checked);
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    FolderController *m_folderCtr;
    QMenu *m_contextMenu;
    QAction *m_renameAction;
    QAction *m_delAction;
    void initUI();
    void initConnection();

};

#endif // LEFTFOLDERVIEW_H
