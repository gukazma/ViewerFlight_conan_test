#include "OSGViewerWidget.h"
#include <osg/Camera>
#include <osg/Image>
#include <osg/ComputeBoundsVisitor>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgEarth/AutoClipPlaneHandler>
#include <osgEarth/AutoScaleCallback>
#include <osgEarth/EarthManipulator>
#include <osgEarth/ExampleResources>
#include <osgEarth/GeoData>
#include <osgEarth/GeoTransform>
#include <osgEarth/ModelLayer>
#include <osgEarth/Registry>
#include <osgEarth/Sky>
#include <osgEarth/SpatialReference>
#include <osgViewer/Viewer>
#include <osg/BlendFunc>
#include <osgGA/MultiTouchTrackballManipulator>
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

    osg::ref_ptr<osgEarth::Map> map = new osgEarth::Map();
    osg::ref_ptr<osgEarth::MapNode> mapNode = new osgEarth::MapNode(map);
    m_root->addChild(mapNode);

    m_cameraManipulator      = new osgGA::MultiTouchTrackballManipulator();
    auto standardManipulator = (osgGA::StandardManipulator*)m_cameraManipulator.get();
    standardManipulator->setAllowThrow(false);
    getOsgViewer()->setCameraManipulator(m_cameraManipulator);
    getOsgViewer()->setSceneData(m_root);

    osg::Camera* camera = getOsgViewer()->getCamera();
    camera->setClearColor(
        osg::Vec4(0.9529411764705882, 0.9529411764705882, 0.9529411764705882, 1.0));


    //// initialize a viewer:
    //auto viewer = getOsgViewer();
    //viewer->getCamera()->addCullCallback(new osgEarth::Util::AutoClipPlaneCullCallback(mapNode));

    //osgEarth::Util::Controls::LabelControl* PositionLabel =
    //    new osgEarth::Util::Controls::LabelControl("", osg::Vec4(1.0, 1.0, 1.0, 1.0));

    //m_root->addChild(osgEarth::Util::Controls::ControlCanvas::get(viewer));
    //osgEarth::Util::Controls::ControlCanvas* canvas =
    //    osgEarth::Util::Controls::ControlCanvas::get(viewer);
    //canvas->addControl(PositionLabel);
}
