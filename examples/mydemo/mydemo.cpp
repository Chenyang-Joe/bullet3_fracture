#include "mydemo.h"
#include <iostream>

#include "btBulletDynamicsCommon.h"
#define ARRAY_SIZE_Y 5
#define ARRAY_SIZE_X 5
#define ARRAY_SIZE_Z 5

#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"

#include "../CommonInterfaces/CommonRigidBodyBase.h"

#include "../Importers/ImportObjDemo/ImportObjExample.h"

// #include "../Importers/ImportObjDemo/ImportObjExample.h"
// #include "../Importers/ImportMeshUtility/b3ImportMeshUtility.h"
// #include "../Utils/b3BulletDefaultFileIO.h"
// #include "../OpenGLWindow/GLInstanceGraphicsShape.h"

// #include "myobjImporter/ImportObjExample.h"
// #include <vector>
// #include "../OpenGLWindow/GLInstancingRenderer.h"
// #include "../ThirdPartyLibs/Wavefront/tiny_obj_loader.h"
// #include "../OpenGLWindow/GLInstanceGraphicsShape.h"
// #include "btBulletDynamicsCommon.h"
// #include "../OpenGLWindow/SimpleOpenGL3App.h"
// #include "myobjImporter/Wavefront2GLInstanceGraphicsShape.h"
// #include "../Utils/b3ResourcePath.h"
// #include "../Utils/b3BulletDefaultFileIO.h"
// #include "Bullet3Common/b3FileUtils.h"

// #include "../ThirdPartyLibs/stb_image/stb_image.h"

// #include "../CommonInterfaces/CommonRigidBodyBase.h"
// #include "../Importers/ImportMeshUtility/b3ImportMeshUtility.h"




struct myExample : public CommonRigidBodyBase
{
	myExample(struct GUIHelperInterface* helper)
		: CommonRigidBodyBase(helper)
	{
	}
	virtual ~myExample() {}
	virtual void initPhysics();
	virtual void renderScene();
	void resetCamera()
	{
		float dist = 4;
		float pitch = -35;
		float yaw = 52;
		float targetPos[3] = {0, 0, 0};
		m_guiHelper->resetCamera(dist, yaw, pitch, targetPos[0], targetPos[1], targetPos[2]);
	}
};


// int myloadAndRegisterMeshFromFile(const std::string& fileName, CommonRenderInterface* renderer)
// {
// 	int shapeId = -1;

// 	b3ImportMeshData meshData;
// 	b3BulletDefaultFileIO fileIO;
// 	if (b3ImportMeshUtility::loadAndRegisterMeshFromFileInternal(fileName, meshData,&fileIO))
// 	{
// 		int textureIndex = -1;

// 		if (meshData.m_textureImage1)
// 		{
// 			textureIndex = renderer->registerTexture(meshData.m_textureImage1, meshData.m_textureWidth, meshData.m_textureHeight);
// 		}

// 		shapeId = renderer->registerShape(&meshData.m_gfxShape->m_vertices->at(0).xyzw[0],
// 										  meshData.m_gfxShape->m_numvertices,
// 										  &meshData.m_gfxShape->m_indices->at(0),
// 										  meshData.m_gfxShape->m_numIndices,
// 										  B3_GL_TRIANGLES,
// 										  textureIndex);
// 		delete meshData.m_gfxShape;
// 		if (!meshData.m_isCached)
// 		{
// 			delete meshData.m_textureImage1;
// 		}
// 	}
// 	return shapeId;
// }





void myExample::initPhysics()
{
	m_guiHelper->setUpAxis(1);

	createEmptyDynamicsWorld();
	//m_dynamicsWorld->setGravity(btVector3(0,0,0));
	m_guiHelper->createPhysicsDebugDrawer(m_dynamicsWorld);

	if (m_dynamicsWorld->getDebugDrawer())
		m_dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe + btIDebugDraw::DBG_DrawContactPoints);

	///create a few basic rigid bodies
	btBoxShape* groundShape = createBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

	//groundShape->initializePolyhedralFeatures();
	//btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),50);

	m_collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -50, 0));

	{
		btScalar mass(0.);
		createRigidBody(mass, groundTransform, groundShape, btVector4(0, 0, 1, 1));
	}

	{
		//create a few dynamic rigidbodies
		// Re-using the same collision is better for memory usage and performance

		btBoxShape* colShape = createBoxShape(btVector3(.1, .1, .1));

		//btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		m_collisionShapes.push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass(1.f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass, localInertia);

		for (int k = 0; k < ARRAY_SIZE_Y; k++)
		{
			for (int i = 0; i < ARRAY_SIZE_X; i++)
			{
				for (int j = 0; j < ARRAY_SIZE_Z; j++)
				{
					startTransform.setOrigin(btVector3(
						btScalar(0.2 * i),
						btScalar(2 + .2 * k),
						btScalar(0.2 * j)));

					createRigidBody(mass, startTransform, colShape);
				}
			}
		}
	}

    // import a bullet
    // btBulletWorldImporter* importer = new btBulletWorldImporter(m_dynamicsWorld);
    // const char* prefix[] = {"", "./", "./data/", "../data/", "../../data/", "../../../data/", "../../../../data/"};
	// int numPrefixes = sizeof(prefix) / sizeof(const char*);
	// char relativeFileName[1024];
	// FILE* f = 0;

    // const char* fileName = "/Users/chenyangxu/Codebase/AI4CE/assembly2025spring/bullet/bullet3_fracture/examples/mydemo/Core2.obj";
    // char m_fileName[1024];
    // memcpy(m_fileName, fileName, strlen(fileName) + 1);


	// for (int i = 0; !f && i < numPrefixes; i++)
	// {
	// 	sprintf(relativeFileName, "%s%s", prefix[i], m_fileName);
	// 	f = fopen(relativeFileName, "rb");
	// 	if (f)
	// 	{
    //         std::cout << "file detected" << std::endl;
	// 		break;
	// 	}
	// }
	// if (f)
	// {
	// 	fclose(f);
	// }

	// importer->loadFile(relativeFileName);

    // import a obj


    btTransform trans;
    // const char* m_fileName = "mydata/Core2.obj";
	// const char* m_fileName = "mydata/cube.obj";
	const char* m_fileName = "cube.obj";
	trans.setIdentity();
	trans.setRotation(btQuaternion(btVector3(1, 0, 0), SIMD_HALF_PI));
	btVector3 position = trans.getOrigin();
	btQuaternion orn = trans.getRotation();

	btVector3 scaling(1, 1, 1);
	btVector4 color(1, 1, 1,1);

	int shapeId = loadAndRegisterMeshFromFile2(m_fileName, m_guiHelper->getRenderInterface());

	if (shapeId >= 0)
	{
		//int id =
		m_guiHelper->getRenderInterface()->registerGraphicsInstance(shapeId, position, orn, color, scaling);
	}

	m_guiHelper->autogenerateGraphicsObjects(m_dynamicsWorld);
}

void myExample::renderScene()
{
	CommonRigidBodyBase::renderScene();
}

CommonExampleInterface* myCreateFunc(CommonExampleOptions& options)
{
	return new myExample(options.m_guiHelper);
}

B3_STANDALONE_EXAMPLE(myCreateFunc)
