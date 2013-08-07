#-------------------------------------------------
#
# Project created by QtCreator 2013-06-27T16:57:34
#
#-------------------------------------------------

QT += core gui opengl
CONFIG += c++11
#QMAKE_CXXFLAGS += -stdlib=libc++
#QMAKE_CXXFLAGS += -mmacosx-version-min=10.7

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = test
TEMPLATE = app

OBJECTIVE_SOURCES += \
Display.mm \
../cocos2d/cocos2dx/platform/mac/CCWindow.mm \
../cocos2d/cocos2dx/platform/mac/CCApplication.mm \
../cocos2d/cocos2dx/platform/mac/CCCommon.mm \
../cocos2d/cocos2dx/platform/mac/CCDevice.mm \
../cocos2d/cocos2dx/platform/mac/CCDirectorCaller.mm \
../cocos2d/cocos2dx/platform/mac/CCEGLView.mm \
../cocos2d/cocos2dx/platform/mac/CCEventDispatcher.mm \
../cocos2d/cocos2dx/platform/mac/CCFileUtilsMac.mm \
../cocos2d/cocos2dx/platform/mac/CCImage.mm \
../cocos2d/cocos2dx/platform/mac/CCThread.mm \
../cocos2d/cocos2dx/platform/mac/EAGLView.mm \
../cocos2d/CocosDenshion/mac/CDAudioManager.mm \
../cocos2d/CocosDenshion/mac/CDOpenALSupport.mm \
../cocos2d/CocosDenshion/mac/CDXMacOSXSupport.mm \
../cocos2d/CocosDenshion/mac/CocosDenshion.mm \
../cocos2d/CocosDenshion/mac/SimpleAudioEngine.mm \
../cocos2d/CocosDenshion/mac/SimpleAudioEngine_objc.mm \
../cocos2d/extensions/GUI/CCEditBox/CCEditBoxImplMac.mm

