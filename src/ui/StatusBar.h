#pragma once
#include <QLabel>
#include <QStatusBar>

namespace Spide::UI {

class StatusBar : public QStatusBar {
    Q_OBJECT
public:
    explicit StatusBar(QWidget* parent = nullptr);
    void setCursorPosition(int line, int col);
    void setEncoding(const QString& encoding);

private:
    QLabel* m_cursorLabel;
    QLabel* m_encodingLabel;
};

} // namespace Spide::UI
