#include "..\Header Files\EditorFPS.h"
#include "AppManager.h"
#include "GUI.h"
#include "imgui.h"
#include "Timer.h"
#include "RendererManager.h"

Protostar::PEditorFPS::PEditorFPS()
{
}

Protostar::PEditorFPS::~PEditorFPS()
{
}

void Protostar::PEditorFPS::OnRender()
{
	if (!PGUI::GetGUIInfo().bOpenEditorFPS)
	{
		return;
	}

	PAppManager* appManager = PAppManager::GetAppHandle();
	SWindowDimParams wndDim = appManager->GetInitWindowDimParams();
	float x = (float)wndDim.Width - 200;
	float y = (float)wndDim.Height * .1f;
	ImGui::SetNextWindowSize(ImVec2(160.0f, 80.0f), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Editor FPS", &PGUI::GetGUIInfo().bOpenEditorFPS))
	{
		ImGui::End();
		return;
	}

	ImGui::Checkbox("VSync", &CRendererManager::GetVSync());

	ImGui::Text("%.3f ms/frame", PTimer::GetDeltaSeconds());
	ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);


	ImGui::End();
}
