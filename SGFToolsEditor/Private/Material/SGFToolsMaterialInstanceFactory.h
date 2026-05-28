// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Factories/Factory.h"

#include "SGFToolsMaterialInstanceFactory.generated.h"

class UMaterialInterface;

/**
 * SGFTools 材质实例资产的编辑器创建工厂。
 *
 * Factory 属于 Editor-only：它只负责在内容浏览器里创建资产，不应该放进 Runtime。
 */
UCLASS()
class USGFToolsMaterialInstanceFactory : public UFactory
{
	GENERATED_BODY()

public:
	USGFToolsMaterialInstanceFactory(const FObjectInitializer& ObjectInitializer);

	UPROPERTY()
	TObjectPtr<UMaterialInterface> InitialParent;

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual FText GetDisplayName() const override;
	virtual uint32 GetMenuCategories() const override;
	virtual FString GetDefaultNewAssetName() const override;
};
