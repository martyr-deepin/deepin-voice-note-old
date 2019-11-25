#ifndef SEARCHNONEPAGE_H
#define SEARCHNONEPAGE_H

#include <DFrame>
#include <DLabel>

DWIDGET_USE_NAMESPACE
class SearchNonePage : public DFrame
{
    Q_OBJECT
public:
    explicit SearchNonePage(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent * event);

private:
    void checkPos();

signals:

public slots:
    void onChangeColor();

private:
    DLabel *m_Text;
};

#endif // SEARCHNONEPAGE_H
