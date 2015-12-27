#include <QDir>

#include "albumimagefinder.h"

#include <QDebug>

AlbumImageFinder::AlbumImageFinder(QObject *parent) :
    QObject(parent)
{
    m_suffixList << "jpg";
    //Link the analysis next item.
    connect(this, &AlbumImageFinder::requireAnalysisNext,
            this, &AlbumImageFinder::analysisNext,
            Qt::QueuedConnection);
}

void AlbumImageFinder::analysisPaths(QStringList paths)
{
    //Append the urls to the waiting list.
    m_queue.append(paths);
    //Check the queue, if the queue is not empty then ask to analysis one.
    if(!m_queue.isEmpty())
    {
        //Ask to anlaysis next file.
        emit requireAnalysisNext();
    }
}

void AlbumImageFinder::analysisNext()
{
    //Check the queue first.
    if(m_queue.isEmpty())
    {
        return;
    }
    //Get the first path in the queue, use QFileInfo to parse it.
    QFileInfo typeChecker(m_queue.takeFirst());
    //Check whether it's a dir.
    if(typeChecker.isDir())
    {
        analysisFolder(typeChecker);
    }
    else if(typeChecker.isFile())
    {
        analysisFile(typeChecker);
    }
    //Emit the parse next signal.
    emit requireAnalysisNext();
}

void AlbumImageFinder::analysisFolder(QFileInfo folderInfo)
{
    //Get the entry file info under the folder.
    QFileInfoList contents=QDir(folderInfo.absoluteFilePath()).entryInfoList();
    //Check all the items of the folder.
    for(auto i=contents.constBegin(); i!=contents.constEnd(); ++i)
    {
        //Get the file name.
        QString fileName=(*i).fileName();
        //Ignore the dot and dotdot.
        if(fileName=="." || fileName=="..")
        {
            continue;
        }
        //Check the current item.
        if((*i).isFile())
        {
            analysisFile(*i);
        }
        else if((*i).isDir())
        {
            //If it's a directory, prepend it to the analysis queue.
            m_queue.prepend((*i).absoluteFilePath());
        }
    }
}

inline void AlbumImageFinder::analysisFile(const QFileInfo &fileInfo)
{
    //Check whether the suffix is in the suffix list.
    if(m_suffixList.contains(fileInfo.suffix().toLower()))
    {
        //If we can find the suffix, emit the find out signal.
        emit findFile(fileInfo.absoluteFilePath());
    }
}
