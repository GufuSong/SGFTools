// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Containers/Array.h"
#include "Modules/ModuleManager.h"
#include "Templates/SharedPointer.h"

class IAssetTools;
class IAssetTypeActions;

class FSGFToolsEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterAssetTypeActions();
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> AssetTypeAction);
	void RegisterMenus();

	TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;
};
