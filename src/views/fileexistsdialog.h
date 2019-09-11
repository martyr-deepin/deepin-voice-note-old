#ifndef FILEEXISTSDIALOG_H
#define FILEEXISTSDIALOG_H

#include <DDialog>
#include <consts.h>
#include <QObject>

DWIDGET_USE_NAMESPACE

class FileExistsDialog : public QObject
{
    Q_OBJECT
public:
    FileExistsDialog();
    ~FileExistsDialog();

    DDialog *m_dialog;
    void setNote(NOTE note);
    void setSavePath(QString saveFilePath);
    void show();
    void hide();
signals:
    void saveFileEnd(bool result);

public slots:
    void handleDialogClicked(int index, const QString &text);

private:
    void initUI();
    void initConnetion();
    NOTE m_note;
    QString m_filePath;

};

#endif // FILEEXISTSDIALOG_H