SOURCES += \
main.cpp\
mainwindow.cpp \
myqglwidget.cpp \
mysceneeditor.cpp \
../cocos2d/cocos2dx/CCClassRegistry.cpp \
../cocos2d/cocos2dx/CCEndian.cpp \
../cocos2d/cocos2dx/ccFPSImages.c \
../cocos2d/cocos2dx/CCCamera.cpp \
../cocos2d/cocos2dx/CCConfiguration.cpp \
../cocos2d/cocos2dx/CCDirector.cpp \
../cocos2d/cocos2dx/CCScheduler.cpp \
../cocos2d/cocos2dx/cocos2d.cpp \
../cocos2d/cocos2dx/actions/CCAction.cpp \
../cocos2d/cocos2dx/actions/CCActionCamera.cpp \
../cocos2d/cocos2dx/actions/CCActionCatmullRom.cpp \
../cocos2d/cocos2dx/actions/CCActionEase.cpp \
../cocos2d/cocos2dx/actions/CCActionGrid.cpp \
../cocos2d/cocos2dx/actions/CCActionGrid3D.cpp \
../cocos2d/cocos2dx/actions/CCActionInstant.cpp \
../cocos2d/cocos2dx/actions/CCActionInterval.cpp \
../cocos2d/cocos2dx/actions/CCActionManager.cpp \
../cocos2d/cocos2dx/actions/CCActionPageTurn3D.cpp \
../cocos2d/cocos2dx/actions/CCActionProgressTimer.cpp \
../cocos2d/cocos2dx/actions/CCActionTiledGrid.cpp \
../cocos2d/cocos2dx/actions/CCActionTween.cpp \
../cocos2d/cocos2dx/base_nodes/CCAtlasNode.cpp \
../cocos2d/cocos2dx/base_nodes/CCNode.cpp \
../cocos2d/cocos2dx/cocoa/CCAffineTransform.cpp \
../cocos2d/cocos2dx/cocoa/CCArray.cpp \
../cocos2d/cocos2dx/cocoa/CCAutoreleasePool.cpp \
../cocos2d/cocos2dx/cocoa/CCDictionary.cpp \
../cocos2d/cocos2dx/cocoa/CCGeometry.cpp \
../cocos2d/cocos2dx/cocoa/CCNS.cpp \
../cocos2d/cocos2dx/cocoa/CCObject.cpp \
../cocos2d/cocos2dx/cocoa/CCSet.cpp \
../cocos2d/cocos2dx/cocoa/CCString.cpp \
../cocos2d/cocos2dx/cocoa/CCZone.cpp \
../cocos2d/cocos2dx/cocoa/CCData.cpp \
../cocos2d/cocos2dx/cocoa/CCDataVisitor.cpp \
../cocos2d/cocos2dx/draw_nodes/CCDrawNode.cpp \
../cocos2d/cocos2dx/draw_nodes/CCDrawingPrimitives.cpp \
../cocos2d/cocos2dx/effects/CCGrabber.cpp \
../cocos2d/cocos2dx/effects/CCGrid.cpp \
../cocos2d/extensions/CCBReader/CCBAnimationManager.cpp \
../cocos2d/extensions/CCBReader/CCBFileLoader.cpp \
../cocos2d/extensions/CCBReader/CCBKeyframe.cpp \
../cocos2d/extensions/CCBReader/CCBReader.cpp \
../cocos2d/extensions/CCBReader/CCBSequence.cpp \
../cocos2d/extensions/CCBReader/CCBSequenceProperty.cpp \
../cocos2d/extensions/CCBReader/CCBValue.cpp \
../cocos2d/extensions/CCBReader/CCControlButtonLoader.cpp \
../cocos2d/extensions/CCBReader/CCControlLoader.cpp \
../cocos2d/extensions/CCBReader/CCLabelBMFontLoader.cpp \
../cocos2d/extensions/CCBReader/CCLabelTTFLoader.cpp \
../cocos2d/extensions/CCBReader/CCLayerColorLoader.cpp \
../cocos2d/extensions/CCBReader/CCLayerGradientLoader.cpp \
../cocos2d/extensions/CCBReader/CCLayerLoader.cpp \
../cocos2d/extensions/CCBReader/CCMenuItemImageLoader.cpp \
../cocos2d/extensions/CCBReader/CCMenuItemLoader.cpp \
../cocos2d/extensions/CCBReader/CCNode+CCBRelativePositioning.cpp \
../cocos2d/extensions/CCBReader/CCNodeLoader.cpp \
../cocos2d/extensions/CCBReader/CCNodeLoaderLibrary.cpp \
../cocos2d/extensions/CCBReader/CCParticleSystemQuadLoader.cpp \
../cocos2d/extensions/CCBReader/CCScale9SpriteLoader.cpp \
../cocos2d/extensions/CCBReader/CCScrollViewLoader.cpp \
../cocos2d/extensions/CCBReader/CCSpriteLoader.cpp \
../cocos2d/extensions/GUI/CCControlExtension/CCControl.cpp \
../cocos2d/extensions/GUI/CCControlExtension/CCControlButton.cpp \
../cocos2d/extensions/GUI/CCControlExtension/CCControlColourPicker.cpp \
../cocos2d/extensions/GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp \
../cocos2d/extensions/GUI/CCControlExtension/CCControlHuePicker.cpp \
../cocos2d/extensions/GUI/CCControlExtension/CCControlPotentiometer.cpp \
../cocos2d/extensions/GUI/CCControlExtension/CCControlSlider.cpp \
../cocos2d/extensions/GUI/CCControlExtension/CCControlStepper.cpp \
../cocos2d/extensions/GUI/CCControlExtension/CCControlUtils.cpp \
../cocos2d/extensions/GUI/CCControlExtension/CCInvocation.cpp \
../cocos2d/extensions/GUI/CCControlExtension/CCScale9Sprite.cpp \
../cocos2d/extensions/GUI/CCEditBox/CCEditBox.cpp \
../cocos2d/extensions/GUI/CCScrollView/CCScrollView.cpp \
../cocos2d/extensions/GUI/CCScrollView/CCSorting.cpp \
../cocos2d/extensions/GUI/CCScrollView/CCTableView.cpp \
../cocos2d/extensions/GUI/CCScrollView/CCTableViewCell.cpp \
../cocos2d/cocos2dx/kazmath/src/GL/mat4stack.c \
../cocos2d/cocos2dx/kazmath/src/GL/matrix.c \
../cocos2d/cocos2dx/kazmath/src/aabb.c \
../cocos2d/cocos2dx/kazmath/src/mat3.c \
../cocos2d/cocos2dx/kazmath/src/mat4.c \
../cocos2d/cocos2dx/kazmath/src/neon_matrix_impl.c \
../cocos2d/cocos2dx/kazmath/src/plane.c \
../cocos2d/cocos2dx/kazmath/src/quaternion.c \
../cocos2d/cocos2dx/kazmath/src/ray2.c \
../cocos2d/cocos2dx/kazmath/src/utility.c \
../cocos2d/cocos2dx/kazmath/src/vec2.c \
../cocos2d/cocos2dx/kazmath/src/vec3.c \
../cocos2d/cocos2dx/kazmath/src/vec4.c \
../cocos2d/cocos2dx/keypad_dispatcher/CCKeypadDelegate.cpp \
../cocos2d/cocos2dx/keypad_dispatcher/CCKeypadDispatcher.cpp \
../cocos2d/cocos2dx/label_nodes/CCLabelAtlas.cpp \
../cocos2d/cocos2dx/label_nodes/CCLabelBMFont.cpp \
../cocos2d/cocos2dx/label_nodes/CCLabelTTF.cpp \
../cocos2d/cocos2dx/layers_scenes_transitions_nodes/CCLayer.cpp \
../cocos2d/cocos2dx/layers_scenes_transitions_nodes/CCScene.cpp \
../cocos2d/cocos2dx/layers_scenes_transitions_nodes/CCTransition.cpp \
../cocos2d/cocos2dx/layers_scenes_transitions_nodes/CCTransitionPageTurn.cpp \
../cocos2d/cocos2dx/layers_scenes_transitions_nodes/CCTransitionProgress.cpp \
../cocos2d/cocos2dx/menu_nodes/CCMenu.cpp \
../cocos2d/cocos2dx/menu_nodes/CCMenuItem.cpp \
../cocos2d/cocos2dx/misc_nodes/CCClippingNode.cpp \
../cocos2d/cocos2dx/misc_nodes/CCMotionStreak.cpp \
../cocos2d/cocos2dx/misc_nodes/CCProgressTimer.cpp \
../cocos2d/cocos2dx/misc_nodes/CCRenderTexture.cpp \
../cocos2d/cocos2dx/particle_nodes/CCParticleBatchNode.cpp \
../cocos2d/cocos2dx/particle_nodes/CCParticleExamples.cpp \
../cocos2d/cocos2dx/particle_nodes/CCParticleSystem.cpp \
../cocos2d/cocos2dx/particle_nodes/CCParticleSystemQuad.cpp \
../cocos2d/cocos2dx/platform/CCEGLViewProtocol.cpp \
../cocos2d/cocos2dx/platform/CCImageCommonWebp.cpp \
../cocos2d/cocos2dx/platform/CCSAXParser.cpp \
../cocos2d/cocos2dx/platform/CCFileUtils.cpp \
../cocos2d/cocos2dx/platform/platform.cpp \
../cocos2d/cocos2dx/script_support/CCScriptSupport.cpp \
../cocos2d/cocos2dx/shaders/CCGLProgram.cpp \
../cocos2d/cocos2dx/shaders/CCShaderCache.cpp \
../cocos2d/cocos2dx/shaders/ccGLStateCache.cpp \
../cocos2d/cocos2dx/shaders/ccShaders.cpp \
../cocos2d/cocos2dx/sprite_nodes/CCAnimation.cpp \
../cocos2d/cocos2dx/sprite_nodes/CCAnimationCache.cpp \
../cocos2d/cocos2dx/sprite_nodes/CCSprite.cpp \
../cocos2d/cocos2dx/sprite_nodes/CCSpriteBatchNode.cpp \
../cocos2d/cocos2dx/sprite_nodes/CCSpriteFrame.cpp \
../cocos2d/cocos2dx/sprite_nodes/CCSpriteFrameCache.cpp \
../cocos2d/cocos2dx/support/CCNotificationCenter.cpp \
../cocos2d/cocos2dx/support/CCPointExtension.cpp \
../cocos2d/cocos2dx/support/CCProfiling.cpp \
../cocos2d/cocos2dx/support/CCVertex.cpp \
../cocos2d/cocos2dx/support/TransformUtils.cpp \
../cocos2d/cocos2dx/support/base64.cpp \
../cocos2d/cocos2dx/support/ccUTF8.cpp \
../cocos2d/cocos2dx/support/ccUtils.cpp \
../cocos2d/cocos2dx/support/data_support/ccCArray.cpp \
../cocos2d/cocos2dx/support/image_support/TGAlib.cpp \
../cocos2d/cocos2dx/support/tinyxml2/tinyxml2.cpp \
../cocos2d/cocos2dx/support/user_default/CCUserDefault.cpp \
../cocos2d/cocos2dx/support/user_default/CCUserDefaultAndroid.cpp \
../cocos2d/cocos2dx/support/zip_support/ZipUtils.cpp \
../cocos2d/cocos2dx/support/zip_support/ioapi.cpp \
../cocos2d/cocos2dx/support/zip_support/unzip.cpp \
../cocos2d/cocos2dx/support/component/CCComponent.cpp \
../cocos2d/cocos2dx/support/component/CCComponentContainer.cpp \
../cocos2d/cocos2dx/text_input_node/CCIMEDispatcher.cpp \
../cocos2d/cocos2dx/text_input_node/CCTextFieldTTF.cpp \
../cocos2d/cocos2dx/textures/CCTexture2D.cpp \
../cocos2d/cocos2dx/textures/CCTextureETC.cpp \
../cocos2d/cocos2dx/textures/CCTextureAtlas.cpp \
../cocos2d/cocos2dx/textures/CCTextureCache.cpp \
../cocos2d/cocos2dx/textures/CCTexturePVR.cpp \
../cocos2d/cocos2dx/tilemap_parallax_nodes/CCParallaxNode.cpp \
../cocos2d/cocos2dx/tilemap_parallax_nodes/CCTMXLayer.cpp \
../cocos2d/cocos2dx/tilemap_parallax_nodes/CCTMXObjectGroup.cpp \
../cocos2d/cocos2dx/tilemap_parallax_nodes/CCTMXTiledMap.cpp \
../cocos2d/cocos2dx/tilemap_parallax_nodes/CCTMXXMLParser.cpp \
../cocos2d/cocos2dx/tilemap_parallax_nodes/CCTileMapAtlas.cpp \
../cocos2d/cocos2dx/touch_dispatcher/CCTouch.cpp \
../cocos2d/cocos2dx/touch_dispatcher/CCTouchDispatcher.cpp \
../cocos2d/cocos2dx/touch_dispatcher/CCTouchHandler.cpp \
../cocos2d/cocos2dx/keyboard_dispatcher/CCKeyboardDispatcher.cpp \
    dialogimportccb.cpp \
    fileutil.cpp \
    componentbase.cpp \
    componentnode.cpp \
    componentsprite.cpp \
    nodeitem.cpp \
    exporter.cpp \
    componentnodergba.cpp \
    componentparticlesystem.cpp \
    exporterproject.cpp

