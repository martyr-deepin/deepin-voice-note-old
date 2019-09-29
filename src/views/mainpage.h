#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include "dfmsplitter.h"
#include "leftfolderlist.h"
#include "rightview.h"
#include "leftview.h"
#include <DMainWindow>
#include <QFrame>
#include <QObject>
#define DEFAULT_WINDOWS_WIDTH 820
#define DEFAULT_WINDOWS_HEIGHT 634


DWIDGET_USE_NAMESPACE

//第一层Page
class MainPage : public QWidget
{
    Q_OBJECT
public:
    MainPage();
    ~MainPage();

public:
    void updateNoteList();
    void searchFolder(QString searchKey);

signals:
    void textEditClicked(NOTE textNote);

private:
     DFMSplitter *m_splitter;
     LeftView *m_leftView;

     RightView *m_rightView;

    void initUI();

    void initConnection();

    void initTitleBar();

    void initSplitter();

    void initLeftView();

    void initRightView();

    //void initCentralWidget();
};

#endif // MAINPAGE_H
