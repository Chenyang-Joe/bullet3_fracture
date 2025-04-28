#ifndef IMPORT_OBJ_EXAMPLE_H
#define IMPORT_OBJ_EXAMPLE_H

#include "../CommonInterfaces/CommonRigidBodyBase.h"

class CommonExampleInterface* ImportObjCreateFunc(struct CommonExampleOptions& options);

int loadAndRegisterMeshFromFile2(const std::string& fileName, CommonRenderInterface* renderer);


#endif  //IMPORT_OBJ_EXAMPLE_H
