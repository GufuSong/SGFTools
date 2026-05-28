// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Materials/MaterialInstanceConstant.h"

#include "SGFToolsMaterialInstance.generated.h"

/**
 * SGFTools 自定义材质实例资产。
 *
 * 这个类放在 Runtime 模块，是因为资产本身需要被编辑器和运行时共同识别。
 * 当前阶段只继承 UMaterialInstanceConstant，不添加任何新属性或新功能。
 */
UCLASS(BlueprintType)
class SGFTOOLSRUNTIME_API USGFToolsMaterialInstance : public UMaterialInstanceConstant
{
	GENERATED_BODY()
};
