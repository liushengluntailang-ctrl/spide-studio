#include "CommandManager.h"

namespace Spide::Core {

CommandManager::CommandManager(QObject* parent) : QObject(parent) {}

QAction* CommandManager::registerCommand(const QString& id, const QString& title, const QKeySequence& shortcut, std::function<void()> handler) {
    auto* action = new QAction(title, this);
    if (!shortcut.isEmpty()) {
        action->setShortcut(shortcut);
        action->setShortcutContext(Qt::ApplicationShortcut);
    }
    connect(action, &QAction::triggered, this, [handler]() {
        if (handler) handler();
    });
    m_commands[id] = action;
    return action;
}

QAction* CommandManager::getAction(const QString& id) const {
    auto it = m_commands.find(id);
    return (it != m_commands.end()) ? it->second : nullptr;
}

void CommandManager::executeCommand(const QString& id) {
    if (auto* action = getAction(id)) action->trigger();
}

} // namespace Spide::Core
