#include "rightview.h"
#include "textnoteitem.h"

//#include <QVBoxLayout>
#include "consts.h"
#include <DArrowRectangle>
#include <DtkGuis>
#include <QPalette>
#include <QTableWidgetItem>


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
    this->resize(548,this->height());
//    //this->setStyleSheet("background: blue");
//    m_stackedWidgetLayout = new QVBoxLayout();
//    this->setLayout(m_stackedWidgetLayout);
//    m_stackedWidget = new QStackedWidget();
//    m_stackedWidgetLayout->addWidget(m_stackedWidget);
//    this->setStyleSheet("background: green");
//    //m_stackedWidget->setGeometry(QRect(10, 10, 548, this->height()));
//    //m_stackedWidget->setGeometry(QRect(10, 10, this->width(), this->height()));
//    m_stackedWidget->setGeometry(QRect(0, 0, this->width(), this->height()));
//    m_stackedWidget->setObjectName("stackedWidget");
//    /*self.listPage.setObjectName("listPage")
//    self.listWidget = QtWidgets.QListWidget(self.listPage)
//    self.listWidget.setGeometry(QtCore.QRect(0, 10, 1111, 861))
//    self.listWidget.setObjectName("listWidget")*/
//    //m_noteListPage->resize(548,m_noteListPage->height());
//    m_stackedWidget->addWidget(m_noteListPage);
//    //m_noteListWidget->resize(548,m_noteListWidget->height());
//    m_detailPage = new QWidget();
//    m_plainTextEdit = new QPlainTextEdit(m_detailPage);
////    self.detailPage = QtWidgets.QWidget()
////    self.detailPage.setObjectName("detailPage")
////    self.plainTextEdit = QtWidgets.QPlainTextEdit(self.detailPage)
////    self.plainTextEdit.setGeometry(QtCore.QRect(10, 40, 1071, 821))
////    self.plainTextEdit.setObjectName("plainTextEdit")
//    m_stackedWidget->addWidget(m_detailPage);
//    QPalette palette;
//    palette.setColor(QPalette::Background, QColor(255, 255, 255));
//    this->setAutoFillBackground(true);
//    this->setPalette(palette);
}


void RightView::initConnection()
{
    //&RightView::addTextNote
    connect(m_noteListWidget, SIGNAL(addTextItem()), this, SLOT(addTextNote()));
    connect(m_noteListWidget, SIGNAL(textEditClicked(NOTE)), this, SIGNAL(textEditClicked(NOTE)));
    connect(m_noteListWidget, SIGNAL(currentRowChanged(int)), this, SIGNAL(OnCurrentRowChanged(int)));
    connect(m_addVoiceBtn, &DImageButton::clicked, this, &RightView::handleStartRecord);
    connect(m_addVoiceBtn, &DImageButton::clicked, m_noteListWidget, &RightNoteList::handleClickRecordButton);
    connect(m_recordPage, &RecordPage::finishRecord, this, &RightView::handleStopRecord);
}


void RightView::initNoteList()
{
    m_noteController = new NoteController();
    m_noteListPage = new QWidget();
    //m_noteListPage->resize(500,m_noteListPage->height());
    m_noteListPage->resize(548,m_noteListPage->height());
    //m_noteListPage->setStyleSheet("background: blue");
    m_noteListLayout = new QVBoxLayout();
    m_noteListLayout->setContentsMargins(0, 0, 0, 0);



    m_noteListWidget = new RightNoteList(m_noteController);
    //m_noteListWidget.set

    m_noteListWidget->setFocusPolicy(Qt::NoFocus);
    //qDebug()<<"m_noteListWidget width7:"<<m_noteListWidget->width();
    m_noteListLayout->addWidget(m_noteListWidget);
    //qDebug()<<"m_noteListWidget width8:"<<m_noteListWidget->width();
    //m_noteListWidget->setObjectName("LeftSideBar");
    //leftFolderView->setFixedWidth(LEFTVIEW_MAX_WIDTH);
    //m_noteListWidget->addWidget(m_leftFolderView);

//    m_addTextBtn = new DImageButton();
//    m_addTextBtn->setNormalPic(":/image/add_text_btn.png");
//    m_addTextBtn->setHoverPic(":/image/add_text_btn.png");
//    m_addTextBtn->setPressPic(":/image/add_text_btn_press.png");

    //m_noteListLayout->addWidget(m_addTextBtn);

    //initRecordStackedWidget();

    //m_noteListLayout->addWidget(m_recordStackedWidget);
    m_noteListLayout->addSpacing(1);

    QSizePolicy sp = m_noteListWidget->sizePolicy();
    sp.setVerticalStretch(1);
    //sp.setVerticalPolicy(QSizePolicy::Expanding);
    m_noteListWidget->setSizePolicy(sp);
    //qDebug()<<"m_noteListWidget width1:"<<m_noteListWidget->width();
    m_noteListPage->setLayout(m_noteListLayout);
    //qDebug()<<"m_noteListWidget width2:"<<m_noteListWidget->width();
    QVBoxLayout *rightViewLayout = new QVBoxLayout();
    rightViewLayout->setContentsMargins(0, 0, 0, 0);
    rightViewLayout->addWidget(m_noteListPage);
    //qDebug()<<"m_noteListWidget width3:"<<m_noteListWidget->width();
    this->setLayout(rightViewLayout);
    //qDebug()<<"m_noteListWidget width4:"<<m_noteListWidget->width();
    //m_noteListPage->setFixedWidth(pare);

    initRecordStackedWidget();

    //test
    //m_noteListPage->move(0,m_noteListPage->y());
//    QWidget *ptm = new QWidget(this);
//    ptm->setFixedSize(this->width(),this->height());
//    ptm->move(0,0);
//    QPalette p;
//    //p.setBrush(m_BackGround->backgroundRole(),QBrush(QColor(255,245,245,100)));
//    p.setBrush(ptm->backgroundRole(),QBrush(QColor(QRgb(0x00000000))));
//    ptm->setPalette(p);
//    ptm->setAutoFillBackground(true);
    //ptm->show();
}

