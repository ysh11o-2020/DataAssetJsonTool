// Copyright Epic Games, Inc. All Rights Reserved.

#include "DataAssetJsonTool.h"
#include "FDataAssetContextMenuExtension.h"

#define LOCTEXT_NAMESPACE "FDataAssetJsonToolModule"


void FDataAssetJsonToolModule::StartupModule()
{
	FDataAssetContextMenuExtension::RegisterMenus();
}

void FDataAssetJsonToolModule::ShutdownModule()
{
	FDataAssetContextMenuExtension::UnregisterMenus();
}
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDataAssetJsonToolModule, DataAssetJsonTool)