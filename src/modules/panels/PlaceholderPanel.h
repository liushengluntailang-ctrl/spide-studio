#pragma once
#include <QWidget>

namespace Spide::Modules::Panels {

class PlaceholderPanel : public QWidget {
    Q_OBJECT
public:
    explicit PlaceholderPanel(const QString& title, const QString& statusText, QWidget* parent = nullptr);
};

} // namespace Spide::Modules::Panels
