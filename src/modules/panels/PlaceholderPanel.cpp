#include "PlaceholderPanel.h"
#include <QLabel>
#include <QVBoxLayout>

namespace Spide::Modules::Panels {

PlaceholderPanel::PlaceholderPanel(const QString& title, const QString& statusText, QWidget* parent)
    : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    auto* titleLabel = new QLabel(QString("<h3>%1</h3>").arg(title), this);
    titleLabel->setAlignment(Qt::AlignCenter);

    auto* descLabel = new QLabel(statusText, this);
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setStyleSheet("color: #777777;");

    layout->addWidget(titleLabel);
    layout->addWidget(descLabel);
}

} // namespace Spide::Modules::Panels
