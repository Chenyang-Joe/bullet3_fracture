
INCLUDE_DIRECTORIES(
	.
	${BULLET_PHYSICS_SOURCE_DIR}/src
	${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs
)

FILE(GLOB GwenGUISupport_SRCS  "GwenGUISupport/*" )
FILE(GLOB GwenGUISupport_HDRS  "GwenGUISupport/*" )


IF (WIN32)
        INCLUDE_DIRECTORIES(
                ${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad
        )
				ADD_DEFINITIONS(-DGLEW_STATIC)
ELSE(WIN32)
        IF(APPLE)
                find_library(COCOA NAMES Cocoa)
  			ELSE(APPLE)
                ADD_DEFINITIONS("-DGLEW_INIT_OPENGL11_FUNCTIONS=1")
                ADD_DEFINITIONS("-DGLEW_STATIC")
                ADD_DEFINITIONS("-DGLEW_DYNAMIC_LOAD_ALL_GLX_FUNCTIONS=1")
                INCLUDE_DIRECTORIES( ${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad )
     		ENDIF(APPLE)
ENDIF(WIN32)


ADD_LIBRARY(BulletExampleBrowserLibNew
	# OpenGLExampleBrowser.cpp
	# OpenGLGuiHelper.cpp
	# GL_ShapeDrawer.cpp
	# CollisionShape2TriangleMesh.cpp
	# CollisionShape2TriangleMesh.h
	../Utils/b3Clock.cpp
	../Utils/b3Clock.h
	../Utils/ChromeTraceUtil.cpp
	../Utils/ChromeTraceUtil.h
	../Utils/b3ResourcePath.cpp
	../Utils/b3ResourcePath.h
	../Utils/b3ERPCFMHelper.hpp
	../Utils/b3ReferenceFrameHelper.hpp
	${GwenGUISupport_SRCS}
	${GwenGUISupport_HDRS}
	
)

SET_TARGET_PROPERTIES(BulletExampleBrowserLibNew PROPERTIES VERSION ${BULLET_VERSION})
SET_TARGET_PROPERTIES(BulletExampleBrowserLibNew PROPERTIES SOVERSION ${BULLET_VERSION})
IF (BUILD_SHARED_LIBS)
		IF (WIN32)
                TARGET_LINK_LIBRARIES(
                        BulletExampleBrowserLibNew Bullet3Common BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamicsUtils
                        BulletInverseDynamics LinearMath OpenGLWindow gwen BussIK
                        ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY}
                )
		ELSE(WIN32)
        IF(APPLE)
                 TARGET_LINK_LIBRARIES(
                                BulletExampleBrowserLibNew Bullet3Common BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamicsUtils
                                BulletInverseDynamics LinearMath OpenGLWindow gwen BussIK
                                ${COCOA} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY}
                 )
				ELSE(APPLE)
                 FIND_PACKAGE(Threads)
                 TARGET_LINK_LIBRARIES(
                                BulletExampleBrowserLibNew Bullet3Common BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamicsUtils
                                BulletInverseDynamics LinearMath OpenGLWindow gwen BussIK
                                ${CMAKE_THREAD_LIBS_INIT} ${DL}
                        )
        ENDIF(APPLE)
	ENDIF(WIN32)
ENDIF(BUILD_SHARED_LIBS)

INSTALL(TARGETS BulletExampleBrowserLibNew
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX})

#************************** borrow the example browser's library


# App_BasicExample is a minimal sample creating, stepping and deleting a Bullet dynamics world



INCLUDE_DIRECTORIES(
${BULLET_PHYSICS_SOURCE_DIR}/src
)

# LINK_LIBRARIES(
# BulletDynamics BulletCollision LinearMath
# )

LINK_LIBRARIES(
        BulletExampleBrowserLibNew Bullet3Common BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamicsUtils BulletInverseDynamics LinearMath OpenGLWindow gwen BussIK
)

# For import obj

file(GLOB_RECURSE ImportersCPP "../Importers/*.cpp")



Set( ObjImportSrc
# ../Importers/ImportObjDemo/ImportObjExample.cpp
# ../Importers/ImportObjDemo/LoadMeshFromObj.cpp
# ../Importers/ImportObjDemo/Wavefront2GLInstanceGraphicsShape.cpp
${ImportersCPP}

../ThirdPartyLibs/stb_image/stb_image.cpp
# ../ThirdPartyLibs/stb_image/stb_image.h
../ThirdPartyLibs/stb_image/stb_image_write.cpp
../ThirdPartyLibs/Wavefront/tiny_obj_loader.cpp

../ThirdPartyLibs/tinyxml2/tinyxml2.cpp


../../Extras/Serialize/BulletWorldImporter/btWorldImporter.cpp
../../Extras/Serialize/BulletWorldImporter/btMultiBodyWorldImporter.cpp
../../Extras/Serialize/BulletWorldImporter/btBulletWorldImporter.cpp
../../Extras/Serialize/BulletFileLoader/bChunk.cpp		
../../Extras/Serialize/BulletFileLoader/bFile.cpp
../../Extras/Serialize/BulletFileLoader/bDNA.cpp		
../../Extras/Serialize/BulletFileLoader/btBulletFile.cpp

)


