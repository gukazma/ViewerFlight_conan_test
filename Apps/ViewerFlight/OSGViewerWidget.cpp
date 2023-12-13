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
    setMouseTracking(true);
    connect(this, &osgQOpenGLWidget::initialized, this, &OSGViewerWidget::init);
}

OSGViewerWidget::~OSGViewerWidget() {}

void OSGViewerWidget::init()
{
    auto m_mainpulator = new osgEarth::Util::EarthManipulator;
    getOsgViewer()->setCameraManipulator(m_mainpulator);
    

    // load an earth file, and support all or our example command-line options
    auto node       = osgDB::readRefNodeFile("D:/softwares/ViewerFlight/Resources/earthfile/china-simple.earth");
    m_root     = new osg::Group();
    auto mapNode    = osgEarth::MapNode::findMapNode(node);
    auto map        = mapNode->getMap();

    osgEarth::SkyOptions skyOptions;   // ��ջ���ѡ��
    skyOptions.ambient() = 1;          // ��������ˮƽ(0~1)
    auto skyNode =
        osgEarth::SkyNode::create(skyOptions);   // ���������ṩ��ա���������������Ч������
    skyNode->setDateTime(
        osgEarth::DateTime(2021, 4, 15, 12 - 8));   // ���û���������/ʱ�䡣(�������Σ�ʱ��8Сʱ)
    skyNode->setEphemeris(new osgEarth::Util::Ephemeris);   // ���ڸ�������/ʱ�䶨λ̫��������������
    skyNode->setLighting(true);                             // ����Ƿ�������������ͼ
    skyNode->addChild(mapNode);                             // ��ӵ�ͼ�ڵ�
    skyNode->attach(getOsgViewer());   // ������սڵ㸽�ŵ���ͼ��������⣩
    m_root->addChild(skyNode);
    m_root->addChild(node);
    getOsgViewer()->setSceneData(m_root);

    // initialize a viewer:
    auto viewer = getOsgViewer();
    viewer->getCamera()->addCullCallback(new osgEarth::Util::AutoClipPlaneCullCallback(mapNode));

    osgEarth::Util::Controls::LabelControl* PositionLabel =
        new osgEarth::Util::Controls::LabelControl("", osg::Vec4(1.0, 1.0, 1.0, 1.0));
    
    m_root->addChild(osgEarth::Util::Controls::ControlCanvas::get(viewer));
    osgEarth::Util::Controls::ControlCanvas* canvas =
        osgEarth::Util::Controls::ControlCanvas::get(viewer);
    canvas->addControl(PositionLabel);
}
