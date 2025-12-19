# DataAssetJsonTool

## Overview

An Unreal Engine editor plugin for bidirectional conversion between DataAsset assets and JSON files, enabling flexible data import/export workflows.

## Author

**ysh11o**  
Contact: ysh11o0@163.com or 1014717994@qq.com

## Description

This plugin provides seamless conversion capabilities between Unreal Engine's native DataAsset system and standardized JSON file format. Designed for developers who need to exchange data between UE projects and external tools, or version control structured game data in a human-readable format.

## Features

- **Bidirectional Conversion**- Convert DataAssets to JSON files and import JSON files back into DataAssets
  
- **Editor Integration**- Right-click context menu integration in Content Browser
  
- **Asset Type Support**- Works with any UDataAsset-derived classes and their property hierarchies
  
- **Simple Workflow**- Straightforward single-file conversion operations
  

## Installation

1. Copy the`DataAssetJsonTool`folder to your project's`Plugins`directory
  
2. Enable the plugin via**Edit → Plugins → Project → DataAssetJsonTool**
  
3. Restart the Unreal Editor when prompted
  

## Usage

### Export DataAsset to JSON

1. In the Content Browser, right-click on a DataAsset file
  
2. Select  "Export to json" from the context menu
  
3. Choose the destination folder and filename in the dialog
  
4. The JSON file will be created with all serializable properties
  
  ![](https://oss-liuchengtu.hudunsoft.com/userimg/f3/f3c55143f5eb6272e949a008d70733f4.png)


### Import New JSON to Cover Old DataAsset

1. In the Content Browser, right-click on a DataAsset file
  
2. Select "Import from json" from the context menu

3. The DataAsset will be covered with data from the JSON file
  
![](https://oss-liuchengtu.hudunsoft.com/userimg/17/17751cfa462dd97bbc23588fd886b617.png)


## Technical Details

- Built using Unreal Engine's JsonUtilities module for reliable serialization
  
- Supports all common property types (strings, numbers, arrays, structs, enums)
  
- Preserves asset references as string paths where applicable
  


## Notes

- Conversion is limited to serializable properties (marked with`UPROPERTY`)
  
- Complex asset references may require manual adjustment after import
  
- Each operation processes one file at a time
  
- UE5.5 Windows

## Support

For issues or feature requests, please contact the author via email or submit through the project repository.
