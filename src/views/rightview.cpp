#include "rightview.h"

#include <QVBoxLayout>
#include "consts.h"


RightView::RightView()
{
    initUI();
}

void RightView::initUI()
{
    initNoteList();
    //this->setStyleSheet("background: green");
    m_stackedWidget = new QStackedWidget(this);
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


void RightView::initNoteList()
{
    noteController = new NoteController();
    m_noteListPage = new QWidget();
    m_noteListLayout = new QVBoxLayout();
    m_noteListLayout->setContentsMargins(0, 0, 0, 0);



    m_noteListWidget = new RightNoteList(noteController);
    NOTE note1;
    note1.folderId = 1;
    note1.noteType = NOTE_TYPE::TEXT;
    note1.createTime = QDateTime::currentDateTime();
    note1.contentText = "这是一条测试用的case，sougo输入法这么难用吗";
    m_noteListWidget->addWidgetItem(note1);

    NOTE note2;
    note2.folderId = 1;
    note2.noteType = NOTE_TYPE::TEXT;
    note2.createTime = QDateTime::currentDateTime();
    note2.contentText = "这是一条测试用的case，sougo输入法这么难用吗";
    m_noteListWidget->addWidgetItem(note2);
    m_noteListLayout->addWidget(m_noteListWidget);
//    QList<FOLDER> folderList = m_folderCtr->getFolderList();
//    for (int i = 0; i < folderList.size(); i++)
//    {
//        m_leftFolderView->addWidgetItem(folderList.at(i));
//    }
    //m_noteListWidget->setObjectName("LeftSideBar");
    //leftFolderView->setFixedWidth(LEFTVIEW_MAX_WIDTH);
    //m_noteListWidget->addWidget(m_leftFolderView);

    m_addTextBtn = new DImageButton();
    m_addTextBtn->setNormalPic(":/image/add_text_btn.png");
    m_addTextBtn->setHoverPic(":/image/add_text_btn.png");
    m_addTextBtn->setPressPic(":/image/add_text_btn_press.png");

    m_noteListLayout->addWidget(m_addTextBtn);
    m_addVoiceBtn = new DImageButton();
    m_addVoiceBtn->setNormalPic(":/image/add_normal.svg");
    m_addVoiceBtn->setHoverPic(":/image/add_hover.svg");
    m_addVoiceBtn->setPressPic(":/image/add_press.svg");

    m_noteListLayout->addWidget(m_addVoiceBtn);

    QSizePolicy sp = m_noteListWidget->sizePolicy();
    sp.setVerticalPolicy(QSizePolicy::Expanding);
    m_noteListWidget->setSizePolicy(sp);
    m_noteListPage->setLayout(m_noteListLayout);
    //m_noteListPage->setFixedWidth(pare);
}
