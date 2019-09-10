#ifndef LEFTFOLDERVIEW_H
#define LEFTFOLDERVIEW_H

#include <DListWidget>
#include <QMenu>
#include "folerwidgetitem.h"
#include "src/app/consts.h"



class LeftFolderList : public DListWidget
{
    Q_OBJECT
public:
    LeftFolderList(FolderController *m_folderCtr);
    ~LeftFolderList();
    void addWidgetItem(FOLDER folder, QString searchKey);
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
