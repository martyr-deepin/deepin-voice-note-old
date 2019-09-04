#include "databaseoper.h"
#include "noteoper.h"

NoteOper::NoteOper()
{

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

bool NoteOper::addNote(NOTE noteInfo)
{
    QStringList columnName = {"note_type", "content_text", "content_path", "voice_time", "voice_sample_data", "folder_id", "create_time"};
    QList<QVariant> values;
    values.append(noteInfo.noteType);
    values.append(noteInfo.contentText);
    values.append(noteInfo.contentPath);
    values.append(noteInfo.voiceTime);
    values.append(noteInfo.voiceSampleData);
    values.append(noteInfo.folderId);
    values.append(noteInfo.createTime);
    return DatabaseOper::getInstance()->insertData(TABLE_NOTE, columnName, values);

}

bool NoteOper::updateNote(NOTE noteInfo)
{
    QString updateSql = "update %1 set content_text = :content, content_path = :contentPath where id = :id";
    QString queryStrFinal = QString(updateSql).arg(TABLE_NOTE);
    QMap<QString, QVariant> valuesMap;
    valuesMap[":content"] = noteInfo.contentText;
    valuesMap[":contentPath"] = noteInfo.contentPath;
    valuesMap[":id"] = noteInfo.id;
    return DatabaseOper::getInstance()->updateData(queryStrFinal, valuesMap);

}

bool NoteOper::deleteNote(int id)
{
    return DatabaseOper::getInstance()->deleteDataById(TABLE_NOTE, "id", id);
}
