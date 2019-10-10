#include "addtextbtn.h"

AddTextBtn::AddTextBtn(QWidget *parent) : DWidget(parent)
{
    this->setFixedHeight(84);
    m_addBtn = new DPushButton();
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

    QPalette pb;
    pb.setColor(QPalette::Button,QColor(00,00,00,10));
    m_addBtn->setPalette(pb);
}

AddTextBtn::~AddTextBtn()
{

}

void AddTextBtn::init()
{
    if(nullptr != m_addBtn)
    {
        QFont Font;
        Font.setFamily("SourceHanSansSC-Normal");
        Font.setPointSize(13);
        m_addBtn->setFont(Font);
        m_addBtn->setText("点击添加文字记事项");

        QPalette pe;
        pe.setColor(QPalette::Text,QColor(QRgb(0x526A7F)));
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
