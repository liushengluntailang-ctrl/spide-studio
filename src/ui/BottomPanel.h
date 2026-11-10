#pragma once
#include "modules/panels/OutputPanel.h"
#include "modules/terminal/TerminalWidget.h"
#include <QTabWidget>

namespace Spide::UI {

class BottomPanel : public QTabWidget {
    Q_OBJECT
public:
    explicit BottomPanel(QWidget* parent = nullptr);
    Modules::Terminal::TerminalWidget* terminalWidget() const { return m_terminal; }
    Modules::Panels::OutputPanel* outputPanel() const { return m_outputPanel; }

private:
    Modules::Terminal::TerminalWidget* m_terminal;
    Modules::Panels::OutputPanel* m_outputPanel;
};

} // namespace Spide::UI
