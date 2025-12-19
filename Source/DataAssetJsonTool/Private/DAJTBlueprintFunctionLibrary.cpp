// DAJTBlueprintFunctionLibrary.cpp
#include "DAJTBlueprintFunctionLibrary.h"
#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

bool UDAJTBlueprintFunctionLibrary::ExportDataAssetToJson(UDataAsset* DataAsset, const FString& FilePath)
{
    if (!DataAsset)
    {
        UE_LOG(LogTemp, Error, TEXT("DataAsset is null"));
        return false;
    }

    FString JsonString;
    if (!DataAssetToJsonString(DataAsset, JsonString))
    {
        return false;
    }
    
    if (!FFileHelper::SaveStringToFile(JsonString, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to save JSON to file: %s"), *FilePath);
        return false;
    }

    UE_LOG(LogTemp, Log, TEXT("Successfully exported DataAsset to: %s"), *FilePath);
    return true;
}

bool UDAJTBlueprintFunctionLibrary::ImportJsonToDataAsset(UDataAsset* DataAsset, const FString& FilePath)
{
    if (!DataAsset)
    {
        UE_LOG(LogTemp, Error, TEXT("DataAsset is null"));
        return false;
    }
    
    FString JsonString;
    if (!FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load JSON from file: %s"), *FilePath);
        return false;
    }

    return JsonStringToDataAsset(DataAsset, JsonString);
}

bool UDAJTBlueprintFunctionLibrary::DataAssetToJsonString(UDataAsset* DataAsset, FString& OutJsonString)
{
    if (!DataAsset)
    {
        UE_LOG(LogTemp, Error, TEXT("DataAsset is null"));
        return false;
    }
    
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    
    if (!FJsonObjectConverter::UStructToJsonObject(
        DataAsset->GetClass(),
        DataAsset,
        JsonObject.ToSharedRef(),
        0,
        0))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to convert DataAsset to JSON"));
        return false;
    }
    
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutJsonString);
    if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to serialize JSON"));
        return false;
    }

    return true;
}

bool UDAJTBlueprintFunctionLibrary::JsonStringToDataAsset(UDataAsset* DataAsset, const FString& JsonString)
{
    if (!DataAsset)
    {
        UE_LOG(LogTemp, Error, TEXT("DataAsset is null"));
        return false;
    }
    
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
    
    if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON string"));
        return false;
    }
    
    DataAsset->Modify();
    
    if (!FJsonObjectConverter::JsonObjectToUStruct(
        JsonObject.ToSharedRef(),
        DataAsset->GetClass(),
        DataAsset,
        0,
        0))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to convert JSON to DataAsset"));
        return false;
    }
    
    return DataAsset->MarkPackageDirty();
    
    UE_LOG(LogTemp, Log, TEXT("Successfully imported JSON to DataAsset"));
    return true;
}