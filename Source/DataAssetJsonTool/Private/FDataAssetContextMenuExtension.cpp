// DataAssetContextMenu.cpp
#include "FDataAssetContextMenuExtension.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "DAJTBlueprintFunctionLibrary.h"
#include "DesktopPlatformModule.h"
#include "Engine/DataAsset.h"

void FDataAssetContextMenuExtension::RegisterMenus()
{
    FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
    TArray<FContentBrowserMenuExtender_SelectedAssets>& MenuExtenders = ContentBrowserModule.GetAllAssetViewContextMenuExtenders();
    
    MenuExtenders.Add(FContentBrowserMenuExtender_SelectedAssets::CreateStatic(&OnExtendContentBrowserAssetSelectionMenu));
}

void FDataAssetContextMenuExtension::UnregisterMenus()
{
    if (FModuleManager::Get().IsModuleLoaded("ContentBrowser"))
    {
        FContentBrowserModule& ContentBrowserModule = FModuleManager::GetModuleChecked<FContentBrowserModule>("ContentBrowser");
        TArray<FContentBrowserMenuExtender_SelectedAssets>& MenuExtenders = ContentBrowserModule.GetAllAssetViewContextMenuExtenders();
        MenuExtenders.RemoveAll([](const FContentBrowserMenuExtender_SelectedAssets& Delegate) {
            return true;
        });
    }
}

TSharedRef<FExtender> FDataAssetContextMenuExtension::OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& SelectedAssets)
{
    TSharedRef<FExtender> Extender = MakeShareable(new FExtender());
    
    bool bHasDataAsset = false;
    for (const FAssetData& Asset : SelectedAssets)
    {
        if (Asset.GetClass()->IsChildOf(UDataAsset::StaticClass()))
        {
            bHasDataAsset = true;
            break;
        }
    }

    if (bHasDataAsset && SelectedAssets.Num() == 1)
    {
        Extender->AddMenuExtension(
            "CommonAssetActions",
            EExtensionHook::After,
            nullptr,
            FMenuExtensionDelegate::CreateLambda([SelectedAssets](FMenuBuilder& MenuBuilder)
            {
                const FAssetData AssetData = SelectedAssets[0];
                
                MenuBuilder.AddMenuEntry(
                    FText::FromString(TEXT("导出为Json文件(Export as json)")),
                    FText::FromString("Export this DataAsset to a JSON file"),
                    FSlateIcon(),
                    FUIAction(FExecuteAction::CreateLambda([AssetData]()
                    {
                        FDataAssetContextMenuExtension::OnExportToJson(AssetData);
                    }))
                );

                MenuBuilder.AddMenuEntry(
                    FText::FromString(TEXT("从Json文件导入信息(Import form json)")),
                    FText::FromString("Import data from a JSON file to this DataAsset"),
                    FSlateIcon(),
                    FUIAction(FExecuteAction::CreateLambda([AssetData]()
                    {
                        FDataAssetContextMenuExtension::OnImportFromJson(AssetData);
                    }))
                );
            })
        );
    }

    return Extender;
}


void FDataAssetContextMenuExtension::OnExportToJson(const FAssetData& AssetData)
{
    UDataAsset* DataAsset = Cast<UDataAsset>(AssetData.GetAsset());
    if (!DataAsset)
    {
        return;
    }
    
    if (IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get())
    {
        TArray<FString> SaveFilenames;
        bool bSaved = DesktopPlatform->SaveFileDialog(
            nullptr,
            TEXT("Export DataAsset to JSON"),
            FPaths::ProjectDir(),
            AssetData.AssetName.ToString() + TEXT(".json"),
            TEXT("JSON Files (*.json)|*.json"),
            EFileDialogFlags::None,
            SaveFilenames
        );

        if (bSaved && SaveFilenames.Num() > 0)
        {
            UDAJTBlueprintFunctionLibrary::ExportDataAssetToJson(DataAsset, SaveFilenames[0]);
        }
    }
}

void FDataAssetContextMenuExtension::OnImportFromJson(const FAssetData& AssetData)
{
    UDataAsset* DataAsset = Cast<UDataAsset>(AssetData.GetAsset());
    if (!DataAsset)
    {
        return;
    }

    if (IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get())
    {
        TArray<FString> OpenFilenames;
        bool bOpened = DesktopPlatform->OpenFileDialog(
            nullptr,
            TEXT("Import JSON to DataAsset"),
            FPaths::ProjectDir(),
            TEXT(""),
            TEXT("JSON Files (*.json)|*.json"),
            EFileDialogFlags::None,
            OpenFilenames
        );

        if (bOpened && OpenFilenames.Num() > 0)
        {
            UDAJTBlueprintFunctionLibrary::ImportJsonToDataAsset(DataAsset, OpenFilenames[0]);
        }
    }
}