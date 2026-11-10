#include "Sidebar.h"
#include "modules/panels/PlaceholderPanel.h"
#include <QVBoxLayout>

namespace Spide::UI {

Sidebar::Sidebar(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_headerLabel = new QLabel(tr("EXPLORER"), this);
    m_headerLabel->setObjectName("SidebarHeader");
    layout->addWidget(m_headerLabel);

    m_stack = new QStackedWidget(this);
    m_explorer = new Modules::Explorer::ExplorerWidget(this);
    m_stack->addWidget(m_explorer);

    m_stack->addWidget(new Modules::Panels::PlaceholderPanel(
        tr("Search"), tr("Workspace search engine scheduled for Phase 3."), this));
    m_stack->addWidget(new Modules::Panels::PlaceholderPanel(
        tr("Source Control"), tr("Git VCS module scheduled for Phase 4."), this));
    m_stack->addWidget(new Modules::Panels::PlaceholderPanel(
        tr("Run & Debug"), tr("DAP Debugger module scheduled for Phase 5."), this));

    layout->addWidget(m_stack);
}

void Sidebar::setCurrentIndex(int index) {
    if (index >= 0 && index < m_stack->count()) {
        m_stack->setCurrentIndex(index);
        static const QString headers[] = {
            tr("EXPLORER"),
            tr("SEARCH"),
            tr("SOURCE CONTROL"),
            tr("RUN & DEBUG")
        };
        m_headerLabel->setText(headers[index]);
    }
}

} // namespace Spide::UI
