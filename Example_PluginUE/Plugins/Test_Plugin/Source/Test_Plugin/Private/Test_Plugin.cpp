// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Test_Plugin.h"
#include "Editor/LevelEditor/Public/LevelEditor.h"
#include "BlueprintEditorModule.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "../Public/MyAwesomeTestActor.h"

#define LOCTEXT_NAMESPACE "FTest_PluginModule"

FDelegateHandle customExtendHandler;

static void OnCreateButton(FMenuBuilder& builder, AMyAwesomeTestActor* selectedActor) {
	FUIAction callback_function(FExecuteAction::CreateLambda([selectedActor]() { selectedActor->GetAllStaticMeshesInScene(); }));
	builder.AddMenuEntry(
		LOCTEXT("MyAwesomeActorButton", "Display Actors"),
		LOCTEXT("MyAwesomeActor_Tooltip", "A simple Button to display actors"),
		FSlateIcon(),
		callback_function,
		NAME_None,
		EUserInterfaceActionType::Button);
}

static TSharedRef<FExtender> OnViewportContextMenu(const TSharedRef<FUICommandList> CommandList, TArray<AActor*> SelectedActors) {
	
	TSharedRef<FExtender> NewMenuExtender(new FExtender());
	for (auto* actor : SelectedActors) {
		if (actor->IsA(AMyAwesomeTestActor::StaticClass())) {
			//Inject button code to view port menu 
			NewMenuExtender->AddMenuExtension(
				"EditAsset",
				EExtensionHook::Before,
				nullptr,
				FMenuExtensionDelegate::CreateStatic(&OnCreateButton,(AMyAwesomeTestActor*)actor));
			return NewMenuExtender;
		}
	}
	return NewMenuExtender;
}

//inside editor -> preferences -> Display UI extension points TICK
void FTest_PluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if (GIsEditor)
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		auto& MenuExtenders = LevelEditorModule.GetAllLevelViewportContextMenuExtenders(); 
		MenuExtenders.Add(FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateStatic(&OnViewportContextMenu));
		customExtendHandler = MenuExtenders.Last().GetHandle();
	}
}
 
void FTest_PluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (FModuleManager::Get().IsModuleLoaded("LevelEditor"))
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditorModule.GetAllLevelViewportContextMenuExtenders().RemoveAll([&](const FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors& Delegate) {
			return Delegate.GetHandle() == customExtendHandler;
		});
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTest_PluginModule, Test_Plugin)



