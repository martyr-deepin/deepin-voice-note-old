#include "addtextbtn.h"
#include "consts.h"

AddTextBtn::AddTextBtn(QWidget *parent) : DWidget(parent)
{
    this->setFixedHeight(ADDBUTTON_HEIGHT_HEIGHT);
    m_addBtn = new DPushButton(this);
    m_addBtn->setFixedSize(QSize(548,64));

    connect(m_addBtn, SIGNAL(clicked()), this, SIGNAL(addTextItem()));

    m_itemLayout = new QHBoxLayout(this);
    m_itemLayout->setContentsMargins(0, 0, 0, 0);

    QSpacerItem *phorizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_itemLayout->addItem(phorizontalSpacer1);
    m_itemLayout->addWidget(m_addBtn);
    QSpacerItem *phorizontalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_itemLayout->addItem(phorizontalSpacer2);

    //m_itemLayout->setSizeConstraint(QLayout::SetNoConstraint);

    this->setLayout(m_itemLayout);
    //this->setStyleSheet("background: red");

}

AddTextBtn::~AddTextBtn()
{
    if(nullptr != m_addBtn)
    {
        delete m_addBtn;
        m_addBtn = nullptr;
    }
}

void AddTextBtn::init()
{
    if(nullptr != m_addBtn)
    {
        QFont Font;
        Font.setFamily("SourceHanSansSC-Normal");
        Font.setPointSize(13);
        m_addBtn->setFont(Font);
        m_addBtn->setText(tr("点击添加文字记事项"));

        QPalette pe;
        //pe.setColor(QPalette::Text,QColor(82,106,127,00));
        pe.setColor(QPalette::ButtonText,QColor(82,106,127,255));
        pe.setColor(QPalette::Button,QColor(00,00,00,10));
        //pe.setColor(QPalette::Text,QColor(00,82,106,127));
        //pe.setColor(QPalette::Text,QColor(QRgb(0x526A7F)));
        m_addBtn->setPalette(pe);
    }
}

void AddTextBtn::setDisableBtn(bool flag)
{
    if(nullptr != m_addBtn)
    {
        m_addBtn->setDisabled(flag);
    }
}