void RightView::initRecordStackedWidget()
{
    m_recordStackedWidget = new QStackedWidget(this);
    m_recordStackedWidget->setFixedSize(QSize(548,64));

    m_addVoiceBtn = new DImageButton();
    m_addVoiceBtn->setFixedSize(QSize(68,68));
    m_addVoiceBtn->setNormalPic(":/image/icon/normal/circlebutton_voice.svg");
    m_addVoiceBtn->setHoverPic(":/image/icon/hover/circlebutton_voice_hover.svg");
    m_addVoiceBtn->setPressPic(":/image/icon/press/circlebutton_voice_press.svg");


//    QHBoxLayout *HLayout = new QHBoxLayout(HBoard);
//    HLayout->addWidget(m_addVoiceBtn);
//    DWidget *VBoard = new DWidget;
//    QVBoxLayout *VLayout = new QVBoxLayout(VBoard);
//    VLayout->addWidget(HBoard);

    m_recordPage = new RecordPage();

    m_recordStackedWidget->addWidget(m_addVoiceBtn);
    m_recordStackedWidget->addWidget(m_recordPage);
    m_recordStackedWidget->setCurrentIndex(0);
    m_recordStackedWidget->setFixedSize(QSize(m_addVoiceBtn->width(),m_recordStackedWidget->height()));
    m_recordStackedWidget->move((this->width() - m_recordStackedWidget->width())/2,m_recordStackedWidget->y());
    //m_recordStackedWidget->setFixedWidth(m_addVoiceBtn->width());
    //qDebug()<<"m_recordStackedWidget x y:"<<m_recordStackedWidget->x()<<" "<<m_recordStackedWidget->y();
    //m_recordStackedWidget->move(0,0);

//    qDebug()<<"RightView width:"<<this->width();
//    m_recordStackedWidget->move((this->width() - m_recordStackedWidget->width())/2,this->height() - 10 - m_recordStackedWidget->height());
//    m_recordStackedWidget->show();
}


void RightView::handleSelFolderChg(int folderId)
{
    //stopAllNeedStop
    m_noteListWidget->stop();

    m_currFolderId = folderId;
    updateNoteList();

}

void RightView::handleSearchNote(int folderId, QString searchKey)
{
    m_currFolderId = folderId;

    searchNoteList(searchKey);
}

void RightView::addTextNote()
{
    NOTE note;
    note.folderId = m_currFolderId;
    note.noteType = NOTE_TYPE::TEXT;
    note.createTime = QDateTime::currentDateTime();
    note.contentText = "";


    m_noteController->addNote(note);
    addNoteToNoteList(note);
    //updateNoteList();

//    TextNoteItem *item = (TextNoteItem*)(m_noteListWidget->itemWidget(m_noteListWidget->item(m_noteListWidget->count() - 1)));
//    item->changeToEditMode();

//    m_leftFolderView->setCurrentRow(0);
}

