// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core\Public\Internationalization\Internationalization.h"
#include "Modules/ModuleManager.h"
#include "ContentBrowserModule.h"
#include "Templates/SharedPointer.h"

class FTest_PluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};
