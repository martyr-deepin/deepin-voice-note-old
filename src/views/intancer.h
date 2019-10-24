#ifndef INTANCER_H
#define INTANCER_H


class Intancer
{
public:
    Intancer();
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
    void setTryToDelEmptyTextNote(bool value);
    bool getTryToDelEmptyTextNote();
    void setRecodingFlag(bool value);
    bool getRecodingFlag();
    void setRenameRepeatFlag(bool value);
    bool getRenameRepeatFlag();
private:
     static Intancer *instance_;
     bool tryToDelEmptyTextNote;
     bool recording;
     bool isRenameRepeat;
};

#endif // INTANCER_H
