// Copyright Epic Games, Inc. All Rights Reserved.

#include "SGFToolsEditor.h"

#include "Material/SGFToolsMaterialInstanceHierarchyDetails.h"

void FSGFToolsEditorModule::StartupModule()
{
	SGFTools::MaterialInstanceHierarchyDetails::Startup();
}

void FSGFToolsEditorModule::ShutdownModule()
{
	SGFTools::MaterialInstanceHierarchyDetails::Shutdown();
}

IMPLEMENT_MODULE(FSGFToolsEditorModule, SGFToolsEditor)