Set( ObjImportInclude
# ../Importers/ImportObjDemo
../Importers
../ThirdPartyLibs
../mydemo
)

INCLUDE_DIRECTORIES(${ObjImportInclude})

IF (WIN32)
	ADD_EXECUTABLE(App_mydemo
		mydemo.cpp
		main.cpp
		${BULLET_PHYSICS_SOURCE_DIR}/build3/bullet.rc
                ${ObjImportSrc}
	)
ELSE()
	ADD_EXECUTABLE(App_mydemo
                mydemo.cpp
		main.cpp
                ${ObjImportSrc}
	)
ENDIF()




IF (INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
			SET_TARGET_PROPERTIES(App_mydemo PROPERTIES  DEBUG_POSTFIX "_Debug")
			SET_TARGET_PROPERTIES(App_mydemo PROPERTIES  MINSIZEREL_POSTFIX "_MinsizeRel")
			SET_TARGET_PROPERTIES(App_mydemo PROPERTIES  RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
ENDIF(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)





#################
# Standalone BasicExampleGui using OpenGL (but not the example browser)


INCLUDE_DIRECTORIES(
        ${BULLET_PHYSICS_SOURCE_DIR}/src
        ${BULLET_PHYSICS_SOURCE_DIR}/btgui
        ${BULLET_PHYSICS_SOURCE_DIR}/examples
        ${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad
        ${ObjImportInclude}
)


SET(AppmydemoGui_SRCS
        mydemo.cpp
        ${BULLET_PHYSICS_SOURCE_DIR}/build3/bullet.rc
	../StandaloneMain/main_opengl_single_example.cpp
        ../ExampleBrowser/OpenGLGuiHelper.cpp
        ../ExampleBrowser/GL_ShapeDrawer.cpp
        ../ExampleBrowser/CollisionShape2TriangleMesh.cpp
		../Utils/b3Clock.cpp
)

#this define maps StandaloneExampleCreateFunc to the right 'CreateFunc'
ADD_DEFINITIONS(-DB3_USE_STANDALONE_EXAMPLE)

# LINK_LIBRARIES(
#         BulletDynamics BulletCollision LinearMath OpenGLWindow Bullet3Common
# )

LINK_LIBRARIES(
        BulletExampleBrowserLibNew Bullet3Common BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamicsUtils BulletInverseDynamics LinearMath OpenGLWindow gwen BussIK
)

#some code to support OpenGL and Glew cross platform
IF (WIN32)
        INCLUDE_DIRECTORIES(
             ${BULLET_PHYSICS_SOURCE_DIR}/btgui/OpenGLWindow/GlewWindows
        )
        ADD_DEFINITIONS(-DGLEW_STATIC)
	LINK_LIBRARIES( ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} )
ELSE(WIN32)
        IF(APPLE)
                find_library(COCOA NAMES Cocoa)
                MESSAGE(${COCOA})
                link_libraries(${COCOA} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})

        ELSE(APPLE)
                INCLUDE_DIRECTORIES(
                        ${BULLET_PHYSICS_SOURCE_DIR}/btgui/OpenGLWindow/GlewWindows
                )
                ADD_DEFINITIONS("-DGLEW_INIT_OPENGL11_FUNCTIONS=1")
                ADD_DEFINITIONS("-DGLEW_STATIC")
                ADD_DEFINITIONS("-DGLEW_DYNAMIC_LOAD_ALL_GLX_FUNCTIONS=1")

                FIND_PACKAGE(Threads)
                LINK_LIBRARIES( ${CMAKE_THREAD_LIBS_INIT} ${DL} )
        ENDIF(APPLE)
ENDIF(WIN32)


ADD_EXECUTABLE(AppmydemoGui       
                ${AppmydemoGui_SRCS}
                ${ObjImportSrc}
)


IF (INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
                        SET_TARGET_PROPERTIES(AppmydemoGui PROPERTIES  DEBUG_POSTFIX "_Debug")
                        SET_TARGET_PROPERTIES(AppmydemoGui PROPERTIES  MINSIZEREL_POSTFIX "_MinsizeRel")
                        SET_TARGET_PROPERTIES(AppmydemoGui PROPERTIES  RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
ENDIF(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)

