#include "CameraView.hpp"

#include <QDebug>
#include <QCamera>
#include <QGridLayout>
#include <QGraphicsView>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QPushButton>

CameraView::CameraView()
{
    m_cameras = QCameraInfo::availableCameras();
    m_viewFinder = new QCameraViewfinder();
    m_nextCamBtn = new QPushButton("next cam");

    QGridLayout* l = new QGridLayout();
    this->setLayout(l);
    l->addWidget(m_nextCamBtn);
    l->addWidget(m_viewFinder);


    foreach (const QCameraInfo &cameraInfo, m_cameras) {
        qDebug() << "------------------- camera --------------------";
        qDebug() << cameraInfo.deviceName();
        qDebug() << cameraInfo.description();
    }

    this->m_currentCameraIndex = m_cameras.length() > 0 ? 0 : -1;

    QObject::connect(m_nextCamBtn, SIGNAL(clicked(bool)),
                     this, SLOT(nextCamera()));

    showCamera();
}

CameraView::~CameraView() {
//    delete m_currentCamera;
}

void CameraView::nextCamera() {
    if (m_cameras.length() > 0) {
        m_currentCameraIndex = (m_currentCameraIndex + 1) % m_cameras.length();
        showCamera();
    }
}

void CameraView::showCamera() {
    delete m_currentCamera;
    m_currentCamera = new QCamera(m_cameras.at(m_currentCameraIndex));
    m_currentCamera->setViewfinder(m_viewFinder);
    m_viewFinder->show();

    m_imageCapture = new QCameraImageCapture(m_currentCamera);
    m_currentCamera->setCaptureMode(QCamera::CaptureStillImage);
    m_currentCamera->start(); // to start the viewfinder
}
