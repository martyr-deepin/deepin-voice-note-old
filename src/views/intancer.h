#ifndef INTANCER_H
#define INTANCER_H

#include <QObject>

class Intancer : public QObject
{
    Q_OBJECT
public:
    explicit Intancer(QObject *parent = nullptr);
    ~Intancer();
    static Intancer* get_Intancer(){
        if(instance_ == nullptr){
          instance_ = new Intancer();
        }
        return instance_;
    }
    static void destroyIntance(){
        if(nullptr != instance_)
        {
            delete instance_;
        }
    }    

    void initHeightForRight();
    void clearHeightForRightList();
    void addHeightForRightList(int addheight);
    void delHeightForRightList(int delheight);
    void setViewHeightForRightList(int viewHeight);

    void setTryToDelEmptyTextNote(bool value);
    bool getTryToDelEmptyTextNote();
    void setRecodingFlag(bool value);
    bool getRecodingFlag();
    void setRenameRepeatFlag(bool value);
    bool getRenameRepeatFlag();
    bool setViewAddTextButtonShowFlag(bool value);
    bool getViewAddTextButtonShowFlag();

signals:
    void sigShowViewAddTextButton();
    void sigHideViewAddTextButton();

private:
     static Intancer *instance_;
     bool tryToDelEmptyTextNote;
     bool recording;
     bool isRenameRepeat;
     bool isViewAddTextButtonShow;

     int m_RightListHeight;
     int m_RightViewHeight;
};

#endif // INTANCER_H
