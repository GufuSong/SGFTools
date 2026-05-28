// Copyright Epic Games, Inc. All Rights Reserved.

#include "Material/SGFToolsMaterialInstanceAssetTypeActions.h"

#include "AssetTypeCategories.h"
#include "Material/SGFToolsMaterialInstance.h"
#include "MaterialEditorModule.h"

#define LOCTEXT_NAMESPACE "SGFToolsMaterialInstanceAssetTypeActions"

FText FSGFToolsMaterialInstanceAssetTypeActions::GetName() const
{
	return LOCTEXT("AssetName", "SGF Material Instance");
}

FColor FSGFToolsMaterialInstanceAssetTypeActions::GetTypeColor() const
{
	return FColor(0, 128, 0);
}

UClass* FSGFToolsMaterialInstanceAssetTypeActions::GetSupportedClass() const
{
	return USGFToolsMaterialInstance::StaticClass();
}

uint32 FSGFToolsMaterialInstanceAssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Materials;
}

void FSGFToolsMaterialInstanceAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	IMaterialEditorModule& MaterialEditorModule = FModuleManager::LoadModuleChecked<IMaterialEditorModule>("MaterialEditor");
	const EToolkitMode::Type ToolkitMode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (UObject* Object : InObjects)
	{
		if (USGFToolsMaterialInstance* MaterialInstance = Cast<USGFToolsMaterialInstance>(Object))
		{
			MaterialEditorModule.CreateMaterialInstanceEditor(ToolkitMode, EditWithinLevelEditor, MaterialInstance);
		}
	}
}

#undef LOCTEXT_NAMESPACE
