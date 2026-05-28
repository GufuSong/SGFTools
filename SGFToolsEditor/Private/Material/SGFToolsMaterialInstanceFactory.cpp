// Copyright Epic Games, Inc. All Rights Reserved.

#include "Material/SGFToolsMaterialInstanceFactory.h"

#include "AssetTypeCategories.h"
#include "Material/SGFToolsMaterialInstance.h"
#include "Materials/MaterialInterface.h"

#define LOCTEXT_NAMESPACE "SGFToolsMaterialInstanceFactory"

USGFToolsMaterialInstanceFactory::USGFToolsMaterialInstanceFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = USGFToolsMaterialInstance::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* USGFToolsMaterialInstanceFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	USGFToolsMaterialInstance* MaterialInstance = NewObject<USGFToolsMaterialInstance>(InParent, InClass, InName, Flags);

	if (MaterialInstance)
	{
		if (InitialParent)
		{
			MaterialInstance->SetParentEditorOnly(InitialParent);
		}
	}

	return MaterialInstance;
}

FText USGFToolsMaterialInstanceFactory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "SGF Material Instance");
}

uint32 USGFToolsMaterialInstanceFactory::GetMenuCategories() const
{
	return EAssetTypeCategories::Materials;
}

FString USGFToolsMaterialInstanceFactory::GetDefaultNewAssetName() const
{
	return TEXT("MI_SGF_MaterialInstance");
}

#undef LOCTEXT_NAMESPACE
