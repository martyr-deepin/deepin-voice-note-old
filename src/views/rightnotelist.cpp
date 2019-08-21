#include "rightnotelist.h"
#include "textnoteitem.h"

RightNoteList::RightNoteList(NoteController *noteController)
{
    initUI();
    initConnection();
}

RightNoteList::~RightNoteList()
{

}

void RightNoteList::initUI()
{

}
void RightNoteList::initConnection()
{

}

//void LeftFolderList::addWidgetItem(FOLDER folder) {
//    QListWidgetItem *item=new QListWidgetItem(this);
//    item->setBackground(QBrush(QPixmap(":/image/folder_normal.png")));
//    item->setSizeHint(QSize(200,60));
//    FolerWidgetItem *folderItem = new FolerWidgetItem(folder, m_folderCtr);
//    this->setItemWidget(item, folderItem);
//}

void RightNoteList::addWidgetItem(NOTE note)
{
    QListWidgetItem *item=new QListWidgetItem(this);
    item->setSizeHint(QSize(this->width(),100));
    if(note.noteType == NOTE_TYPE::TEXT)
    {
        TextNoteItem *textItem = new TextNoteItem(note, m_noteController);
        this->setItemWidget(item, textItem);
    }
    else {
        //todo加载voice note
    }
}
