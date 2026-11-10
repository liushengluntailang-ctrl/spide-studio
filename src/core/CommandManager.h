#pragma once
#include <QAction>
#include <QKeySequence>
#include <QObject>
#include <functional>
#include <unordered_map>

namespace Spide::Core {

class CommandManager : public QObject {
    Q_OBJECT
public:
    explicit CommandManager(QObject* parent = nullptr);
    QAction* registerCommand(const QString& id, const QString& title, const QKeySequence& shortcut, std::function<void()> handler);
    QAction* getAction(const QString& id) const;
    void executeCommand(const QString& id);
private:
    std::unordered_map<QString, QAction*> m_commands;
};

} // namespace Spide::Core
