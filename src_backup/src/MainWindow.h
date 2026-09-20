#pragma once

#include <QMainWindow>

class AIChat;
class Editor;
class Explorer;
class SPIDEProvider;
class Terminal;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void openProject();
    void showSettings();
    void updateAIContext();

private:
    void setProjectPath(const QString &path);
    void applySettings();

    Explorer *explorer;
    Editor *editor;
    Terminal *terminal;
    AIChat *aiChat;
    SPIDEProvider *spide;
    QString projectPath;
};
