#include "databaseoper.h"
#include "noteoper.h"
#include "uiutil.h"
#include <QFileInfo>

NoteOper::NoteOper()
{

}

void NoteOper::checkCleanDataBaseForVoiceByForderId(int folderId)
{
    QString queryStr = "select id, note_type, content_text, content_path, voice_time, voice_sample_data, folder_id, create_time from %1 where folder_id = %2 order by create_time asc";
    QString queryStrFinal = QString(queryStr).arg(TABLE_NOTE).arg(folderId);

    QList<QList<QVariant>> result;
    if (DatabaseOper::getInstance()->queryData(queryStrFinal, 8, result))
    {
        for (int i = 0; i < result.size(); i++)
        {
            QList<QVariant> tmp = result.at(i);
            NOTE noteInfoTmp;
            noteInfoTmp.id = tmp.at(0).toInt();
            noteInfoTmp.noteType = NOTE_TYPE(tmp.at(1).toInt());
            if(VOICE == noteInfoTmp.noteType)
            {
                noteInfoTmp.contentPath = tmp.at(3).toString();
                QString filepath = UiUtil::getRecordingVoiceFullPath(noteInfoTmp.contentPath);

                QFileInfo fileInfo(filepath);
                if(!fileInfo.isFile())
                {
                    DatabaseOper::getInstance()->deleteDataById(TABLE_NOTE, "id", noteInfoTmp.id);
                }
            }
        }
    }
}

QList<NOTE> NoteOper::getNoteListByFolderId(int folderId)
{
    QString queryStr = "select id, note_type, content_text, content_path, voice_time, voice_sample_data, folder_id, create_time from %1 where folder_id = %2 order by create_time asc";
    QString queryStrFinal = QString(queryStr).arg(TABLE_NOTE).arg(folderId);

    QList<QList<QVariant>> result;
    QList<NOTE> noteInfo;
    if (DatabaseOper::getInstance()->queryData(queryStrFinal, 8, result))
    {
        for (int i = 0; i < result.size(); i++)
        {
            QList<QVariant> tmp = result.at(i);
            NOTE noteInfoTmp;
            noteInfoTmp.id = tmp.at(0).toInt();
            noteInfoTmp.noteType = NOTE_TYPE(tmp.at(1).toInt());
            noteInfoTmp.contentText = tmp.at(2).toString();
            noteInfoTmp.contentPath = tmp.at(3).toString();
            noteInfoTmp.voiceTime = tmp.at(4).toInt();
            noteInfoTmp.voiceSampleData = tmp.at(5).toString();
            noteInfoTmp.folderId = tmp.at(6).toInt();
            noteInfoTmp.createTime = tmp.at(7).toDateTime();
            noteInfo.append(noteInfoTmp);

        }

    }
    return noteInfo;

}

QList<NOTE> NoteOper::searchNote(int folderId, QString searchKey)
{
    QString queryStr = "select id, note_type, content_text, content_path, voice_time, voice_sample_data, folder_id, create_time from %1 where folder_id = %2 and content_text like \'\%%3\%\' order by create_time asc";
    QString queryStrFinal = QString(queryStr).arg(TABLE_NOTE).arg(folderId).arg(searchKey);

    QList<QList<QVariant>> result;
    QList<NOTE> noteInfo;
    if (DatabaseOper::getInstance()->queryData(queryStrFinal, 8, result))
    {
        for (int i = 0; i < result.size(); i++)
        {
            QList<QVariant> tmp = result.at(i);
            NOTE noteInfoTmp;
            noteInfoTmp.id = tmp.at(0).toInt();
            noteInfoTmp.noteType = NOTE_TYPE(tmp.at(1).toInt());
            noteInfoTmp.contentText = tmp.at(2).toString();
            noteInfoTmp.contentPath = tmp.at(3).toString();
            noteInfoTmp.voiceTime = tmp.at(4).toInt();
            noteInfoTmp.voiceSampleData = tmp.at(5).toString();
            noteInfoTmp.folderId = tmp.at(6).toInt();
            noteInfoTmp.createTime = tmp.at(7).toDateTime();
            noteInfo.append(noteInfoTmp);

        }

    }
    return noteInfo;

}
QString NoteOper::getConttextByNoteID(int folderId, int noteId, QDateTime *time)//liuyang 3547
//QString NoteOper::getConttextByNoteID(int folderId, int noteId)
{
    QString queryStr = "select id, note_type, content_text, content_path, voice_time, voice_sample_data, folder_id, create_time from %1 where folder_id = %2 order by create_time asc";
    QString queryStrFinal = QString(queryStr).arg(TABLE_NOTE).arg(folderId);

    QList<QList<QVariant>> result;
    QList<NOTE> noteInfo;
    QString text;
    if (DatabaseOper::getInstance()->queryData(queryStrFinal, 8, result))
    {
        for (int i = 0; i < result.size(); i++)
        {
            QList<QVariant> tmp = result.at(i);
            NOTE noteInfoTmp;
            noteInfoTmp.id = tmp.at(0).toInt();
            if(noteId == noteInfoTmp.id)
            {
                noteInfoTmp.contentText = tmp.at(2).toString();
                text = noteInfoTmp.contentText;
                //liuyang 3547
                if(time != nullptr)
                {
                    *time = tmp.at(7).toDateTime();
                }
                //liuyang 3547
                break;
            }
        }

    }
    return text;
}

