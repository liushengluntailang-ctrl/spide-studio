#pragma once
#include <QButtonGroup>
#include <QWidget>

namespace Spide::UI {

class ActivityBar : public QWidget {
    Q_OBJECT
public:
    explicit ActivityBar(QWidget* parent = nullptr);

signals:
    void activityChanged(int id);

private:
    QButtonGroup* m_group;
};

} // namespace Spide::UI
