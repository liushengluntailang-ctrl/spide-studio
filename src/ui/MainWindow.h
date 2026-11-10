#pragma once
#include "ActivityBar.h"
#include "BottomPanel.h"
#include "Sidebar.h"
#include "StatusBar.h"
#include "core/CommandManager.h"
#include "modules/editor/EditorManager.h"
#include <QMainWindow>
#include <QSplitter>

namespace Spide::UI {

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onOpenFolder();
    void onOpenFile();
    void toggleSidebar();
    void toggleBottomPanel();

private:
    void setupUi();
    void setupCommands();
    void setupMenus();

    Core::CommandManager* m_commands;
    ActivityBar* m_activityBar;
    Sidebar* m_sidebar;
    Modules::Editor::EditorManager* m_editorManager;
    BottomPanel* m_bottomPanel;
    StatusBar* m_statusBar;
    QSplitter* m_mainSplitter;
    QSplitter* m_centerSplitter;
    int m_lastSidebarId = 0;
};

} // namespace Spide::UI
