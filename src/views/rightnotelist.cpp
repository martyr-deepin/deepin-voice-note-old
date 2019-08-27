#include "rightnotelist.h"
#include "textnoteitem.h"
#include "voicenoteitem.h"
#include <QDebug>
#include <uiutil.h>

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
    m_contextMenu = new QMenu;
    m_saveAsAction = new QAction(tr(NOTE_MENU_SAVE_AS),this);
    m_delAction = new QAction(tr(FOLDER_MENU_DELETE),this);
    m_contextMenu->addAction(m_saveAsAction);
    m_contextMenu->addAction(m_delAction);
    m_arrowMenu = new DArrowRectangle(DArrowRectangle::ArrowTop, DArrowRectangle::FloatWindow);
    m_arrowMenu->setHeight(200);
    m_arrowMenu->setWidth(200);

    m_arrowMenu->setContent(m_contextMenu);
    m_arrowMenu->setBorderColor(QColor::fromRgb(255, 0, 0));

    m_delConfirmDialog = UiUtil::createDialog(QString(""), QString(tr("您确定要删除这条记事项吗？")), nullptr);
//    m_delConfirmDialog->setOkButtonText(tr("删除"));
//    m_delConfirmDialog->setCancelButtonText(tr("取消"));
//    m_delConfirmDialog->setMessage(tr("您确定要删除这条记事项吗？"));
//    m_delConfirmDialog->setIcon()


}
void RightNoteList::initConnection()
{
    connect(m_delAction, SIGNAL(triggered(bool)), this, SLOT(handleDelItem(bool)));
    connect(m_saveAsAction, SIGNAL(triggered(bool)), this, SLOT(handleSaveAsItem(bool)));
    connect(m_delConfirmDialog, &DDialog::buttonClicked, this, &RightNoteList::handleDelDialogClicked);
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


    if(note.noteType == NOTE_TYPE::TEXT)
    {
        TextNoteItem *textItem = new TextNoteItem(note, m_noteController);
        connect(textItem, SIGNAL(textEditClicked(NOTE)), this, SIGNAL(textEditClicked(NOTE)));
        connect(textItem, SIGNAL(menuBtnClicked(QPoint, QPoint, TextNoteItem *, NOTE)), this, SLOT(handleMenuBtnClicked(QPoint, QPoint, TextNoteItem *, NOTE)));
        QListWidgetItem *item=new QListWidgetItem(this);
        qDebug() << "text item height: " << textItem->height();
        item->setSizeHint(QSize(this->width(),140));
        this->setItemWidget(item, textItem);

    }
    else if(note.noteType == NOTE_TYPE::VOICE){
        VoiceNoteItem *voiceItem = new VoiceNoteItem(note, m_noteController);
        QListWidgetItem *item=new QListWidgetItem(this);
        item->setSizeHint(QSize(this->width(),140));
        this->setItemWidget(item, voiceItem);
    }
}

void RightNoteList::handleMenuBtnClicked(QPoint menuArrowPointGlobal, QPoint menuArrowPointToItem, TextNoteItem *textNoteItem, NOTE note)
{
    QPoint itemGlobalPoint = textNoteItem->mapTo(this, menuArrowPointToItem);
    m_currSelItem= this->itemAt(itemGlobalPoint);
    m_currSelNote = note;
    m_arrowMenu->show(menuArrowPointGlobal.x(), menuArrowPointGlobal.y());

//    this->removeItemWidget(widgetItem);
//    delete widgetItem;
//    qDebug() << "handleMenuBtnClicked: x:" << itemGlobalPoint.x() << "handleMenuBtnClicked: y: " << itemGlobalPoint.y();

}


void RightNoteList::handleDelItem(bool)
{
    m_delConfirmDialog->show();

    m_arrowMenu->hide();
//    return;
}
void RightNoteList::handleSaveAsItem(bool)
{

    m_arrowMenu->hide();
}

void RightNoteList::handleDelDialogClicked(int index, const QString &text)
{
    if (index == 1)
    {
        if (m_noteController->deleteNote(m_currSelNote.id))
        {

            this->removeItemWidget(m_currSelItem);
            delete m_currSelItem;
            m_currSelItem = nullptr;
        }
        else {
            qDebug() << "error: delete item error";
        }
    }

}
