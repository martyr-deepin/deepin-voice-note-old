#ifndef RENAMEEDIT_H
#define RENAMEEDIT_H

#include <DLineEdit>

DWIDGET_USE_NAMESPACE

class RenameEdit : public DLineEdit
{
    Q_OBJECT
public:
    explicit RenameEdit(QWidget *parent = nullptr);
    void setToEdited(bool flag);
    void tryToFouceout();

signals:

public slots:

protected:
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);

private:
    bool m_isEdited;
    bool m_mouseIsIn;
};

#endif // RENAMEEDIT_H
