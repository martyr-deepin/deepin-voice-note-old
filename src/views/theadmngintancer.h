#ifndef THEADMNGINTANCER_H
#define THEADMNGINTANCER_H

#include <QObject>

class TheadMngIntancer : public QObject
{
    Q_OBJECT
public:
    explicit TheadMngIntancer(QObject *parent = nullptr);
    ~TheadMngIntancer();

    static TheadMngIntancer* get_Intancer(){
        if(instance_ == nullptr){
          instance_ = new TheadMngIntancer();
        }
        return instance_;
    }
    static void destroyIntance(){
        if(nullptr != instance_)
        {
            delete instance_;
        }
    }
signals:

public slots:

private:

     static TheadMngIntancer *instance_;
};

#endif // THEADMNGINTANCER_H
