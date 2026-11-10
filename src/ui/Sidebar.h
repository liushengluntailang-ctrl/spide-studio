#pragma once
#include "modules/explorer/ExplorerWidget.h"
#include <QLabel>
#include <QStackedWidget>
#include <QWidget>

namespace Spide::UI {

class Sidebar : public QWidget {
    Q_OBJECT
public:
    explicit Sidebar(QWidget* parent = nullptr);
    Modules::Explorer::ExplorerWidget* explorerWidget() const { return m_explorer; }
    void setCurrentIndex(int index);

private:
    QLabel* m_headerLabel;
    QStackedWidget* m_stack;
    Modules::Explorer::ExplorerWidget* m_explorer;
};

} // namespace Spide::UI
