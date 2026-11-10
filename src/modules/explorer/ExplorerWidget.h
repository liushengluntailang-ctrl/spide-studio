#pragma once
#include <QFileSystemModel>
#include <QTreeView>
#include <QWidget>
#include <QContextMenuEvent>

namespace Spide::Modules::Explorer {

class ExplorerWidget : public QWidget {
    Q_OBJECT
public:
    explicit ExplorerWidget(QWidget* parent = nullptr);
    void setRootPath(const QString& path);
    QString currentRootPath() const { return m_rootPath; }

signals:
    void fileSelected(const QString& filePath);

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;

private slots:
    void onItemDoubleClicked(const QModelIndex& index);
    void createNewFile();
    void createNewFolder();
    void renameSelectedItem();
    void deleteSelectedItem();

private:
    QString getSelectedPath() const;
    QTreeView* m_treeView;
    QFileSystemModel* m_fileModel;
    QString m_rootPath;
};

} // namespace Spide::Modules::Explorer
