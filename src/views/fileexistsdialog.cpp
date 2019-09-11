#include "fileexistsdialog.h"

#include <uiutil.h>
#include <QFile>

FileExistsDialog::FileExistsDialog()
{
    initUI();
    initConnetion();
}

FileExistsDialog::~FileExistsDialog()
{

}

void FileExistsDialog::initUI()
{
    m_dialog = UiUtil::createChooseDialog(QString(""), QString(tr("文件名已存在，是否覆盖？")), nullptr, QString(tr("否")), QString(tr("是")));
    m_dialog->hide();
}

void FileExistsDialog::initConnetion()
{
    QObject::connect(m_dialog, &DDialog::buttonClicked, this, &FileExistsDialog::handleDialogClicked);
}

void FileExistsDialog::handleDialogClicked(int index, const QString &text)
{
    if (index == 1)
    {
        bool result = false;
        if ((TEXT == m_note.noteType) && (!m_filePath.isEmpty()))
        {
            QFile::remove(m_filePath);
            result = UiUtil::saveTxt(m_filePath, m_note.contentText);
        }
        else if (VOICE == m_note.noteType)
        {

        }
        emit saveFileEnd(result);
    }
}

void FileExistsDialog::setNote(NOTE note)
{
    m_note = note;
}
void FileExistsDialog::setSavePath(QString saveFilePath)
{
    m_filePath = saveFilePath;
}
void FileExistsDialog::show()
{
    m_dialog->show();
}
void FileExistsDialog::hide()
{
    m_dialog->hide();
}
