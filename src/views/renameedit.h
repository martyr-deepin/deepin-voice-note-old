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
    void sigCancelRename();

public slots:

protected:
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
    void keyPressEvent(QKeyEvent *event);
    //void paintEvent(QPaintEvent *event);
private:
    bool m_isEdited;
    bool m_mouseIsIn;
};

#endif // RENAMEEDIT_H
