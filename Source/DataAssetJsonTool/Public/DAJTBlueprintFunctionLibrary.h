// DAJTBlueprintFunctionLibrary.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DAJTBlueprintFunctionLibrary.generated.h"

/**
 * 用于DataAsset的JSON导入导出工具类
 */
UCLASS()
class DATAASSETJSONTOOL_API UDAJTBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * 将DataAsset导出为JSON文件
	 * @param DataAsset 要导出的DataAsset对象
	 * @param FilePath 导出的文件路径（绝对路径）
	 * @return 是否成功导出
	 */
	UFUNCTION(BlueprintCallable, Category = "DataAsset|JSON")
	static bool ExportDataAssetToJson(UDataAsset* DataAsset, const FString& FilePath);

	/**
	 * 从JSON文件导入数据到DataAsset
	 * @param DataAsset 要导入数据的DataAsset对象
	 * @param FilePath 导入的文件路径（绝对路径）
	 * @return 是否成功导入
	 */
	UFUNCTION(BlueprintCallable, Category = "DataAsset|JSON")
	static bool ImportJsonToDataAsset(UDataAsset* DataAsset, const FString& FilePath);

	/**
	 * 将DataAsset转换为JSON字符串
	 * @param DataAsset 要转换的DataAsset对象
	 * @param OutJsonString 输出的JSON字符串
	 * @return 是否成功转换
	 */
	UFUNCTION(BlueprintCallable, Category = "DataAsset|JSON")
	static bool DataAssetToJsonString(UDataAsset* DataAsset, FString& OutJsonString);

	/**
	 * 从JSON字符串导入数据到DataAsset
	 * @param DataAsset 要导入数据的DataAsset对象
	 * @param JsonString JSON字符串
	 * @return 是否成功导入
	 */
	UFUNCTION(BlueprintCallable, Category = "DataAsset|JSON")
	static bool JsonStringToDataAsset(UDataAsset* DataAsset, const FString& JsonString);
};