bool NoteOper::addNote(NOTE &noteInfo)
{
    bool ret = false;
    QStringList columnName = {"note_type", "content_text", "content_path", "voice_time", "voice_sample_data", "folder_id", "create_time"};
    QList<QVariant> values;
    values.append(noteInfo.noteType);
    values.append(noteInfo.contentText);
    values.append(noteInfo.contentPath);
    values.append(noteInfo.voiceTime);
    values.append(noteInfo.voiceSampleData);
    values.append(noteInfo.folderId);
    values.append(noteInfo.createTime);
    //return DatabaseOper::getInstance()->insertData(TABLE_NOTE, columnName, values);
    if (DatabaseOper::getInstance()->insertData(TABLE_NOTE, columnName, values))
    {
        QString queryStr = "select id, note_type, content_text, content_path, voice_time, voice_sample_data, folder_id, create_time from %1 where folder_id = %2 order by create_time asc";
        QString queryStrFinal = QString(queryStr).arg(TABLE_NOTE).arg(noteInfo.folderId);

        QList<QVariant> result;
        if (DatabaseOper::getInstance()->queryLastData(queryStrFinal, 8, result))
        {
            noteInfo.id = result.at(0).toInt();
            ret = true;
        }
    }
    return ret;
}

bool NoteOper::updateNote(const NOTE &noteInfo)
{
    //QString updateSql = "update %1 set content_text = :content, content_path = :contentPath where id = :id";
    QString updateSql = "update %1 set content_text = :content, content_path = :contentPath, create_time = :createTime where id = :id";
    QString queryStrFinal = QString(updateSql).arg(TABLE_NOTE);
    QMap<QString, QVariant> valuesMap;
    valuesMap[":content"] = noteInfo.contentText;
    valuesMap[":contentPath"] = noteInfo.contentPath;
    valuesMap[":createTime"] = noteInfo.createTime;
    valuesMap[":id"] = noteInfo.id;
    return DatabaseOper::getInstance()->updateData(queryStrFinal, valuesMap);

}

bool NoteOper::deleteNote(NOTE noteInfo)
{
    if(VOICE == noteInfo.noteType)
    {
        QString filepath = UiUtil::getRecordingVoiceFullPath(noteInfo.contentPath);

        QFileInfo fileInfo(filepath);
        if(fileInfo.isFile())
        {
            QFile file(filepath);
            file.remove();
        }
    }
//    //====add start 20191105  bug2162  bug2963
//    else
//    {
//        if (!UiUtil::autoDeleteTxt(noteInfo))
//        {
//            //qDebug() << "error: delete file error";
//            UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("error: delete file error"), QString("error: delete file error"));
//        }
//    }
//    //====add end 20191105  bug2162  bug2963
    return DatabaseOper::getInstance()->deleteDataById(TABLE_NOTE, "id", noteInfo.id);
}
