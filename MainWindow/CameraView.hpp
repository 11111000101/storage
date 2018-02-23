#ifndef CAMERAVIEW_HPP
#define CAMERAVIEW_HPP

#include <QWidget>
#include <QList>
#include <QCameraInfo>
#include <QGraphicsView>

class QCameraViewfinder;
class QCameraImageCapture;
class QPushButton;
class QCamera;

class CameraView : public QWidget
{
    Q_OBJECT
public:
    CameraView();
    ~CameraView();
    void showCamera();

public slots:
    void nextCamera();

private:
    QList<QCameraInfo> m_cameras;
    int m_currentCameraIndex;
    QCameraViewfinder* m_viewFinder;
    QPushButton* m_nextCamBtn;
    QCamera* m_currentCamera = nullptr;
    QCameraImageCapture* m_imageCapture;
};

#endif // CAMERAVIEW_HPP
