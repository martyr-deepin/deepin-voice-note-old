#ifndef DATABASEOPER_H
#define DATABASEOPER_H

#include <QSqlDatabase>
#include <QStringList>
#include <QSqlQuery>
#include <QDebug>
#include "consts.h"


class DatabaseOper
{
public:
    DatabaseOper();
    ~DatabaseOper();

    static DatabaseOper *getInstance();

    bool insertData(QString tableName, QStringList columnName, QList<QVariant> values);
    bool updateData(QString updateSql, QMap<QString, QVariant> valuesMap);
    bool queryData(QString queryStr, int resultItemSize, QList<QList<QVariant>> & result);
    bool deleteDataById(QString tableName, QString id, int idValue);


private:
    static DatabaseOper *instance;
    QSqlDatabase sqlDatabase;
    QSqlQuery sqlQuery;
    bool initFlag = false;
    const QStringList TABLE_NAME = {TABLE_FOLDER};
    QMap<QString, QString> createSqlMap;

    void initDatabase();
    void checkTableExist();
    void createTable(QString createSql);



};



#endif // DATABASEOPER_H
