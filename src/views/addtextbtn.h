#ifndef ADDTEXTBTN_H
#define ADDTEXTBTN_H

#include <QWidget>
#include <DPushButton>
#include <QHBoxLayout>

DWIDGET_USE_NAMESPACE

class AddTextBtn : public DWidget
{
    Q_OBJECT
public:
    explicit AddTextBtn(QWidget *parent = nullptr);
    ~AddTextBtn();
    void init();
signals:
    void addTextItem();

public slots:

private:
    DPushButton *m_addBtn;
    QHBoxLayout *m_itemLayout;
};

#endif // ADDTEXTBTN_H