void RightView::addNoteToNoteList(NOTE note)
{
    m_noteListWidget->addWidgetItem(note, "");
    m_noteListWidget->scrollToBottom();

//    if (m_currFolderId > 0)
//    {
//        QList<NOTE> noteList = m_noteController->getNoteListByFolderId(m_currFolderId);
//        for (int i = noteList.size() - 1; i < noteList.size(); i++)
//        {
//            m_noteListWidget->addWidgetItem(noteList.at(i), "");
//        }
//        m_noteListWidget->scrollToBottom();
//    }
}

void RightView::updateNoteList()
{
    //qDebug()<<"before clear m_noteListWidget width:"<<m_noteListWidget->width();
    m_noteListWidget->delAddTextBtn();
    m_noteListWidget->clear();
    //qDebug()<<"after clear m_noteListWidget width:"<<m_noteListWidget->width();
    if (m_currFolderId > 0)
    {
        m_noteListWidget->addAddTextBtn();
        QList<NOTE> noteList = m_noteController->getNoteListByFolderId(m_currFolderId);
        for (int i = 0; i < noteList.size(); i++)
        {
            m_noteListWidget->addWidgetItem(noteList.at(i), "");
        }
        m_noteListWidget->scrollToBottom();
    }
}

void RightView::searchNoteList(QString searchKey)
{
    m_noteListWidget->delAddTextBtn();
    m_noteListWidget->clear();
    if (m_currFolderId > 0)
    {
        QList<NOTE> noteList;
        if (searchKey.isEmpty())
        {
            noteList = m_noteController->getNoteListByFolderId(m_currFolderId);
        }
        else
        {
            noteList = m_noteController->searchNote(m_currFolderId, searchKey);
        }

        m_noteListWidget->addAddTextBtn();
        for (int i = 0; i < noteList.size(); i++)
        {
            m_noteListWidget->addWidgetItem(noteList.at(i), searchKey);
        }
        m_noteListWidget->scrollToBottom();
    }
}

void RightView::handleStartRecord()
{
    m_recordStackedWidget->setCurrentIndex(1);
    m_recordStackedWidget->setFixedSize(QSize(548,m_recordStackedWidget->height()));
    m_recordStackedWidget->move((this->width() - m_recordStackedWidget->width())/2,m_recordStackedWidget->y());
    //m_recordStackedWidget->move(0,this->height() - m_recordStackedWidget->height());
    m_recordPage->startRecord();
}
//typedef struct
//{
//    int id;
//    NOTE_TYPE noteType;
//    QString contentText;
//    QString contentPath;
//    int voiceTime;
//    int folderId;
//    QDateTime createTime;
//}NOTE;

//typedef struct
//{
//    QString voicePath;
//    int voiceLength;
//}VOICE_INFO;
void RightView::handleStopRecord(VOICE_INFO voiceInfo)
{
    NOTE voiceNote;
    voiceNote.noteType = NOTE_TYPE::VOICE;
    voiceNote.contentPath = voiceInfo.voicePath;
    voiceNote.voiceTime = voiceInfo.voiceLength;
    voiceNote.voiceSampleData = voiceInfo.voiceSampleData;
    voiceNote.folderId = m_currFolderId;
    voiceNote.createTime = QDateTime::currentDateTime();
    if (!m_noteController->addNote(voiceNote))
    {
        qDebug() << "handleStopRecord： add voice note error！";
    }
    m_recordStackedWidget->setCurrentIndex(0);
    m_recordStackedWidget->setFixedSize(QSize(m_addVoiceBtn->width(),m_recordStackedWidget->height()));
    m_recordStackedWidget->move((this->width() - m_recordStackedWidget->width())/2,m_recordStackedWidget->y());
    addNoteToNoteList(voiceNote);
    //updateNoteList();
}

void RightView::handleClearNote()
{
    m_noteListWidget->clear();
    m_currFolderId = -1;
}

void RightView::OnCurrentRowChanged(int curRow)
{
    qDebug()<<"curRow:"<<curRow;
    m_noteListWidget->setCurrentRow(1);
}

void RightView::resizeEvent(QResizeEvent * event)
{
    if(nullptr != m_recordStackedWidget)
    {
        qDebug()<<"RightView width:"<<this->width();
        qDebug()<<"m_recordStackedWidget width:"<<m_recordStackedWidget->width();
        m_recordStackedWidget->move((this->width() - m_recordStackedWidget->width())/2,this->height() - 12 - m_recordStackedWidget->height());
        qDebug()<<"m_recordStackedWidget x y:"<<m_recordStackedWidget->x()<<" "<<m_recordStackedWidget->y();
        m_recordStackedWidget->show();
    }
}
