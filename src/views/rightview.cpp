#include "rightview.h"
#include "textnoteitem.h"

#include <QVBoxLayout>
#include "consts.h"
#include "darrowrectangle.h"


RightView::RightView()
{
    m_currFolderId = -1;
    initUI();
    initConnection();
}

RightView::~RightView()
{

}

void RightView::initUI()
{
//    DArrowRectangle *m_arrowMenu = new DArrowRectangle(DArrowRectangle::ArrowTop, DArrowRectangle::FloatWidget, this);
//    m_arrowMenu->setHeight(80);
//    m_arrowMenu->setWidth(80);
//    m_arrowMenu->show(0, 0);
    initNoteList();
    //this->setStyleSheet("background: blue");
    m_stackedWidgetLayout = new QVBoxLayout();
    this->setLayout(m_stackedWidgetLayout);
    m_stackedWidget = new QStackedWidget();
    m_stackedWidgetLayout->addWidget(m_stackedWidget);
    //m_stackedWidget->setStyleSheet("background: blue");
    m_stackedWidget->setGeometry(QRect(10, 10, this->width(), this->height()));
    m_stackedWidget->setObjectName("stackedWidget");

    /*self.listPage.setObjectName("listPage")
    self.listWidget = QtWidgets.QListWidget(self.listPage)
    self.listWidget.setGeometry(QtCore.QRect(0, 10, 1111, 861))
    self.listWidget.setObjectName("listWidget")*/
    m_stackedWidget->addWidget(m_noteListPage);
    m_detailPage = new QWidget();
    m_plainTextEdit = new QPlainTextEdit(m_detailPage);
//    self.detailPage = QtWidgets.QWidget()
//    self.detailPage.setObjectName("detailPage")
//    self.plainTextEdit = QtWidgets.QPlainTextEdit(self.detailPage)
//    self.plainTextEdit.setGeometry(QtCore.QRect(10, 40, 1071, 821))
//    self.plainTextEdit.setObjectName("plainTextEdit")
    m_stackedWidget->addWidget(m_detailPage);


}

void RightView::initConnection()
{
    connect(m_addTextBtn, &DImageButton::clicked, this, &RightView::addTextNote);
    connect(m_noteListWidget, SIGNAL(textEditClicked(NOTE)), this, SIGNAL(textEditClicked(NOTE)));
}


void RightView::initNoteList()
{
    m_noteController = new NoteController();
    m_noteListPage = new QWidget();
    //m_noteListPage->setStyleSheet("background: blue");
    m_noteListLayout = new QVBoxLayout();
    m_noteListLayout->setContentsMargins(0, 0, 0, 0);



    m_noteListWidget = new RightNoteList(m_noteController);
    //m_noteListWidget->setStyleSheet("background: blue");
//    NOTE note1;
//    note1.folderId = 1;
//    note1.noteType = NOTE_TYPE::TEXT;
//    note1.createTime = QDateTime::currentDateTime();
//    note1.contentText = "这是一条测试用的case，sougo输入法这么难用吗";
//    m_noteListWidget->addWidgetItem(note1);
//    //m_noteController->addNote(note1);

//    NOTE note2;
//    note2.folderId = 1;
//    note2.noteType = NOTE_TYPE::TEXT;
//    note2.createTime = QDateTime::currentDateTime();
//    note2.contentText = "这是一条测试用的case2，sougo输入法这么难用吗";
//    m_noteListWidget->addWidgetItem(note2);
//    //m_noteController->addNote(note2);

    m_noteListLayout->addWidget(m_noteListWidget);

    //m_noteListWidget->setObjectName("LeftSideBar");
    //leftFolderView->setFixedWidth(LEFTVIEW_MAX_WIDTH);
    //m_noteListWidget->addWidget(m_leftFolderView);

    m_addTextBtn = new DImageButton();
    m_addTextBtn->setNormalPic(":/image/add_text_btn.png");
    m_addTextBtn->setHoverPic(":/image/add_text_btn.png");
    m_addTextBtn->setPressPic(":/image/add_text_btn_press.png");

    m_noteListLayout->addWidget(m_addTextBtn);
    m_addVoiceBtn = new DImageButton();
    m_addVoiceBtn->setNormalPic(":/image/icon/normal/circlebutton_voice.svg");
    m_addVoiceBtn->setHoverPic(":/image/icon/hover/circlebutton_voice_hover.svg");
    m_addVoiceBtn->setPressPic(":/image/icon/press/circlebutton_voice_press.svg");

    m_noteListLayout->addWidget(m_addVoiceBtn);

    QSizePolicy sp = m_noteListWidget->sizePolicy();
    sp.setVerticalStretch(1);
    //sp.setVerticalPolicy(QSizePolicy::Expanding);
    m_noteListWidget->setSizePolicy(sp);
    m_noteListPage->setLayout(m_noteListLayout);
    //m_noteListPage->setFixedWidth(pare);
}

void RightView::handleSelFolderChg(int folderId)
{
    m_currFolderId = folderId;
    updateNoteList();

}

void RightView::addTextNote()
{
    NOTE note;
    note.folderId = m_currFolderId;
    note.noteType = NOTE_TYPE::TEXT;
    note.createTime = QDateTime::currentDateTime();
    note.contentText = "";
    m_noteListWidget->addWidgetItem(note);


    m_noteController->addNote(note);
    updateNoteList();
    TextNoteItem *item = (TextNoteItem*)(m_noteListWidget->itemWidget(m_noteListWidget->item(m_noteListWidget->count() - 1)));
    item->changeToEditMode();
//    m_leftFolderView->setCurrentRow(0);
}

void RightView::updateNoteList()
{
    m_noteListWidget->clear();
    if (m_currFolderId > 0)
    {
        QList<NOTE> noteList = m_noteController->getNoteListByFolderId(m_currFolderId);
        for (int i = 0; i < noteList.size(); i++)
        {
            m_noteListWidget->addWidgetItem(noteList.at(i));
        }
        m_noteListWidget->scrollToBottom();
    }
}
