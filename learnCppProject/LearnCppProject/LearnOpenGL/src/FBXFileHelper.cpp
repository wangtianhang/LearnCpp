// #include "./FBXFileHelper.h"
// #include "./fbxsdk.h"
// #include "./fbxsdk/scene/geometry/fbxmesh.h"
// 
// // bool FBXFileHelper::loadFBXAsModel(std::string path, MeshFliter & ret, BoneAnimation & bones)
// // {
// // 	return false;
// // }
// 
// /* Tab character ("\t") counter */
// int numTabs = 0;
// 
// /**
//  * Print the required number of tabs.
//  */
// void PrintTabs() {
// 	for (int i = 0; i < numTabs; i++)
// 		GUtil::Print("\t");
// }
// 
// /**
//  * Return a string-based representation based on the attribute type.
//  */
// FbxString GetAttributeTypeName(FbxNodeAttribute::EType type) {
// 	switch (type) {
// 	case FbxNodeAttribute::eUnknown: return "unidentified";
// 	case FbxNodeAttribute::eNull: return "null";
// 	case FbxNodeAttribute::eMarker: return "marker";
// 	case FbxNodeAttribute::eSkeleton: return "skeleton";
// 	case FbxNodeAttribute::eMesh: 
// 		return "mesh";
// 	case FbxNodeAttribute::eNurbs: return "nurbs";
// 	case FbxNodeAttribute::ePatch: return "patch";
// 	case FbxNodeAttribute::eCamera: return "camera";
// 	case FbxNodeAttribute::eCameraStereo: return "stereo";
// 	case FbxNodeAttribute::eCameraSwitcher: return "camera switcher";
// 	case FbxNodeAttribute::eLight: return "light";
// 	case FbxNodeAttribute::eOpticalReference: return "optical reference";
// 	case FbxNodeAttribute::eOpticalMarker: return "marker";
// 	case FbxNodeAttribute::eNurbsCurve: return "nurbs curve";
// 	case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface";
// 	case FbxNodeAttribute::eBoundary: return "boundary";
// 	case FbxNodeAttribute::eNurbsSurface: return "nurbs surface";
// 	case FbxNodeAttribute::eShape: return "shape";
// 	case FbxNodeAttribute::eLODGroup: return "lodgroup";
// 	case FbxNodeAttribute::eSubDiv: return "subdiv";
// 	default: return "unknown";
// 	}
// }
// 
// /**
//  * Print an attribute.
//  */
// void PrintAttribute(FbxNodeAttribute* pAttribute) {
// 	if (!pAttribute) return;
// 
// 	FbxString typeName = GetAttributeTypeName(pAttribute->GetAttributeType());
// 	FbxString attrName = pAttribute->GetName();
// 	PrintTabs();
// 
// 	// Note: to retrieve the character array of a FbxString, use its Buffer() method.	
// 	char buffer[256] = { 0 };
// 	sprintf_s(buffer, "<attribute type='%s' name='%s'/>\n", typeName.Buffer(), attrName.Buffer());
// 	GUtil::Print(buffer);
// }
// 
// /**
//  * Print a node, its attributes, and all its children recursively.
//  */
// void PrintNode(FbxNode* pNode) {
// 	PrintTabs();
// 	const char* nodeName = pNode->GetName();
// 	FbxDouble3 translation = pNode->LclTranslation.Get();
// 	FbxDouble3 rotation = pNode->LclRotation.Get();
// 	FbxDouble3 scaling = pNode->LclScaling.Get();
// 
// 	// Print the contents of the node.
// 	char buffer[512] = { 0 };
// 	sprintf_s(buffer, "<node name='%s' translation='(%f, %f, %f)' rotation='(%f, %f, %f)' scaling='(%f, %f, %f)'>\n",
// 		nodeName,
// 		translation[0], translation[1], translation[2],
// 		rotation[0], rotation[1], rotation[2],
// 		scaling[0], scaling[1], scaling[2]
// 	);
// 	GUtil::Print(buffer);
// 	numTabs++;
// 
// 	// Print the node's attributes.
// 	int attributeCount = pNode->GetNodeAttributeCount();
// 	for (int i = 0; i < attributeCount; i++)
// 		PrintAttribute(pNode->GetNodeAttributeByIndex(i));
// 
// 	// Recursively print the children.
// 	int childCount = pNode->GetChildCount();
// 	for (int j = 0; j < childCount; j++)
// 		PrintNode(pNode->GetChild(j));
// 
// 	numTabs--;
// 	PrintTabs();
// 	GUtil::Print("</node>\n");
// }
// 
// bool FBXFileHelper::logFbx(std::string path)
// {
// 	// Change the following filename to a suitable filename value.
// 	//const char* lFilename = "file.fbx";
// 
// 	// Initialize the SDK manager. This object handles all our memory management.
// 	FbxManager* lSdkManager = FbxManager::Create();
// 
// 	// Create the IO settings object.
// 	FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
// 	lSdkManager->SetIOSettings(ios);
// 
// 	// Create an importer using the SDK manager.
// 	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");
// 
// 	char buffer[256] = { 0 };
// 
// 	// Use the first argument as the filename for the importer.
// 	if (!lImporter->Initialize(path.c_str(), -1, lSdkManager->GetIOSettings())) {
// 		GUtil::Print("Call to FbxImporter::Initialize() failed.\n");
// 		sprintf_s(buffer, "Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
// 		GUtil::Print(buffer);
// 		return false;
// 	}
// 
// 	// Create a new scene so that it can be populated by the imported file.
// 	FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");
// 
// 	// Import the contents of the file into the scene.
// 	lImporter->Import(lScene);
// 
// 	// The file is imported; so get rid of the importer.
// 	lImporter->Destroy();
// 	FbxAxisSystem::DirectX.ConvertScene(lScene);
// 
// 	// Print the nodes of the scene and their attributes recursively.
// 	// Note that we are not printing the root node because it should
// 	// not contain any attributes.
// 	FbxNode* lRootNode = lScene->GetRootNode();
// 	if (lRootNode) {
// 		for (int i = 0; i < lRootNode->GetChildCount(); i++)
// 			PrintNode(lRootNode->GetChild(i));
// 	}
// 	// Destroy the SDK manager and all the other objects it was handling.
// 	lSdkManager->Destroy();
// 	return true;
// }
// 
// // void ConvertFBXMesh(FbxMesh* currMesh, std::vector<Vector3> &vertices, std::vector<Vector3> &normals, std::vector<GLuint> &elements)
// // {
// // // 	int vertexCount = currMesh->GetControlPointsCount();
// // // 	FbxVector4 *controlPoints = currMesh->GetControlPoints();
// // // 	for (int i = 0; i < vertexCount; i++)
// // // 	{
// // // 		FbxVector4 cpitem = controlPoints[i];
// // // 		Vector3 pos = Vector3(cpitem[0], cpitem[1], cpitem[2]);
// // // 		vertices.push_back(pos);
// // // 	}
// // // 	int pvCount = currMesh->GetPolygonVertexCount();
// // // 	int polyCount = currMesh->GetPolygonCount();
// // // 	for (int i = 0; i < polyCount; i++)
// // // 	{
// // // 		int polyItemSize = currMesh->GetPolygonSize(i);
// // // 		for (int j = 0; j < polyItemSize; j++)
// // // 		{
// // // 			int cpIndex = currMesh->GetPolygonVertex(i, j);
// // // 			elements.push_back(cpIndex);
// // // 		}
// // // 	}
// // 	//FbxGeometryElementNormal* vertexNormal = currMesh->GetElementNormal(0);
// // 
// // 	//int test = 0;
// // }
// 
// // extern MeshFliter GetMeshFilter(std::vector<Vector3> vertices,
// // 	std::vector<Vector3> normals,
// // 	std::vector<GLuint> indexs);
// // 
// // void ConvertFBXMeshToMeshFilter(FbxMesh* fbxMesh, MeshFliter & meshfilter, Vector3 pos, Vector3 euler, Vector3 scale)
// // {
// // 	std::vector<Vector3> vertices;
// // 	std::vector<GLuint> indices;
// // 	std::vector<Vector3> normals;
// // 
// // 	ConvertFBXMesh(fbxMesh, vertices, normals, indices);
// // 
// // 	meshfilter = GetMeshFilter(vertices, normals, indices);
// // }
// // 
// // /**
// //  * Print a node, its attributes, and all its children recursively.
// //  */
// // void TravelNode(FbxNode* pNode, std::vector<MeshFliter> & ret) {
// // 	//PrintTabs();
// // 	const char* nodeName = pNode->GetName();
// // 	FbxDouble3 translation = pNode->LclTranslation.Get();
// // 	FbxDouble3 rotation = pNode->LclRotation.Get();
// // 	FbxDouble3 scaling = pNode->LclScaling.Get();
// // 
// // 	// Print the contents of the node.
// // // 	char buffer[512] = { 0 };
// // // 	sprintf_s(buffer, "<node name='%s' translation='(%f, %f, %f)' rotation='(%f, %f, %f)' scaling='(%f, %f, %f)'>\n",
// // // 		nodeName,
// // // 		translation[0], translation[1], translation[2],
// // // 		rotation[0], rotation[1], rotation[2],
// // // 		scaling[0], scaling[1], scaling[2]
// // // 	);
// // 	//GUtil::Print(buffer);
// // 	//numTabs++;
// // 
// // 	// Print the node's attributes.
// // 	int attributeCount = pNode->GetNodeAttributeCount();
// // 	//for (int i = 0; i < attributeCount; i++)
// // 	//	PrintAttribute(pNode->GetNodeAttributeByIndex(i));
// // 	bool isMesh = false;
// // 	for (int i = 0; i < attributeCount; ++i)
// // 	{
// // 		if (pNode->GetNodeAttributeByIndex(i)->GetAttributeType() == FbxNodeAttribute::eMesh)
// // 		{
// // 			isMesh = true;
// // 		}
// // 	}
// // 	if (isMesh)
// // 	{
// // 		FbxMesh* currMesh = pNode->GetMesh();
// // 		MeshFliter meshFilter;
// // 		Vector3 pos = Vector3(translation[0], translation[1], translation[2]);
// // 		Vector3 euler = Vector3(rotation[0], rotation[1], rotation[2]);
// // 		Vector3 scale = Vector3(scaling[0], scaling[1], scaling[2]);
// // 		ConvertFBXMeshToMeshFilter(currMesh, meshFilter, pos, euler, scale);
// // 		ret.push_back(meshFilter);
// // 	}
// // 
// // 	// Recursively print the children.
// // 	int childCount = pNode->GetChildCount();
// // 	for (int j = 0; j < childCount; j++)
// // 		TravelNode(pNode->GetChild(j), ret);
// // 
// // 	//numTabs--;
// // 	//PrintTabs();
// // 	//GUtil::Print("</node>\n");
// // }
// // 
// // bool FBXFileHelper::loadFbxMeshes(std::string path, std::vector<MeshFliter> & ret)
// // {
// // 	// Change the following filename to a suitable filename value.
// // 	//const char* lFilename = "file.fbx";
// // 
// // 	// Initialize the SDK manager. This object handles all our memory management.
// // 	FbxManager* lSdkManager = FbxManager::Create();
// // 
// // 	// Create the IO settings object.
// // 	FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
// // 	lSdkManager->SetIOSettings(ios);
// // 
// // 	// Create an importer using the SDK manager.
// // 	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");
// // 
// // 	char buffer[256] = { 0 };
// // 
// // 	// Use the first argument as the filename for the importer.
// // 	if (!lImporter->Initialize(path.c_str(), -1, lSdkManager->GetIOSettings())) {
// // 		GUtil::Print("Call to FbxImporter::Initialize() failed.\n");
// // 		sprintf_s(buffer, "Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
// // 		GUtil::Print(buffer);
// // 		return false;
// // 	}
// // 
// // 	// Create a new scene so that it can be populated by the imported file.
// // 	FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");
// // 
// // 	// Import the contents of the file into the scene.
// // 	lImporter->Import(lScene);
// // 
// // 	// The file is imported; so get rid of the importer.
// // 	lImporter->Destroy();
// // 	FbxAxisSystem::DirectX.ConvertScene(lScene);
// // 
// // 	// Print the nodes of the scene and their attributes recursively.
// // 	// Note that we are not printing the root node because it should
// // 	// not contain any attributes.
// // 	FbxNode* lRootNode = lScene->GetRootNode();
// // 	if (lRootNode) {
// // 		for (int i = 0; i < lRootNode->GetChildCount(); i++)
// // 			TravelNode(lRootNode->GetChild(i), ret);
// // 	}
// // 	// Destroy the SDK manager and all the other objects it was handling.
// // 	lSdkManager->Destroy();
// // 	return true;
// // }
