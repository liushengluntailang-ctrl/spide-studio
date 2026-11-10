#include "BottomPanel.h"
#include "modules/panels/PlaceholderPanel.h"

namespace Spide::UI {

BottomPanel::BottomPanel(QWidget* parent) : QTabWidget(parent) {
    setTabPosition(North);
    m_terminal = new Modules::Terminal::TerminalWidget(this);
    addTab(m_terminal, tr("Terminal"));

    addTab(new Modules::Panels::PlaceholderPanel(
        tr("Problems"), tr("Diagnostics & linting will connect to LSP in Phase 3."), this), tr("Problems"));

    m_outputPanel = new Modules::Panels::OutputPanel(this);
    addTab(m_outputPanel, tr("Output"));

    addTab(new Modules::Panels::PlaceholderPanel(
        tr("Debug Console"), tr("Debug console will connect to DAP in Phase 5."), this), tr("Debug Console"));
}

} // namespace Spide::UI