HEADERS  += \
mainwindow.h \
myqglwidget.h \
mysceneeditor.h \
    Singleton.h \
    dialogimportccb.h \
    fileutil.h \
    componentbase.h \
    componentnode.h \
    componentsprite.h \
    nodeitem.h \
    widgetpoint.h \
    widgetnumber.h \
    widgetmisc.h \
    widgetSize.h \
    widgetTexture.h \
    nodedriver.h \
    exporter.h \
    componentnodergba.h \
    componentparticlesystem.h \
    exporterproject.h

FORMS += mainwindow.ui \
    dialogimportccb.ui

DEFINES += CC_TARGET_OS_MAC QT_MAC_USE_COCOA USE_FILE32API COCOS2D_DEBUG KEYBOARD_SUPPORT

INCLUDEPATH += \
"../cocos2d/cocos2dx" \
"../cocos2d/cocos2dx/platform" \
"../cocos2d/cocos2dx/include" \
"../cocos2d/cocos2dx/kazmath/include" \
"../cocos2d/cocos2dx/platform/mac" \
"../cocos2d/cocos2dx/platform/third_party/mac/webp" \
"../cocos2d/extensions" \
"../cocos2d/cocos2dx/cocoa" \
"../cocos2d/cocos2dx/touch_dispatcher" \
"../cocos2d/cocos2dx/keyboard_dispatcher" \
"../cocos2d/cocos2dx/textures" \
"../cocos2d/cocos2dx/text_input_node" \
"../cocos2d/CocosDenshion/include"

LIBS += \
    -framework AppKit \
    -framework Foundation \
    -framework ApplicationServices \
    -framework QuartzCore \
    -framework OpenAL \
    -framework CoreGraphics \
    -framework AudioToolbox \
    -lz \
   "/usr/lib/libc++.dylib" \
    "../cocos2d/cocos2dx/platform/third_party/mac/libraries/libwebp.a" #\
    #"../libs/libcocos2dx.a"

