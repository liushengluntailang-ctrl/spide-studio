#pragma once
#include <QPlainTextEdit>
#include <QWidget>

namespace Spide::Modules::Panels {

class OutputPanel : public QWidget {
    Q_OBJECT
public:
    explicit OutputPanel(QWidget* parent = nullptr);
    void appendLog(const QString& message);
    void clearLog();
private:
    QPlainTextEdit* m_logArea;
};

} // namespace Spide::Modules::Panels
