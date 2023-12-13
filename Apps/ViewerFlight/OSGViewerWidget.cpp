#include "OSGViewerWidget.h"
#include <osg/Group>
#include <osg/BlendFunc>
#include <osgGA/MultiTouchTrackballManipulator>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
OSGViewerWidget::OSGViewerWidget(QWidget* parent) {
    connect(this, &osgQOpenGLWidget::initialized, this, &OSGViewerWidget::init);
}

OSGViewerWidget::~OSGViewerWidget() {}

void OSGViewerWidget::init()
{
    m_root                   = new osg::Group;
    auto            stateSet = m_root->getOrCreateStateSet();
    osg::BlendFunc* blend    = new osg::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    stateSet->setAttributeAndModes(blend, osg::StateAttribute::ON);
    m_root->addChild(osgDB::readNodeFile("D:/data/viewerFlightData/AutoRes/Data/Tile_+048/Tile_+048_14_0.osgb"));
    // m_root->addChild(osgDB::readNodeFile("D:/data/ply/test1.ply"));

    m_cameraManipulator      = new osgGA::MultiTouchTrackballManipulator();
    auto standardManipulator = (osgGA::StandardManipulator*)m_cameraManipulator.get();
    standardManipulator->setAllowThrow(false);
    getOsgViewer()->setCameraManipulator(m_cameraManipulator);
    getOsgViewer()->setSceneData(m_root);

    osg::Camera* camera = getOsgViewer()->getCamera();
    camera->setClearColor(
        osg::Vec4(0.9529411764705882, 0.9529411764705882, 0.9529411764705882, 1.0));
}
