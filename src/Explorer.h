#pragma once

#include <QFileSystemModel>
#include <QWidget>

class QTreeView;

class Explorer : public QWidget
{
    Q_OBJECT
public:
    explicit Explorer(QWidget *parent = nullptr);
    void setRootPath(const QString &path);
    QString rootPath() const;
signals:
    void fileActivated(const QString &path);
public slots:
    void openFolder();
    void createFile();
    void createFolder();
    void deleteSelected();
    void renameSelected();
private:
    QString selectedPath() const;
    QFileSystemModel *model;
    QTreeView *tree;
    QString projectPath;
};