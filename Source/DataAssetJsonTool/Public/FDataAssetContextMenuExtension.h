// ========================================
// 编辑器扩展部分 - 添加右键菜单
// DataAssetContextMenu.h
#pragma once

#include "CoreMinimal.h"

class FDataAssetContextMenuExtension
{
public:
	static void RegisterMenus();
	static void UnregisterMenus();

private:
	static void OnExportToJson(const FAssetData& AssetData);
	static void OnImportFromJson(const FAssetData& AssetData);
	static TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& SelectedAssets);
};