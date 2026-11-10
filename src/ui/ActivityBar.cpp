#include "ActivityBar.h"
#include <QToolButton>
#include <QVBoxLayout>

namespace Spide::UI {

ActivityBar::ActivityBar(QWidget* parent) : QWidget(parent) {
    setObjectName("ActivityBar");
    setFixedWidth(48);

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_group = new QButtonGroup(this);
    m_group->setExclusive(true);

    auto addButton = [this, layout](int id, const QString& text, const QString& tooltip) {
        auto* btn = new QToolButton(this);
        btn->setText(text);
        btn->setToolTip(tooltip);
        btn->setCheckable(true);
        btn->setFixedHeight(48);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        m_group->addButton(btn, id);
        layout->addWidget(btn);
        return btn;
    };

    auto* expBtn = addButton(0, "EXP", tr("Explorer"));
    addButton(1, "SRC", tr("Search (Phase 3)"));
    addButton(2, "GIT", tr("Source Control (Phase 4)"));
    addButton(3, "DBG", tr("Run & Debug (Phase 5)"));

    expBtn->setChecked(true);
    layout->addStretch();

    connect(m_group, &QButtonGroup::idClicked, this, &ActivityBar::activityChanged);
}

} // namespace Spide::UI
