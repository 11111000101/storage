#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>

#include "Data/datamodel.h"

class IMainWindowView;
class IMainWindowModel;
class MainWindowPresenter;
class AddItemPresenter;
class CameraView;

namespace Ui {
class MainWindow;
}

class QWidget;

class Application : public QMainWindow
{
    Q_OBJECT
public:
    explicit Application(QWidget* parent = 0);
    ~Application();

public slots:
    void showAddItemView();
    void showMainView();

    void setPushButtonLabel(const QString& label);

private slots:
    void onPushButtonClicked();
    void onMainBtnClicked();
    void showTakePhoto();

private:
    void setNewLayout();

    Ui::MainWindow* ui;

    DataModel m_dataModel;
    MainWindowPresenter* m_presenter;
    AddItemPresenter* m_addItemPresenter = nullptr;
    CameraView* m_cameraView;

    enum CurrentState {
        StateMain,
        StateAddItemView,
        StateTakePhoto
    };

    CurrentState state = CurrentState::StateMain;
};

#endif // APPLICATION_H
