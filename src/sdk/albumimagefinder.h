#ifndef ALBUMIMAGEFINDER_H
#define ALBUMIMAGEFINDER_H

#include <QFileInfo>
#include <QStringList>

#include <QObject>

class AlbumImageFinder : public QObject
{
    Q_OBJECT
public:
    explicit AlbumImageFinder(QObject *parent = 0);

signals:
    /*!
     * \brief This signal is used privately. It's only used for avoid a deep
     * function recursive.
     */
    void requireAnalysisNext();

    /*!
     * \brief When the searcher find out there's a file meets the requirements
     * of the suffix list, this will be emitted.
     * \param filePath The path of the file.
     */
    void findFile(QString filePath);

public slots:
    /*!
     * \brief Analysis several paths. You can add both folder and file path. The
     * file path will be analysis straightly. The folder will find all the file
     * inside recursive.
     * \param paths The path list.
     */
    void analysisPaths(QStringList paths);

private slots:
    void analysisNext();
    void analysisFolder(QFileInfo folderInfo);

private:
    inline void analysisFile(const QFileInfo &fileInfo);
    QStringList m_queue, m_suffixList;
};

#endif // ALBUMIMAGEFINDER_H
