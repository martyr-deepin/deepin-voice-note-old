#ifndef AISERVICECONTROLLER_H
#define AISERVICECONTROLLER_H
#include <QObject>
#include <com_iflytek_aiservice_session.h>
#include <com_iflytek_aiservice_asr.h>

//转写状态及结果
class AsrResult
{
public:
    QString             code;
    QString             descInfo;
    QString             failType;
    QString             status;
    QString             txt;
    QString             ErrorMsg;
};

class AiServiceController:public QObject
{
    Q_OBJECT
public:
    AiServiceController();
    virtual ~AiServiceController();
    //转写开始
    //filePath:必填，待转写文件路径，时长最大为5小时，5分钟以上效果最佳
    //fileDuration: 必填,音频真实时长，单位是毫秒 服务端将针对用户上传的duration和服务端转码后的音频时长进行对比，如果偏差在10秒内（含10秒），则视为合法。
    //srcLanguage: 选填，用于上传的语种识别，仅可填入en、cn中的某一个值。en：英文，cn：中文，默认cn
    //targetLanguage: 选填，如果该字段不为空，代表客户需要使用转写+翻译的功能；字段值支持cn：中文，en：英文；该字段需要和 language 字段配套使用。language代表源语言，targetLanguage代表翻译后的语言。例如：language=cn，targetLanguage=en，表示中翻英。
    QString startAsr(QString filePath,int fileDuration,QString srcLanguage, QString targetLanguage);
    //停止转写，如果转写尚未结束，调用此接口会自动停止转写，如果转写已经完成，调用此结果则不会做任何动作
    void stopAsr();
signals:
     void AsrResultReq(class AsrResult result);
public slots:
    //转写状态及结果回调
    void notifySlot(const QString &msg);
private:
    //创建会话
    QString createSession(QString ability);
    //释放会话
    void freeSession(QString ability);
    //转写json解析
    void asrJsonParse(const QString &msg, class AsrResult &result);
    //错误码对应ErrMsg
    void ErrorCodeToMsg(const class AsrResult &clsResult, QString &ErrorMsg);
private:
    com::iflytek::aiservice::session *m_session;  //会话
    com::iflytek::aiservice::asr *m_asrInterface; //转写
    QString ability;
    QString m_status;

};

#endif // AISERVICECONTROLLER_H
